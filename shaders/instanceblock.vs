#version 330 core
#define M_PI 3.1415926535897932384626433832795
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in mat4 instanceModelMatrix;
layout (location = 6) in vec4 instanceShade;

uniform float time;
uniform mat4 projection;
uniform mat4 view;
out vec2 TexCoord;
out vec4 Shade;

void main() {
  gl_Position = projection * view * instanceModelMatrix * vec4(aPos, 1.0);
  TexCoord = aTexCoord;
  Shade = instanceShade;
}
 