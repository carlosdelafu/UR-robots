#include "BitOperation.h"

BitOperation::BitOperation()
{
}

BitOperation::~BitOperation()
{
}

void BitOperation::char_to_bits(char c, std::vector<int>& bits)
{
	bits.resize(8);

	char tmp = c;

	for (int i = 0; i < 8; i++)
	{
		if (tmp & 0x00000001)
		{
			bits[8 - i - 1] = 1;
		}
		else
		{
			bits[8 - i - 1] = 0;
		}
		tmp = tmp >> 1;
	}
}

void BitOperation::char_array_to_bits(unsigned char * c_array, int count, std::vector<int>& bits)
{
	bits.resize(0);

	for (int i = 0; i < count; i++)
	{
		std::vector<int> tmp;

		char_to_bits(c_array[i], tmp);

		bits.insert(bits.end(), tmp.begin(), tmp.end());
	}
}

void BitOperation::bits_to_float(std::vector<int>& bits, int begin, float & v)
{
	__int32 val = 0;

	for (int i = begin + 0; i < begin + 32; ++i)
	{
		val = val << 1;

		if (bits[i] == 1)
		{
			val = val | 0x000000001;
		}
	}
	v = *(float*)&val;
}

void BitOperation::bits_to_double(std::vector<int>& bits, int begin, double & v)
{
	__int64 val = 0;

	for (int i = begin + 0; i < begin + 64; ++i)
	{
		val = val << 1;

		if (bits[i] == 1)
		{
			val = val | 0x000000001;
		}
	}
	v = *(double*)&val;
}
