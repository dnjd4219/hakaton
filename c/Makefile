CC = gcc
CFLAGS = `pkg-config --cflags --libs gtk+-2.0` -I/usr/include/mysql -lmysqlclient
TARGET = main
OBJECTS = dbconn.o window.o
SRCS = dbconn.c window.c

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(OBJECTS)

clean:
	rm *.o main

dbconn.o: dbconn.c dbconn.h
window.o: window.c dbconn.h
