#!/bin/bash

# Loop para executar o programa com todos os grafos.
for i in {1..20}; do
    input_file="grafo${i}.mtx"
    
    echo
    echo "Executando para o grafo do arquivo : ${input_file}"
    echo
    
    ./bellman_ford.bin -f "${input_file}"
done