all: entrada.o mostrar.o play.o preencher.o respostas.o sorteios.o
	gcc entrada.o mostrar.o play.o preencher.o respostas.o sorteios.o main.c -o main

entrada.o: funcoes.h
	gcc -c entrada.c
mostrar.o: funcoes.h
	gcc -c mostrar.c
play.o: funcoes.h
	gcc -c play.c
preencher.o: funcoes.h
	gcc -c preencher.c
respostas.o: funcoes.h
	gcc -c respostas.c
sorteios.o: funcoes.h
	gcc -c sorteios.c

