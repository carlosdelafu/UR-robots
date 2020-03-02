#include "U3REALTIME.h"



U3REALTIME::U3REALTIME()
{
}


U3REALTIME::~U3REALTIME()
{
	m_socketmm.client_close();

	m_socketmm.server_close();
}

int U3REALTIME::init_socket_connection(const string & _ur_ip, const int _ur_port)
{
	int URRES = URSUCCED;

	if (!m_socketmm.client_init(_ur_ip, _ur_port))
	{
		cerr << "[client] client_init done" << endl;
	}
	else
	{
		cerr << "[client] client_init failed" << endl;
		URRES = URFAILED;
	}

	return URRES;
}


// convert bytes to int, which is 32 bits
unsigned int U3REALTIME::bytes_to_uint(unsigned char* b, unsigned int length)
{
	unsigned int val = 0;

	for (size_t i = 0; i < length; ++i)
	{
		val = val << 8;

		val = val | b[i];
	}

	return val;
}

uint64_t U3REALTIME::bytes_to_uint_64(unsigned char* b, unsigned int length)
{
	uint64_t val = 0;

	for (size_t i = 0; i < length; ++i)
	{
		val = val << 8;

		val = val | b[i];
	}

	return val;
}

// convert bytes to char, which is 32 bits
int U3REALTIME::bytes_to_int(unsigned char* b, unsigned int length)
{
	unsigned int val = 0;

	for (size_t i = 0; i < length; ++i)
	{
		val = val << 8;

		val = val | b[i];
	}

	return *(int*)&val;
}

// default convert bytes to double, which is 64 bits!!
double U3REALTIME::bytes_to_double(unsigned char* b, unsigned int length)
{
	__int64 val = 0;

	for (size_t i = 0; i < length; ++i)
	{
		val = val << 8;
		// cout << val << endl;
		val = val | b[i];
		// cout << val << endl;
	}

	return *(double*)&val;
}

// get the specific data in _data, and store the result in _result
void U3REALTIME::get_specific_data(unsigned char * _data, size_t _count, std::vector<double> & _result)
{
	_result.resize(_count,0);

	double tmp_data = 0.0;

	for (size_t i = 0; i < _count; ++i)
	{
		tmp_data = bytes_to_double(_data);
		_result[i] = tmp_data;
		_data += 8;
	}
}

// only print the vector of double
void U3REALTIME::print(std::vector<double> & _vec)
{
	for (auto i : _vec)
	{
		cout << i << " ";
	}
	cout << endl;
}

// delete the pointer safely
void U3REALTIME::saft_delete_pointer(unsigned char ** p)
{
	if (*p)
	{
		delete[] * p;
	}
	*p = nullptr;
}
