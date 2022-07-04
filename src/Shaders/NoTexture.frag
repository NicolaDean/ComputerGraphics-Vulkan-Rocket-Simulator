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

layout(location = 0) flat in vec3 fragNorm;
layout(location = 1) flat in vec3 fragColor;
layout(location = 2) flat in vec3 fragPosWorld;

layout(location = 0) out vec4 outColor;

void main() {
    vec3 color = vec3(0.45,0.35,0.2); // yellow
    vec3 diffuseLight = gubo.ambientLightColor.xyz * gubo.ambientLightColor.w;
    vec3 surfaceNormal = fragNorm;//normalize(fragNorm);

    for (int i = 0; i < gubo.numLights; i++) {
        LightUniform light = gubo.lights[i];
        vec3 directionToLight = light.position.xyz - fragPosWorld;
        float attenuation = 1.0 / dot(directionToLight, directionToLight);// distance squared
        float cosAngIncidence = max(dot(surfaceNormal, normalize(directionToLight)), 0);
        vec3 intensity = light.color.xyz * light.color.w * attenuation;



        diffuseLight += intensity * cosAngIncidence;
    }

    //S
    vec3 dir = vec3(0,1,1); // high noon
    vec3 col = vec3(0.45,0.35,0.2); // yellow
    vec3 col2 = vec3(0.39,0.30,0.1); // yellow

    vec3 N = normalize(fragColor);
    vec3 diffuseToon = vec3(0,0,0); //Dark
    float diffusee = (.5 + dot(N,dir)) * 1;
    //TOON SHADING
    if (diffusee>0.4){ //If if more than threshold---> light
        diffuseToon =  diffusee*col ;
    }
    else if(diffusee>0){ // else if still positive --> a bit darker
        diffuseToon = diffusee*col ;
    }
    outColor = vec4(diffuseToon + diffuseLight * color, 1.0);

    //outColor = vec4(diffuseToon,1.0);
}
