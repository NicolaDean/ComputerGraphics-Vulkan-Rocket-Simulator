#version 450

struct LightUniform {
    vec3 pos;
    vec3 col;
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
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragViewDir;
layout(location = 1) flat out vec3 fragColor;

void main() {
    vec2 a = inTexCoord;
    gl_Position = gubo.proj * gubo.view * ubo.model * vec4(inPosition, 1.0);
    fragViewDir  = (gubo.view[3]).xyz - (ubo.model * vec4(inPosition,  1.0)).xyz;
    // normal * 2 -1 (to be from -1 to 1)
    fragColor = inColor;
}