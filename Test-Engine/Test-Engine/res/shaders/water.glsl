//#VERTEX
#version 460 core

layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main() {
	gl_Position =  projection * view * model * vec4(aPos, 1.0);
}

//#FRAGMENT
#version 460 core

out vec4 FragColor;

void main() {
	FragColor = vec4(0.5, 07, 1.0, 1.0);
}

//#UNIFORMS
0
//#END