//#VERTEX
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

void main() {
	gl_Position = projection * view * model * vec4(aPos, 1);
}

//#FRAGMENT
#version 460 core

out vec4 FragColor;

void main() {
	FragColor = vec4(1, 1, 1, 1);
}

//#UNIFORMS
0
//#END