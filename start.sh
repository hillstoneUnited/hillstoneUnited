#!/bin/sh

export LD_LIBRARY_PATH=./:/usr/local/lib/simspark

host=$1;
team=$2;

if [ -e $host ]; then
    host="localhost";
fi

if [ -e $team ]; then
    team="HillstoneUnited";
fi

a=0
while [ $a -ne 11 ]
do
    ./hillstoneUnited/hillstoneUnited --host=$host --team=$team &
    a=`expr $a + 1`
    sleep 0.4;
done
