#version 450

struct LightUniform {
    vec3 pos;
    vec3 col;
};
layout(set = 0, binding = 0) uniform globalUniformBufferObject {
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

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec2 texCoord;

layout(location = 0) out vec3 fragViewDir;
layout(location = 1) out vec3 fragNorm;
layout(location = 2) out vec2 fragTexCoord;

void main() {
    gl_Position = gubo.proj * gubo.view * ubo.model * vec4(pos, 1.0);
    fragViewDir  = (gubo.view[3]).xyz - (ubo.model * vec4(pos,  1.0)).xyz;
    fragNorm     = (ubo.model * vec4(norm, 0.0)).xyz;
    fragTexCoord = texCoord;
}