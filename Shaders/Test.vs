#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 Color;
out vec3 MyColor;

void main(){
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
    MyColor = gl_Position.xyz;
}