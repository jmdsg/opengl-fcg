#ifndef FRAMEBUFFER_SHADOW_H
#define FRAMEBUFFER_SHADOW_H

#include <cstdio>
#include "Framebuffer.h"

class CFramebufferShadow : public CFramebuffer{
private:

public:

	CFramebufferShadow();
	~CFramebufferShadow();

	void init(const GLuint nWidth, const GLuint nHeight);

};

#endif