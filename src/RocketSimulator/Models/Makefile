CFLAGS = -std=c++17 -O2

FOLDER_PATH = ./src/RocketSimulator/Models
BUILD_PATH	= ./build/RocketSimulator/Models
#TODO PUT BUILD_PATH INTO THE .o file generation

SOURCES := $(shell find ./ -name '*.cpp')
OBJECTS = $(SOURCES:%.cpp=%.o)

%.o:%.cpp $(SOURCES)
	echo $(SOURCES)
	g++ $(CFLAGS)  $(INC) -c $< -o $@

genObj:$(OBJECTS)
	#ENDED Compilation of ./src/RocketSimulator/Models

