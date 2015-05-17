#ifndef GPU_PROPERTIES_H
#define GPU_PROPERTIES_H

#include <string>
#include <Core\gl_core_4_3.h>

using std::string;

class CGPUProperties{

public:

	CGPUProperties();
	~CGPUProperties();

	string getVendor();
	string getRenderer();
	string getGLSLVersion();
	string getOpenGLVersion();

};

#endif