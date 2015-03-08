// fragment shader
#version 150

// this is how we receive the texture
uniform sampler2DRect tex1;
uniform float amount;
uniform int mode;

in vec2 varyingtexcoord;
out vec4 outputColor;

void main()
{
  vec4 texel = texture(tex1, varyingtexcoord);
  outputColor = vec4(texel.r, texel.g, texel.b, amount);

  if(mode == 0) {
    outputColor = vec4(texel.r, texel.g, texel.b, amount);
  }
  else if(mode == 1) {
    outputColor = vec4(texel.r, texel.b, texel.g, amount);
  }
  else if(mode == 2) {
    outputColor = vec4(texel.b, texel.g, texel.r, amount);
  }
  else if(mode == 3) {
    outputColor = vec4(texel.b, texel.r, texel.g, amount);
  }
  else if(mode == 4) {
    outputColor = vec4(texel.g, texel.b, texel.r, amount);
  }
  else if(mode == 5) {
    float fac = (texel.r + texel.g + texel.b) / 3.0;
    outputColor = vec4(fac, fac, fac, amount);
  }
  else {
    outputColor = vec4(texel.g, texel.r, texel.b, amount);
  }
}
