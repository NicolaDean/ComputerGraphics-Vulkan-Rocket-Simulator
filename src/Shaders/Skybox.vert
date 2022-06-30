#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec2 texCoord;

layout(location = 0) out vec3 fragViewDir;
layout(location = 1) out vec3 fragNorm;
layout(location = 2) out vec3 fragTexCoord;

void main()
{
    mat4 m = ubo.view;
    // Cancel out translation -> ONLY ANGLES
    m[3] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    //Change scale for resize skybox
    int scale = 100;
    fragTexCoord = pos*scale;
    gl_Position = ubo.proj * m * vec4(pos.xyz*scale, 1.0);
}
