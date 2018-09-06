//#VERTEX
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

out vec3 FragPos;  
out vec3 Normal;

void main() {
	vec4 worldPos = model * vec4(aPos, 1.0);
	FragPos = worldPos.xyz;
	Normal = mat3(transpose(inverse(model))) * aNorm;
	gl_Position = projection * view * worldPos;
}

//#FRAGMENT
#version 460 core

out vec4 FragColor;

struct DirLight {
	vec3 mDirection;
	vec3 mColor;
};

uniform DirLight sun;

in vec3 FragPos;
in vec3 Normal;

void main() {

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(sun.mDirection);

	float diff = max(dot(norm, lightDir), 0.1);
	vec3 diffuse = diff * sun.mColor;

	FragColor = vec4(diffuse, 1);
}

//#UNIFORMS
0
//#END