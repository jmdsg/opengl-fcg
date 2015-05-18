#include "Mesh.h"

// <-- Constructor --> //

CMesh::CMesh(){

	mpBuffer = new CBuffer();

}

// <-- Destructor --> //

CMesh::~CMesh(){

}

// <-- Draws mesh --> //

void CMesh::draw(){

	mpBuffer->draw();

}
