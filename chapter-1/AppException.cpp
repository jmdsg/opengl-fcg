#include "AppException.h"

// <-- Constructor --> //

CAppException::CAppException(const string nMessage) : runtime_error(nMessage){

}

// <-- Destructor --> //

CAppException::~CAppException(){

}
