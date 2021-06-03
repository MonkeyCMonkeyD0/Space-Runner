#include <commu.h>


commu::commu(const std::string & buffer) : 
	type(com_type(buffer[9] - '0')), msg(buffer.substr(10)) {}

commu::commu(const char * buffer) : 
	type(com_type(buffer[9] - '0')), msg(std::string(buffer + 10)) {}

commu::commu(const com_type & type, const std::string & msg) : 
	type(type), msg(msg) {}


char * commu::to_buf() const
{
	std::string buffer = "________";
	buffer += (char) 0x04;
	buffer += (char) this->type + '0';
	buffer += this->msg;
	char * buf = new char[buffer.size()];
	strcpy(buf, buffer.c_str());
	return buf;
}