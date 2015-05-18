#version 430 core

layout(location = 0) out vec4 fragmentColor;

struct lightInfo{
	// ...
};

struct meshInfo{
	// ...
};

vec3 point(){

	vec3 ambient, diffuse, specular;

	// TODO
	
	return ambient + diffuse + specular;

}

vec3 spotlight(){

	vec3 ambient, diffuse, specular;

	// TODO
	
	return ambient + diffuse + specular;

}

vec3 directional(){

	vec3 ambient, diffuse, specular;

	// TODO
	
	return ambient + diffuse + specular;

}

void main(){

	vec3 color;

	// TODO
	
	fragmentColor = vec4(color, 1.0);
	
}