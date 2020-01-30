#pragma once
#include "U3REALTIME.h"

class REALTIME_PRE :
	public U3REALTIME
{
public:
	REALTIME_PRE();
	
	~REALTIME_PRE();

	virtual void read_data_from_robot(double millisecond = 1000);
};

