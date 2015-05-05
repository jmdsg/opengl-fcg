#include "Buffer.h"

#include <cstdio>

namespace nBuffer{

	// <-- Id, Use, Size, Target, Layout --> //

	struct bufferProperties gBufferProperties[2] = {

		// <-- Vertexes 2D buffer properties --> //

		{
			nBuffer::bufferId::VERTEXES_2D_BUFFER,
			nBuffer::bufferUse::STATIC_DRAW,
			nBuffer::bufferDataSize::VERTEXES_2D_SIZE,
			nBuffer::bufferTarget::ARRAY_BUFFER,
			nBuffer::bufferLayout::VERTEXES_2D_LAYOUT
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

	memset(mVBO, 0, mNumberOfBuffers * sizeof(GLuint));
	memset(mVBOSize, 0, mNumberOfBuffers * sizeof(GLuint));

}

// <-- Destructor --> //

CBuffer::~CBuffer(){

}

// <-- Draws --> //

void CBuffer::draw(){

	glBindVertexArray(mVao);
	glDrawElements(GL_TRIANGLES, mVBOSize[nBuffer::bufferId::VERTEXES_INDEXES_BUFFER], GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

// <-- Fills new buffer --> //

void CBuffer::fillBuffer(nBuffer::bufferId nId, const GLuint nSize, void *npData){

	GLuint id, layout, size, use, target;

	layout = -1;
	id = size = use = target = 0;

	if (!nSize || !npData)
		return;

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
