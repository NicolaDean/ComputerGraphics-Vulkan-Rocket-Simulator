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
    // Cancel out translation
    m[3] = vec4(0.0f, 0.0f, 0.0f, 1.0f);

    fragTexCoord = pos*100;
    // Convert cubemap coordinates into Vulkan coordinate space
    //fragTexCoord.xy *= -1.0;
    //TODO scale the skybox
    gl_Position = ubo.proj * m * vec4(pos.xyz*100, 1.0);
    //gl_Position = (ubo.model * vec4(pos, 1.0)).xyww;
}
