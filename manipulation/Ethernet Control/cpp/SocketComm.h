#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
using namespace std;

#pragma  comment(lib,"ws2_32.lib")

class SocketComm
{
public:
	SocketComm();

	~SocketComm();

public:
	/*server*/
	int server_init(const string & ip, const int port);

	int server_receive(unsigned char * rece_data, size_t rece_size);

	int server_close();

	/*client*/
	int client_init(const string & ip, const int port);

	int client_send(string & str);

	int client_receive(unsigned char * rece_data, size_t rece_size);

	int client_close();

private:
	/*server paraments*/
	SOCKET m_server_socket;

	SOCKET m_server_client_socket;

	SOCKADDR_IN 
		server_addr, 
		server_client_addr;

	string m_server_ip;

	int m_server_port;

	char * m_server_buf;

	/*client paraments*/
	SOCKET m_client_socket;

	SOCKADDR_IN m_client_addr;

	string m_client_ip;

	int m_client_port;
	
	char * m_client_buf;
};

