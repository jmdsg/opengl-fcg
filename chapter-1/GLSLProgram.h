#ifndef GLSL_PROGRAM_H
#define GLSL_PROGRAM_H

#include <map>
#include <string>
#include <fstream>
#include <Core\gl_core_4_3.h>
#include "AppException.h"

using std::ios;
using std::map;
using std::string;
using std::fstream;

namespace nGLSLProgram{

	enum GLSLUniform{
		UNIFORM_SIZE_1D = 1,
		UNIFORM_SIZE_2D = 2,
		UNIFORM_SIZE_3D = 3,
		UNIFORM_SIZE_4D = 4,
		UNIFORM_SIZE_2X2 = 2,
		UNIFORM_SIZE_3X3 = 3,
		UNIFORM_SIZE_4X4 = 4
	};

	enum GLSLShader{
		VERTEX = GL_VERTEX_SHADER,
		COMPUTE = GL_COMPUTE_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER,
		GEOMETRY = GL_GEOMETRY_SHADER,
		TESSELATION_CONTROL = GL_TESS_CONTROL_SHADER,
		TESSELATION_EVALUATION = GL_TESS_EVALUATION_SHADER
	};

	enum Positions{
		VERTEX_POSITION,
		COMPUTE_POSITION,
		FRAGMENT_POSITION,
		GEOMETRY_POSITION,
		TESSELATION_CONTROL_POSITION,
		TESSELATION_EVALUATION_POSITION
	};

	struct GLSLShaderFileExtension{
		const GLchar * mExtension;
		nGLSLProgram::GLSLShader mType;
	};

	extern struct GLSLShaderFileExtension Extensions[9];

};

class CGLSLProgram{

private:

	GLuint mProgram, mShaders[6];
	map<string, GLuint> mUniformsList, mAttributesList;

	string getTypeString(const GLenum nType);
	GLuint getShaderType(const string nFilePath);

	string getFileExtension(const string nFilePath);
	void compileShader(const GLuint nGLSLProgramType, const string nGLSLProgramCode) throw (CAppException);

public:

	CGLSLProgram();
	~CGLSLProgram();

	void use();
	void unUse();

	void createProgram() throw (CAppException);

	void loadUniformVariables();
	void loadAttributeVariables();

	void addUniform(const string nUniformName);
	void addAttribute(const string nAttributeName);

	GLuint getUniform(const string nUniformName);
	GLuint getAttribute(const string nAttributeName);

	void loadFromFile(const string nFilePath);
	void loadFromString(const string nFileExtension, const string nGLSLProgramCode);

	void loadUniformi(const string nUniformName, const GLint nSize, const GLint *npData);
	void loadUniformf(const string nUniformName, const GLint nSize, const GLfloat *npData);
	void loadUniformMatrix(const string nUniformName, const GLint nSize, const GLfloat *npData);

};

#endif