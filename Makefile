CC = gcc

CFLAGS = -Wall -Wextra -I./src/lib/cjson -I./src/dataImporter -I./src/http -I./src/locationService -I./src/speedTest -I./src/helpers -I./src/bestServer
LDFLAGS = -lcurl

SRC = src/main.c src/lib/cjson/cJSON.c src/dataImporter/dataImporter.c src/http/httpClient.c src/locationService/locationService.c src/speedTest/speedTest.c src/helpers/helpers.c src/bestServer/bestServer.c
OBJ = $(SRC:src/%.c=obj/%.o)

TARGET = bin/speedtest

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p bin
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)