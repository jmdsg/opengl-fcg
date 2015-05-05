#ifndef GPU_PROPERTIES
#define GPU_PROPERTIES

#include <string>
#include <Core\gl_core_4_3.h>

using std::string;

class CGPUProperties{

private:

	string mVendor, mRenderer, mGLSLVersion, mOpenGLVersion;

public:

	CGPUProperties();
	~CGPUProperties();

	string getVendor();
	string getRenderer();
	string getGLSLVersion();
	string getOpenGLVersion();
};

#endif