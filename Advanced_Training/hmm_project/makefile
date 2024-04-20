static: libhmm.a

dynamic: libhmm.so

libhmm.a: hmm.o list.o
	ar -rs libhmm.a hmm.o list.o

hmm.o: hmm.c
	gcc -c hmm.c

list.o: list.c
	gcc -c list.c

libhmm.so: hmmdyn.o listdyn.o
	gcc -shared -o libhmm.so hmmdyn.o listdyn.o
	export LD_LIBRARY_PATH=./

hmmdyn.o: hmm.c
	gcc -c -fPIC hmm.c -o hmmdyn.o
listdyn.o: list.c
	gcc -c -fPIC list.c -o listdyn.o

clean:
	rm *.o
