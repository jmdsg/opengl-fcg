#ifndef LOADER_TEXTURE_H
#define LOADER_TEXTURE_H

#include "Loader.h"

class CLoaderTexture : public CLoader{

private:

	GLuint mTextureId;

public:

	CLoaderTexture();
	~CLoaderTexture();

	GLuint getTextureId();
	void load(const string nFilePath);

};

#endif