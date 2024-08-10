#!/bin/bash

if [ "$#" -ne 1 ]
then
    echo "MISSING ARGUMENT: path for values to insert in log"
    exit 1
fi

database="database.txt"
data="$1"
count=0
lines=()
insert="./dist/set"
retrieve="./dist/get"

make

# Check if database file exists if not then create
if [ ! -e "$database" ]; then
    touch "$database"
fi

# iterate through values and insert into database using key as id number
while IFS= read -r value
do
    "$insert" "$count" "$value"
    ((count++))
done < "$data"

# get the values back using the same count
for ((i=0; i<count; i++))
do
    "$retrieve" "$i"
done

# remove files by using makefile
make clean
