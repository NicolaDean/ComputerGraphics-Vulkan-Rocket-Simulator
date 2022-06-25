#version 450

layout(location = 0) in vec3 fragViewDir;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec3 fragTexCoord;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform samplerCube texSampler;
void main() {
   // outColor = texture(texSampler, fragTexCoord);
    outColor = vec4(1,0,0,1);
}
