#!/bin/bash

# Compilar tu programa (ajusta el nombre de archivo y el compilador según sea necesario)
g++ ejercicio3.cpp -o e3  # Cambia 'e2.cpp' al nombre de tu archivo de código fuente

# Verificar si la compilación fue exitosa
if [ $? -ne 0 ]; then
    echo "Error en la compilación."
    exit 1
fi

# Definir la ruta de los archivos de entrada y salida
input_folder="tests/ejercicio3"
output_folder="outputs"  # Puedes cambiarlo a donde quieras guardar las salidas
expected_folder="tests/ejercicio3"  # Carpeta para las salidas esperadas

# Crear los directorios de salida si no existen
mkdir -p "$output_folder"
mkdir -p "$expected_folder"

# Definir los casos de prueba (números sin extensiones)
declare -a test_cases=("5_3" "10_3" "100_10" "200_30" "1000_10" "10000_100" "100000_300" "1000000_1000")  # Agrega más números según sea necesario

# Ejecutar cada caso de prueba
for number in "${test_cases[@]}"; do
    input_file="${number}.in.txt"  # Archivo de entrada
    input_path="$input_folder/$input_file"
    output_path="$output_folder/${number}.out.txt"  # Salida generada
    expected_path="$expected_folder/${number}.out.txt"  # Archivo de salida esperado

    # Ejecutar el programa con el archivo de entrada y redirigir la salida
    ./e3 < "$input_path" > "$output_path"

    # Verificar si la ejecución fue exitosa
    if [ $? -eq 0 ]; then
        echo "Caso de prueba: $input_file - Salida guardada en $output_path"

        # Comparar la salida generada con la salida esperada, ignorando espacios en blanco
        if diff -w -q "$output_path" "$expected_path" > /dev/null; then
            echo "  Salida CORRECTA"
        else
            echo "  Salida INCORRECTA"
            
        fi
    else
        echo "Error al ejecutar el caso de prueba: $input_file"
    fi
done