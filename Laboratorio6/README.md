# Laboratorio 6

En este laboratorio se pretende mejorar las tecnicas de programacion en C y aprender colas y punteros a funciones. Para ello se trabaja con dos ejercicios, uno para cada tema. El primer ejercicio consiste en realizar una cola a partir de una lista enlazada y el segundo en trabjar con un array de usuarios y su informacion.

## Ejercicio 1 colas.c
Este ejercicio consiste en realizar una cola de prioridad. Las colas de prioridad son de gran uso en diversas aplicaciones para ejecutar problemas. Se implemento una cola donde el ultimo elemento es el de mayor prioridad. Para ello se efectuaron operaciones como insertar un nuevo nodo, eliminar el nodo de mayor prioridar e imprimir la lista.

## Ejercicio 2 callback.c
Para el segundo ejercicio relacionado a punteros a funciones se trabaja con un array de usuarios que contiene nombre, ID y año de ingreso, para luego implementar funciones que ordenen el array segun cada parametro o filtren los usuarios segun cuantos años lleva de haber ingresado.

## Ejecucion

Para ejecutar los programas descritos anteriomente, se tiene un Makefile donde unicamente se debe cambiar el OBJFILES para correr uno o el otro, el nombre se encuenta comentado para mayor facilidad. Cabe aclarar que al utilizar el Makefile con callback.c se presenta un warning relacionado a los corchetes del array, este warning no es ningun error propio del codigo ya que ejecuta de manera correcta, pero mas bien un problema dado por GCC.