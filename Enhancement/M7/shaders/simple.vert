#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 normal;

out vec4 vertexColor;
out vec2 tc;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main(){
    gl_Position =  projection * view * model * vec4(position, 1.0);
    vertexColor = vec4(color, 1.0);
}