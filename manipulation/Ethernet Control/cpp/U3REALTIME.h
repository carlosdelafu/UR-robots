#pragma once
#include <string>
#include <vector>
#include <thread>
#include <fstream>

#include "SocketComm.h"
//using namespace std;

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
	virtual void begin_to_receive_data_from_UR(unsigned int milliseconds = 30) = 0;

	virtual void send_data_move_to(double x, double y, double z, double rx, double ry, double rz, double acceleration = 0.5, double velocity = 0.1) = 0;

protected:
	// convert bytes to int, which is 32 bits
	int bytes_to_int(unsigned char* b, unsigned int length);

	unsigned int bytes_to_uint(unsigned char* b, unsigned int length);

	uint64_t bytes_to_uint_64(unsigned char* b, unsigned int length);

	// default convert bytes to double, which is 64 bits!!
	double bytes_to_double(unsigned char* b, unsigned int length = 8);

	// get the specific data in _data, and store the result in _result
	void get_specific_data(unsigned char * _data, size_t _count, std::vector<double> & _result);

	// only print the std::vector of double
	void print(std::vector<double> & _vec);

	// delete the pointer safely
	void saft_delete_pointer(unsigned char ** p);

protected:
	// for socket connection
	string m_ip;
	
	int m_port;

	SocketComm m_socketmm;

};

