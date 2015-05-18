# Capitulo III - Mapas de sombra

## Introducción

Los recientes avances en computación grafica han producido un conjunto de técnicas de dibujado que producen efectos de iluminación y sombras muy realistas. `OpenGL` se puede usar para implementar casi todos los efectos. En este capítulo, vamos a cubrir una de las técnicas más populares para la simulación de sombras, conocida como mapas de sombra (en inglés `shadow mapping`) que provee una solución al dibujado de sombras.

## ¿Qué es Shadow Mapping?

Es una técnica que fue propuesta por Lance Williams en 1978 que tiene dos pasadas y usa texturas de profundidad para proveer una solución al dibujado de sombras.

En la primera pasada, la escena se dibuja desde el punto de vista de la fuente de luz, la información de profundidad es almacenada en una textura denominada mapa de sombra (shadow map), que va a proveer de información acerca de la visibilidad de los objetos desde la perspectiva de la fuente de luz, Así, para cada punto de la escena que tenga valores de profundidad más cercanos a la fuente de luz de los que tiene almacenados el mapa de sombras estarán iluminados, de lo contrario se encontrarán en sombra.

En la segunda pasada, la escena es dibujada normalmente, pero la profundidad de cada fragmento debe ser primero comparada contra el mapa de sombras para determinar si está o no en sombra. El fragmento entonces será coloreado de una forma diferente dependiendo del resultado de la prueba. Si el fragmento está en sombra entonces, se va a colorear únicamente con el color de la luz ambiental, en caso contrario se va a colorear de una forma normal.

Problemas que posee la técnica de Shadow Mapping

Los principales problemas que tienen los mapas de sombras yacen en el acné de sombra (en inglés `shadow acne`) que representa una fluctuación entre los pixeles que se encuentran iluminados y los que se encuentran en sombra por falta de precisión de la aritmética punto flotante al consultar los valores de profundidad almacenados en la textura. Por otro lado, está el `aliasing` que hace que la sombra no tenga bordes lisos sino escalonados.

## Aspectos teóricos

Antes de entrar en detalles de implementación, es importante que tengamos presente cuales herramientas vamos a utilizar para llevar a cabo nuestra implementación de los mapas de sombras. Ellas son:

* Renderbuffer Objects (RBOs): También llamados buffer de imagen, son aquellos que contienen información sobre una imagen y su formato, adicionalmente es administrado de forma eficiente por `OpenGL`. La información que manejan los Renderbuffer objects toma sentido cuando estos se unen a los Framebuffer Object (FBO) con la finalidad de minimizar la copia de datos y optimizar el rendimiento, es importante que el formato que va a manejar el buffer de imagen coincida con lo que OpenGL espera dibujar en su interior. Por ejemplo, no tiene sentido que en un Renderbuffer object que almacena información de color almacenemos información acerca de la profundidad de una escena.

* Framebuffer Objects (FBOs): Los framebuffer objects son aquellos que almacenan la información de dibujado en una textura. Un aspecto importante es que el único FBO que puede visualizar el usuario es el que se provee por defecto por el sistema manejador de ventana (en nuestro caso `GLFW`), todos aquellos FBOs que se creen en nuestra aplicación no podrán ser desplegados directamente en el monitor, ya que ellos solo tienen soporte al dibujado fuera de pantalla (en inglés off-screen rendering). Otra diferencia entre el framebuffer que provee el sistema de ventanas y los framebuffers que se crean dentro de la aplicación, yace en que el que es controlado por el sistema manejador de ventanas reserva internamente sus propios buffers (color, profundidad y stencil) cuando una ventana es creada. Cuando en la aplicación se crean FBOs, se deben crear Renderbuffers objects adicionales que se deben asociar con un FBO para especificar lo que va almacenar. Los buffers que provee el sistema manejador de ventana nunca podrán ser asociados con los que están asociados a un FBO creado en la aplicación y viceversa.

## Aspectos de implementación

Para implementar la técnica de shadow mapping, debemos cumplir con tres pasos de configuración antes de realizar el proceso de dibujado de la escena, ellos son:

