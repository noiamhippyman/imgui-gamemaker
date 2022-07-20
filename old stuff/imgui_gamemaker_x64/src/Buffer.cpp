#include "Buffer.h"

Buffer::Buffer(void* data, unsigned int data_size)
{
	set_data(data, data_size);
}

void Buffer::set_data(void* data, unsigned int data_size)
{
	this->data = (unsigned char*)data;
	this->data_size = data_size;
	this->data_index = 0;
}

void* Buffer::get_data() {
	return this->data;
}

void Buffer::seek(unsigned int index)
{
	this->data_index = index;
}


void Buffer::write(float value)
{
	charfloat cf; cf.f = value;
	for (int i = 0; i < 4; ++i) {
		data[data_index + i] = cf.c[i];
	}
	data_index += 4;
}

void Buffer::write(std::string value)
{
	const char* c_str = value.c_str();
	int size = value.capacity() + 1;
	for (int i = 0; i < size; ++i) {
		data[data_index + i] = c_str[i];
	}

	data_index += size;
}

float Buffer::read_float()
{
	charfloat val;
	for (int i = 0; i < 4; ++i) {
		val.c[i] = data[data_index + i];
	}
	data_index += 4;
	return val.f;
}

#include <iostream>
std::string Buffer::read_string()
{
	std::string str;
	while (data[data_index] != (unsigned char)0) {
		str.push_back(data[data_index]);
		data_index++;
	}
	data_index++;
	return str;
}



void Buffer::poke(unsigned int offset, float value)
{
	charfloat cf; cf.f = value;
	for (int i = 0; i < 4; ++i) {
		data[offset + i] = cf.c[i];
	}
}

void Buffer::poke(unsigned int offset, std::string value)
{
	const char* c_str = value.c_str();
	int size = value.capacity() + 1;
	for (int i = 0; i < size; ++i) {
		data[offset + i] = c_str[i];
	}
}

float Buffer::peek_float(unsigned int offset)
{
	charfloat val;
	for (int i = 0; i < 4; ++i) {
		val.c[i] = data[offset + i];
	}
	return val.f;
}

std::string Buffer::peek_string(unsigned int offset)
{
	return std::string((char*)&data[offset]);
}
