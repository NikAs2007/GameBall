#version 150

uniform float cenx;
uniform float ceny;
uniform float zoom;

void main() {

    vec2 cen = vec2(cenx, ceny);
    vec2 pix = gl_FragCoord.xy;

    float dist = distance(cen, pix);
    //vec3 color = vec3(1.0,1.0,0.5);
    vec3 color = vec3(1.0,1.0,0.5);
    dist = 10.0/dist;
    float alpha = 1.0;
    color *= dist/zoom;
    alpha *= dist/zoom;
    if (dist <= 1.0){
        color *= dist/zoom;
        alpha *= dist/zoom;
    }

    gl_FragColor = vec4(color,alpha);
}