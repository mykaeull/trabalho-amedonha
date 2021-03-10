target: main

main: main.o entrada.o mostrar.o play.o preencher.o respostas.o sorteios.o
	gcc main.o entrada.o mostrar.o play.o preencher.o respostas.o sorteios.o -o main

main.o: main.c funcoes.h
	gcc -c main.c
entrada.o: entrada.c funcoes.h
	gcc -c entrada.c
mostrar.o: mostrar.c funcoes.h
	gcc -c mostrar.c
play.o: play.c funcoes.h
	gcc -c play.c
preencher.o: preencher.c funcoes.h
	gcc -c preencher.c
respostas.o: respostas.c funcoes.h
	gcc -c respostas.c
sorteios.o: sorteios.c funcoes.h
	gcc -c sorteios.c

clean:
	rm -f *.o main