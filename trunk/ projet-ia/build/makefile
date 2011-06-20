# Makefile 


CC= cc
CFLAG=-Wall -lm -DNDEBUG=1 -O3 
LDFLAG=-Wall -lm 

PATH_OUT=../out
PATH_OBJ=../obj
PATH_INC=../inc
PATH_SRC=../src
PATH_TESTS=../tests

Production: clean init 

Tests: clean init 



clean:
	-rm *.o
	-rm -R ../obj/*
	-rm -R ../out/*
	
init:
	-mkdir ../obj
	-mkdir ../out
