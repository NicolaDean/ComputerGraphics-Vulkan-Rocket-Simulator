# ComputerGraphics-Vulkan-Rocket-Simulator

- FINISH VERTEX BUFFER TUTORIAL
- FINISH UNIFORM BUFFER TUTORIAL
- ADD THE "LOAD OBJ" FUNCTIONS
- CREATE A "CUSTOMIZABLE" VERSION OF "createPipeline" function
  (see how prof do it, so we can create multiple pipeline for multiple object/scenes)
- CREATE A "appLoop" structure so we can define RocketLogic in RocketSimulator.cpp and 
  NOT in ENGINE

#SOME IDEAS: 
###This can simplify the logic of the simulator
##Entity System
- CREATE a base "ENTITY" class with some basic methods like
  * OnWClick()
  * OnSClick()
  * OnUpdate()
  * OnDrawFrame()
- THIS ENTITY SHOULD THEN BE EXTENDED BY:
    * Camera
    * SceneObject
    * Player
- THE ENTITY SHOULD HAVE A "subscribe method" and use
  OBSERVER PATTERN so that we can subscribe entity to be 
  updated on events
  (eg, we subscribe rocket so when drawFrame we increment velocity,position...)
  
##Camera System
- Copy the camera matrixes used in the assignment and 
convert them into a class so we can easily select what kind
of view we want

##Light System
- Copy the shader done in A16/A17 and use it to "load shader"
 and use it on some "LIGHT OBJECT"
    * Direct light
    * Point Light
    * Area Light
