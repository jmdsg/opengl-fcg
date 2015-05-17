#include "LoaderMesh.h"

// <-- Constructor --> //

CLoaderMesh::CLoaderMesh(){

}

// <-- Destructor --> //

CLoaderMesh::~CLoaderMesh(){

	mMeshes.clear();

}

// <-- Get Meshes --> //

vector<CMesh*> CLoaderMesh::getMeshes(){

	return mMeshes;

}

// <-- Load Meshes --> //

void CLoaderMesh::load(const string nFilePath){

	// TODO

}