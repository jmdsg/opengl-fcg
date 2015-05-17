#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Buffer.h"
#include "AppException.h"

using std::cerr;
using std::endl;

class CDrawable{

protected:

	CBuffer *mpBuffer;

public:

	CDrawable();
	~CDrawable();

	virtual void draw() = 0;
	void fillBuffer(nBuffer::bufferId nId, const GLuint nSize, void *npData);

};

#endif