#version 330 core
#define M_PI 3.1415926535897932384626433832795
out vec4 FragColor;
in vec2 TexCoord;
uniform vec4 shade;
in vec3 pos;
in vec3 vpos;

uniform int textureEnabled;
uniform sampler2D textureobj;
vec4 FragTexture;

void main() {
  FragColor = shade * vec4(pos*0.005, 1.0) + 0.1 * vec4(vpos, 1.0) + vec4(0,128*0.005,0,0);
}
