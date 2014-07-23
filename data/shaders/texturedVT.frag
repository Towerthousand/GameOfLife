#version 420

uniform sampler2D diffuse;
in vec2 vTexCoord;
out vec4 color;

void main(void) {
	vec3 col = texture(diffuse,vTexCoord).xyz;
	if(length(col) == 0.0f) discard;
	color = vec4(col, 1.0);
}
