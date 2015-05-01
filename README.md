![Logo](http://190.169.70.132/wp-content/uploads/2014/06/logo1.jpg)

El objetivo principal de la elaboración de este tutorial es guiar a los estudiantes de la materia Fundamentos y Técnicas Computación Gráfica de la Universidad Central de Venezuela para el desarrollo de sus proyectos, aportando plantillas de proyecto y tips de importancia para el desarrollo rápido de los mismos. Este tutorial podria ser util a estudiantes de otras universidades o cualquier persona interesada en aprender conocimientos intermedios/avanzados de OpenGL.

A lo largo del tutorial se usará `C++` y las siguientes bibliotecas: 
* [OpenGL Core Generator](https://bitbucket.org/alfonse/glloadgen/wiki/Home) (Generador del core de OpenGL) Es un generador de un core de OpenGL especifico con sus respectivas extensiones, esta escrito en el lenguaje de programación LUA.

* [GLFW](http://www.glfw.org/) (Biblioteca Gráfica Para Ventanas) es ligera y multiplataforma, permite crear ventanas con el contexto de OpenGL y manejar diversos eventos relacionados a estas.

* [AntTweakBar](http://anttweakbar.sourceforge.net/doc/) es una biblioteca escrita en `C/C++` que permite a los programadores agregar rápidamente una interfaz de usuario gráfica en las aplicaciones basadas en OpenGL o DirectX.

* [GLM](http://glm.g-truc.net/0.9.6/index.html) (OpenGL Matemáticas) unicamente para  `C++`, provee diversas estructuras matemáticas y sus respectivas operaciones basadas en las de GLSL.

* [DevIL](http://openil.sourceforge.net/) (Biblioteca para la carga de imágenes) Biblioteca escrita en `C++`, se usara para cargar las texturas necesarias a aplicar en los proyectos.

### Configuración de proyectos usando Microsoft Visual Studio 2013

Todos estos códigos se deben correr en Microsoft Visual Studio 2013 siguiendo los aspectos de configuración.

### Configuración de librerias adicionales

+ Ir a: Project Properties -> C/C++ -> General -> Aditional Include Directories.
+ Pegar: $(ProjectDir)\Assets\Libraries;

### Configuración del enlazador del proyecto

+ Ir a: Project Properties -> Linker -> Input -> Additional Library Directories.
+ Pegar: $(ProjectDir)\Assets\Libs;

+ Ir a: Project Properties -> Linker -> Input -> Additional Dependencies.
+ Pegar: OpenGL32.lib;glfw3dll.lib;AntTweakBar.lib;ILU.lib;ILUT.lib;DevIL.lib;

#### Aspectos importantes
+ En la carpeta Assets\Libs deben encontrarse todos los libs especificados anteriormente menos el OpenGL32.lib.

+ Todos las librerias de enlace dinámico `DLL` deben colocarse en la carpeta Debug específicamente al lado del ejecutable.

### Formato para la entrega de proyectos

* TODO