CFLAGS = -std=c++17 -O2
INC=-I ../headers/

FOLDER_PATH = ./src/RocketSimulator/
BUILD_PATH	= ../../build/engine/
BUILD_PATH_CORE	= ../../build/engine/core
#TODO PUT BUILD_PATH INTO THE .o file generation

SOURCES := $(shell find ./ -name '*.cpp')
OBJECTS = $(SOURCES:./%.cpp=$(BUILD_PATH)%.o)

createFolder:
	mkdir -p $(BUILD_PATH)
	mkdir -p $(BUILD_PATH_CORE)
	mkdir -p $(BUILD_PATH_CORE)/Device
	mkdir -p $(BUILD_PATH_CORE)/Drawing
	mkdir -p $(BUILD_PATH_CORE)/DrawingNew
	mkdir -p $(BUILD_PATH_CORE)/Geometry
	mkdir -p $(BUILD_PATH_CORE)/GraphicPipeline
	mkdir -p $(BUILD_PATH_CORE)/Objects
	mkdir -p $(BUILD_PATH_CORE)/Presentation
	mkdir -p $(BUILD_PATH_CORE)/Utils

$(BUILD_PATH)%.o:%.cpp $(SOURCES)
	g++ $(CFLAGS)  $(INC) -c $< -o $@

genObj:createFolder $(OBJECTS)
	#ENDED Compilation of ./src/engine

