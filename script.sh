#-----Script Bash-----#
#   @brief It compilates the tests files (or a concrete one if indicated). Mode 0 without valgrind, Mode 1 with valgrind
#   @file script.sh
#   @author Paula de la Fuente
#   version: 1
#   Date: 20-04-2026
#   @copyright GNU Public License


#!/bin/bash



#argumento 0 -> script.sh
#argumento 1 -> $1 si es 0 -> make without valgrind || si es 1 -> make valgrind
#argumento 2 -> $2 (opcional) specific test which will be executed || if these argument is not there -> execute all tests

#  -> $# número de argumentos introducidos
#  -> -lt es menor
#  -> -eq es igual


#Variables -> luego usar con el $ delante
modo=$1  #0=normal || 1 =valgrind
test=$2 #si existe -> fichero concreto || si no todos
numArgs=$# #(argument 0 doesn't count)
alltests="spacetest settest charactertest linktest inventorytest objecttest playertest"

make clean

#Check that there're the minimum arguments
if [ $numArgs -lt 1 ]; then
    echo "Error. Few arguments: $0 <mode(0 or 1)> <test(optional)>"
    exit 1
fi

#CASO 1 -> ALL the tests (only one argument)
if [ $numArgs -eq 1 ]; then
    #Caso 1.0 -> make without valgrind (mode 0)
    if [ $modo -eq 0 ]; then
        make alltests #makes all tests
        make runtests 

        exit 0
    fi

    #Caso 1.1 -> make valgrind (mode 1)
    if [ $modo -eq 1 ]; then
        for i in $alltests #go through all the tests
            do
                make $i
                valgrind ./$i
            done

        exit 0
    fi
fi

#CASO 2 -> ONE concrete test (two arguments)
if [ $numArgs -eq 2 ]; then
    #Caso 2.0 -> make without valgrind (mode 0)
    if [ $modo -eq 0 ]; then
        make $test
        ./$test

        exit 0
    fi

    #Caso 2.1 -> make valgrind (mode 1)
    if [ $modo -eq 1 ]; then
        make $test
        valgrind ./$test

        exit 0
    fi
fi





