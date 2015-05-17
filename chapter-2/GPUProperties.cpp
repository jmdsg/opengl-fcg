#include "GPUProperties.h"

// <-- Constructor --> //

CGPUProperties::CGPUProperties(){

}

// <-- Destructor --> //

CGPUProperties::~CGPUProperties(){

}

// <-- Gets vendor --> //

string CGPUProperties::getVendor(){

	return reinterpret_cast<const GLchar*>(glGetString(GL_VENDOR));

}

// <-- Gets renderer --> //

string CGPUProperties::getRenderer(){

	return reinterpret_cast<const GLchar*>(glGetString(GL_RENDERER));

}

// <-- Gets GLSL version --> //

string CGPUProperties::getGLSLVersion(){

	return reinterpret_cast<const GLchar*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

}

// <-- Gets OpenGL version --> //

string CGPUProperties::getOpenGLVersion(){

	return reinterpret_cast<const GLchar*>(glGetString(GL_VERSION));

}