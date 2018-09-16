//#VERTEX
#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aIndicators;

struct DirLight {
	vec3 mDirection;
	vec3 mColor;
};

uniform DirLight sun;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

uniform vec3 cameraPos;
uniform float waveTime;
uniform float height;

out vec4 clipSpace;
out vec4 clipSpaceGrid;
out vec3 Normal;
out vec3 toCamera;
out vec3 Specular;
out vec3 Diffuse;

const float PI = 3.14159265358979323846;
const float waveLength = 7.0;
const float waveAmplitude = 0.4;
const float specularReflectivity = 0.8;
const float shineDamper = 20.0;

vec3 calcSpecularLighting(vec3 toCamVector, vec3 toLightVector, vec3 normal){
	vec3 reflectedLightDirection = reflect(-toLightVector, normal);
	float specularFactor = dot(reflectedLightDirection , toCamVector);
	specularFactor = max(specularFactor,0.0);
	specularFactor = pow(specularFactor, shineDamper);
	return specularFactor * specularReflectivity * sun.mColor;
}

vec3 calculateDiffuseLighting(vec3 toLightVector, vec3 normal){
	float brightness = max(dot(toLightVector, normal), 0.0);
	return (sun.mColor) + (brightness * sun.mColor);
}

float generateOffset(float x, float z, float val1, float val2){
	float radiansX = ((mod(x+z*x*val1, waveLength)/waveLength) + waveTime * mod(x * 0.8 + z, 1.5)) * 2.0 * PI;
	float radiansZ = ((mod(val2 * (z*x +x*z), waveLength)/waveLength) + waveTime * 2.0 * mod(x , 2.0) ) * 2.0 * PI;
	return waveAmplitude * 0.5 * (sin(radiansZ) + cos(radiansX));
}

vec3 applyDistortion(vec3 vertex){
	float xDistortion = generateOffset(vertex.x, vertex.z, 0.2, 0.1);
	float yDistortion = generateOffset(vertex.x, vertex.z, 0.1, 0.3);
	float zDistortion = generateOffset(vertex.x, vertex.z, 0.15, 0.2);
	return vertex + vec3(xDistortion, yDistortion, zDistortion);
}

vec3 calcNormal(vec3 vertex0, vec3 vertex1, vec3 vertex2){
	vec3 tangent = vertex1 - vertex0;
	vec3 bitangent = vertex2 - vertex0;
	vec3 norm = normalize(cross(bitangent, tangent));
	return norm;
}

void main() {

	mat4 pvm = projection * view * model;

	vec3 currentVertex = vec3(aPos.x, height, aPos.y);
	vec3 vertex1 = vec3(aIndicators.x, height, aIndicators.y);
	vec3 vertex2 = vec3(aIndicators.z, height, aIndicators.w);

	clipSpaceGrid = pvm * vec4(currentVertex, 1.0);

	currentVertex = applyDistortion(currentVertex);
	vertex1 = applyDistortion(vertex1);
	vertex2 = applyDistortion(vertex2);

	Normal = calcNormal(currentVertex, vertex1, vertex2);

	clipSpace = pvm * vec4(currentVertex, 1.0);

	toCamera = normalize(cameraPos - currentVertex);

	gl_Position = clipSpace;

	vec3 toLightVector = -normalize(sun.mDirection);
	Specular = calcSpecularLighting(toCamera, toLightVector, Normal) / 2.0;
	Diffuse = calculateDiffuseLighting(toLightVector, Normal);
}

//#FRAGMENT
#version 460 core

const vec3 waterColor = vec3(0.604, 0.867, 0.851);
const float fresnelReflective = 0.7;
const float edgeSoftness = 1;
const float minBlueness = 0.2;
const float maxBlueness = 0.75;
const float murkyDepth = 20;
const vec2 nearFarPlanes = vec2(0.1, 1000.0);

out vec4 FragColor;

uniform sampler2D waterReflection;
uniform sampler2D waterRefraction;
uniform sampler2D waterRefractionDepth;

in vec4 clipSpace;
in vec4 clipSpaceGrid;
in vec3 Normal;
in vec3 toCamera;
in vec3 Specular;
in vec3 Diffuse;


vec3 applyMurkiness(vec3 refractColour, float waterDepth){
	float murkyFactor = smoothstep(0, murkyDepth, waterDepth);
	float murkiness = minBlueness + murkyFactor * (maxBlueness - minBlueness);
	return mix(refractColour, waterColor, murkiness);
}

float calculateFresnel() {
	vec3 viewVector = normalize(toCamera);
	vec3 normal = normalize(Normal);
	float refractiveFactor = dot(viewVector, normal);
	refractiveFactor = pow(refractiveFactor, fresnelReflective);
	return clamp(refractiveFactor, 0.0, 1.0);
}

vec2 clipSpaceToTexCoords(vec4 clipSpace){
	vec2 ndc = (clipSpace.xy / clipSpace.w);
	vec2 texCoords = ndc / 2.0 + 0.5;
	return clamp(texCoords, 0.002, 0.998);
}

float toLinearDepth(float zDepth){
	float near = nearFarPlanes.x;
	float far = nearFarPlanes.y;
	return 2.0 * near * far / (far + near - (2.0 * zDepth - 1.0) * (far - near));
}

float calculateWaterDepth(vec2 texCoords){
	float depth = texture(waterRefractionDepth, texCoords).r;
	float floorDistance = toLinearDepth(depth);
	depth = gl_FragCoord.z;
	float waterDistance = toLinearDepth(depth);
	return floorDistance - waterDistance;
}

void main() {

	vec2 texCoordsReal = clipSpaceToTexCoords(clipSpace);
	vec2 texCoordsGrid = clipSpaceToTexCoords(clipSpaceGrid);

	vec2 refractionTexCoords = texCoordsGrid;
	vec2 reflectionTexCoords = vec2(texCoordsGrid.x, 1 - texCoordsGrid.y);
	float waterDepth = calculateWaterDepth(texCoordsGrid);

	vec3 refractColor = texture(waterRefraction, refractionTexCoords).rgb;
	vec3 reflectColor = texture(waterReflection, reflectionTexCoords).rgb;

	refractColor = applyMurkiness(refractColor, waterDepth);
	reflectColor = mix(reflectColor, waterColor, minBlueness);

	vec3 finalColor = mix(reflectColor, refractColor, calculateFresnel());
	finalColor = finalColor + Specular;

	FragColor = vec4(finalColor, 1.0);
	FragColor.a = clamp(waterDepth / edgeSoftness, 0.0, 1.0);

}

//#UNIFORMS
0
//#END