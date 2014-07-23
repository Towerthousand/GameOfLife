#version 420

uniform sampler2D tex;
uniform vec2 invResolution;
uniform float alpha;

out vec4 finalColor;

void main(void) {
    vec2 vTexCoord = gl_FragCoord.xy*invResolution;
	finalColor = vec4(texture(tex,vTexCoord).xyz, alpha);
}
