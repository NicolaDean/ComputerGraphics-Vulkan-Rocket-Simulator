CFLAGS = -std=c++17 -O2
STB_INCLUDE_PATH = ./src/headers/

INC=-I ./headers -I $(STB_INCLUDE_PATH)
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
GLSLC_PATH = /usr/local/bin

PRECOMPILE =  ./src/engine/commonLibs

#SHADER INFO:
SHADER_FOLDER = ./src/Shaders
COMPILED_SHADER = $(SHADER_FOLDER)/compiledShaders

#SOURCES PATHS
#TODO modify the script, if we add more subfolder
ENGINE_FOLDER = src/engine
ENGINE = $(ENGINE_FOLDER)/*.cpp $(ENGINE_FOLDER)/*/*.cpp $(ENGINE_FOLDER)/*/*/*.cpp
MAIN = src/main.cpp src/RocketSimulator/RocketSimulator.cpp src/RocketSimulator/Models/Rocket.cpp
#SOURCE COMPOSITION
SOURCES = $(MAIN) $(ENGINE)
SOURCES_O =  ./build/engine/*.o ./build/engine/*/*.o ./build/engine/*/*/*.o ./build/RocketSimulator/*.o ./build/RocketSimulator/*/*.o ./src/main.o
#TODO CHECK HOW DO ACTUAL LIBRARY
#OS DETECTION
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

#Precompiled header allow to fast up the compile time (by precompiling some static non changing code)
#For example when Engine will be done we can put Engine and App compiler so we can include Engine as a PRECOMPILED HEADER
#https://gcc.gnu.org/onlinedocs/gcc/Precompiled-Headers.html
Precompile: $(PRECOMPILE).cpp
	g++ -std=c++17 $(PRECOMPILE).h
	#g++ $(CFLAGS) -o $(PRECOMPILE).h.gch $(PRECOMPILE).h

Engine:  $(MAIN)  clean
	echo OS:$(OSNAME)
	g++ -g  $(CFLAGS)  $(INC) -o Engine $(SOURCES) $(LDFLAGS)
	echo "Ended Compilation"

.PHONY: test clean debug Precompile

test: Engine
	./Engine

debug:
	g++ -g $(CFLAGS) $(INC) -o Engine $(SOURCES) $(LDFLAGS)
	gdb ./Engine

clean:
	rm -f Engine

run: clean test

###########################FAST COMPILE METHOD###################################################
completeCompile: cleanCore fastCompile

cleanCore:
	rm -r ./build/engine

cleanAll:
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

fastExe: fastCompile
	./Engine


########################SHADER COMPILER############################################
#Put here the shaders name (in the format of name.x)
SHADER_NAMES = Shader.x NoTexture.x

FRAGMENTS_NAME 	= $(SHADER_NAMES:%.x=%.frag)
VERTEXS_NAME 	= $(SHADER_NAMES:%.x=%.vert)
COMPILED_FRAG_NAMES = $(SHADER_NAMES:%.x=frag_%.spv)
COMPILED_VERT_NAMES = $(SHADER_NAMES:%.x=vert_%.spv)
COMPILED_FRAG_INFOLDER = $(SHADER_NAMES:%.x=$(COMPILED_SHADER)/frag%.spv)
COMPILED_VERT_INFOLDER = $(SHADER_NAMES:%.x=$(COMPILED_SHADER)/vert%.spv)

#Compile CODE FOR FRAGMENT SHADER
$(COMPILED_SHADER)/frag%.spv: $(SHADER_FOLDER)/%.frag
	$(GLSLC_PATH)/glslc $< -o $@
#Compile CODE FOR VERTEX SHADER
$(COMPILED_SHADER)/vert%.spv: $(SHADER_FOLDER)/%.frag
	$(GLSLC_PATH)/glslc $< -o $@
#Compile all Fragments shader
frag:$(COMPILED_FRAG_INFOLDER)
	# "Ended Fragment Shader Compilation"
#Compile all Vertex shader
vert:$(COMPILED_VERT_INFOLDER)
	# "Ended Vertex Shader Compilation"

#Global Compile command for shaders
compile_shader: frag vert
	# "COMPLETED ALL SHADER COMPILATION"

shaders:
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/Shader.frag -o $(COMPILED_SHADER)/fragShader.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/Shader.vert -o $(COMPILED_SHADER)/vertShader.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/NoTexture.frag -o $(COMPILED_SHADER)/fragNoTexture.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/NoTexture.vert -o $(COMPILED_SHADER)/vertNoTexture.spv
