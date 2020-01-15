#version 330 core
#define M_PI 3.1415926535897932384626433832795
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 instancesimpleModelMatrix;
layout (location = 6) in vec4 instanceShade;

uniform float time;
uniform mat4 projection;
uniform mat4 view;
out vec2 TexCoord;
out vec4 Shade;
out vec3 pos;
out vec3 vpos;

void main() {
  mat4 modelmatrix = mat4(
    1., 0., 0., 0.,
    0., 1., 0., 0.,
    0., 0., 1., 0.,
    0., 0., 0., 1.
  );
  modelmatrix[3] = vec4(instancesimpleModelMatrix, 1.);
  gl_Position = projection * view * modelmatrix * vec4(aPos, 1.0);
  TexCoord = aTexCoord;
  Shade = instanceShade;
  vpos = aPos;
  pos = instancesimpleModelMatrix;
}
 