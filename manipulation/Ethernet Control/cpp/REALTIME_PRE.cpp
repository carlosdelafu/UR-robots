#include "REALTIME_PRE.h"

REALTIME_PRE::REALTIME_PRE()
{
	m_stop_receive_data = false;

	m_received_data_once = false;
}


REALTIME_PRE::~REALTIME_PRE()
{
	m_stop_receive_data = true;

	receive_data_thread.join();
}

void REALTIME_PRE::begin_to_receive_data_from_UR(float millisecond)
{
	// test with ur 
	//receive_data_thread = std::thread(&REALTIME_PRE::receive_data, this, millisecond);
	
	// test offline
	receive_data(millisecond);

	// waiting for receiving data from the UR.
	while (true)
	{
		if (m_received_data_once)
		{
			break;
		}
	}
}

void REALTIME_PRE::send_data_move_to(float x, float y, float z, float rx, float ry, float rz, float acceleration, float velocity)
{
	char command[200] = {};

#ifdef _MSC_VER 

	sprintf_s(command, "movej(p[%f,%f,%f,%f,%f,%f], a=%f, v=%f)\n", x, y, z, rx, ry, rz, acceleration, velocity);

#else
	sprintf(command, "movej(p[%f,%f,%f,%f,%f,%f], a=%f, v=%f)\n", x , y, z, rx, ry, rz, acceleration, velocity);

#endif // _MSC_VER 

	string command_str(command);

	m_socketmm.client_send(command_str);
}

void REALTIME_PRE::send_data_move_x(float x, float a, float v)
{
	float added_x = m_cartesian_data[0] + x;

	send_data_move_to(
		added_x, m_cartesian_data[1], m_cartesian_data[2],
		m_cartesian_data[3], m_cartesian_data[4], m_cartesian_data[5], a, v);
}

void REALTIME_PRE::send_data_move_y(float y, float a, float v)
{
	float added_y = m_cartesian_data[1] + y;

	send_data_move_to(
		m_cartesian_data[0], added_y, m_cartesian_data[2],
		m_cartesian_data[3], m_cartesian_data[4], m_cartesian_data[5], a, v);
}

void REALTIME_PRE::send_data_move_z(float z, float a, float v)
{
	float added_z = m_cartesian_data[2] + z;

	send_data_move_to(
		m_cartesian_data[0], m_cartesian_data[1], added_z,
		m_cartesian_data[3], m_cartesian_data[4], m_cartesian_data[5], a, v);
}

void REALTIME_PRE::get_base_tools_position(float & x, float & y, float z, float & rx, float ry, float & rz)
{
	x = m_cartesian_data[0];
	y = m_cartesian_data[1];
	z = m_cartesian_data[2];
	rx = m_cartesian_data[3];
	ry = m_cartesian_data[4];
	rz = m_cartesian_data[5];
}

void REALTIME_PRE::wait_to_arrive_specific_position(float x, float y, float z, float rx, float ry, float rz, float threshold)
{
	clock_t b_t = clock();

	bool b_arrived = false;
	
	while (true)
	{
		b_arrived = is_arrived(x, y, z, rx, ry, rz, threshold);

		if (b_arrived)
		{
			break;
		}
		else
		{
		}
	}
	cout << "spend " << (float)(clock() - b_t) << "ms to arrive specific position" << endl;
}

void REALTIME_PRE::received_data_as_int(int data_size, int & res)
{
	unsigned char * data = m_receive_buf;

	m_socketmm.client_receive(&data, data_size);

	if (data)
	{
		res = bytes_to_int(data, data_size);

		//delete[]data;

		//data = nullptr;
	}
}

void REALTIME_PRE::receive_data(float millisecond)
{
	int
		total_message_size = 0,
		message_type = 0;

	// save the received data to file
	/*std::fstream ofile("data", std::ios::out);
	for (int i = 0; i < 50; i++)
	{
		if (i == 0)
		{
			unsigned char * receive_buf_p = m_receive_buf;

			int rs = m_socketmm.client_receive(&receive_buf_p, 1254);

			ofile.write((char *)receive_buf_p, 1254);
		}
		else
		{
			unsigned char * receive_buf_p = m_receive_buf;

			int rs = m_socketmm.client_receive(&receive_buf_p, 560);

			ofile.write((char *)receive_buf_p, 560);
		}
	}
	exit(1);
	*/// end for saving data 

	while (!m_stop_receive_data)
	{
		// get the length of overall package
		received_data_as_int(4, total_message_size);

		// get robot message type
		received_data_as_int(1, message_type);

		// receive the rest data.
		int rest_data_size = total_message_size - 5;

		if (rest_data_size > 0)
		{
			cout << "total_message_size=" << total_message_size << " message_type=" << message_type << endl;
			
			unsigned char * receive_buf_p = m_receive_buf;

			int rs = m_socketmm.client_receive(&receive_buf_p, rest_data_size);

			process_data(receive_buf_p, rest_data_size);
			
			m_received_data_once = true;
		}

		Sleep((DWORD)millisecond);
	}
}

void REALTIME_PRE::process_data(unsigned char *& data, int data_size)
{
	int processed_data_size = 0,
		sub_package_size = 0,
		sub_package_type = 0;

	while (processed_data_size < data_size)
	{
		// get length of sub-package
		sub_package_size = bytes_to_int(data + processed_data_size, 4);

		// get the package-type
		sub_package_type = bytes_to_int(data + processed_data_size + 4, 1);

		if (sub_package_type == 4)
		{
			//cout << "here we go!" << endl;
			std::vector<double> position_result;
			// add 5 because 4(sub_package_size)+1(sub_pack_type)
			get_specific_data(data + processed_data_size + 5, 6, position_result);

			for (int i = 0; i < 6; ++i)
			{
				m_cartesian_data[i] = (float)position_result[i];

				cout << m_cartesian_data[i] << " ";
			}
			cout << endl;
		}
		processed_data_size += sub_package_size;
	}
}

void REALTIME_PRE::get_distance(
	float x0, float y0, float z0, float rx0, float ry0, float rz0,
	float x1, float y1, float z1, float rx1, float ry1, float rz1, 
	float & distance)
{
	distance = sqrt(
		(x0 - x1)*(x0 - x1) +
		(y0 - y1)*(y0 - y1) +
		(z0 - z1)*(z0 - z1) +
		(rx0 - rx1)*(rx0 - rx1) +
		(ry0 - ry1)*(ry0 - ry1) +
		(rz0 - rz1)*(rz0 - rz1));
}

bool REALTIME_PRE::is_arrived(float x, float y, float z, float rx, float ry, float rz, float threshold)
{
	float distance = 0.0, x1 = 0, y1 = 0, z1 = 0, rx1 = 0, ry1 = 0, rz1 = 0;

	get_base_tools_position(x1, y1, z1, rx1, ry1, rz1);

	// TODO
	get_distance(x, y, z, rx, ry, rz, x1, y1, z1, rx1, ry1, rz1, distance);
	
	//cout << "distance=" << distance << endl;

	if (distance < threshold)
	{
		return true;
	}
	else
	{
		return false;
	}
}