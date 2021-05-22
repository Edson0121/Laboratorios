#!/bin/bash
#clear

# Primero se debe extraer el contenido del comando ps 
# aux y redirigirlo a un archvio procesos
# Para ello se ejecuta el comando ps aux y se utiliza > para 
# redirigr a un archivo creado llamado procesos
ps aux > procesos.txt

# Para parsear el contenido de procesos y extraer la columna %MEM y 
# la command, se utiliza el comando awk que en grosso modo busca en archivos
# por una caracteristica especificada y ejecuta una accion al hallarla.
# Luego se redirigen las columnas a un archivo memoria.txt
cat procesos.txt | awk '{print $4 " " $11}' > memoria.txt

# Se guarda en valoresMemoria solo la columna de %MEM eliminado esta primera 
# fila que no es un valor
valoresMemoria=$(cat memoria.txt | awk '$1 !~ /^%MEM/{print $1}')

# Se crea un array a partir de los valores de la variable valoresMemoria
arrayValores=( $valoresMemoria )

# Se crea una variable que alamcene el valor maximo
maxMemoria=0.0

for i in "${arrayValores[@]}"; do # Se recorre el array
    if (( ${i%.*} > ${maxMemoria%.*} || ( ${i%.*} == ${maxMemoria%.*} && ${i#*.} > ${maxMemoria#*.} ) )); then # Se compara parte entera y parte decimal
        maxMemoria=$i # Se almacena el valor de maxima memoria
    fi
done

# Se utiliza awk para hallar el valor de maxima memoria en memoria.txt 
# y se imprime toda la linea.
dispositivo=$(cat memoria.txt | awk -v pat="$maxMemoria" '$1 ~ pat {print $0}')

# Se muestra en terminal lo que conusume mayor memoria.
echo $dispositivo