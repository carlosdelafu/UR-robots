#include "U3REALTIME.h"



U3REALTIME::U3REALTIME()
{
}


U3REALTIME::~U3REALTIME()
{
}

int U3REALTIME::init_socket_connection(const string & _ip, const int _port)
{
	if (!m_socketmm.client_init(_ip, _port))
	{
		cerr << "client_init done" << endl;
		return URSUCCED;
	}
	else
	{
		cerr << "client_init failed" << endl;
		return URFAILED;
	}

}


// convert bytes to int, which is 32 bits
int U3REALTIME::bytes_to_int(unsigned char* b, unsigned int length)
{
	unsigned int val = 0;

	for (size_t i = 0; i < length; ++i)
	{
		val = val << 8;
		val = val | b[i];
	}

	return val;
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
void U3REALTIME::get_specific_data(unsigned char * _data, size_t _count, vector<double> & _result)
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
void U3REALTIME::print(vector<double> & _vec)
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
