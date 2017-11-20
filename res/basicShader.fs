#version 330 core
#define NUM_POINT_LIGHTS 4

in vec2 texCoordV;
in vec3 normalV;
in vec3 posV;

struct Material {
    vec3 specular;
    float shininess;
};

struct PointLight {
    vec3 position;
    vec3 color;
};

struct DirectionalLight {
    vec3 direction;
    vec3 color;
};

uniform Material material;
uniform PointLight pointLights[NUM_POINT_LIGHTS];
uniform DirectionalLight directionalLight;
uniform vec3 ambientLight;
uniform sampler2D tex;

vec3 applyDirectionalLighting(vec3 color, DirectionalLight light, vec3 normal, vec3 viewDir){
    vec3 diffuseColor = max(0.0, dot(normal, -light.direction)) * color * light.color;
    vec3 halfDir = normalize(-light.direction + viewDir);
    float spec = max(0.0, dot(halfDir, normal));
    vec3 specColor = pow(spec, material.shininess) * material.specular * light.color;
    return diffuseColor + specColor;
}

vec3 applyPointLighting(vec3 color, PointLight light, vec3 normal, vec3 pos, vec3 viewDir){
    float fallOff = 1.0/length(pos - light.position);
    vec3 lightDir = normalize(pos - light.position);
    vec3 diffuseColor = max(0.0, dot(normal, -lightDir)) * color * light.color;
    vec3 halfDir = normalize(-lightDir + viewDir);
    float spec = max(0.0, dot(halfDir, normal));
    vec3 specColor = pow(spec, material.shininess) * material.specular * light.color;
    return (diffuseColor + specColor)*fallOff;
}

void main(){
    vec3 color = texture(tex, texCoordV).rgb;
    vec3 result = color * ambientLight;
    vec3 viewDir = normalize(-posV);
    result += applyDirectionalLighting(color, directionalLight, normalV, viewDir);
    for(int i=0; i<NUM_POINT_LIGHTS; i++)
        result += applyPointLighting(color, pointLights[i], normalV, posV, viewDir);
    gl_FragColor = vec4(result, 1);
}