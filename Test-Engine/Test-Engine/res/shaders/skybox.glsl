//#VERTEX
#version 460 core

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main() {
	mat3 newView = mat3(view);
	TexCoords = aPos;
	vec4 pos = projection * mat4(newView) * vec4(aPos, 1);
	gl_Position = pos.xyww;
}

//#FRAGMENT
#version 460 core

out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube tCube;

void main() {
	FragColor = texture(tCube, TexCoords);
}

//#UNIFORMS
0
//#END