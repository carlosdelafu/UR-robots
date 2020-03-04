#include "URobot.h"

URobot::URobot()
{
	m_stop_receive_data = false;

	m_received_data_once = false;
}


URobot::~URobot()
{
	m_stop_receive_data = true;

	if (m_receive_data_thread.joinable())
	{
		m_receive_data_thread.join();
	}
}

void URobot::begin_to_receive_data_from_UR(unsigned int milliseconds)
{
	// test with ur 
	m_receive_data_thread = std::thread(&URobot::receive_data, this, milliseconds);
	
	// test offline
	//receive_data(milliseconds);

	// waiting for receiving data from the UR.
	while (true)
	{
		m_ur_ready.lock();

		bool is_ready = m_received_data_once;

		m_ur_ready.unlock();

		if (is_ready)
		{
			break;
		}
		else
		{
			// not ready
		}
	}
}

void URobot::send_data_move_to(double x, double y, double z, double rx, double ry, double rz, double acceleration, double velocity)
{
	char command[200] = {};

#ifdef _MSC_VER 

	sprintf_s(command, "movej(p[%f,%f,%f,%f,%f,%f], a=%f, v=%f)\n", x, y, z, rx, ry, rz, acceleration, velocity);
	
	//sprintf_s(command, "servoc(p[%f,%f,%f,%f,%f,%f], a=%f, v=%f)\n", x, y, z, rx, ry, rz, acceleration, velocity);

#else
	sprintf(command, "movej(p[%f,%f,%f,%f,%f,%f], a=%f, v=%f)\n", x , y, z, rx, ry, rz, acceleration, velocity);

#endif // _MSC_VER 

	string command_str(command);

	m_socketmm.client_send(command_str);
}

void URobot::disconnection()
{
	m_socketmm.client_close();

	m_socketmm.server_close();
}

void URobot::send_data_move_x(double x_add, double a, double v, bool wait)
{
	std::vector<double> p;

	get_base_tools_position(p);

	double added_x = p[0] + x_add;

	send_data_move_to(added_x, p[1], p[2], p[3], p[4], p[5], a, v);

	if (wait)
	{
		wait_to_arrive_specific_position(added_x, p[1], p[2], p[3], p[4], p[5]);
	}
}

void URobot::send_data_move_y(double y_add, double a, double v, bool wait)
{
	std::vector<double> p;

	get_base_tools_position(p);

	double added_y = p[1] + y_add;

	send_data_move_to(p[0], added_y, p[2], p[3], p[4], p[5], a, v);

	if (wait)
	{
		wait_to_arrive_specific_position(p[0], added_y, p[2], p[3], p[4], p[5]);
	}
}

void URobot::send_data_move_z(double z_add, double a, double v, bool wait)
{
	std::vector<double> p;

	get_base_tools_position(p);

	double added_z = p[2] + z_add;

	send_data_move_to(p[0], p[1], added_z, p[3], p[4], p[5], a, v);

	if (wait)
	{
		wait_to_arrive_specific_position(p[0], p[1], added_z, p[3], p[4], p[5]);
	}
}

void URobot::get_base_tools_position(double & x, double & y, double &z, double & rx, double &ry, double & rz)
{
	m_rw_position.lock();
	x = m_cartesian_data[0];
	y = m_cartesian_data[1];
	z = m_cartesian_data[2];
	rx = m_cartesian_data[3];
	ry = m_cartesian_data[4];
	rz = m_cartesian_data[5];
	m_rw_position.unlock();
}

void URobot::get_base_tools_position(std::vector<double> & p)
{
	p.resize(6);

	m_rw_position.lock();

	for (int i = 0; i < 6; ++i)

		p[i] = m_cartesian_data[i];

	m_rw_position.unlock();
}

void URobot::wait_to_arrive_specific_position(double x, double y, double z, double rx, double ry, double rz, double threshold)
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
	cout << "took " << (float)(clock() - b_t) << "ms to arrive the given position" << endl;
}

void URobot::received_data_as_uchar(int data_size, unsigned char & res)
{
	unsigned char * data = m_receive_buf;

	m_socketmm.client_receive(&data, data_size);

	if (data)
	{
		std::vector<int> bits;

		m_bit_operation.char_array_to_bits(data, data_size, bits);;

		m_bit_operation.bits_to_number<unsigned char>(bits, 0, 8, res);
	}

	memset(data, '\0', data_size);
}


