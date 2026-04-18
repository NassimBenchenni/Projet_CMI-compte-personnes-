CC = g++
CFLAGS = --std=c++26 -Wall -Wextra
LIBFLAGS = -lssl -lcrypto -lsqlite3 -lpthread


FINAL = prog
SOURCES=$(wildcard *.cpp)

all: $(SRC_DIR)
	$(CC) $(CFLAGS) -o $(FINAL) $(SOURCES) $(LIBFLAGS)

test: $(FINAL)
	./$(FINAL)

clean:
	rm -f $(FINAL)