##############################################################################
# DON'T NEED TO MODIFY
##############################################################################

CC=gcc -m32
CFLAGS= -Wall
LIBS=-lpthread

FILES = Makefile csapp.h csapp.c proxy.c http.c

PROGS = proxy http

all: $(PROGS)

proxy: proxy.c csapp.o csapp.h
	$(CC) $(CFLAGS) $(LIBS) -o proxy proxy.c csapp.o

http: http.c csapp.o csapp.h
	$(CC) $(CFLAGS) $(LIBS) -o http http.c csapp.o

csapp.o: csapp.c csapp.h
	$(CC) $(CFLAGS) -c csapp.c

clean:
	rm -f *.o *~ *.tar
	rm -f $(PROGS)