void URobot::received_data_as_int(int data_size, int & res)
{
	unsigned char * data = m_receive_buf;

	m_socketmm.client_receive(&data, data_size);

	if (data)
	{
		std::vector<int> bits;

		m_bit_operation.char_array_to_bits(data, data_size, bits);;

		m_bit_operation.bits_to_number<int>(bits, 0, 32, res);
	}

	memset(data, '\0', data_size);
}

void URobot::receive_data(unsigned int millisecond)
{
	int	total_message_size = 0;
	
	unsigned char message_type = 0;

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
		received_data_as_uchar(1, message_type);

		// receive the rest data.
		int rest_data_size = total_message_size - 5;

		if (rest_data_size > 0)
		{

#ifdef ROBOT_DEBUG
			cout << "total_message_size=" << total_message_size << " header message_type=" << (int)message_type << endl;
#endif // ROBOT_DEBUG
			
			cout << "total_message_size=" << total_message_size << " header message_type=" << (int)message_type << endl;
			
			unsigned char * receive_buf_p = m_receive_buf;

			int rs = m_socketmm.client_receive(&receive_buf_p, rest_data_size);

			m_bit_operation.char_array_to_bits(receive_buf_p, rest_data_size, m_bits);

			process_data(m_bits);

			//process_data(receive_buf_p, rest_data_size);
			
			m_ur_ready.lock();
			
			m_received_data_once = true;
			
			m_ur_ready.unlock();
		}
		else
		{
			m_ur_ready.lock();

			m_received_data_once = false;
			
			m_ur_ready.unlock();
		}

		memset(m_receive_buf, '\0', 1500);

		std::this_thread::sleep_for(std::chrono::milliseconds((unsigned int)millisecond));
	}
}

void URobot::process_data(unsigned char *& data, int data_size)
{
	int processed_data_size = 0,
		sub_package_size = 0;

	unsigned int
		sub_package_type = 0;

	while (processed_data_size < data_size)
	{
		// get length of sub-package
		sub_package_size = bytes_to_int(data + processed_data_size, 4);

		if (sub_package_size < 0)
		{
			return ;
		}

		// get the package-type
		sub_package_type = bytes_to_uint(data + processed_data_size + 4, 1);

		//cout << "sub_package_size=" << sub_package_size << " sub_package_type=" << sub_package_type << endl;

		if (sub_package_type == 0)
		{
			process_type_0(data + processed_data_size + 5);
		}

		if (sub_package_type == 4)
		{
			process_type_4(data + processed_data_size + 5);
		}

		processed_data_size += sub_package_size;
	}
}

void URobot::process_data(std::vector<int>& bits)
{
	int sub_package_size = 0;

	unsigned char sub_package_type = 0;

	int i = 0;

	while (i < bits.size())
	{
		m_bit_operation.bits_to_number<int>(bits, i, 32, sub_package_size);

		m_bit_operation.bits_to_number<unsigned char>(bits, i + 32, 8, sub_package_type);

#ifdef ROBOT_DEBUG

		cout << "sub_package_size=" << sub_package_size << " sub_package_type=" << (int)sub_package_type << endl;

#endif // ROBOT_DEBUG

		if (sub_package_type == 0)
		{
			process_type_0(bits, i, sub_package_size);
		}
		else if (sub_package_type == 1)
		{
			process_type_1(bits, i, sub_package_size);
		}
		else if (sub_package_type == 4)
		{
			process_type_4(bits,i, sub_package_size);
		}

		i += (sub_package_size * 8);
	}
}

void URobot::get_distance(
	double x0, double y0, double z0, double rx0, double ry0, double rz0,
	double x1, double y1, double z1, double rx1, double ry1, double rz1,
	double & distance)
{
	distance = sqrt(
		(x0 - x1)*(x0 - x1) +
		(y0 - y1)*(y0 - y1) +
		(z0 - z1)*(z0 - z1) +
		(rx0 - rx1)*(rx0 - rx1) +
		(ry0 - ry1)*(ry0 - ry1) +
		(rz0 - rz1)*(rz0 - rz1));
}

void URobot::process_type_0(unsigned char * data)
{
	__time64_t timestamp = 0;

	timestamp = bytes_to_uint_64(data, 8);

	//auto sysTime = std::chrono::system_clock::from_time_t(timestamp);

	std::cout << timestamp << endl;
}

