#include "REALTIME_PRE.h"

int main()
{
	REALTIME_PRE realtime_pre;

	float x = 0, y = 0, z = 0, rx = 0, ry = 0, rz = 0;

	int state = realtime_pre.init_socket_connection("127.0.0.1", 30002);

	if (URFAILED == state)
	{
		return 1;
	}

	realtime_pre.begin_to_receive_data_from_UR(30);

	realtime_pre.get_base_tools_position(x, y, z, rx, ry, rz);
	cout << x << " " << y << " " << z << " " << rx << " " << ry << " " << rz << endl;

	float add = 0.1;

	realtime_pre.send_data_move_x(add, 1.0, 1.0);
	//realtime_pre.send_data_move_y(add);

	realtime_pre.wait_to_arrive_specific_position(x + add, y, z, rx, ry, rz);

	realtime_pre.get_base_tools_position(x, y, z, rx, ry, rz);
	cout << x << " " << y << " " << z << " " << rx << " " << ry << " " << rz << endl;

	system("pause");
	return 0;
}