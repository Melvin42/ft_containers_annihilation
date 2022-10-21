#!/bin/bash

for i in *.cpp
do
	mv $i $(echo $i | sed "s/.cpp/.hpp/g")
done
