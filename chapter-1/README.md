# Capitulo I - El comienzo

En este capítulo se explicaran diversos aspectos básicos de como trabajar con una estructura de proyecto en computación gráfica, se explicará el uso del core de `OpenGL` con sus ventajas con respecto a la biblioteca `GLEW`, el uso de una clase `GLSLProgram` que se encargará de manejar de forma generica los distintos shaders escritos en el lenguaje `GLSL` asociados a cada etapa programable del pipeline gráfico y el uso de la clase `Buffer` que se encarga de llevar a cabo el proceso de rendering en el `OpenGL` moderno haciendo uso de Vertex Buffer Objects (VBOs) y Vertex Array Objects (VAOs).

## ¡Llegamos a Fundamentos y Técnicas!

Muchos al llegar a esta materia tenemos ciertas interrogantes con respecto a lo aprendido en Introducción a la Computación Gráfica como cuando hablaron de VBOs, VAOs, Shaders etc. ¿Qué es en concreto todo esto? ¿Para que los uso? ¿Como lo uso?, ¡TENGO QUE APRENDER TODO YA!, pues les participo que tengan calma, todo a su tiempo, todo lo veremos con detenimiento para ir cubriendo cada interrogante que pueda haber quedado con respecto al final de la primera materia de esta interesante rama de las ciencias de la computación.

Un aspecto importante de esta materia es que trabajaremos absolutamente todo haciendo uso de las ultimas funcionalidades de `OpenGL`, es decir, ya a nuestro nivel como programadores gráficos debemos entender el concepto de la GPU y como podemos representar las etapas programables del pipeline gráfico mediante los distintos tipos de shaders y aprovecharlos al máximo como herramienta. Con esto ya debemos olvidar los famosos:

* ¡La vieja forma de despliegue!

```c++
glBegin(GL_TRIANGLES, GL_POINTS ...)

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

Cada vez que en nuestro proyecto vayamos a requerir de variables globales, enumerados, namespaces, clases y sus respectivos atributos etc. lo ideal siempre será tener un formato para asi asociar rápidamente lo que queremos programar, en esta parte lógica les presento algunas buenas prácticas:

* Namespaces (Espacios de nombre): Los usaremos para almacenar enumerados, variables globales, etc. propios de un módulo. Cuando nos vayamos a referir a un namespace el nombre de este debe comenzar con el prefijo `n`. Adicionalmente, cuando declaramos un nuevo módulo en `C++` y este requiere de un namespace, debemos declararlo dos veces, una en el archivo de cabecera `.h` y el otro en nuestro `.cpp` de la siguiente manera:

	* Ejemplo de namespace `nMain` para un archivo `.h`:
```c++
namespace nMain{
	extern vec3 gEyePosition;

	// ...
};
```
	* Ejemplo de namespace `nMain` para un archivo `.cpp`:
```c++
namespace nMain{
	vec3 gEyePosition;

	// ...	
};
```

## El core de OpenGL

## ¿Clase shader o clase programa?

## La clase Buffer