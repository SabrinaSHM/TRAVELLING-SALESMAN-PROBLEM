CC = gcc
CFLAGS = -Wall -Wfatal-errors -ansi
LDFLAGS = -lMLV -lm
OBJ = main.o ville.o visite.o calculs.o fichier.o carte.o


PVC: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	make clean


main.o: main.c ville.h visite.h calculs.h fichier.h carte.h

ville.o: ville.c ville.h

visite.o: visite.c visite.h ville.h calculs.h

calculs.o: calculs.c calculs.h visite.h

fichier.o: fichier.c fichier.h ville.h carte.h visite.h

carte.o: carte.c carte.h visite.h fichier.h calculs.h


%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f *.gch