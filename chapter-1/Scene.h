#ifndef SCENE_H
#define SCENE_H

#include "Buffer.h"
#include "GLSLProgram.h"

class CScene{

private:

	CBuffer *mpBuffer;
	CGLSLProgram *mpGLSLProgram;

public:

	CScene();
	~CScene();
	void draw();
	void init();

};

#endif