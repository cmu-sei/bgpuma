
CC=g++
DEBUG=-g
CPPFLAGS=$(CFLAGS)
LFLAGS=-Wall $(DEBUG)
LIBS=-lsilk -lbgpdump -lbz2 -lz
INCLUDEDIR=-I /usr/local/include/ -I ../bgpdump/
LIBDIR=-L/usr/local/lib  -L../bgpdump/
CFLAGS=$(DEBUG) -Wall $(INCLUDEDIR)



all: bgpuma
SRCS=data.cpp main.cpp createset.cpp dates.cpp dir.cpp readasnfile.cpp readdir.cpp readfile.cpp readfiles.cpp

OBJ=data.o main.o createset.o dates.o dir.o readasnfile.o readdir.o readfile.o readfiles.o


%.o: %.c %.cpp
	$(CC) $(CFLAGS) $(INCLUDEDIR) -c $< $(DEBUG) -o $@

bgpuma: $(OBJ)
	$(CC) $(CFLAGS) $(LIBDIR) $(LIBS) $(OBJ) -o bgpuma 

clean:
	rm -f bgpuma *.o
