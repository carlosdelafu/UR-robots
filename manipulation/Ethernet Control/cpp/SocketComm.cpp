#include "SocketComm.h"

SocketComm::SocketComm()
{
}

SocketComm::~SocketComm()
{
}

int SocketComm::server_init(const string & ip, const int port)
{
	m_server_ip = ip;
	m_server_port = port;

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (HIBYTE(wsaData.wVersion) != 2 || LOBYTE(wsaData.wVersion) != 2)
	{
		cerr << "请求版本失败！" << endl;
		return -1;
	}
	//创建socket
	m_server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//创建协议地址族
	server_addr = { 0 };
	server_addr.sin_family = AF_INET;
	//server_addr.sin_addr.S_un.S_addr = inet_addr(m_server_ip.c_str());
	// Ready to listen any connection
	//InetPton(AF_INET, INADDR_ANY, &server_addr.sin_addr.S_un.S_addr);
	InetPton(AF_INET, m_server_ip.c_str(), &server_addr.sin_addr.S_un.S_addr);
	server_addr.sin_port = htons(m_server_port);

	//绑定
	int r = bind(m_server_socket, (sockaddr*)&server_addr, sizeof server_addr);

	//监听
	r = listen(m_server_socket, 10);

	//接受客户端连接
	server_client_addr = { 0 };
	int size = sizeof server_client_addr;
	m_server_client_socket = accept(m_server_socket, (sockaddr*)&server_client_addr, &size);
	
	if (m_server_client_socket == INVALID_SOCKET)
	{
#ifdef _DEBUG
		cerr << "invalid socket !" << endl;;
#endif // _DEBUG
		return -1;
	}
#ifdef _DEBUG
	cout << "[server] listening to " << m_server_ip << ":" << m_server_port << endl;
	cout << "[server] waiting" << endl;
#endif // _DEBUG

	return 0;
}

int SocketComm::server_receive(unsigned char * rece_data, size_t rece_size)
{
	m_server_buf = new char[rece_size + 1]();

	int rs = recv(m_client_socket, m_server_buf, rece_size, NULL);

	if (rs > 0)
	{
		printf("received %d bytes data successfully.\n>>%s\n", rs, m_server_buf);
	}

	memcpy(rece_data, m_server_buf, rece_size);

	delete[] m_server_buf;
	m_server_buf = nullptr;

	return rs;
}

int SocketComm::server_close()
{
	closesocket(m_server_client_socket);

	WSACleanup();

	return 0;
}

int SocketComm::client_init(const string & ip, const int port)
{
	m_client_ip = ip;
	m_client_port = port;

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (HIBYTE(wsaData.wVersion) != 2 || LOBYTE(wsaData.wVersion) != 2)
	{
		cerr << "请求版本失败！" << endl;
		return -1;
	}
	//创建socket
	m_client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_client_socket == INVALID_SOCKET)
	{
#ifdef _DEBUG
		cerr << "invalid socket !" << endl;;
#endif // _DEBUG
		return -1;
	}

	//创建协议地址族
	SOCKADDR_IN m_client_addr = { 0 };
	m_client_addr.sin_family = AF_INET;
	//m_client_addr.sin_addr.S_un.S_addr = inet_addr(m_client_ip.c_str());
	InetPton(AF_INET, m_client_ip.c_str(), &m_client_addr.sin_addr.S_un.S_addr);

	m_client_addr.sin_port = htons(m_client_port);

	int r = connect(m_client_socket, (sockaddr*)&m_client_addr, sizeof m_client_addr);

	if (r == SOCKET_ERROR)
	{
#ifdef _DEBUG
		cerr << "connect error !" << endl;
		closesocket(m_client_socket);
#endif // _DEBUG
		return -1;
	}

	return 0;
}

int SocketComm::client_send(string & str)
{
	m_client_buf = new char[str.size() + 1]();

	memcpy(m_client_buf, str.data(), str.size());

	int rs = send(m_client_socket, m_client_buf, strlen(m_client_buf), NULL);

	if (rs > 0)
	{
		printf("sent %d bytes data successfully.>>%s\n", rs, m_client_buf);
	}

	delete[] m_client_buf;
	m_client_buf = nullptr;

	return rs;
}

int SocketComm::client_receive(unsigned char * rece_data,size_t rece_size)
{
	m_client_buf = new char[rece_size + 1]();

	int rs = recv(m_client_socket, m_client_buf, rece_size, NULL);

	if (rs > 0)
	{
		printf("received %d bytes data successfully.\n>>%s\n", rs, m_client_buf);
	}

	memcpy(rece_data, m_client_buf, rece_size);

	delete[] m_client_buf;
	m_client_buf = nullptr;

	return rs;
}

int SocketComm::client_close()
{
	closesocket(m_client_socket);

	WSACleanup();

	return 0;
}

