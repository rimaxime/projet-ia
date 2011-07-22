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

Tests: clean init test_meteo test_fichiers

test_meteo.o: $(PATH_TESTS)/test_meteo.c 
	$(CC) $(CFLAG) -c $(PATH_OBJ)/$<

test_fichiers.o: $(PATH_TESTS)/test_fichiers.c 
	$(CC) $(CFLAG) -c $(PATH_OBJ)/$<

meteo.o: $(PATH_SRC)/meteo.c $(PATH_INC)/meteo.h
	$(CC) $(CFLAG) -c $(PATH_OBJ)/$<

gestion_fichiers.o:$(PATH_SRC)/gestion_fichiers.c $(PATH_INC)/gestion_fichiers.h
	$(CC) $(CFLAG) -c $(PATH_OBJ)/$<

test_meteo: test_meteo.o meteo.o
	$(CC) $(LDFLAG) -o $(PATH_OUT)/$@ $^

test_fichiers: test_fichiers.o gestion_fichiers.o
	$(CC) $(LDFLAG) -o $(PATH_OUT)/$@ $^



clean:
	-rm *.o
	-rm -R ../obj/*
	-rm -R ../out/*
	
init:
	-mkdir ../obj/
	-mkdir ../out/
