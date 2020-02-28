#pragma once
#include "U3REALTIME.h"

class REALTIME_PRE :
	public U3REALTIME
{
public:
	REALTIME_PRE();

	~REALTIME_PRE();

	virtual void begin_to_receive_data_from_UR(float millisecond = 1000);

	virtual void send_data_move_to(float x, float y, float z, float rx, float ry, float rz, float acceleration = 0.5, float velocity = 0.1);

	void send_data_move_x(float x, float a = 0.5, float v = 0.1);

	void send_data_move_y(float y, float a = 0.5, float v = 0.1);

	void send_data_move_z(float z, float a = 0.5, float v = 0.1);

	void get_base_tools_position(float & x, float &y, float z, float &rx, float ry, float &rz);

	void wait_to_arrive_specific_position(float x, float y, float z, float rx, float ry, float rz, float threshold = 10e-4);

	bool is_arrived(float x, float y, float z, float rx, float ry, float rz, float threshold = 10e-4);
private:

	void received_data_as_int(int data_size, int & res);

	void receive_data(float millisecond);

	void process_data(unsigned char *& data, int data_size);

	void get_distance(float x0, float y0, float z0, float rx0, float ry0, float rz0,
		float x1, float y1, float z1, float rx1, float ry1, float rz1, float & distance);

private:

	std::thread receive_data_thread;

	float m_cartesian_data[6];

	bool m_stop_receive_data;
	
	bool m_received_data_once;

	unsigned char m_receive_buf[1500];
};
