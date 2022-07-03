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

layout(location = 0) in vec3 fragViewDir;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragTexCoord;
layout(location = 3) out vec3 fragPosWorld;

layout(location = 0) out vec4 outColor;

void main() {
    const vec3  diffColor = texture(texSampler, fragTexCoord).rgb;
    vec3 surfaceNormal = normalize(fragNorm);
    const vec3  specColor = vec3(1.0f, 1.0f, 1.0f);
    const float specPower = 150.0f;
    const vec3  L = vec3(-0.4830f, 0.8365f, -0.2588f);

    vec3 N = normalize(fragNorm);
    vec3 R = -reflect(L, N);
    vec3 V = normalize(fragViewDir);

    // Lambert diffuse
    vec3 diffuse  = diffColor * max(dot(N,L), 0.0f);
    // Phong specular
    vec3 specular = specColor * pow(max(dot(R,V), 0.0f), specPower);
    // Hemispheric ambient
    vec3 ambient  = (vec3(0.1f,0.1f, 0.1f) * (1.0f + N.y) + vec3(0.0f,0.0f, 0.1f) * (1.0f - N.y));

    vec3 diffuseLight = ambient;
    for (int i = 0; i < gubo.numLights; i++) {
        LightUniform light = gubo.lights[i];
        vec3 directionToLight = light.position.xyz - fragNorm;
        float attenuation = 1.0 / dot(directionToLight, directionToLight);// distance squared
        float cosAngIncidence = max(dot(surfaceNormal, normalize(directionToLight)), 0);
        vec3 intensity = light.color.xyz * light.color.w * attenuation;

        diffuseLight += intensity * cosAngIncidence;
    }
    diffuseLight = diffuseLight * diffColor;
    outColor = vec4(clamp(diffuseLight + diffuse + specular, vec3(0.0f), vec3(1.0f)), 1.0f);
}