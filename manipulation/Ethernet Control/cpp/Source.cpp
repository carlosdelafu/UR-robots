#include "URobot.h"

#include <conio.h>

int main()
{
	URobot ur_robot;

	int state = ur_robot.init_socket_connection("192.168.0.2", 30002);

	if (URFAILED == state)
	{
		return 1;
	}

	ur_robot.begin_to_receive_data_from_UR();
	
	// test receive data from the UR in loop.
	//while (true)
	//{
	//	double x = 0, y = 0, z = 0, rx = 0, ry = 0, rz = 0;
	//	ur_robot.get_base_tools_position(x, y, z, rx, ry, rz);
	//	cout << x << " " << y << " " << z << " " << rx << " " << ry << " " << rz << endl;
	//	std::this_thread::sleep_for(std::chrono::milliseconds((unsigned int)200));
	//}

	double x = 0, y = 0, z = 0, rx = 0, ry = 0, rz = 0;

	ur_robot.get_base_tools_position(x, y, z, rx, ry, rz);

	cout << "[beginning position]" << x << " " << y << " " << z << " " << rx << " " << ry << " " << rz << endl;

	char c;

	while (true)
	{
		// without enter key
		c = getch();
		
		if (c == 'a')
		{
			ur_robot.send_data_move_y(0.05, 0.5, 0.5);
		}
		else if (c == 'w')
		{
			ur_robot.send_data_move_x(0.05, 0.5, 0.5);
		}
		else if (c == 's')
		{
			ur_robot.send_data_move_x(-0.05, 0.5, 0.5);
		}
		else if (c == 'd')
		{
			ur_robot.send_data_move_y(-0.05, 0.5, 0.5);
		}
		else if (c == 'q')
		{
			ur_robot.send_data_move_z(0.05, 0.5, 0.5);
		}
		else if (c == 'e')
		{
			ur_robot.send_data_move_z(-0.05, 0.5, 0.5);
		}
		else if (c == 'r')
		{
			ur_robot.disconnection();
			
			int rs = ur_robot.init_socket_connection("192.168.0.2", 30002);

		}
		else if (c == 'q')
		{
			return 0;
		}

		ur_robot.get_base_tools_position(x, y, z, rx, ry, rz);

		cout << "[new position]" << x << " " << y << " " << z << " " << rx << " " << ry << " " << rz << endl;
	}
	
	system("pause");
	return 0;
}