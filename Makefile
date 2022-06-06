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
MAIN = src/main.cpp
#SOURCE COMPOSITION
SOURCES = $(MAIN) $(ENGINE)
SOURCES_O =  $(ENGINE_FOLDER)/core/build/*.o $(ENGINE_FOLDER)/core/build/*/*.o $(ENGINE_FOLDER)/App.o  ./src/RocketSimulator/RocketSimulator.o ./src/main.o
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


shaders:
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/Shader.frag -o $(COMPILED_SHADER)/Frag.spv
	$(GLSLC_PATH)/glslc $(SHADER_FOLDER)/Shader.vert -o $(COMPILED_SHADER)/Vert.spv

cleanCore:
	rm -r ./src/engine/core/build
fastCompile:
	#Check if core is builded or not
	make -C ./src/engine/core all
	#Those file are always created:
	g++ $(CFLAGS)  $(INC) -c ./src/engine/App.cpp -o ./src/engine/App.o
	g++ $(CFLAGS)  $(INC) -c ./src/RocketSimulator/RocketSimulator.cpp -o ./src/RocketSimulator/RocketSimulator.o
	g++ $(CFLAGS)  $(INC) -c ./src/main.cpp -o ./src/main.o
	#Link all .o files and compile Engine
	g++ -g  $(CFLAGS)  $(INC) -L ./src/engine/core/build/ -l Core -o Engine  $(SOURCES_O)  $(LDFLAGS)
