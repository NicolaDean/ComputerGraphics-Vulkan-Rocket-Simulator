CFLAGS = -std=c++17 -O2
COMPILER = g++
LDFLAGS = -lglfw -lvulkan -ldl -lpthread

BUILD_FOLDER = ./build

INC=-I ../../headers/
Devices = ./Device/*.cpp

#Device
DEVICE = DeviceManager.cpp LogicDeviceManager.cpp QueueFamily.cpp
DEVICE_FOLD = $(DEVICE:%.cpp=./Device/%.cpp)
DEVICE_OBJS = $(DEVICE:%.cpp=./build/Device/%.o)

#Drawing
DRAWING = BufferManager.cpp CommandBuffer.cpp DepthImage.cpp FrameBuffer.cpp Renderer.cpp TextureManager.cpp UniformBuffer.cpp VertexBuffer.cpp
DRAWING_FOLD = $(DRAWING:%.cpp=./Drawing/%.cpp)
DRAWING_OBJS = $(DRAWING:%.cpp=./build/Drawing/%.o)

#DrawingNew
DRAWINGNEW = CommandManager.cpp DescriptorManager.cpp GraphicPipelineCustom.cpp UniformBufferManager.cpp
DRAWINGNEW_FOLD = $(DRAWINGNEW:%.cpp=./DrawingNew/%.cpp)
DRAWINGNEW_OBJS = $(DRAWINGNEW:%.cpp=./build/DrawingNew/%.o)

#Geometry

#GraphicPipeline

#Objects
OBJECTS = Camera.cpp Entity.cpp Mesh.cpp Model.cpp Texture.cpp
OBJECTS_FOLD = $(OBJECTS:%.cpp=./Objects/%.cpp)
OBJECTS_OBJS = $(OBJECTS:%.cpp=./build/Objects/%.o)

#Presentation
PRESENTATION = SwapChain.cpp WindowsSurface.cpp
PRESENTATION_FOLD = $(PRESENTATION:%.cpp=./Presentation/%.cpp)
PRESENTATION_OBJS = $(PRESENTATION:%.cpp=./build/Presentation/%.o)

#Utils
UTILS = Constants.cpp ValidationLayer.cpp ValidationLayerHelper.cpp
UTILS_FOLD = $(UTILS:%.cpp=./Utils/%.cpp)
UTILS_OBJS = $(UTILS:%.cpp=./build/Utils/%.o)

#Core
CORE = Core.cpp
CORE_OBJ = build/Core.o

OBJ = $(DEVICE_OBJS) $(DRAWING_OBJS)
# -c flag mean we compile to object (no main needed)

./build/%.o: %.cpp $(DEVICE_FOLD) $(DRAWING_FOLD) $(DRAWINGNEW_FOLD) $(OBJECTS_FOLD) $(CORE) $(UTILS_FOLD)
	g++ -g $(CFLAGS)  $(INC) -c $< -o $@ $(LDFLAGS)


Engine:
	echo OS:$(OSNAME)
	g++ -g  $(CFLAGS)  $(INC) -o Engine  $(LDFLAGS)
	echo "Ended Compilation"

checkFolders:
	mkdir -p "./build/"
	mkdir -p "./build/Device"
	mkdir -p "./build/Drawing"
	mkdir -p "./build/DrawingNew"
	mkdir -p "./build/Geometry"
	mkdir -p "./build/Objects"
	mkdir -p "./build/Presentation"
	mkdir -p "./build/Utils"

build/libCore.a: checkFolders $(DEVICE_OBJS) $(DRAWING_OBJS) $(DRAWINGNEW_OBJS) $(OBJECTS_OBJS) $(PRESENTATION_OBJS) $(UTILS_OBJS) $(CORE_OBJ)
	echo "Object Generation Completed!"
	ar rcs ./build/libCore.a  ./build/*/*.o ./build/Core.o
all:build/libCore.a

#ar -t file.a mostra il contenuto della libreria

