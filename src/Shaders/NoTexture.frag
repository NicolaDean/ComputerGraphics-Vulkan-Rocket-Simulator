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


vec3 pointLightContribution(LightUniform light){
    vec3 diffuseLight = vec3(0,0,0);
    //Normalize normal vector
    vec3 surfaceNormal = fragNorm;//normalize(fragNorm);

    //Calculate distance of this pixel from light
    vec3 directionToLight = light.position.xyz - fragPosWorld;
    //Calculate Attenuation using ((g/(|p-x|))^b) * color; //TODO
    float attenuation = 1.0 / dot(directionToLight, directionToLight);// distance squared
    float cosAngIncidence = max(dot(surfaceNormal, normalize(directionToLight)), 0);
    vec3 intensity = light.color.xyz * light.color.w * attenuation;

    diffuseLight += intensity * cosAngIncidence;

    return diffuseLight;
}

void main() {
    vec3 color = vec3(0.45,0.35,0.2); // yellow
    vec3 surfaceNormal = fragNorm;//normalize(fragNorm);
    vec3 diffusePointLight = gubo.ambientLightColor.xyz * gubo.ambientLightColor.w;

    vec3 tmpLightEffect = vec3(0,0,0);
    /***********POINT LIGHTS CONTRIBUTION************/
    for (int i = 0; i < gubo.numLights; i++) {
        LightUniform light = gubo.lights[i];
        tmpLightEffect += pointLightContribution(light);
    }

    /***********SUM POINT LIGHT TO AMBIENT LIGHT*********/
    diffusePointLight = tmpLightEffect + diffusePointLight;

    vec3 dir = vec3(0,1,1); // high noon
    vec3 N              = normalize(fragNorm);
    float brightness    = (.5 + dot(N,gubo.ambientLightDir)) * 1;
    float LdotN         = max(0.0, dot(N, gubo.ambientLightDir));
    /*************TOON SHADING****************/
    vec3 diffuseToon = vec3(0,0,0); //Dark
    if (LdotN>0.9){ //If if more than threshold---> light
        diffuseToon =  brightness*fragColor ;
    }
    else if(LdotN>0){ // else if still positive --> a bit darker
        diffuseToon = brightness*fragColor*0.9;
    }

    /**************OUTPUT RESULT SUMMING ALL LIGHTS********************/
    outColor = vec4(diffuseToon + diffusePointLight * fragColor, 1.0);

    //outColor = vec4(diffuseToon,1.0);
}
