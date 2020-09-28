#pragma once
#include <string>


typedef int BufferDataType;
enum BufferDataType_ {
	BufferDataType_Float,
	BufferDataType_String
};

union charfloat {
	unsigned char c[4];
	float f;
};

class Buffer
{
public:
	Buffer(void* data, unsigned int data_size);
	void set_data(void* data, unsigned int data_size);

	void seek(unsigned int index);

	void write(float value);
	void write(std::string value);
	float read_float();
	std::string read_string();
	
	void poke(unsigned int offset, float value);
	void poke(unsigned int offset, std::string value);
	float peek_float(unsigned int offset);
	std::string peek_string(unsigned int offset);

private:
	unsigned char* data;
	unsigned int data_size;
	unsigned int data_index;
};

