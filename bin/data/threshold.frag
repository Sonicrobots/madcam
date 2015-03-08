#version 330

uniform sampler2DRect tex0;

uniform float threshold;

uniform int xoffset;
uniform int yoffset;

uniform float winWidth;
uniform float winHeight;

layout(origin_upper_left) in vec2 gl_FragCoord;

in vec2 TexCoord0;
out vec4 outputColor;

void main()
{
  // float r = gl_FragCoord.x / winWidth;
  // float g = gl_FragCoord.y / winHeight;
  vec4 texel0 = texture(tex0, gl_FragCoord.xy);

  if(texel0.r > threshold && texel0.g > threshold && texel0.b > threshold) {
    outputColor = vec4(texel0.g, texel0.g, texel0.g, 1.0);
  } else {
    outputColor = vec4(0,0,0,0);
  }
}
