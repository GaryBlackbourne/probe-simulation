INCLUDE_DIR = inc
SOURCE_DIR = src
OBJ_DIR = output/obj

#HEADERS = $(INCLUDE_DIR)/%.h
#OBJS = $(OBJ_DIR)/%.o

CC = g++
GCC_FLAGS = -I$(INCLUDE_DIR) -Wall -ggdb -std=c++20
LD_FLAGS = -pthread

SOURCES = src/main.cpp
SOURCES += src/probe-model.cpp
SOURCES += src/pwr-mngr.cpp
SOURCES += src/battery.cpp
SOURCES += src/solar-panel.cpp

all: output/rover

output/rover: $(SOURCES)
	$(CC) $(GCC_FLAGS)  $^ -o $@ $(LD_FLAGS)



