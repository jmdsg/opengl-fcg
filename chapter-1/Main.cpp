#include "Main.h"

namespace nMain{

	CScene *gpScene;
	GLFWwindow *gpWindow;
	ivec2 gViewportDimensions;
	CGPUProperties *gpGPUProperties;

};

// <-- Inits application --> //

void initApp(){

	nMain::gpScene = new CScene();
	nMain::gpScene->init();

}

// <-- Clears application --> //

void clearApp(){

	delete nMain::gpScene;
	glfwDestroyWindow(nMain::gpWindow);

}

// <-- Inits GLFW --> //

bool initGLFW(){

	if (!glfwInit()){
		
		glfwTerminate();
		return false;

	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	nMain::gViewportDimensions.x = 1200;
	nMain::gViewportDimensions.y = 800;

	nMain::gpWindow = glfwCreateWindow(nMain::gViewportDimensions.x, nMain::gViewportDimensions.y, "Chapter - 1", NULL, NULL);

	if (!nMain::gpWindow){
		
		glfwTerminate();
		return false;

	}

	glfwMakeContextCurrent(nMain::gpWindow);
	glfwSetWindowSizeCallback(nMain::gpWindow, windowResizeCallback);

	return true;

}

// <-- Inits OpenGL core --> //

bool initCore(){

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED){

		glfwTerminate();
		return false;

	}

	nMain::gpGPUProperties = new CGPUProperties();

	printf("Vendor : %s\n", nMain::gpGPUProperties->getVendor().c_str());
	printf("Renderer : %s\n", nMain::gpGPUProperties->getRenderer().c_str());
	printf("GLSL Version : %s\n", nMain::gpGPUProperties->getGLSLVersion().c_str());
	printf("OpenGL Version : %s\n", nMain::gpGPUProperties->getOpenGLVersion().c_str());

	return true;

}

// <-- Application main loop --> //

void mainLoop(){

	while (!glfwWindowShouldClose(nMain::gpWindow) && !glfwGetKey(nMain::gpWindow, GLFW_KEY_ESCAPE)){

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		nMain::gpScene->draw();

		glfwSwapBuffers(nMain::gpWindow);
		glfwPollEvents();

	}

}

// <-- Window resize callback --> //

void windowResizeCallback(GLFWwindow *pWindow, GLint nWidth, GLint nHeight){

	nMain::gViewportDimensions.x = nWidth;
	nMain::gViewportDimensions.y = nHeight;

	glViewport(0, 0, nMain::gViewportDimensions.x, nMain::gViewportDimensions.y);

}

// <-- Main --> //

void main(GLint argc, GLchar **argv){

	if (initGLFW() && initCore()){

		initApp();
		mainLoop();

	}

	clearApp();

}