# Capitulo I - El comienzo

En este capítulo se explicarán diversos aspectos básicos de como trabajar con una estructura de proyecto en computación gráfica, se explicará el uso del core de `OpenGL` con sus ventajas con respecto a la biblioteca `GLEW`, el uso de una clase `GLSLProgram` que se encargará de manejar de forma generica los distintos shaders escritos en el lenguaje `GLSL` asociados a cada etapa programable del pipeline gráfico y el uso de la clase `Buffer` que se encarga de llevar a cabo el proceso de rendering en el `OpenGL` moderno haciendo uso de Vertex Buffer Objects (VBOs) y Vertex Array Objects (VAOs).

## ¡Llegamos a Fundamentos y Técnicas!

Muchos al llegar a esta materia tenemos ciertas interrogantes con respecto a lo aprendido en Introducción a la Computación Gráfica como cuando hablaron de VBOs, VAOs, Shaders etc. ¿Qué es en concreto todo esto? ¿Para que los uso? ¿Como lo uso?, ¡TENGO QUE APRENDER TODO YA!, pues les participo que tengan calma, todo a su tiempo, todo lo veremos con detenimiento para ir cubriendo cada interrogante que pueda haber quedado con respecto al final de la primera materia de esta interesante rama de las ciencias de la computación.

Un aspecto importante de esta materia es que trabajaremos absolutamente todo haciendo uso de las ultimas funcionalidades de `OpenGL`, es decir, ya a nuestro nivel como programadores gráficos debemos entender el concepto de la GPU y como podemos representar las etapas programables del pipeline gráfico mediante los distintos tipos de shaders y aprovecharlos al máximo como herramienta. Con esto ya debemos olvidar:

* ¡La vieja forma de despliegue!

```c++
glBegin(GL_TRIANGLES, GL_POINTS ...);

 // ...

glEnd();
```

* ¡O la famosa pila de matrices!

```c++
glMatrixMode(GL_MODELVIEW, GL_PROJECTION ...);
glLoadIdentity();

 // ...

```

Esto por el cuello de botella que se forma entre el procesador y la unidad de procesamiento gráfico (GPU) que nos limita en explotar las grandes capacidades del hardware, adicionalmente esta no es la forma correcta de trabajar actualmente en computación gráfica, solo se utilizó para entender como desplegar de forma básica y como llevar a cabo las transformaciones a aplicar a los distintos datos mediante el uso de una pila de matrices en versiones viejas de `OpenGL`.

## Estructura de un proyecto en Computación Gráfica

En este punto nos preguntamos, ¿Para qué una estructura de proyecto?, pues por experiencia propia estas son mis razones:

* Por una mejor organización.
* Por tener un código limpio y modular.
* Porque a la hora de tener un bug, este sea ubicado y corregido rápidamente, ya que como todos sabemos, hacer un debug en una aplicación gráfica no es una tarea sencilla.

Nuestra estructura de proyecto será sencilla, constara de dos partes:

* Parte física: Que constará de las carpetas donde estaran todos nuestros archivos adicionales como pueden ser bibliotecas, modelos, texturas, archivos de configuración etc.

* Parte lógica: Que será a nivel de código `C++`, como se usaran las variables globales, enumerados, namespaces, formatos para los nombres de las clases, formatos para los nombres de las variables y como llevar a cabo la interacción entre módulos.

### Parte física

* Dentro de nuestro proyecto de VS 2013 tendremos una carpeta con el mismo nombre de nuestro proyecto, en su interior es donde nuestro IDE va a crear todos nuestros archivos `.h .cpp .hpp`, ahí lo primero que debemos hacer es crear una carpeta llamada `Assets`, esta carpeta va a contener varias carpetas adicionales, las cuales son:

	* Headers, aqui colocaremos todas las bibliotecas adicionales a nuestra aplicación.

	* Libs, aqui colocaremos todos los archivos con extension `.lib`.

	* Models, aqui colocaremos todos los modelos de nuestra aplicación.

	* Config, aqui colocaremos los archivos con una extension propia de configuración de nuestra escena. Para el caso de los modelos se especifican las transformaciones afines necesarias, los coeficientes ambientales, difusos y especulares y para las luces las posiciones, direcciones, coeficientes etc. Nota: Se recomienda usar el formato `JSON` y usar una biblioteca para la lectura del mismo.

	* Shaders, aqui colocaremos todos los shaders que usaremos en nuestra aplicación.

	* Textures, aqui se colocan todas las texturas a usar en la aplicación.

