#include "GLSLProgram.h"

namespace nGLSLProgram{

	struct GLSLShaderFileExtension Extensions[9] = {
		{ ".vs", nGLSLProgram::VERTEX },
		{ ".cs", nGLSLProgram::COMPUTE },
		{ ".vert", nGLSLProgram::VERTEX },
		{ ".gs", nGLSLProgram::GEOMETRY },
		{ ".fs", nGLSLProgram::FRAGMENT },
		{ ".geom", nGLSLProgram::GEOMETRY },
		{ ".frag", nGLSLProgram::FRAGMENT },
		{ ".tcs", nGLSLProgram::TESSELATION_CONTROL },
		{ ".tes", nGLSLProgram::TESSELATION_EVALUATION }
	};

};

// <-- Constructor --> //

CGLSLProgram::CGLSLProgram(){

	mProgram = 0;

	for (int k = 0; k < 6; ++k)
		mShaders[k] = 0;

}

// <-- Destructor --> //

CGLSLProgram::~CGLSLProgram(){

	mUniformsList.clear();
	mAttributesList.clear();
	glDeleteProgram(mProgram);

}

// <-- Use GLSL program --> //

void CGLSLProgram::use(){

	glUseProgram(mProgram);

}

// <-- Un use GLSL program --> //

void CGLSLProgram::unUse(){

	glUseProgram(0);

}

// <-- Create a new GLSL program --> //

void CGLSLProgram::createProgram() throw (CAppException){

	GLint programLinkStatus;

	mProgram = glCreateProgram();

	glAttachShader(mProgram, mShaders[nGLSLProgram::VERTEX_POSITION]);
	glAttachShader(mProgram, mShaders[nGLSLProgram::COMPUTE_POSITION]);
	glAttachShader(mProgram, mShaders[nGLSLProgram::FRAGMENT_POSITION]);
	glAttachShader(mProgram, mShaders[nGLSLProgram::GEOMETRY_POSITION]);
	glAttachShader(mProgram, mShaders[nGLSLProgram::TESSELATION_CONTROL_POSITION]);
	glAttachShader(mProgram, mShaders[nGLSLProgram::TESSELATION_EVALUATION_POSITION]);

	glLinkProgram(mProgram);
	glGetProgramiv(mProgram, GL_LINK_STATUS, &programLinkStatus);

	if (!programLinkStatus){

		GLint infoLogLength;
		glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *infoLog = new GLchar[infoLogLength];
		glGetProgramInfoLog(mProgram, infoLogLength, NULL, infoLog);
		printf("Compile Log : %s\n", infoLog);
		delete[] infoLog;

		throw CAppException("GLSLProgram exception has been detected : Program link error!\n");

	}
	else{

		printf("The program was successfully created!!\n");
		glDeleteShader(mShaders[nGLSLProgram::VERTEX_POSITION]);
		glDeleteShader(mShaders[nGLSLProgram::COMPUTE_POSITION]);
		glDeleteShader(mShaders[nGLSLProgram::FRAGMENT_POSITION]);
		glDeleteShader(mShaders[nGLSLProgram::GEOMETRY_POSITION]);
		glDeleteShader(mShaders[nGLSLProgram::TESSELATION_CONTROL_POSITION]);
		glDeleteShader(mShaders[nGLSLProgram::TESSELATION_EVALUATION_POSITION]);

	}

}

// <-- Load uniform variables --> //

void CGLSLProgram::loadUniformVariables(){

	GLenum uniformVariableType;
	GLint uniformMaxLength, numberOfUniforms, uniformVariableSize;

	glGetProgramiv(mProgram, GL_ACTIVE_UNIFORMS, &numberOfUniforms);
	glGetProgramiv(mProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniformMaxLength);

	GLchar *uniformName = new GLchar[uniformMaxLength];

	printf("\nActive Uniforms\n---------------------------------------------\nID  -  Name  -  Type\n\n");

	for (int k = 0; k < numberOfUniforms; ++k){

		glGetActiveUniform(mProgram, k, uniformMaxLength + 1, NULL, &uniformVariableSize, &uniformVariableType, uniformName);
		addUniform(uniformName);
		printf("%d | %s (%s)\n", mUniformsList[uniformName], uniformName, getTypeString(uniformVariableType).c_str());

	}

	printf("\n---------------------------------------------\n");

}

