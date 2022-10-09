
INCLUDE_DIR = inc
SOURCE_DIR = src
OBJ_DIR = output/obj

#HEADERS = $(INCLUDE_DIR)/%.h
#OBJS = $(OBJ_DIR)/%.o

CC = gcc
GCC_FLAGS = -I$(INCLUDE_DIR) -Wall -ggdb -std=gnu11
LD_FLAGS = -pthread

SOURCES = src/main.c
SOURCES += src/probe-model.c

all: output/rover

output/rover: $(SOURCES)
	$(CC) $(GCC_FLAGS)  $^ -o $@ $(LD_FLAGS)



