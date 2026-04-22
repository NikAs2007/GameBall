#version 150

uniform sampler2D u_texture;
uniform float strength;
uniform float zoom;

void main(){
	vec2 thispix = gl_TexCoord[0].xy;
	float r = texture2D(u_texture, thispix + vec2(-strength, 0.0)/zoom).r;
	float g = texture2D(u_texture, thispix + vec2(0.0, 0.0)/zoom).g;
	float b = texture2D(u_texture, thispix + vec2(strength, 0.0)/zoom).b;

	

	gl_FragColor = vec4(r,g,b,1.0);
}