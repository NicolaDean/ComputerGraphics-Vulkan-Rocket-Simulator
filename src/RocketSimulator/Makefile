CFLAGS = -std=c++17 -O2

FOLDER_PATH = ./src/RocketSimulator/
BUILD_PATH	= ../../build/RocketSimulator/
#TODO PUT BUILD_PATH INTO THE .o file generation

SOURCES := $(shell find ./ -name '*.cpp')
SOURCESMAC := $(SOURCES:.//%.cpp=./%.cpp)

OBJECTS = $(SOURCESMAC:./%.cpp=$(BUILD_PATH)%.o)

createFolder:
	mkdir -p $(BUILD_PATH)
	mkdir -p $(BUILD_PATH)/Models
	mkdir -p $(BUILD_PATH)/Utils
	mkdir -p $(BUILD_PATH)/Terrain
	mkdir -p $(BUILD_PATH)/Lights

$(BUILD_PATH)%.o:%.cpp $(SOURCES)
	g++ $(CFLAGS)  $(INC) -c $< -o $@

genObj:createFolder $(OBJECTS)
	#ENDED Compilation of ./src/RocketSimulator/

