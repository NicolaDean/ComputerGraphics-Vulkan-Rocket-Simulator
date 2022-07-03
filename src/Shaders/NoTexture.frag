#version 450
struct LightUniform {
    vec3 position;
    vec4 color;
};
layout(set = 0, binding = 0) uniform GlobalUniformBuffer {
    mat4 view;
    mat4 proj;
    vec3 ambientLightDir;
    vec4 ambientLightColor;
    vec3 eyePos;
    LightUniform lights[2];
    int numLights;
} gubo;

layout(set=1,binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragNorm;
layout(location = 1) flat in vec3 fragColor;
layout(location = 2) out vec3 fragPosWorld;

layout(location = 0) out vec4 outColor;

void main() {
    vec3 color = vec3(0.45,0.35,0.2); // yellow
    vec3 diffuseLight = gubo.ambientLightColor.xyz * gubo.ambientLightColor.w;
    vec3 surfaceNormal = fragNorm;//normalize(fragNorm);

    for (int i = 0; i < gubo.numLights; i++) {
        LightUniform light = gubo.lights[i];
        vec3 directionToLight = light.position.xyz - fragNorm;
        float attenuation = 1.0 / dot(directionToLight, directionToLight);// distance squared
        float cosAngIncidence = max(dot(surfaceNormal, normalize(directionToLight)), 0);
        vec3 intensity = light.color.xyz * light.color.w * attenuation;

        diffuseLight += intensity * cosAngIncidence;
    }


    outColor = vec4(diffuseLight * fragColor , 1.0);
}
