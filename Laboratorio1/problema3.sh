#!/bin/bash
#clear

# Primero se debe recibir de argumento el numero de bus
#Esto solo es texto pidiendole al usuario el numero de bus
echo "Por favor ingrese el numero de bus. Recuerde que es un numero de 3 digitos. Presione <CTRL>+C para salir"

# Este loop es con el objetivo de que si el usuario sigue dando un valor 
# incorrecto se le siga pidiendo. Se sale con CTRL+C
while true; do
    # El comando read pide al usuario un input y lo guarda en una variable
    read numBus
    # Se revisa que el numero de bus sea de 3 digitos.
    if [[ ${#numBus} -eq 3 ]]; then
        # Se utiliza el comando awk para buscar el bus, y en linea se agrega 
        # todo a partir de la columna 7 (nombre del dispositivo)
        linea=$(lsusb | awk -v pat="$numBus" '$2~pat{for(i=7;i<=NF;++i)printf $i ""FS ; print","}')
        # Se revisa si el valor de linea es vacio,
        # que implica que elbus ingresado no esta en el sistema
        if test -z "$linea"; then
            echo "El bus que ingreso no existe en el sistema, por favor trate de nuevo."
            continue # El continue es para seguir dentro del loop
        else # Si el valor de linea si contiene informacion, se imprime en terminal
            echo "Los dispositivos conectados en el bus son: $linea"
            break #Como ya se cumplio la salida, se sale del loop
        fi
    else # Esto es por si el valor ingresado difere de 3 digitos
        echo "Por favor ingrese un valor valido de bus. Recuerde que debe ser de 3 digitos. Ejemplo: 002."
        continue
    fi
done