// <-- Load attribute variables --> //

void CGLSLProgram::loadAttributeVariables(){

	GLenum attributeVariableType;
	GLint attributeMaxLength, numberOfAttributes, numberOfWrittenChars, attributeVariableSize;

	glGetProgramiv(mProgram, GL_ACTIVE_ATTRIBUTES, &numberOfAttributes);
	glGetProgramiv(mProgram, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &attributeMaxLength);

	GLchar * attributeName = new GLchar[attributeMaxLength];

	printf("\nActive Attributes\n---------------------------------------------\nID  -  Name  -  Type\n\n");

	for (int k = 0; k < numberOfAttributes; ++k){

		glGetActiveAttrib(mProgram, k, attributeMaxLength + 1, &numberOfWrittenChars, &attributeVariableSize, &attributeVariableType, attributeName);
		addAttribute(attributeName);

		printf("%d | %s (%s)\n", mAttributesList[attributeName], attributeName, getTypeString(attributeVariableType).c_str());

	}

	printf("\n---------------------------------------------\n");

}

// <-- Add new uniform --> //

void CGLSLProgram::addUniform(const string name){

	mUniformsList[name] = glGetUniformLocation(mProgram, name.c_str());

}

// <-- Add new attribute --> //

void CGLSLProgram::addAttribute(const string name){

	mAttributesList[name] = glGetAttribLocation(mProgram, name.c_str());

}

// <-- Gets specific uniform --> //

GLuint CGLSLProgram::getUniform(const string name){

	return mUniformsList[name];

}

// <-- Gets specific attribute --> //

GLuint CGLSLProgram::getAttribute(const string name){

	return mAttributesList[name];

}

// <-- Loads GLSL shader from a file --> //

void CGLSLProgram::loadFromFile(const string filePath){

	fstream shaderFile;
	string shaderLine, shaderCode;

	shaderFile.open(filePath, ios::in);

	if (shaderFile){

		while (getline(shaderFile, shaderLine))
			shaderCode.append(shaderLine + "\n");

		compileShader(getShaderType(filePath), shaderCode);

	}
	else{

		printf("The shader file doesnt exist !!\n");

	}

	shaderFile.close();

}

// <-- Gets uniform/attribute type --> //

string CGLSLProgram::getTypeString(const GLenum nType){

	switch (nType){

	case GL_FLOAT:
		return "float";
		break;
	case GL_FLOAT_VEC2:
		return "vec2";
		break;
	case GL_FLOAT_VEC3:
		return "vec3";
		break;
	case GL_FLOAT_VEC4:
		return "vec4";
		break;
	case GL_DOUBLE:
		return "double";
		break;
	case GL_INT:
		return "int";
		break;
	case GL_UNSIGNED_INT:
		return "unsigned int";
		break;
	case GL_BOOL:
		return "bool";
		break;
	case GL_FLOAT_MAT2:
		return "mat2";
		break;
	case GL_FLOAT_MAT3:
		return "mat3";
		break;
	case GL_FLOAT_MAT4:
		return "mat4";
		break;
	case GL_SAMPLER_2D:
		return "sampler2D";
		break;
	case GL_SAMPLER_2D_SHADOW:
		return "sampler2DShadow";
		break;
	case GL_SAMPLER_CUBE:
		return "samplerCube";
		break;
	default:
		return "?";
		break;

	}

}

// <-- Gets shader type from a GLSL file extension --> //

GLuint CGLSLProgram::getShaderType(const string fileName){

	string fileExtension = getFileExtension(fileName);
	GLuint numberOfExtensions, shaderType;

	shaderType = nGLSLProgram::VERTEX;
	numberOfExtensions = sizeof(nGLSLProgram::Extensions) / sizeof(nGLSLProgram::GLSLShaderFileExtension);

	for (int k = 0; k < (GLint)numberOfExtensions; ++k)
		if (fileExtension == nGLSLProgram::Extensions[k].mExtension){

			shaderType = nGLSLProgram::Extensions[k].mType;
			break;

		}

	return shaderType;

}

// <-- Gets file extension from GLSL file --> //

string CGLSLProgram::getFileExtension(const string nFilePath){

	size_t dotLoc = nFilePath.find_last_of('.');
	return nFilePath.substr(dotLoc, string::npos);

}

// <-- Compiles new GLSL shader code --> //

