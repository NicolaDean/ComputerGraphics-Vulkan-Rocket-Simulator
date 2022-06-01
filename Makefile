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
ENGINE = $(ENGINE_FOLDER)/*.cpp $(ENGINE_FOLDER)/*/*.cpp
MAIN = src/main.cpp
#SOURCE COMPOSITION
SOURCES = $(MAIN) $(ENGINE)

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

Engine: $(MAIN)  clean
	echo OS:$(OSNAME)
	g++ $(CFLAGS) $(INC) -o Engine $(SOURCES) $(LDFLAGS)

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

