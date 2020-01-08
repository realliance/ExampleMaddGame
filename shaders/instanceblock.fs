#version 330 core
#define M_PI 3.1415926535897932384626433832795
out vec4 FragColor;
in vec2 TexCoord;
in vec4 Shade;

uniform int textureEnabled;
uniform sampler2D textureobj;
vec4 FragTexture;

void main() {
  if(textureEnabled == 1){
    FragColor = texture(textureobj, TexCoord) * Shade;
  }else{
    FragColor = Shade;
  }
}
