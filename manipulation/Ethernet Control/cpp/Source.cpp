#include "REALTIME_PRE.h"
//
//// convert bytes to int, which is 32 bits
//int bytes_to_int(unsigned char* b, unsigned int length)
//{
//	unsigned int val = 0;
//
//	for (size_t i = 0; i < length; ++i)
//	{
//		val = val << 8;
//		val = val | b[i];
//	}
//
//	return val;
//}
//
//// default convert bytes to double, which is 64 bits!!
//double bytes_to_double(unsigned char* b, unsigned int length = 8)
//{
//	long long int val = 0;
//
//	for (size_t i = 0; i < length; ++i)
//	{
//		val = val << 8;
//		// cout << val << endl;
//		val = val | b[i];
//		// cout << val << endl;
//	}
//
//	return *(double*)&val;
//}
//
//// get the specific data in _data, and store the result in _result
//void get_specific_data(unsigned char * _data, size_t _count,vector<double> & _result)
//{
//	_result.resize(_count);
//
//	double tmp_data = 0.0;
//
//	for (size_t i = 0; i < _count; ++i)
//	{
//		tmp_data = bytes_to_double(_data);
//		_result[i] = tmp_data;
//		_data += 8;
//	}
//}
//
//// only print the vector of double
//void print(vector<double> & _vec)
//{
//	for (auto i : _vec)
//	{
//		cout << i << " ";
//	}
//	cout << endl;
//}
//
//// delete the pointer safely
//void saft_delete_pointer(unsigned char ** p)
//{
//	if (*p)
//	{
//		delete[] *p;
//	}
//	*p = nullptr;
//}

int main()
{
	//fstream ifile;
	//ifile.open("data_from_UR_CB2",std::ios::in | std::ios::binary);

	//if (!ifile.is_open())
	//{
	//	return -1;
	//}

	//// Retrieve the data size first
	//unsigned char * i_p = new unsigned char[5]();
	//ifile.read((char *)i_p, 4);
	//size_t all_data_size = bytes_to_int(i_p, 4);

	//// Retrieve the left data, and remove the first 4 byte of data size.
	//unsigned char * data = new unsigned char[all_data_size - 4 + 1]();
	//ifile.read((char *)data, all_data_size - 4);
	//unsigned char * opr_data = data;

	//vector<double> res;

	//// The number of vlaues list, you could get this list in "Client_interface_V3.12and5.6.xlsx"
	//unsigned int number_of_values[] = { 1,1,6,6,6,6,6,6,6,6,3,15,6,6,6,1,6,1,1,1,6 };
	//
	//size_t number_of_values_size = sizeof(number_of_values) / sizeof(unsigned int);

	//// Skip the first one, that is the total message length in bytes.
	//for (int data_count = 1; data_count < number_of_values_size; ++data_count)
	//{
	//	get_specific_data(opr_data, number_of_values[data_count], res);
	//	print(res);
	//	opr_data += number_of_values[data_count] * 8;
	//}
	//
	//saft_delete_pointer(&i_p);
	//saft_delete_pointer(&data);
	//opr_data = nullptr;

	REALTIME_PRE realtime_pre;
	int state = realtime_pre.init_socket_connection("192.168.0.2", 30002);
	if (URFAILED == state)
	{
		return 1;
	}

	realtime_pre.read_data_from_robot(1000);

	return 0;
}