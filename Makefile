#REMOVE -g and replace vis -O2 for release (now is debug)
#RELEASE MODE:
#CFLAGS = -std=c++17 -O2
#DEBUG MODE:
CFLAGS = -std=c++17 -g

#Project headers folder and flags#########################################
STB_INCLUDE_PATH = ./src/headers/
INC=-I ./headers -I $(STB_INCLUDE_PATH)
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

###################SHADER INFO:############################################
GLSLC_PATH = /usr/local/bin
SHADER_FOLDER = ./src/Shaders
COMPILED_SHADER = $(SHADER_FOLDER)/compiledShaders

#SOURCES PATHS########################################################################
#TODO modify the script, if we add more subfolder
ENGINE_FOLDER = src/engine
ENGINE = $(ENGINE_FOLDER)/*.cpp $(ENGINE_FOLDER)/*/*.cpp $(ENGINE_FOLDER)/*/*/*.cpp
MAIN = src/main.cpp src/RocketSimulator/RocketSimulator.cpp src/RocketSimulator/Models/Rocket.cpp
#SOURCE COMPOSITION
SOURCES = $(MAIN) $(ENGINE)
SOURCES_O =  ./build/engine/*.o ./build/engine/*/*.o ./build/engine/*/*/*.o ./build/RocketSimulator/*.o ./build/RocketSimulator/*/*.o ./src/main.o
#TODO CHECK HOW DO ACTUAL LIBRARY
#####################OS DETECTION#############################################################################
OSNAME = LINUX
UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OSNAME = LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		OSNAME = MAC
	endif
#OS DISTINCTION FOR FLAGS:
ifeq ($(OSNAME),LINUX)
	GLSLC_PATH = /usr/local/bin
	LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
endif
ifeq ($(OSNAME),MAC)
	GLSLC_PATH = /Users/fasa/VulkanSDK/1.3.204.0/macOS/bin
    LDFLAGS = -lglfw -lvulkan -ldl -lpthread
endif

###########################FAST COMPILE METHOD###################################################
completeCompile: clean fastCompileV2

clean:
	rm -r ./build

#TODO PUT OBJECTS INTO ENGINE FOLDER WITH ITS OWN MAKEFILE (Almost done)
fastCompile:
	#Check if core is builded or not
	make -C ./src/engine genObj
	#Check if Rocket Simulator
	make -C ./src/RocketSimulator genObj
	#Compile the main object
	g++ $(CFLAGS)  $(INC) -c ./src/main.cpp -o ./src/main.o
	#Link all .o files and compile Engine
	g++ -g  $(CFLAGS)  $(INC) -L ./src/engine/core/build/ -l Core -o Engine  $(SOURCES_O)  $(LDFLAGS)

#10 seconds full compilation
fastCompileV2: EngineGen RocketGen
	#Compile the main object
	g++ $(CFLAGS)  $(INC) -c ./src/main.cpp -o ./build/main.o
    #Link all .o files and compile Engine
	g++ -g  $(CFLAGS)  $(INC) -L ./src/engine/core/build/ -l Core -o Engine  $(OBJECTS_E)  $(OBJECTS_R) ./build/main.o $(LDFLAGS)
	#END COMPILATION

fastExe: fastCompileV2
	./Engine
run: fastCompileV2
all: run
########################ENGINE PROJECT#############################################
FOLDER_PATH_E=./src/engine/
BUILD_PATH_E=./build/engine/
BUILD_PATH_CORE_E=./build/engine/core
BUILD_PATH_UI	= ./build/engine/UI
#TODO PUT BUILD_PATH INTO THE .o file generation

SOURCES_E:= $(shell find $(FOLDER_PATH_E) -name '*.cpp')
OBJECTS_E=$(SOURCES_E:$(FOLDER_PATH_E)%.cpp=$(BUILD_PATH_E)%.o)

createFolderE:
	mkdir -p $(BUILD_PATH_E)
	mkdir -p $(BUILD_PATH_CORE_E)
	mkdir -p $(BUILD_PATH_CORE_E)/Device
	mkdir -p $(BUILD_PATH_CORE_E)/Drawing
	mkdir -p $(BUILD_PATH_CORE_E)/DrawingNew
	mkdir -p $(BUILD_PATH_CORE_E)/Geometry
	mkdir -p $(BUILD_PATH_CORE_E)/GraphicPipeline
	mkdir -p $(BUILD_PATH_CORE_E)/Objects
	mkdir -p $(BUILD_PATH_CORE_E)/Presentation
	mkdir -p $(BUILD_PATH_CORE_E)/Utils
	mkdir -p $(BUILD_PATH_UI)
	mkdir -p $(BUILD_PATH_UI)/components

$(BUILD_PATH_E)%.o:$(FOLDER_PATH_E)%.cpp $(SOURCES_E)
	g++ $(CFLAGS)  $(INC) -c $< -o $@

EngineGen:createFolderE $(OBJECTS_E)
	#ENDED Compilation of ./src/engine
########################ROCKET PROJECT#############################################
FOLDER_PATH_R = ./src/RocketSimulator/
BUILD_PATH_R= ./build/RocketSimulator/
#TODO PUT BUILD_PATH INTO THE .o file generation

SOURCES_R := $(shell find $(FOLDER_PATH_R) -name '*.cpp')
OBJECTS_R = $(SOURCES_R:./src/RocketSimulator/%.cpp=$(BUILD_PATH_R)%.o)

createFolderR:
	mkdir -p $(BUILD_PATH_R)
	mkdir -p $(BUILD_PATH_R)Models
	mkdir -p $(BUILD_PATH_R)Utils
	mkdir -p $(BUILD_PATH_R)Terrain
	mkdir -p $(BUILD_PATH_R)Lights

$(BUILD_PATH_R)%.o:$(FOLDER_PATH_R)%.cpp $(SOURCES_R)
	g++ $(CFLAGS)  $(INC) -c $< -o $@

RocketGen:createFolderR $(OBJECTS_R)
	#ENDED Compilation of ./src/RocketSimulator/

banana:
	echo $(OBJECTS_E)
########################SHADER COMPILER############################################
#TODO automatize the shader compilation like for c++
shaders:
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/Shader.frag -o $(COMPILED_SHADER)/fragShader.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/Shader.vert -o $(COMPILED_SHADER)/vertShader.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/NoTexture.frag -o $(COMPILED_SHADER)/fragNoTexture.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/NoTexture.vert -o $(COMPILED_SHADER)/vertNoTexture.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/UIshader.frag -o $(COMPILED_SHADER)/fragUIshader.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/UIshader.vert -o $(COMPILED_SHADER)/vertUIshader.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/Skybox.frag -o $(COMPILED_SHADER)/fragSkybox.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/Skybox.vert -o $(COMPILED_SHADER)/vertSkybox.spv