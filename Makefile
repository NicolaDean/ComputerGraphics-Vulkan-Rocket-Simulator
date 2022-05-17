CFLAGS = -std=c++17 -O2
INC=-I./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

GLSLC_PATH = /usr/local/bin

#SHADER INFO:
SHADER_FOLDER = ./src/Shaders
COMPILED_SHADER = $(SHADER_FOLDER)/compiledShader

#SOURCES PATHS
#TODO modify the script, if we add more subfolder
ENGINE_FOLDER = src/engine
ENGINE = $(ENGINE_FOLDER)/*.cpp $(ENGINE_FOLDER)/*.h $(ENGINE_FOLDER)/*/*.cpp $(ENGINE_FOLDER)/*/*.h
MAIN = src/main.cpp
#SOURCE COMPOSITION
SOURCES = $(MAIN) $(ENGINE)

Engine: $(SOURCES)
	g++ $(CFLAGS) $(INC) -o Engine $(SOURCES) $(LDFLAGS)

.PHONY: test clean debug

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

