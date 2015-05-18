#include "Drawable.h"

// <-- Constructor --> //

CDrawable::CDrawable(){

}

// <-- Destructor --> //

CDrawable::~CDrawable(){

}

// <-- Fills a buffer --> //

void CDrawable::fillBuffer(nBuffer::bufferId nId, const GLuint nSize, void *npData){

	mpBuffer->fillBuffer(nId, nSize, npData);

}