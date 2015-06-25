#version 440 core

//in vec4 MyColor;
in vec3 MyColor;
out vec4 color;

void main(){
    color = vec4(MyColor.r, MyColor.g, MyColor.b, 1.0);
}