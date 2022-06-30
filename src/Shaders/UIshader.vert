#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

vec2 positions[4] = vec2[](
    vec2(-0.5, 0.5),
    vec2(0.5, 0.5),
    vec2(0.5, -0.5),
    vec2(-0.5, -0.5)
);

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec2 texCoord;

layout(location = 0) out vec3 fragViewDir;
layout(location = 1) out vec3 fragNorm;
layout(location = 2) out vec2 fragTexCoord;

void main() {

    //POS IS IN VIEWPORT COORDINATES NOT WORLD COORDINATES
    gl_Position =  vec4(pos, 1.0);
    fragTexCoord = texCoord;

    //NOT USEFUL
    fragViewDir  = (ubo.view[3]).xyz - (ubo.model * vec4(pos,  1.0)).xyz;
    fragNorm     = norm;

}
