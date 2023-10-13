#!/bin/bash

# Binary Executables
prim=./prim.bin
kruskal=./kruskal.bin
dijkstra=./dijkstra.bin

echo "Testing Kruskal's Algorithm"
for i in instances/*.mtx
do
    echo -e "\e[33mInstance $i\e[0m";
    val=$($kruskal -f $i);
    correct=$(grep $i gabarito_agm.txt | cut -d ' ' -f 2);
    [ $val -eq $correct ] && echo -e "Cost \e[32mOK\e[0m" || echo -e "\e[31mIncorrect cost\e[0m";

    $kruskal -f $i -s | sed -e 's/ /\n/g' -e 's/,/ /g' -e 's/[()]//g' | ./agm $i
    if [ $? -eq 0 ]; then
        echo -e "\e[32mOK\e[0m"
    else
        echo -e "\e[31mNot a subgraph\e[0m";
    fi
done

echo -e "\n\n";

echo "Testing Prim's Algorithm"
for i in instances/*.mtx
do
    echo -e "\e[33mInstance $i\e[0m";
    val=$($prim -f $i);
    correct=$(grep $i gabarito_agm.txt | cut -d ' ' -f 2);
    [ $val -eq $correct ] && echo -e "Cost \e[32mOK\e[0m" || echo -e "\e[31mIncorrect cost\e[0m";

    $prim -f $i -s | sed -e 's/ /\n/g' -e 's/,/ /g' -e 's/[()]//g' | ./agm $i
    if [ $? -eq 0 ]; then
        echo -e "\e[32mOK\e[0m"
    else
        echo -e "\e[31mNot a subgraph\e[0m";
    fi
done

echo "Testing Dijkstra's Algorithm"
for i in instances/*.mtx
do
    echo -e "\e[33mInstance $i\e[0m";
    $dijkstra -f $i > temp;

    j=$(basename $i);
    diff -w temp ./sp/$j > /dev/null ;
    if [ $? -eq 0 ]; then
        echo -e "\e[32mOK\e[0m"
    else
        echo -e "\e[31mError\e[0m";
    fi
    rm temp;
done
