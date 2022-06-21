#version 450

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragViewDir;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
    vec3 color = vec3(1,0.35,0.2); // yellow
    const vec3  diffColor = texture(texSampler, fragTexCoord).rgb;
    outColor = vec4(diffColor, 1.0);
    //outColor = vec4(color, 1.0);
}