void URobot::process_type_1(std::vector<int>& bits, int begin, int count)
{
	int i = 40 + begin;
	
	int each_joint_size = 41;

	int joint_num = count / each_joint_size;

	//cout << "[process type 1] this robot has " << joint_num << " joints." << endl;

	for (int j = 0; j < joint_num; ++j)
	{
		double q_actual;
		m_bit_operation.bits_to_double(bits, i, q_actual);
		i += 64;

		double q_target;
		m_bit_operation.bits_to_double(bits, i, q_target);
		i += 64;

		double qd_actual;
		m_bit_operation.bits_to_double(bits, i, qd_actual);
		i += 64;

		float I_actual;
		m_bit_operation.bits_to_float(bits, i, I_actual);
		i += 32;

		float V_actual;
		m_bit_operation.bits_to_float(bits, i, V_actual);
		i += 32;

		float T_motor;
		m_bit_operation.bits_to_float(bits, i, T_motor);
		i += 32;

		float T_micro;
		m_bit_operation.bits_to_float(bits, i, T_micro);
		i += 32;

		UINT8 jointMode;
		m_bit_operation.bits_to_number<UINT8>(bits, i, 8, jointMode);
		i += 8;

		//i = i + j * each_joint_size;
	}
}

void URobot::process_type_0(std::vector<int>& bits, int begin, int count)
{
	int i = 40 + begin;

	UINT64 timestamp;

	m_bit_operation.bits_to_number<UINT64>(bits, i, 64, timestamp);
	i += 64;

	int isRobotConnected;
	m_bit_operation.bits_to_number<int>(bits, i, 8, isRobotConnected);
	i += 8;

	int isRealRobotEnabled;
	m_bit_operation.bits_to_number<int>(bits, i, 8, isRealRobotEnabled);
	i += 8;

	int isPowerOnRobot;
	m_bit_operation.bits_to_number<int>(bits, i, 8, isPowerOnRobot);
	i += 8;

	int isEmergencyStopped;
	m_bit_operation.bits_to_number<int>(bits, i, 8, isEmergencyStopped);
	i += 8;

	int isSecurityStopped;
	m_bit_operation.bits_to_number<int>(bits, i, 8, isSecurityStopped);
	i += 8;

	int isProgramRunning;
	m_bit_operation.bits_to_number<int>(bits, i, 8, isProgramRunning);
	i += 8;

	int isProgramPaused;
	m_bit_operation.bits_to_number<int>(bits, i, 8, isProgramPaused);
	i += 8;

	unsigned char robotMode;
	m_bit_operation.bits_to_number<unsigned char>(bits, i, 8, robotMode);
	i += 8;

	double speedFraction;
	m_bit_operation.bits_to_double(bits, i, speedFraction);
	i += 64;

	if (i != count * 8)
	{
		cerr << "[process type 0] dreceived count error, please check version of robot" << endl;
	}
	else
	{
		//cerr << "[process type 0] received successfully" << endl;
	}
}

void URobot::process_type_4(unsigned char * data)
{
	//cout << "here we go!" << endl;
	std::vector<double> position_result;

	// add 5 because 4(sub_package_size)+1(sub_pack_type)
	get_specific_data(data, 6, position_result);

	m_rw_position.lock();

	for (int i = 0; i < 6; ++i)
	{
		m_cartesian_data[i] = (float)position_result[i];
	}

	m_rw_position.unlock();

	for (int i = 0; i < 6; ++i)
	{
		cout << m_cartesian_data[i] << " ";
	}
	cout << endl;
}

void URobot::process_type_4(std::vector<int>& bits, int begin, int count)
{
	double tmp[6] = {};

	// skip the header of sub package
	int i = begin + 40;

	while (i < begin + count * 8)
	{
		for (int j = 0; j < 6; j++)
		{
			m_bit_operation.bits_to_double(bits, i, tmp[j]);

			i += 64;
		}

		m_rw_position.lock();

		for (int j = 0; j < 6; ++j)
		{
			m_cartesian_data[j] = tmp[j];

			//cout << m_cartesian_data[j] << " ";
		}
		//cout << endl;

		m_rw_position.unlock();
	}
}

bool URobot::is_arrived(double x, double y, double z, double rx, double ry, double rz, double threshold)
{
	double distance = 0.0, x1 = 0, y1 = 0, z1 = 0, rx1 = 0, ry1 = 0, rz1 = 0;

	get_base_tools_position(x1, y1, z1, rx1, ry1, rz1);

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