#!/bin/bash
#clear

# Se deben enviar comandos a un chip, el formato es el siguiente:
# Header [2 bytes] = 0x21 0x34, valores fijos
# # of Bytes to write [1 byte] = cantidad de datos a enviar
# Data [8 bytes] = valores a agregar
# Checksum [1 byte] = suma de todos los datos en el comando

# Primero, se va a leer el contenido del config.rom 

# El IFS define como se separan los valores y el read -a crea un array
while IFS="," read -a decimalArray; do
    for i in "${decimalArray[@]}"; do # Se recorre el array creado
        #Se crea un nuevo array con los valores en hexadecimal
        hexArray+=( "$( printf 'obase=16; %s\n' "$i" | bc )" )
    done
done < config.rom # Archivo que se lee

contador=0 # Contador de datos
COMMAND="0x21 0x34" # Header, es fijo para todo comando
checksum=0 # Suma de los bytes
for j in "${hexArray[@]}"; do # Se recorre el array de hexadecimales
    COMMAND+=" 0x${j}" # Se adjunta al string COMMAND cada valor del array de hexadecimales
    contador=$((contador+1)); # Se suma 1 al contador
    # Se revisa la condicion de que se lleve una cuenta de 8 datos
    if [ $contador -gt 7 ]; then
        # Se adjunta en la tercera columna la cantidad de datos
        COMMAND="${COMMAND:0:9} 0x$contador ${COMMAND:10}"
        # Se crea un array a partir del string COMMAND
        commandArray=( $COMMAND )
        # Se recorre el array command
        for k in "${commandArray[@]}"; do
            #  Se realiza la suma del commandArray y se guarda en la variable checksum
            printf -v checksum '%#X' "$((checksum + k))"
        done
        # Se adjunta el valor de checksum al COMMAND
        COMMAND+=" 0x${checksum: -2}"
        # Se redirige el contenido del COMMAND al archivo commands.txt
        echo $COMMAND >> commands.txt
        # Se reinicia el valor de las variables para un nuevo comando
        contador=0
        COMMAND="0x21 0x34"
        checksum=0
    fi
done

# Este if es por si la cantidad de datos es menor a 8 
if [ $contador -ne 0 ]; then
    # Se adjuntan los datos que se tengan
    COMMAND="${COMMAND:0:9} 0x$contador ${COMMAND:10}"
    commandArray=( $COMMAND )
    for k in "${commandArray[@]}"; do
        printf -v checksum '%#X' "$((checksum + k))"
    done
    COMMAND+=" 0x${checksum: -2}"
    echo $COMMAND >> commands.txt
fi
