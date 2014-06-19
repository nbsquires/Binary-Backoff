#!/bin/bash
#Author: Natasha Squires
#Title: backoff.sh
#Just a script to run backoff.c a bunch of times. I just used this to help build my data sets, so
#don't worry too much about this.

file="./results.dat"

echo runs?
read runs

echo workload?
read workload

let n=$runs
echo bin >> $file
while [ $n -gt 0 ]
do
./backoff $workload 'bin'
let n--
done

let n=$runs

echo fib >> $file
while [ $n -gt 0 ]
do
./backoff $workload 'fib'
let n--
done

exit 1
