#include "Scene.h"

// <-- Constructor --> //

CScene::CScene(){

}

// <-- Destructor --> //

CScene::~CScene(){

	delete mpBuffer;

}

// <-- Inits Scene --> //

void CScene::init(){

	GLuint quadIndexes[6] = { 0, 1, 2, 0, 2, 3 };
	GLfloat quadVerts[8] = { -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f };

	mpBuffer = new CBuffer();
	mpBuffer->fillBuffer(nBuffer::bufferId::VERTEXES_2D_BUFFER, 8, quadVerts);
	mpBuffer->fillBuffer(nBuffer::bufferId::VERTEXES_INDEXES_BUFFER, 6, quadIndexes);

	mpGLSLProgram = new CGLSLProgram();
	mpGLSLProgram->loadFromFile("Assets/Shaders/basic.vert");
	mpGLSLProgram->loadFromFile("Assets/Shaders/basic.frag");
	mpGLSLProgram->createProgram();
	mpGLSLProgram->loadUniformVariables();
	mpGLSLProgram->loadAttributeVariables();

}

// <-- Draws Scene --> //

void CScene::draw(){

	mpGLSLProgram->use();

		mpBuffer->draw();

	mpGLSLProgram->unUse();

}
