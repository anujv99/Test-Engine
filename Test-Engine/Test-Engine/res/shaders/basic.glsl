//#VERTEX
#version 460 core
void main() {
	gl_Position = vec4(0, 0, 0, 1);
}

//#FRAGMENT
#version 460 core

out vec4 FragColor;

void main() {
	FragColor = vec4(1, 1, 1, 1);
}

//#UNIFORMS
1
//#END