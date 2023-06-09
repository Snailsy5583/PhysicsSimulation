#version 330 core

uniform float radius;
uniform vec3  pos;

void main() {
    float x = ((gl_FragCoord.x-(((pos.x+1)/2)*800))/(radius*400));
    float y = ((gl_FragCoord.y-(((pos.y+1)/2)*800))/(radius*400));
    float circle = 1-(x*x+y*y);
    gl_FragColor = vec4(circle*5);
//    gl_FragColor = vec4(1);
}