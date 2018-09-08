//#VERTEX
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

out vec3 FragPos;  
flat out vec3 Normal;

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
flat in vec3 Normal;

vec3 lerp(float height) {
	
	height /= 2.0;

	vec3 green = normalize(vec3(80, 171, 93));
	vec3 gray = normalize(vec3(120));

	if (height < 0) {
		green += ((-height) / 4.0) * normalize(vec3(135, 184, 82));
	}

	return gray * height + (1 - height) * green;
}

void main() {

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(sun.mDirection);
	lightDir = vec3(0, 1, 0);

	float diff = max(dot(norm, lightDir), 0.1);
	vec3 diffuse = diff * sun.mColor;

	FragColor = vec4(lerp(FragPos.y) * diffuse, 1);
}

//#UNIFORMS
0
//#END