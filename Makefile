CC = gcc

CFLAGS = -Wall -Wextra -I./src/lib/cjson
LDFLAGS = -lcurl

SRC = src/main.c src/lib/cjson/cJSON.c
OBJ = $(SRC:.c=.o)

TARGET = bin/speedtest

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p bin
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)