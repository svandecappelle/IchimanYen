#!/bin/bash

cd src
rm -r CMakeFile/
rm cmake_install.cmake Makefile CMakeCache.txt 

echo Install being process...
cmake ../
if [[ $? != 1  ]] ; then
    make
    if [[ $? != 1  ]] ; then
	echo
	echo Install sucessed
    else
	echo
	echo Install failed
    fi;

fi;
