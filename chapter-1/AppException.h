#ifndef APP_EXCEPTION_H
#define APP_EXCEPTION_H

#include <string>
#include <iostream>
#pragma warning(disable : 4290)

using std::string;
using std::runtime_error;

class CAppException : public runtime_error{
private:

public:

	CAppException(const string nMessage);
	~CAppException();

};

#endif