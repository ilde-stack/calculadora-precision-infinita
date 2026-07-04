CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
LDFLAGS = 
LDLIBS = 
TARGET = ent
OBJ = main.o bigint.o ops.o utils.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJ) $(LDLIBS)

main.o: main.c bigint.h
	$(CC) $(CFLAGS) -c main.c

bigint.o: bigint.c bigint.h
	$(CC) $(CFLAGS) -c bigint.c

ops.o: ops.c bigint.h
	$(CC) $(CFLAGS) -c ops.c

utils.o: utils.c bigint.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f $(OBJ) $(TARGET)