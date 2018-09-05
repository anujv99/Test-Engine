//#VERTEX
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

out vec2 TexCoords;

void main() {
	TexCoords = aTexCoords;
	gl_Position = projection * view * model * vec4(aPos, 1);
}

//#FRAGMENT
#version 460 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D tDiffuseTexture;

void main() {
	FragColor = texture(tDiffuseTexture, TexCoords);
}

//#UNIFORMS
0
//#END