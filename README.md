# ComputerGraphics-Vulkan-Rocket-Simulator
##TERRAIN GENERATION
 -Create a gradientClass that allow to do gradient between 2 color (eg yellow->dark yellow)
 -Create a PerlinNoise generator
 -Generate a Plane using triangles
 -Use PerlinNoise to generate vertices height
 -Use Gradient to generate vertices colors
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

##Light System
- Create the GlobalUniformBuffer class an insert inside it an array of "LIGHT"
- struct Light{ color, pos, ....}
- create a shader to calculate all light info
- create a descriptor for globalUniform
- create a new Pipeline using this shader and descriptor (SEE TEACHER LECTURE)
- Copy the shader done in A16/A17 and use it to "load shader"
 and use it on some "LIGHT OBJECT"
    * Direct light
    * Point Light
    * Area Light

##SKYBOX
- Create a cube object
- Create 6 images (one for each side)
- Draw the cube putting all the 6 images as face
- Scale the cube to cover all the world
