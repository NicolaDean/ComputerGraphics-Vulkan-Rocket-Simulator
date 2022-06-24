#version 450

layout(location = 0) in vec3 fragViewDir;
layout(location = 1) flat in vec3 fragColor;
layout(location = 2) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main() {
    //TODO ADD LIGHT CALCULATION!!!
    //outColor = vec4(fragColor, 1.0);

    vec3 dir = vec3(0,1,1); // high noon
    vec3 color = vec3(0.45,0.35,0.2); // yellow
    vec3 color2 = vec3(0.39,0.30,0.1); // yellow

    const vec3  diffColor = color;
    const vec3  specColor = vec3(1.0f, 1.0f, 1.0f);
    const float specPower = 150.0f;
    const vec3  L = vec3(-0.4830f, 0.8365f, -0.2588f);

    vec3 N = normalize(fragColor);
    vec3 R = -reflect(L, N);
    vec3 V = normalize(dir);

    // Lambert diffuse
    //vec3 diffuse  =  max(dot(N,L), 0.0f);

    float diffuse = max(0.0, dot(N, L));
    vec3 diffuseToon = vec3(0,0,0); //Dark

    float diffusee = .5 + dot(N,dir);
    if (diffusee>0.4){ //If if more than threshold---> light
        diffuseToon =  diffusee*color ;
    }
    else if(diffusee>0){ // else if still positive --> a bit darker
        diffuseToon = diffusee*color2 ;
    }

    // Phong specular
    vec3 specular = specColor * pow(max(dot(R,V), 0.0f), specPower);
    // Hemispheric ambient
    vec3 ambient  = (vec3(0.1f,0.1f, 0.1f) * (1.0f + N.y) + vec3(0.0f,0.0f, 0.1f) * (1.0f - N.y)) * diffColor;

    //outColor = vec4(clamp(ambient, vec3(0.0f), vec3(1.0f)), 1.0f);//a

    outColor = vec4(diffuseToon,1.0);
    //outColor = vec4(diffusee * color, 1.0);
    //outColor = vec4(fragColor,1.0f);
}