* Crear el Framebuffer object (FBO) que almacenará información acerca de la profundidad que tendrá cada punto de la escena desde la perspectiva de la fuente de luz. Esto lo llevaremos a cabo en la clase `CFramebufferShadow`.

```c++

void CFramebufferShadow::init(const GLuint nWidth, const GLuint nHeight){

	mWidth = nWidth;
	mHeight = nHeight;
	
	// <-- Framebuffer texture init --> //

	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	
	// ...

	glBindTexture(GL_TEXTURE_2D, 0);

	// <-- Framebuffer init --> //

	glGenFramebuffers(1, &mFramebuffer);
	glBindFramebuffer(nFramebuffer::targets::DEFAULT_TARGET, mFramebuffer);
	
	// ...

	glBindFramebuffer(nFramebuffer::targets::DEFAULT_TARGET, 0);

}

```

* En el método `init()` de la clase `CScene`, se debe inicializar el `FBO` que almacena la información de profundidad con sus respectivas dimensiones, así como una  matriz de proyección que almacenará la perspectiva que se tendrá desde la fuente de luz distinta a la que se usa normalmente para desplegar una escena.

```c++

void CScene::init(){

	// ...

	// <-- Framebuffer shadow init --> //

	nScene::gpFramebufferShadow = new CFramebufferShadow();
	nScene::gpFramebufferShadow->init(4096, 4096);

	// <-- Init matrices --> //

	nScene::gLightProjectionMatrix = perspective(50.0f, 1.0f, 0.1f, 1000.0f);

}

```

* Inicializar una `matriz de BIAS`, esto porque el espacio de pantalla se expresa en pares ordenados que varían de `(-1,1)` para todo (x,y), estos deben ser llevados al rango `(0,1)`, pues para cada punto del espacio de pantalla debemos muestrear la textura de profundidad. La `matriz de BIAS` será una matriz de 4x4 y tendrá como transformaciones afines una traslación de 0.5 y escalamiento de 0.5 para llevar a cabo dicha conversión.

```c++

void CScene::init(){

	// ...

	// <-- Init matrices --> //

	// ...

	nScene::gBiasMatrix = scale(translate(mat4(1.0), vec3(0.5, 0.5, 0.5)), vec3(0.5, 0.5, 0.5));

}

```

* Crear e implementar métodos `drawShadows` y `drawShadowMapping` de la clase `CScene`. En el método `drawShadows` se debe llevar a cabo el proceso iterativo de por cada fuente de luz y por cada mallado construir la `matriz de sombra` y llamar al método de despliegue `drawShadowMapping`, que será el encargado de acumular la profundidad dentro del `CFramebufferShadow`.

```c++

// En Main.cpp

void mainLoop(){

	while (!glfwWindowShouldClose(nMain::gpWindow) && !glfwGetKey(nMain::gpWindow, GLFW_KEY_ESCAPE)){

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		updateApp();

		// Primera pasada, método de dibujado de sombras

		nMain::gpScene->drawShadows(); 

		// Segunda pasada, método de dibujado común

		nMain::gpScene->draw();

		TwDraw();

		glfwSwapBuffers(nMain::gpWindow);
		glfwPollEvents();

	}

}

// En Scene.cpp

void CScene::drawShadows(){

	// TODO
		
}

void CScene::drawShadowMapping(const GLint nActualMesh){

	mGLSLProgram[nScene::GLSLProgram::SHADOW_MAPPING]->use();

		// ...

		mMeshes[nActualMesh]->draw();

	mGLSLProgram[nScene::GLSLProgram::SHADOW_MAPPING]->unUse();

}

```

El proceso de dibujado por pasada se llevará a cabo de la siguiente forma:

* Primera pasada

	* Configurar el viewport y la matriz de vista acordes a la fuente de luz.
	* Enlazar el framebuffer que almacenará la información de profundidad.
	* Limpiar el buffer de profundidad.
	* Habilitar front-face culling.
	* Dibujar la escena (sin un algoritmo de sombreado en el vertex o fragment shader).

* Segunda pasada

	* Configurar el viewport, la matriz de vista y de proyección acordes al ojo.
	* Desenlazar el framebuffer que almacena la información de profundidad.
	* Activar back-face culling.
	* Dibujar la escena con los respectivos algoritmos de sombreado.
