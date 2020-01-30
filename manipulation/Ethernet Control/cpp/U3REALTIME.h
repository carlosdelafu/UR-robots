#pragma once
#include <string>
#include <vector>

#include "SocketComm.h"
using namespace std;

#define URSUCCED 0
#define URFAILED 1

//! UR Robot RealTime
// To receive and parse data from UR Robot REALTIME
class U3REALTIME
{
public:
	U3REALTIME();

	virtual ~U3REALTIME();

	// initialize the socket of connenct
	int init_socket_connection(const string & _ip, const int _port);

	// cause there are more kind of realtime table, you need to design the read and alaysis data by different way.
	virtual void read_data_from_robot(double millisecond = 1000) = 0;

protected:
	// convert bytes to int, which is 32 bits
	int bytes_to_int(unsigned char* b, unsigned int length);

	// default convert bytes to double, which is 64 bits!!
	double bytes_to_double(unsigned char* b, unsigned int length = 8);

	// get the specific data in _data, and store the result in _result
	void get_specific_data(unsigned char * _data, size_t _count, vector<double> & _result);

	// only print the vector of double
	void print(vector<double> & _vec);

	// delete the pointer safely
	void saft_delete_pointer(unsigned char ** p);

protected:
	// for socket connection
	string m_ip;
	
	int m_port;

	SocketComm m_socketmm;

};

