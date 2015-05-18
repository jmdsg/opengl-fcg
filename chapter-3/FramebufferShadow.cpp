#include "FramebufferShadow.h"

// <-- Constructor --> //

CFramebufferShadow::CFramebufferShadow(){

}

// <-- Destructor --> //

CFramebufferShadow::~CFramebufferShadow(){

	glDeleteTextures(1, &mTexture);
	glDeleteFramebuffers(1, &mFramebuffer);

}

// <-- Inits framebuffer shadow --> //

void CFramebufferShadow::init(const GLuint nWidth, const GLuint nHeight){

	// TODO 

}
