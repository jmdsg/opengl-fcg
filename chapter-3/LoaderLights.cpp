#include "LoaderLights.h"

// <-- Constructor --> //

CLoaderLights::CLoaderLights(){

}

// <-- Destructor --> //

CLoaderLights::~CLoaderLights(){

	mLights.clear();

}

// <-- Get lights --> //

vector<CLight*> CLoaderLights::getLights(){

	return mLights;

}

// <-- Load lights --> //

void CLoaderLights::load(const string nFilePath){

	// TODO

}
