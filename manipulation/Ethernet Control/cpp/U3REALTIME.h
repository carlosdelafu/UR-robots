#pragma once
#include <string>
#include <vector>
#include <thread>
#include <fstream>

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

	//! initialize the socket of connenct
	/*
	\param[in] _ur_ip The UR's ip address
	\param[in] _remote_ip remote host's ip address, you can input "127.0.0.1" if the remote host is this device.
	\param[in] _port the port socket will listen to.
	*/
	int init_socket_connection(const string & _ur_ip, const int _ur_port);

	// cause there are more kind of realtime table, you need to design the read and alaysis data by different way.
	virtual void begin_to_receive_data_from_UR(float millisecond = 1000) = 0;

	virtual void send_data_move_to(float x, float y, float z, float rx, float ry, float rz, float acceleration = 0.5, float velocity = 0.1) = 0;

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

