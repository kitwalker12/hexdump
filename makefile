CC = g++
CFLAGS = -Wall -g

hw1 : hw1.o base64.o hexdump.o
        ${CC} ${CFLAGS} hw1.o base64.o hexdump.o -o hw1

hexdump.o : hexdump.cpp hexdump.h
        ${CC} ${CFLAGS} -c hexdump.cpp

base64.o : base64.cpp base64.h
        ${CC} ${CFLAGS} -c base64.cpp

hw1.o : hw1.cpp base64.h hexdump.h
        ${CC} ${CFLAGS} -c hw1.cpp