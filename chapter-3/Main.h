#ifndef MAIN_H
#define MAIN_H

#include <glm\glm.hpp>
#include <Core\gl_core_4_3.h>
#include <GLFW\glfw3.h>

#include "Scene.h"
#include "GPUProperties.h"

using glm::ivec2;

namespace nMain{

	extern CScene *gpScene;
	extern GLFWwindow *gpWindow;
	extern ivec2 gViewportDimensions;
	extern CGPUProperties *gpGPUProperties;

};

// <-- Inits application --> //

void initApp();

// <-- Clears application --> //

void clearApp();

// <-- Inits GLFW --> //

bool initGLFW();

// <-- Inits OpenGL core --> //

bool initCore();

// <-- Application main loop --> //

void mainLoop();

// <-- Window resize callback --> //

void windowResizeCallback(GLFWwindow *pWindow, GLint nWidth, GLint nHeight);

#endif