#version 120
uniform sampler2D texture;
uniform int maxIterations;
uniform vec3 col;
uniform vec2 screenSize;
uniform float scale;
uniform vec2 centerPos;
vec2 zsquare(vec2 z){
    return vec2(z.x * z.x-z.y*z.y, 2*z.x*z.y);
}
float color(vec2 xy){
    float col = 0;
    vec2 z = xy;
    for (int i = 0; i < maxIterations; i++){
        z = zsquare(z)+xy;
        if(length(z)>2){
            break;
        }
        col += 1/float(maxIterations);
    }
    return col;
}
void main()
{
    vec2 uv = gl_TexCoord[0].xy;
    uv.x *= screenSize.x/screenSize.y;
    uv -= vec2(0.5, 0.5);
    uv *= scale;
    uv += centerPos;
    gl_FragColor = vec4(pow(color(uv), 0.45)) * vec4(col,1);
}
