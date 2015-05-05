#ifndef BUFFER_H
#define BUFFER_H

#include <Core\gl_core_4_3.h>

#define BUFFER_OFFSET(nOffset)((void*)(nOffset))

namespace nBuffer{

	enum bufferId{
		VERTEXES_2D_BUFFER,
		VERTEXES_INDEXES_BUFFER
	};

	enum bufferTarget{
		ARRAY_BUFFER = GL_ARRAY_BUFFER,
		ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER
	};

	enum bufferUse{
		STATIC_DRAW = GL_STATIC_DRAW
	};

	enum bufferLayout{
		VERTEXES_2D_LAYOUT,
		VERTEXES_INDEXES_LAYOUT = -1
	};

	enum bufferDataSize{
		VERTEXES_2D_SIZE = 2,
		VERTEXES_INDEXES_SIZE = 1
	};

	struct bufferProperties{
		nBuffer::bufferId mId;
		nBuffer::bufferUse mUse;
		nBuffer::bufferDataSize mSize;
		nBuffer::bufferTarget mTarget;
		nBuffer::bufferLayout mLayout;
	};

	extern bufferProperties gBufferProperties[2];

};

class CBuffer{
private:

	GLuint mVao, mVBO[2], mVBOSize[2], mNumberOfBuffers;

public:

	CBuffer();
	~CBuffer();

	void draw();
	void fillBuffer(nBuffer::bufferId nId, const GLuint nSize, void *npData);
};

#endif