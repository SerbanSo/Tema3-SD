efile = movies
efile2 = labirint
ofile = movies.o graph.o list.o task3.o graphRead.o bonus.o binaryTree.o heap.o
ofile2 = labirint.o graph.o list.o stack.o graphRead.o heap.o

build: $(ofile) $(ofile2)
	gcc -Wall $(ofile) -o $(efile)
	gcc -Wall $(ofile2) -o $(efile2)
$@.o: $@.c $@.h
	gcc -c $@.c
clean:
	rm -f $(efile) $(ofile) $(efile2) $(ofile2)
