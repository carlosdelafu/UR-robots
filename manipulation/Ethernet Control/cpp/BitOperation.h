#pragma once
#include <iostream>
#include <vector>

class BitOperation
{
public:
	BitOperation();

	~BitOperation();

	void char_to_bits(char c, std::vector<int> &bits);

	// convert byte array to bits
	/*
	\param[in] c_array char array you want to convert
	\param[in] count the count of byte
	\param[out] bits bits vector of c_array, the size should be equal with 8*count
	*/
	void char_array_to_bits(unsigned char * c_array, int count, std::vector<int> &bits);

	// convert bits array to specific number(unsigned int, int, unsigned char, char)
	/*
	\param[in] bits bits vector
	\param[in] begin begin index
	\param[in] count how many bits you want to use
	\param[out] v result
	*/
	template<typename T>
	void bits_to_number(std::vector<int> &bits, int begin, int count, T &v)
	{
			T tmp = 0;
			for (int i = begin; i < begin + count; i++)
			{
				tmp = tmp << 1;

				if (bits[i] == 1)
				{
					tmp = tmp | 0x000000001;
				}
			}
			v = tmp;
	}

	void bits_to_float(std::vector<int> &bits, int begin, float &v);

	void bits_to_double(std::vector<int> &bits, int begin, double &v);

private:

};
