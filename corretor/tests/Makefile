all: formula.o tp.o
	@gcc formula.o tp.o -o exe
	@rm formula.o tp.o

formula.o: ../formula.c
	@gcc -c ../formula.c -I.. -Wall

tp.o: ../tp.c
	@gcc -c ../tp.c -I.. -Wall

run:
	@./exe

clean:
	@rm -f exe *.o output.out