# Capitulo I

En este capítulo se explicaran diversos aspectos básicos de como trabajar con una estructura de proyecto en computación gráfica, se explicará el uso del core de ´OpenGL´ con sus ventajas con respecto a la biblioteca ´GLEW´, el uso de una clase ´GLSLProgram´ que se encargará de manejar de forma generica los distintos shaders escritos en el lenguaje ´GLSL´ asociados a cada etapa del pipeline gráfico y el uso de la clase ´Buffer´ que se encarga de llevar a cabo el proceso de rendering en el ´OpenGL´ moderno haciendo uso de Vertex Buffer Objects y Vertex Array Objects.

## Bueno, aqui estamos, ya llegamos a Fundamentos y Técnicas !! ...

Muchos al llegar a esta materia tenemos ciertas interrogantes con respecto a lo aprendido en Introducción a la Computación Gráfica como cuando hablaron de VBOs, VAOs, Picking etc. ¿Qué es en concreto todo esto? ¿Para que los uso? ¿Como lo uso?, ¡TENGO QUE APRENDER TODO YA!, calma todo a su tiempo, todo lo veremos con detenimiento para ir cubriendo cada interrogante que pueda haber quedado con respecto al final de la primera materia de esta interesante rama de las ciencias de la computación.

Un aspecto importante de esta materia es que trabajaremos absolutamente todo haciendo uso de las ultimas funcionalidades de ´OpenGL´, es decir, ya a nuestro nivel como programadores gráficos debemos entender el concepto de la GPU y como podemos representar las etapas programables del pipeline gráfico mediante los distintos tipos de shaders. Con esto debemos ya olvidar los famosos:

```c++
glBegin(GL_TRIANGLES, GL_POINTS . . .)

 // . . .

glEnd();
```

```c++
glMatrixMode(GL_MODELVIEW, GL_PROJECTION ...);
glLoadIdentity();

 // . . .

```

Esto por el cuello de botella que se forma entre el procesador y la unidad de procesamiento gráfico (GPU), que nos limita en explotar las grandes capacidades del hardware, adicionalmente esta no es la forma correcta de trabajar actualmente en computación gráfica, solo se utilizo para entender como desplegar de forma básica y como llevar a cabo las transformaciones a aplicar a los distintos datos mediante el uso de matrices.

## Estructura de un proyecto en Computación Gráfica

