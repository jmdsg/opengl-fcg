#include "Light.h"

// <-- Constructor --> //

CLight::CLight(){

	mpBuffer = new CBuffer();

}

// <-- Destructor --> //

CLight::~CLight(){

}

void CLight::draw(){

	mpBuffer->draw();

}