void CGLSLProgram::compileShader(const GLuint nGLSLProgramType, const string nGLSLProgramCode) throw (CAppException){

	GLint shaderCompilationStatus, shader;
	const GLchar * pCode = nGLSLProgramCode.c_str();

	shader = glCreateShader(nGLSLProgramType);
	glShaderSource(shader, 1, &pCode, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompilationStatus);

	if (!shaderCompilationStatus){

		GLchar *infoLog;
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		infoLog = new GLchar[infoLogLength];
		glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
		printf("Compile Log : %s\n", infoLog);
		delete[] infoLog;

		throw CAppException("GLSLProgram exception has been detected : Shader compilation error!");

	}
	else{

		if (nGLSLProgramType == nGLSLProgram::VERTEX){

			printf("Creating Vertex Shader...\n");
			mShaders[nGLSLProgram::VERTEX_POSITION] = shader;

		}
		else if (nGLSLProgramType == nGLSLProgram::COMPUTE){

			printf("Creating Compute Shade...r\n");
			mShaders[nGLSLProgram::COMPUTE_POSITION] = shader;

		}
		else if (nGLSLProgramType == nGLSLProgram::FRAGMENT){

			printf("Creating Fragment Shader...\n");
			mShaders[nGLSLProgram::FRAGMENT_POSITION] = shader;

		}
		else if (nGLSLProgramType == nGLSLProgram::GEOMETRY){

			printf("Creating Geometry Shader...\n");
			mShaders[nGLSLProgram::GEOMETRY_POSITION] = shader;

		}
		else if (nGLSLProgramType == nGLSLProgram::TESSELATION_CONTROL){

			printf("Creating Tesselation Control Shader...\n");
			mShaders[nGLSLProgram::TESSELATION_CONTROL_POSITION] = shader;

		}
		else if (nGLSLProgramType == nGLSLProgram::TESSELATION_EVALUATION){

			printf("Creating Tesselation Evaluation Shader...\n");
			mShaders[nGLSLProgram::TESSELATION_EVALUATION_POSITION] = shader;

		}

	}

}

// <-- Loads GLSL shader from a string --> //

void CGLSLProgram::loadFromString(const string fileName, const string shaderCode){

	compileShader(getShaderType(fileName), shaderCode);

}

// <-- Loads an integer uniform in this GLSL program --> //

void CGLSLProgram::loadUniformi(const string name, const GLint size, const GLint *pointer){

	switch (size){

	case nGLSLProgram::UNIFORM_SIZE_1D:
		glUniform1i(getUniform(name), pointer[0]);
		break;
	case nGLSLProgram::UNIFORM_SIZE_2D:
		glUniform2i(getUniform(name), pointer[0], pointer[1]);
		break;
	case nGLSLProgram::UNIFORM_SIZE_3D:
		glUniform3i(getUniform(name), pointer[0], pointer[1], pointer[2]);
		break;
	case nGLSLProgram::UNIFORM_SIZE_4D:
		glUniform4i(getUniform(name), pointer[0], pointer[1], pointer[2], pointer[3]);
		break;

	}

}

// <-- Loads a float uniform in this GLSL program--> //

void CGLSLProgram::loadUniformf(const string name, const GLint size, const GLfloat* pointer){

	switch (size){

	case nGLSLProgram::UNIFORM_SIZE_1D:
		glUniform1f(getUniform(name), pointer[0]);
		break;
	case nGLSLProgram::UNIFORM_SIZE_2D:
		glUniform2f(getUniform(name), pointer[0], pointer[1]);
		break;
	case nGLSLProgram::UNIFORM_SIZE_3D:
		glUniform3f(getUniform(name), pointer[0], pointer[1], pointer[2]);
		break;
	case nGLSLProgram::UNIFORM_SIZE_4D:
		glUniform4f(getUniform(name), pointer[0], pointer[1], pointer[2], pointer[3]);
		break;

	}

}

// <-- Loads a matrix uniform in this GLSL program --> //

void CGLSLProgram::loadUniformMatrix(const string name, const GLint size, const GLfloat* pointer){

	switch (size){

	case nGLSLProgram::UNIFORM_SIZE_3X3:
		glUniformMatrix3fv(getUniform(name), 1, GL_FALSE, pointer);
		break;
	case nGLSLProgram::UNIFORM_SIZE_4X4:
		glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, pointer);
		break;

	}

}

