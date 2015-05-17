#ifndef BUFFER_H
#define BUFFER_H

#include "AppException.h"
#include <Core\gl_core_4_3.h>

#define BUFFER_OFFSET(nOffset)((void*)(nOffset))

namespace nBuffer{

	enum bufferId{
		VERTEXES_BUFFER,
		NORMAL_BUFFER,
		TEXTURE_COORDINATES_BUFFER,
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
		VERTEXES_LAYOUT,
		NORMALS_LAYOUT,
		TEXTURE_COORDINATES_LAYOUT,
		VERTEXES_INDEXES_LAYOUT = -1
	};

	enum bufferDataSize{
		VERTEXES_SIZE = 3,
		NORMALS_SIZE = 3,
		TEXTURE_COORDINATES_SIZE = 2,
		VERTEXES_INDEXES_SIZE = 1
	};

	struct bufferProperties{
		nBuffer::bufferId mId;
		nBuffer::bufferUse mUse;
		nBuffer::bufferDataSize mSize;
		nBuffer::bufferTarget mTarget;
		nBuffer::bufferLayout mLayout;
	};

	extern bufferProperties gBufferProperties[4];

};

class CBuffer{
private:

	GLuint mVao, *mVBO, *mVBOSize, mNumberOfBuffers;

public:

	CBuffer();
	~CBuffer();

	void draw();
	void fillBuffer(nBuffer::bufferId nId, const GLuint nSize, void *npData) throw (CAppException);
};

#endif