#version 450

struct LightUniform {
    vec3 pos;
    vec4 color;
};
layout(set = 0, binding = 0) uniform GlobalUniformBuffer {
    mat4 view;
    mat4 proj;
    vec3 lightDir;
    vec4 lightColor;
    vec3 eyePos;
    LightUniform lights[2];
    int numLights;
} gubo;

layout(set = 1, binding = 0) uniform UniformBufferObject {
    mat4 model;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;
layout(location = 3) in vec2 inTexCoord;

layout(location = 0) flat out vec3 fragNorm;
layout(location = 1) flat out vec3 fragColor;
layout(location = 2) flat out vec3 fragPosWorld;

void main() {

    vec3 c = vec3(0.45,0.35,0.2); // yellow
    //Position of a vertex in world
    vec4 positionWorld = ubo.model * vec4(inPosition, 1.0);
    //Pixel Position and data for fragment
    fragPosWorld = positionWorld.xyz;
    //fragNorm     = (ubo.model * vec4(inColor, 0.0)).xyz;
    fragColor    = normal;
    fragNorm =  normal.xyz * 2.0 - 1.0;//required just because of the format the normals were stored in (0 - 1)
    //VERTEX POSITION
    gl_Position = gubo.proj * gubo.view * ubo.model * vec4(inPosition, 1.0);
    //fragViewDir  = (gubo.view[3]).xyz - (ubo.model * vec4(inPosition,  1.0)).xyz;
    // normal * 2 -1 (to be from -1 to 1)

}