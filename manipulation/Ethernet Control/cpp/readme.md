
## Description

To connect to the UR robot and retrieve data by the socket.

All the data formatted by `Primary and Secondary Client interface` right now.

## Details

- Platform: Windows 10
- Dependencies: None
- Compiler: MSVC 2017 x64

## Features
- Receive information from the UR in the background.
- Receive the position of TCP based on the base-reference in real-time.
- Let the UR's TCP move to a specific position.
- Block until arrived.

## Example

Control the UR robot in a game controller way: you could use those command to control the robot as following:

- 'w/s': move along the x-axis.
- 'a/d': move along the y-axis.
- 'q/e': move along the z-axis.

``` C++
#include "URobot.h"
#include <conio.h>

int main()
{
	URobot ur_robot;

    // replace it with your UR robot's ip and port
	int state = ur_robot.init_socket_connection("192.168.0.2", 30002);

	if (URFAILED == state)
	{
		return 1;
	}

    // start to connect to the ur robot
	ur_robot.begin_to_receive_data_from_UR();

    // get current position
	double x = 0, y = 0, z = 0, rx = 0, ry = 0, rz = 0;
    // you could use this function to get position any time you want
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
		else if (c == 'q')
		{
			return 0;
		}

		ur_robot.get_base_tools_position(x, y, z, rx, ry, rz);

		cout << "[new position]" << x << " " << y << " " << z << " " << rx << " " << ry << " " << rz << endl;
	}
	
	return 0;
}
```

## Below is the output of running:

```
[client] client_init done
[begining position]0.361781 -0.0439009 0.321387 -3.0657 -0.528965 -0.131213
spend 1035ms to arrive the specific position
[new position]0.312403 -0.0438854 0.321508 -3.06564 -0.528752 -0.131794
spend 1009ms to arrive the specific position
[new position]0.360901 -0.0438964 0.321499 -3.06581 -0.528742 -0.131562
spend 983ms to arrive the specific position
[new position]0.411174 -0.0438618 0.32145 -3.06576 -0.528844 -0.131549
spend 979ms to arrive the specific position
[new position]0.411715 -0.0936432 0.321319 -3.06607 -0.52862 -0.130884
spend 917ms to arrive the specific position
[new position]0.411688 -0.142868 0.321321 -3.06606 -0.528819 -0.130857
spend 909ms to arrive the specific position
[new position]0.411702 -0.193138 0.321309 -3.06609 -0.528875 -0.130812
```
