#include "packet.h"

Packet::Packet() : length_(0), buffer_size_(kInitialSize), buffer_(new unsigned char[kInitialSize]()){}

Packet::~Packet() {
	delete[] buffer_;
}

void Packet::write_hex(const unsigned char* hex, int size){
	if (length_ + size >= buffer_size_) {
		buffer_ = (unsigned char*)realloc(buffer_, buffer_size_ + size);
		buffer_size_ += size;
	}

	for (int i = 0; i < size; ++i){
		buffer_[length_] = hex[i];
		++length_;
	}
}

void Packet::write_null(size_t amount){
	if (length_ + amount >= buffer_size_) {
		buffer_ = (unsigned char*)realloc(buffer_, buffer_size_ + amount);
		buffer_size_ += amount;
	}

	for (; amount > 0; --amount)
	{
		buffer_[length_] = 0;
		++length_;
	}
}


void Packet::write_string(std::string str, std::size_t slen){
	if (length_ + slen >= buffer_size_)
	{
		buffer_ = (unsigned char*)realloc(buffer_, buffer_size_ + slen);
		buffer_size_ += slen;
	}

	memcpy(buffer_ + length_, str.data(), str.length());

	size_t len = str.length();
	length_ += len;

	for (; len < slen; ++len)
	{
		buffer_[length_] = 0;
		++length_;
	}
}

unsigned char *Packet::get_buffer(){
	return buffer_;
}

size_t Packet::get_length(){
	return length_;
}

void Packet::reset() {
	delete[] buffer_;
	buffer_ = new unsigned char[kInitialSize]();
	length_ = 0;
	buffer_size_ = kInitialSize;
}