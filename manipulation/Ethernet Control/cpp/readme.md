
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

    // start to connect to the ur robot, it will return after connection finished
    ur_robot.begin_to_receive_data_from_UR();

    double x = 0, y = 0, z = 0, rx = 0, ry = 0, rz = 0;

    // get current position
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
            ur_robot.send_data_move_y(0.05);
        }
        else if (c == 'w')
        {
            ur_robot.send_data_move_x(0.05);
        }
        else if (c == 's')
        {
            ur_robot.send_data_move_x(-0.05);
        }
        else if (c == 'd')
        {
            ur_robot.send_data_move_y(-0.05);
        }
        else if (c == 'q')
        {
            ur_robot.send_data_move_z(0.05);
        }
        else if (c == 'e')
        {
            ur_robot.send_data_move_z(-0.05);
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

## Below is the output when running:

```
[client] client_init done
[beginning position]0.411645 -0.193868 0.321272 -3.06594 -0.52859 -0.130771
took 946ms to arrive the given position
[new position]0.41162 -0.2439 0.321212 -3.06608 -0.528714 -0.130561
took 886ms to arrive the given position
[new position]0.411658 -0.194263 0.321249 -3.06569 -0.528944 -0.130654
took 901ms to arrive the given position
[new position]0.362342 -0.193859 0.32125 -3.06584 -0.52847 -0.130407
took 983ms to arrive the given position
[new position]0.411647 -0.193913 0.321214 -3.06592 -0.528547 -0.130359
took 883ms to arrive the given position
[new position]0.411701 -0.243337 0.321154 -3.06606 -0.529015 -0.130311
took 992ms to arrive the given position
[new position]0.411704 -0.243879 0.370895 -3.06605 -0.528587 -0.130901
took 959ms to arrive the given position
[new position]0.411736 -0.24389 0.321889 -3.06584 -0.528577 -0.130191
```
