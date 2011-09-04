# Makefile 


CC= cc
CFLAG=-Wall -lm -DNDEBUG=1 -O3 `pkg-config --cflags gtk+-2.0 gmodule-2.0`
LDFLAG=-Wall -lm `pkg-config --libs   gtk+-2.0 gmodule-2.0`

PATH_OUT=../out
PATH_OBJ=../obj
PATH_INC=../inc
PATH_SRC=../src
PATH_TESTS=../tests

Production: clean init solaris

Tests: clean init test_meteo test_fichiers test_gestion_habitations test_ihm test_production test_consomation test_liste_evenement

test_meteo.o: $(PATH_TESTS)/test_meteo.c 
	$(CC) $(CFLAG) -c $(PATH_OBJ)/$<

test_fichiers.o: $(PATH_TESTS)/test_fichiers.c 
	$(CC) $(CFLAG) -c $(PATH_OBJ)/$<

test_ihm.o: $(PATH_TESTS)/test_ihm.c 
	$(CC) $(CFLAG) -c $(PATH_OBJ)/$<

test_gestion_habitations.o: $(PATH_TESTS)/test_gestion_habitations.c 
	$(CC) $(CFLAG) -c $(PATH_OBJ)/$<

test_production.o: $(PATH_TESTS)/test_production.c 
	$(CC) $(CFLAG) -c $(PATH_OBJ)/$<

test_consomation.o: $(PATH_TESTS)/test_consomation.c 
	$(CC) $(CFLAG) -c $(PATH_OBJ)/$<

meteo.o: $(PATH_SRC)/meteo.c $(PATH_INC)/meteo.h
	$(CC) $(CFLAG) -c $(PATH_OBJ)/$<

gestion_fichiers.o:$(PATH_SRC)/gestion_fichiers.c $(PATH_INC)/gestion_fichiers.h
	$(CC) $(CFLAG) -c $(PATH_OBJ)/$<

gestion_habitations.o:$(PATH_SRC)/gestion_habitations.c $(PATH_INC)/gestion_habitations.h
	$(CC) $(CFLAG) -c $(PATH_OBJ)/$<

ihm_general.o:$(PATH_SRC)/ihm_general.c $(PATH_INC)/ihm_general.h
	$(CC) $(CFLAG) -c $(PATH_OBJ)/$<

production.o: $(PATH_SRC)/production.c $(PATH_INC)/production.h
	$(CC) $(CFLAG) -c $(PATH_OBJ)/$<

consomation.o: $(PATH_SRC)/consomation.c $(PATH_INC)/consomation.h
	$(CC) $(CFLAG) -c $(PATH_OBJ)/$<

liste_evenement.o: $(PATH_SRC)/liste_evenement.c $(PATH_INC)/liste_evenement.h
	$(CC) $(CFLAG) -c $(PATH_OBJ)/$<

test_liste_evenement.o: $(PATH_TESTS)/test_liste_evenement.c 
	$(CC) $(CFLAG) -c $(PATH_OBJ)/$<

main.o: $(PATH_SRC)/main.c 
	$(CC) $(CFLAG) -c $(PATH_OBJ)/$<

test_meteo: test_meteo.o meteo.o
	$(CC) $(LDFLAG) -o $(PATH_OUT)/$@ $^

test_fichiers: test_fichiers.o gestion_fichiers.o
	$(CC) $(LDFLAG) -o $(PATH_OUT)/$@ $^

test_gestion_habitations: test_gestion_habitations.o gestion_habitations.o gestion_fichiers.o
	$(CC) $(LDFLAG) -o $(PATH_OUT)/$@ $^

test_ihm: test_ihm.o gestion_habitations.o gestion_fichiers.o  production.o meteo.o consomation.o liste_evenement.o ihm_general.o 
	$(CC) $(LDFLAG) -o $(PATH_OUT)/$@ $^

test_production: test_production.o production.o meteo.o
	$(CC) $(LDFLAG) -o $(PATH_OUT)/$@ $^

test_consomation: test_consomation.o consomation.o
	$(CC) $(LDFLAG) -o $(PATH_OUT)/$@ $^

test_liste_evenement:test_liste_evenement.o meteo.o production.o consomation.o gestion_fichiers.o liste_evenement.o 
	$(CC) $(LDFLAG) -o $(PATH_OUT)/$@ $^

solaris:main.o gestion_habitations.o gestion_fichiers.o  production.o meteo.o consomation.o liste_evenement.o ihm_general.o
	$(CC) $(LDFLAG) -o $(PATH_OUT)/$@ $^

clean:
	-rm *.o
	-rmdir -R ../obj/*
	-rmdir -R ../out/*
	
init:
	-mkdir ../obj/
	-mkdir ../out/