* Dentro de la carpeta `Debug` que nos genera nuestro proyecto se crea un ejecutable o `.exe`, aqui debemos colocar todos nuestras librerias de enlace dinámico `.dll`.

### Parte lógica

#### La estética del código

Cada vez que en nuestro proyecto vayamos a requerir de variables globales, enumerados, namespaces, clases y sus respectivos atributos etc. lo ideal siempre será tener un formato para asi asociar rápidamente lo que queremos programar, en esta parte les presento algunas buenas prácticas:

* Usar el formato `camel case`.

* Namespaces (Espacios de nombre): Los usaremos para almacenar enumerados, variables globales, etc. propios de un módulo. Cuando nos vayamos a referir a un `namespace` el nombre de este debe comenzar con el prefijo `n` seguido del nombre de ese módulo. Adicionalmente, cuando declaramos un nuevo módulo en `C++` y este requiere de un `namespace` que hace uso de variables globales, debemos declararlo dos veces, una en el archivo de cabecera `.h` y el otro en nuestro `.cpp` de la siguiente manera:

```c++
// Namespace en empire.h 

namespace nEmpire{
	extern vec3 gDeathStarPosition;
	// ...
};

// Namespace en empire.cpp

namespace nEmpire{
	vec3 gDeathStarPosition;
	// ...
};
```

Ahora, si nos fijamos en ambos `namespace` las variables globales deben tener como prefijo la letra `g`, por otra parte, en el `namespace` del archivo `empire.h` las variables globales son precedidas por una palabra reservada denominada `extern`. La finalidad de `extern` yace en que cuando nosotros incluimos `empire.h` en otro módulo y queremos hacer uso de la variable `gDeathStarPosition`, le notificamos al compilador de que existe una variable llamada `gDeathStarPosition` declarada para este módulo sin embargo, el archivo de cabecera `empire.h` no posee el valor de dicha variable, ahi es cuando el enlazador resuelve el valor de `gDeathStarPosition` y la encuentra en el `namespace` del archivo `empire.cpp` y de ahí toma su valor. ¿Para qué es esto útil?, es útil porque así no tendremos en memoria dos variables cuya finalidad sea la misma y que posean el mismo nombre para un mismo módulo, es decir, ahorramos memoria.

* Enumerados: Son un conjunto de variables relacionadas que van a tener valores de interés para el programador, en `C++` para indicar los enumerados se usa la palabra reservada `enum`. Cuando a un conjunto de variables de un enumerado no se les asigna un valor predeterminado, se les asignaran valores incrementales desde cero hasta el número de variables que tenga el enumerado menos uno. Es importante destacar, que cuando se tiene un módulo que consta de un `.h` y un `.cpp`, el enumerado solo se va a declarar en el `namespace` del archivo `.h` y las variables deben ser escritas en mayuscula y al ser palabras compuestas separarlas por un underscore `_`.

```c++
// Enumerado en lightSaber.h 

namespace nLightSaber{
	enum nColors{
		RED,
		GREEN,
		BLUE,
		PURPLE,
		DOUBLE_RED // Darth Maul one :)
	};
	// ...
};
```

* Variables del tipo apuntador: Estas variables serán declaradas usando el prefijo `p`. Como ejemplo, tenemos el `namespace` ubicado en el archivo `main.h`:

```c++
namespace nMain{
	GLFWWindow *gpWindow;
	// ...
};
```

* Clases: El formato para los nombres de las clases será el prefijo `C` en mayuscula seguido del nombre de la clase.

	* Atributos: Deben tener como prefijo `m`.
	* Metodos getter: Deben tener como prefijo `get`.
	* Metodos setter: Deben tener como prefijo `set`

