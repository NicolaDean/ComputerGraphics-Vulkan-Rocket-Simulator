#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragViewDir;
layout(location = 1) flat out vec3 fragColor;

//simple diffuse lighting
vec3 calculateLighting(){
    vec3 lightDirection = vec3(-0.4830f, 0.8365f, -0.2588f);
    vec3 lightColour = vec3(0.3f, 0.3f, 0.3f);

    vec3 normal = inColor.xyz * 2.0 - 1.0;//required just because of the format the normals were stored in (0 - 1)
    float brightness = max(dot(-lightDirection, normal), 0.0);
    return (lightColour) + (brightness * lightColour);
}

void main() {
    vec2 a = inTexCoord;
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
    fragViewDir  = (ubo.view[3]).xyz - (ubo.model * vec4(inPosition,  1.0)).xyz;
    vec3 lighting = calculateLighting();
    vec3 normal = inColor.xyz * 2.0 - 1.0;
    //fragColor = vec3(0.45,0.35,0.2).rgb *lighting;
    fragColor = normal;
}