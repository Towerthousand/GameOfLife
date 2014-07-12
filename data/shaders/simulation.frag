#version 420

uniform sampler2D input;

uniform int width;
uniform int height;

in vec2 v_texCoord;

out vec3 finalColor;

float dx[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
float dy[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

void main(void) {
    float x = width*v_texCoord.x;
    float y = height*v_texCoord.y;
    vec3 prev = texture(input, v_texCoord).rgb;
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
    finalColor = next?(alive? prev : color/3.0f):vec3(0.0f);
}
