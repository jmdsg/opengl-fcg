#ifndef LOADER_LIGHTS_H
#define LOADER_LIGHTS_H

#include "Light.h"
#include "Loader.h"

class CLoaderLights : public CLoader{
private:

	vector<CLight*> mLights;

public:

	CLoaderLights();
	~CLoaderLights();

	vector<CLight*> getLights();
	void load(const string nFilePath);

};

#endif