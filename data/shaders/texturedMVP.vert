#version 420

uniform mat4 MVP;

in vec3 a_position;
in vec2 a_texCoord;

out vec2 vTexCoord;

void main(void) {
		vTexCoord = a_texCoord;
        gl_Position = MVP * vec4(a_position,1.0);
}
