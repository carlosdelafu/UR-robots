#pragma once
#include "U3REALTIME.h"
#include "BitOperation.h"

class URobot :
	public U3REALTIME
{
public:
	URobot();

	~URobot();

	virtual void begin_to_receive_data_from_UR(unsigned int milliseconds = 30);

	virtual void send_data_move_to(double x, double y, double z, double rx, double ry, double rz, double acceleration = 0.5, double velocity = 0.1);

	void disconnection();

	void send_data_move_x(double x_add, double a = 0.5, double v = 0.1, bool wait = true);

	void send_data_move_y(double y_add, double a = 0.5, double v = 0.1, bool wait = true);

	void send_data_move_z(double z_add, double a = 0.5, double v = 0.1, bool wait = true);

	void get_base_tools_position(double & x, double &y, double &z, double &rx, double &ry, double &rz);

	void get_base_tools_position(std::vector<double> & p);

	void wait_to_arrive_specific_position(double x, double y, double z, double rx, double ry, double rz, double threshold = 10e-4);

	bool is_arrived(double x, double y, double z, double rx, double ry, double rz, double threshold = 10e-4);

private:

	void received_data_as_int(int data_size, int & res);

	void received_data_as_uchar(int data_size, unsigned char & res);

	void receive_data(unsigned int millisecond);

	void process_data(unsigned char *& data, int data_size);

	void process_data(std::vector<int> & bits);

	void get_distance(double x0, double y0, double z0, double rx0, double ry0, double rz0,
		double x1, double y1, double z1, double rx1, double ry1, double rz1, double & distance);

private:

	void process_type_0(unsigned char * data);

	//Joint data (Sub Package of Robot State Message)
	void process_type_1(std::vector<int> & bits, int begin, int count);

	//Robot mode data (Sub Package of Robot State Message)
	void process_type_0(std::vector<int> & bits, int begin, int count);

	void process_type_4(std::vector<int> & bits, int begin, int count);

	//Cartesian info (Sub Package of Robot State Message)
	void process_type_4(unsigned char * data);


private:

	std::mutex m_ur_ready;

	std::mutex m_rw_position;

	std::thread m_receive_data_thread;

	double m_cartesian_data[6];

	bool m_stop_receive_data;
	
	bool m_received_data_once;

	unsigned char m_receive_buf[1500];

	BitOperation m_bit_operation;

	std::vector<int> m_bits;
};
