#include "Framebuffer.h"

// <-- Constructor --> //

CFramebuffer::CFramebuffer(){

}

// <-- Destructor --> //

CFramebuffer::~CFramebuffer(){

}

// <-- Gets width --> //

GLuint CFramebuffer::getWidth(){

	return mWidth;

}

// <-- Gets height --> //

GLuint CFramebuffer::getHeight(){

	return mHeight;

}

// <-- Gets texture ID --> //

GLuint CFramebuffer::getTextureID(){

	return mTexture;

}

// <-- Uses framebuffer --> //

void CFramebuffer::use(nFramebuffer::targets nTarget){

	glBindFramebuffer(nTarget, mFramebuffer);

}

// <-- Unuses framebuffer --> //

void CFramebuffer::unUse(nFramebuffer::targets nTarget){

	glBindFramebuffer(nTarget, 0);

}