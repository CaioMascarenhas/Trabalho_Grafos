#!/bin/bash

# Loop para executar o programa com todos os grafos.
# Certifique-se de que o arquivo binário do bellman_ford (bellman_ford.bin) esteja na mesma pasta.
for i in {1..20}; do
    input_file="grafo${i}.mtx"
    output_file="output${i}.txt"
    expected_output_file="expected_output${i}.txt"
    
    echo
    echo "Executando para o grafo do arquivo : ${input_file}"
    echo
    
    ./bellman_ford.bin -f "${input_file}" > "${output_file}"
    
    # Comparar a saída com o gabarito.
    diff -q "${output_file}" "${expected_output_file}"
    
    if [ $? -eq 0 ]; then
        echo "Saída correta para o grafo ${i}."
    else
        echo "Saída incorreta para o grafo ${i}."
    fi
done
