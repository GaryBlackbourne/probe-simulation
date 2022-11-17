
INCLUDE_DIR = inc
INCLUDE_JSON_DIR = /home/geri/dev/json/single_include
SOURCE_DIR = src

OBJ_DIR = output/obj

HTTPSERVER_LIB = /usr/local/lib

#HEADERS = $(INCLUDE_DIR)/%.h
#OBJS = $(OBJ_DIR)/%.o

CC = g++
GCC_FLAGS = -I$(INCLUDE_DIR)
GCC_FLAGS += -I$(INCLUDE_JSON_DIR)
GCC_FLAGS += -Wall
GCC_FLAGS += -ggdb
GCC_FLAGS += -std=c++20

LD_FLAGS = -pthread
LD_FLAGS += -L$(HTTPSERVER_LIB)
LD_FLAGS += -lhttpserver

SOURCES = src/main.cpp
SOURCES += src/probe-model.cpp
SOURCES += src/pwr-mngr.cpp
SOURCES += src/battery.cpp
SOURCES += src/solar-panel.cpp

all: output/probe

output/probe: $(SOURCES)
	$(CC) $(GCC_FLAGS)  $^ -o $@ $(LD_FLAGS)



