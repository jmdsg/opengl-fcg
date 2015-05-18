#include "Buffer.h"

namespace nBuffer{

	// <-- Id, Use, Size, Target, Layout --> //

	struct bufferProperties gBufferProperties[4] = {

		// <-- Vertexes buffer properties --> //

		{
			nBuffer::bufferId::VERTEXES_BUFFER,
			nBuffer::bufferUse::STATIC_DRAW,
			nBuffer::bufferDataSize::VERTEXES_SIZE,
			nBuffer::bufferTarget::ARRAY_BUFFER,
			nBuffer::bufferLayout::VERTEXES_LAYOUT
		},

		// <-- Normals buffer properties --> //

		{
			nBuffer::bufferId::NORMAL_BUFFER,
			nBuffer::bufferUse::STATIC_DRAW,
			nBuffer::bufferDataSize::NORMALS_SIZE,
			nBuffer::bufferTarget::ARRAY_BUFFER,
			nBuffer::bufferLayout::VERTEXES_LAYOUT
		},

		// <-- Texture Coordinates buffer properties --> //

		{
			nBuffer::bufferId::TEXTURE_COORDINATES_BUFFER,
			nBuffer::bufferUse::STATIC_DRAW,
			nBuffer::bufferDataSize::TEXTURE_COORDINATES_SIZE,
			nBuffer::bufferTarget::ARRAY_BUFFER,
			nBuffer::bufferLayout::TEXTURE_COORDINATES_LAYOUT
		},

		// <-- Vertexes indexes buffer properties --> //

		{
			nBuffer::bufferId::VERTEXES_INDEXES_BUFFER,
			nBuffer::bufferUse::STATIC_DRAW,
			nBuffer::bufferDataSize::VERTEXES_INDEXES_SIZE,
			nBuffer::bufferTarget::ELEMENT_ARRAY_BUFFER,
			nBuffer::bufferLayout::VERTEXES_INDEXES_LAYOUT
		}

	};

};

// <-- Constructor --> //

CBuffer::CBuffer(){

	mNumberOfBuffers = sizeof(nBuffer::gBufferProperties) / sizeof(nBuffer::bufferProperties);

	glGenVertexArrays(1, &mVao);

	mVBO = new GLuint[mNumberOfBuffers];
	mVBOSize = new GLuint[mNumberOfBuffers];

}

// <-- Destructor --> //

CBuffer::~CBuffer(){

	glDeleteVertexArrays(1, &mVao);
	delete mVBO;
	delete mVBOSize;

}

// <-- Draws --> //

void CBuffer::draw(){

	glBindVertexArray(mVao);
	glDrawElements(GL_TRIANGLES, mVBOSize[nBuffer::bufferId::VERTEXES_INDEXES_BUFFER], GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

// <-- Fills new buffer --> //

void CBuffer::fillBuffer(nBuffer::bufferId nId, const GLuint nSize, void *npData) throw (CAppException){

	GLuint id, layout, size, use, target;

	layout = -1;
	id = size = use = target = 0;

	if (!npData)
		throw CAppException("Null buffer data!!");
	else if (!nSize)
		throw CAppException("Buffer size is zero!!");

	for (int k = 0; k < static_cast<GLint>(mNumberOfBuffers); ++k){

		if (nId == nBuffer::gBufferProperties[k].mId){

			id = nBuffer::gBufferProperties[k].mId;
			use = nBuffer::gBufferProperties[k].mUse;
			size = nBuffer::gBufferProperties[k].mSize;
			target = nBuffer::gBufferProperties[k].mTarget;
			layout = nBuffer::gBufferProperties[k].mLayout;

			break;
		}

	}

	glBindVertexArray(mVao);

	if (id == nBuffer::bufferId::VERTEXES_INDEXES_BUFFER){

		glGenBuffers(1, &mVBO[id]);
		glBindBuffer(target, mVBO[id]);
		glBufferData(target, nSize * sizeof(GLuint), npData, use);

	}
	else{

		glGenBuffers(1, &mVBO[id]);
		glEnableVertexAttribArray(layout);
		glBindBuffer(target, mVBO[id]);
		glBufferData(target, nSize * sizeof(GLfloat), npData, use);
		glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, GL_FALSE, BUFFER_OFFSET(0));

	}

	mVBOSize[id] = nSize;

	glBindVertexArray(0);

}
