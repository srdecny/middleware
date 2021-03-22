#!/bin/bash

export CLASSPATH=../
edgeCounts=(10 100 500 1000 5000 10000 25000 50000)
for c in ${edgeCounts[@]}; do
    java -Xss128m Main $c $1 > $2/$c.csv
    echo $c finished
done