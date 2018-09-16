//#VERTEX
#version 460 core

layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 view;

void main() {
	gl_Position = projection * view * vec4(aPos, 1);
}

//#FRAGMENT
#version 460 core

out vec4 FragColor;

void main() {
	FragColor = vec4(0.2, 0.8, 0.4, 1.0);
}

//#UNIFORMS
0
//#END