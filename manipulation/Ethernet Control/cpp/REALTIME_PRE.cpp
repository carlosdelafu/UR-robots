#include "REALTIME_PRE.h"



REALTIME_PRE::REALTIME_PRE()
{
}


REALTIME_PRE::~REALTIME_PRE()
{
}

void REALTIME_PRE::read_data_from_robot(double millisecond)
{
	unsigned int number_of_values[] = { 1,1,6,6,6,6,6,6,6,6,3,15,6,6,6,1,6,1,1,1,6 };
	size_t number_of_values_size = sizeof(number_of_values) / sizeof(unsigned int);
	vector<double> res;
	unsigned char * data_size = nullptr, *data = nullptr;

	while (true)
	{
		data_size = new unsigned char[5]();
		m_socketmm.server_receive(data_size, 4);

		size_t all_data_size = bytes_to_int(data_size, 4);
		
		if (all_data_size < 1)
		{
			continue;
		}
		
		cout << "data size=" << all_data_size << endl;

		data = new unsigned char[all_data_size - 4 + 1]();
		m_socketmm.server_receive(data, all_data_size - 4);
		unsigned char * opr_data = data;

		for (size_t data_count = 1; data_count < number_of_values_size; ++data_count)
		{
			get_specific_data(opr_data, number_of_values[data_count], res);
			print(res);
			opr_data += number_of_values[data_count] * 8;
		}

		delete[]data_size;
		data_size = nullptr;

		delete[]data;
		data = nullptr;

		opr_data = nullptr;

		Sleep((DWORD)millisecond);
	}

}
