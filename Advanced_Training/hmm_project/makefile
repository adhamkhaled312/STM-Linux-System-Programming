CC=gcc
LIBNAME=libhmm


static: $(LIBNAME).a

dynamic: $(LIBNAME).so

$(LIBNAME).a: hmm.o list.o
	ar -rs $@  $^

hmm.o: hmm.c
	$(CC) -c $^

list.o: list.c
	$(CC) -c $^

$(LIBNAME).so: hmmdyn.o listdyn.o
	$(CC) -shared -o $@ $^

hmmdyn.o: hmm.c
	$(CC) -c -fPIC $^ -o $@ 
listdyn.o: list.c
	$(CC) -c -fPIC $^ -o $@ 

clean:
	rm -f hmm.o list.o hmmdyn.o listdyn.o
