#version 330 core

in vec3 position;
in vec2 texCoord;
in vec3 normal;

out vec2 texCoordV;
out vec3 normalV;
out vec3 posV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    gl_Position = proj * view * model * vec4(position, 1.0);
    texCoordV = texCoord;
    normalV = normalize((transpose(inverse(view*model)) * vec4(normal, 0.0)).xyz);
    posV = (view * model * vec4(position, 1.0)).xyz;
}