```c++
// Punto3D.h

class CPoint3D{
	vec3 mVertex;
	vec3 getVertex();
	void setVertex(vec3 nVertex);
};

// Punto3D.cpp

CPoint3D::CPoint3D(){
	
}

vec3 CPoint3D::getVertex(){
	return mVertex;	
}

void CPoint3D::setVertex(vec3 nVertex){
	mVertex = nVertex;
}
```

#### Módulos principales y sus asociaciones

La interacción la vamos a definir como las distintas asociaciones que van a tener los módulos entre ellos. Básicamente, en nuestra aplicación gráfica tendremos un conjunto de módulos básicos que son los siguientes:

* Buffer (Módulo de despliegue): Es el módulo mas elemental de nuestra aplicación y es el que usaremos para llevar a cabo el despliegue de nuestros modelos y luces haciendo uso de VBOs y VAOs. Nota: Este módulo se explicará con mas detalle en la sección `La clase Buffer`.

* Main (Módulo principal): Que es donde estaran todas las configuraciones de la ventana, el contexto de `OpenGL`, los callbacks en `GLFW` etc.

* Mesh (Módulo de modelos): En el se encuentran todas las propiedades pertenecientes a un mallado que carguemos en nuestra aplicación.

* Light (Módulo de las luces): En el se encuentran todas las propiedades asociadas a una fuente de luz.

* Loader (Módulo cargador): En el nos encargaremos de tener la lógica necesaria para cargar los modelos, luces y texturas de nuestra aplicación. De este módulo es buena práctica que hereden otras clases que sean cargadores especificos, por ejemplo, que del módulo `Loader` hereden los módulos `LoaderObj` u `LoaderOff`.

* GLSLProgram (Módulo de programa `GLSL`): En el nos encargaremos de cargar, enlazar y desenlazar los shaders. Por otro lado, nos sera de muchísima utilidad para enviar nuestros datos al pipeline gráfico. Nota: Este módulo se explicara en detalle en la sección `¿Clase shader o clase programa?`.

* Scene (Módulo de escena): Que será donde se encuentran los distintos procedimientos para renderizar haciendo uso de los programas que contienen a los shaders, el vector de los modelos, el vector de las luces, los objetos que administran las interfaces de usuario, entre otros.

Adicionalmente, cada vez que vayamos a crear un nuevo módulo en nuestra aplicación debemos especificar unas instrucciones que nos van a evitar que el compilador nos notifique redundancia de inclusión cuando vayamos a incluir este nuevo módulo en otro, estas instrucciones son:

```c++
#ifndef MODULO_H
#define MODULO_H

// Código del módulo ...

#endif
```

o

```c++
#pragma once

// Código del módulo ...
```

## El core de OpenGL

Como la mayoria de nosotros estamos acostumbrados a usar `Windows` para llevar a acabo nuestras tareas de computación gráfica haciendo uso de Visual Studio, es importante tener en cuenta una cita historica acerca de como han sido las cosas con respecto a `OpenGL` en los sistemas operativos `Windows`.

Antiguamente, en plataformas `Windows` se hacia uso de `OpenGL` gracias al proyecto `OpenGL ABI` (Application Binary Interface), actualmente, este proyecto no se actualiza desde la version 1.1 del mismo, limitanto el acceso de los programadores gráficos que usan alguno de estos sistemas para acceder a las ultimas funcionalidades de `OpenGL`. `Windows` típicamente, viene con un archivo de cabecera llamado `gl.h` que es donde se accede a las funcionalidades para `OpenGL 1.1`, en vista de que Microsoft no ha tenido planes para continuar con el desarrollo de `OpenGL ABI` ni de la actualización de `gl.h` ni de `opengl32.lib`, han surgido bibliotecas adicionales para evitarnos esta limitación, una de ellas es `GLEW`.

