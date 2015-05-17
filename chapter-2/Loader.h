#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <vector>
#include <Core\gl_core_4_3.h>

using std::string;
using std::vector;

class CLoader{

private:

public:

	CLoader();
	~CLoader();
	virtual void load(const string nFilePath) = 0;

};

#endif