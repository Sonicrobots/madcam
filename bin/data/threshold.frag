// fragment shader
#version 150

// this is how we receive the texture
uniform sampler2DRect tex1;
in vec2 varyingtexcoord;
out vec4 outputColor;

void main()
{
  vec4 texel = texture(tex1, varyingtexcoord);
  outputColor = vec4(texel.g, texel.b, texel.r, 1);
}
