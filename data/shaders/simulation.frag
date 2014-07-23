#version 420
uniform sampler2D input;
uniform int width;
uniform int height;

in vec2 vTexCoord;
out vec4 finalColor;

float dx[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
float dy[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

void main(void) {
	float x = width*vTexCoord.x;
	float y = height*vTexCoord.y;
	vec3 prev = texture(input, vTexCoord).rgb;
    bool alive = length(prev) > 0.0f;
    float sum = 0.0f;
    vec3 color = vec3(0.0f);
    for(int i = 0; i < 8; ++i){
        float nx = x+dx[i];
        float ny = y+dy[i];
        if(nx < 0 || ny < 0 || nx >= width || ny >= height) continue;
        vec3 c = texture(input, vec2(float(nx)/float(width),float(ny)/float(height))).rgb;
        if(length(c) > 0.0f) {
            color += c;
            sum += 1.0f;
        }
    }
    int n = int(sum);
    bool next = (alive?(n<2?false:(n<4?true:false)):(n==3?true:false));
	vec4 col = vec4(next?(alive? prev : color/3.0f):vec3(0.0f),1.0f);
	if(length(col.rgb) == 0.0f) discard;
	finalColor = col;
}
