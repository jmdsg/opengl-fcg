#ifndef LOADER_MESH_H
#define LOADER_MESH_H

#include "Mesh.h"
#include "Loader.h"

class CLoaderMesh : public CLoader{
private:

	vector<CMesh*> mMeshes;

public:

	CLoaderMesh();
	~CLoaderMesh();

	vector<CMesh*> getMeshes();
	void load(const string nFilePath);
	
};

#endif