[GLEW](http://glew.sourceforge.net/) (OpenGL Extension Wrangler), es una biblioteca muy común que se hace presente en las aplicaciones gráficas para que el programador pueda acceder a las últimas funcionalidades de `OpenGL` y es por lo general, con la que todos nosotros comenzamos a trabajar, sin embargo, `GLEW` no es la mejor opción para utilizar las últimas funcionalidades del `OpenGL` moderno por tres sencillas razones:

* Provee un largo archivo de cabecera, que contiene todas las funcionalidades de TODAS las versiones de `OpenGL` las cuales, la mayoria no las vamos usar.

* Algunas funcionalidades que provee pueden estar deprecated.

* `GLEW` se distribuye como una biblioteca que debe ser compilada por separado y enlazada dentro de nuestro proyecto para que funcione.

En vista de esto, surgió un nuevo proyecto el cual se llama [OpenGL Loader Generator](https://bitbucket.org/alfonse/glloadgen/wiki/Home). Esta biblioteca es muy flexible y eficiente y se encarga de solucionar los tres problemas mencionados previamente con `GLEW`, aportandole al programador las funcionalidades específicas del core de `OpenGL` que este necesite, adicionalmente, crea dos archivos:

* gl_core_4_*.h: Que será el archivo de cabecera que contendrá todas las funcionalidades del core que generemos de `OpenGL`.

* gl_core_4_*.c: Que será el archivo de código fuente que contendrá todas las funcionalidades implementadas del core de `OpenGL` generado.

Para hacer uso del core de `OpenGL`, debemos cumplir con dos pasos: 

* Indicarle a `GLFW` que debe ejecutarse en mode core:

```c++
bool initGLFW(){

	if (!glfwInit()){

		glfwTerminate();
		return false;

	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// ...

}
```

* Cargar las funcionalidades:

```c++
bool initCore(){

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED){

		glfwTerminate();
		return false;

	}

	// ...

	return true;
}
```

Es muy importante que estos dos archivos sean agregados como archivos externos a nuestro proyecto en Visual Studio, ya que sino, nuestra aplicación no se ejecutará.

## ¿Clase shader o clase programa?

¡Muy buena pregunta!, es una pregunta que todos nos hacemos cuando nos enfrentamos por primera vez al `OpenGL` moderno, ya que para interactuar con el pipeline gráfico debemos hacerlo mediante shaders y mas ideal aún sería hacerlo mediante un módulo en `C++`, estan pregunta será respondida pronto, pero un segundo, antes de responderla en concreto ¿Qué es un shader?.

Pues un shader, lo podemos ver como un programa que se ejecuta en la unidad de procesamiento gráfico o GPU. Con ellos, el programador posee un control de las etapas programables del pipeline gráfico, pues cada shader es análogo a una etapa del mismo, esto es estandar en los principales APIs de programación de gráficos 3D que son `OpenGL` y `DirectX`. Es importante destacar que la salida de un shader, es la entrada de otro y asi sucesivamente hasta que los datos que viajan por el pipeline sean dibujados. `OpenGL` provee el uso de shaders donde cada uno posee funcionalidades diferentes y adicionalmente requiere que estos sean programados haciendo uso del lenguaje de shaders propio de `OpenGL` que es `GLSL` (OpenGL Shading Language). Los shaders que `OpenGL` provee son:

* Vertex Shader: También conocido como procesador de vertices, se encarga de llevar a cabo todas las operaciones sobre los vértices pertenecientes a los modelos que componen una escena dentro de una aplicación. Es una etapa obligatoria.

* Tessellation Shader: Estos shaders reciben los datos que provienen del vertex shader, en esta etapa la morfología de los objetos se describe mediante un nuevo tipo de dato denominado parches, estos parches son teselados por este shader, produciendo modelos de mayor resolución. Es una etapa opcional.

* Geometry Shader: El geometry shader se encarga de trabajar con las primitivas gráficas elementales directamente. En el, el programador tiene la potestad de crear nuevas primitivas antes de la etapa de rasterización. Representa una etapa adicional dentro del pipeline gráfico.

* Fragment Shader: En este shader es donde el programador tiene control total sobre cada uno de los fragmentos de la pantalla y toma la decisiones acerca de que color va a tener cada uno de ellos o de llevar a cabo un proceso de descarte.

* Compute Shader: Estos shaders fueron agregados a partir de la version 4.3 de `OpenGL`, como tal, no forman parte del pipeline gráfico. El principal proposito de los compute shaders es realizar calculo haciendo uso de bloques de hilos, tienen una finalidad muy similar a lo que son los APIs de programación paralela como `CUDA` u `OpenCL`.

Una vez que hayamos decidido cuales etapas se van a manejar haciendo uso de los shaders, debemos tomar cada uno de los programas escritos en `GLSL`, cargarlos en la aplicación a cada uno de ellos como un `string` de `C++`, compilarlos y adjuntarselos a un programa que será el que posteriormente enlazaremos dentro de nuestra aplicación para enviar los datos al pipeline gráfico.

Con esto, la respuesta a la pregunta es que nuestro clase debe llamarse `GLSLProgram`, porque `OpenGL` provee al programador de una variable del tipo `unsigned int` que es indice en GPU asociado a nuestro programa, el cual se va a encargar de crear la entrada de nuestros datos hacia el pipeline gráfico cuyas etapas estan controladas por los shaders que estan adjuntos a el.

* Ejemplo de inicialización de la clase `GLSLProgram`

```c++
void init(){
	
	CGLSLProgram *pGLSLProgram;
	pGLSLProgram = new CGLSLProgram();
	pGLSLProgram->loadFromFile("Assets/Shaders/basic.vert");
	pGLSLProgram->loadFromFile("Assets/Shaders/basic.frag");
	pGLSLProgram->createProgram();
	pGLSLProgram->loadUniformVariables();
	pGLSLProgram->loadAttributeVariables();

	// ...
	
}

```

* Ejemplo de uso de la clase `GLSLProgram`

```c++
void draw(){
	
	pGLSLProgram->use();

		// ...

	pGLSLProgram->unUse();

}
```

## La clase Buffer

En el `OpenGL` moderno, para llevar a cabo el proceso de rendering es obligatorio tener los datos en la unidad de procesamiento gráfico (GPU), para ello, se hace uso de porciones de memoria denominadas buffers y estos son utilizados desde el contexto del CPU mediante indices del tipo `unsigned int`, algunos de los principales buffers que se usan desplegar en `OpenGL` combinando sus funcionalidades son:

* Vertex Buffer Objects (VBOs): Representa un buffer en GPU que contiene los datos a ser renderizados.

* Vertex Array Objects (VAOs): Representa un arreglo VBOs en la GPU.

* Index Buffer Objects (IBOs): Representa un arreglo de indices en la GPU.

Por otro lado, existen formas de organizar nuestros datos haciendo uso de los buffers previamente mencionados para que el despliegue sea mas eficiente, algunas formas de organización son:

* Array of structures (AOS): La idea de los AOS consiste en ir creando bloques heterogeneos de datos (vértices, normales, coordenadas de textura etc.) en arreglos muy grandes que contienen estos bloques de forma consecutiva.

* Structure of Arrays (SOA): Los SOA hacen uso de los Vertex Array Objects (VAOs), se encargan de crear varios Vertex Buffer Objects (VBOs) homogeneos y se le asocian a los VAOs.

* Indexes structure of array (ISOA): En esta implementación consideramos un SOA pero adicionalmente, le incorporamos un Index Buffer Object (IBO), donde cada indice usado hace referencia a un dato en los distintos Vertex Buffer Objects que maneja el Vertex Array Object.

La clase Buffer, implementa un ISOA, por ende, garantiza un despliegue eficiente de los datos.

* Inicialización de la clase buffer

```c++
void init(){
	
	CBuffer *pBuffer = new CBuffer();
	pBuffer->fillBuffer(nBuffer::bufferId::VERTEXES_2D_BUFFER, 8, quadVerts);
	pBuffer->fillBuffer(nBuffer::bufferId::VERTEXES_INDEXES_BUFFER, 6, quadIndexes);

	// ...

}
```

* Despliegue usando la clase buffer

```c++

// Código en Scene.cpp

void draw(){
	
	pGLSLProgram->use();

		// ...

		pBuffer->draw();

	pGLSLProgram->unUse();

}

// Código en Buffer.cpp

void draw(){
	
	glBindVertexArray(mVao);
	glDrawElements(GL_TRIANGLES, mVBOSize[nBuffer::bufferId::VERTEXES_INDEXES_BUFFER], GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

```

## Bibliotecas para correr el código

* GLM
* GLFW
* OpenGL Loader Generator (Generar el core de OpenGL 4.3)