// fragment shader
#version 150

// this is how we receive the texture
uniform sampler2DRect tex1;
uniform float alpha;
uniform int amountX;
uniform int amountY;
uniform int mode;

in vec2 varyingtexcoord;
out vec4 outputColor;

float hash( float n )
{
  return fract( sin(n) * float(amountX * amountY));
}


float noise( vec2 p )
{
  vec2 pi = floor( p );
  vec2 pf = fract( p );


  float n = pi.x + 59.0 * pi.y;

  pf = pf * pf * (3.0 - 2.0 * pf);

  return mix(
      mix( hash( n ), hash( n + 1.0 ), pf.x ),
      mix( hash( n + 59.0 ), hash( n + 1.0 + 59.0 ), pf.x ),
      pf.y );
}

float noise( vec3 p )
{
  vec3 pi = floor( p );
  vec3 pf = fract( p );

  float n = pi.x + 59.0 * pi.y + 256.0 * pi.z;

  pf.x = pf.x * pf.x * (3.0 - 2.0 * pf.x);
  pf.y = pf.y * pf.y * (3.0 - 2.0 * pf.y);
  pf.z = sin( pf.z );

  float v1 =
      mix(
          mix( hash( n ), hash( n + 1.0 ), pf.x ),
          mix( hash( n + 59.0 ), hash( n + 1.0 + 59.0 ), pf.x ),
          pf.y );

  float v2 =
      mix(
          mix( hash( n + 256.0 ), hash( n + 1.0 + 256.0 ), pf.x ),
          mix( hash( n + 59.0 + 256.0 ), hash( n + 1.0 + 59.0 + 256.0 ), pf.x ),
          pf.y );

  return mix( v1, v2, pf.z );
}

void main()
{
  vec4 texel = texture(tex1, varyingtexcoord);
  //outputColor = vec4(texel.r, texel.g, texel.b, alpha);

  if(mode == 0) {
    outputColor = texel;
  }
  else if(mode == 1) {
    outputColor = vec4(float(amountY / 4) * texel.r, float(amountX / 4) * texel.b, float(amountY / 4) * texel.g, alpha);
  }
  else if(mode == 2) {
    outputColor = vec4(float(amountY / 4) * texel.b, float(amountX / 4) * texel.g, float(amountY / 4) * texel.r, alpha);
  }
  else if(mode == 3) {
    outputColor = vec4(float(amountY / 4) * texel.b, float(amountX / 4) * texel.r, float(amountY / 4) * texel.g, alpha);
  }
  else if(mode == 4) {
    outputColor = vec4(float(amountY / 4) * texel.g, float(amountX / 4) * texel.b, float(amountY / 4) * texel.r, alpha);
  }
  else if(mode == 5) {
    float fac = float(amountY / 3) * ((texel.r + texel.g + texel.b) / 3.0);
    outputColor = vec4(fac, fac, fac, alpha);
  }
  else if(mode == 6) {
    float fac = ((texel.r + texel.g + texel.b) / 3.0);
    if(fac < float(amountX) / 127.0) {
      fac = 0;
    }
    outputColor = vec4(fac * (float(amountY) / 4.0), fac * (float(amountY) / 4.0), fac * (float(amountY) / 4.0), alpha);
  }
  else if(mode == 7) {
    vec3 iResolution = vec3(1920.0, 1080.0, 0);
    vec2 uv = varyingtexcoord.xy / iResolution.xy;
    uv -= 0.5;

    float time = float(amountX) / 127.0;
    time = 0.5 + 0.5 * sin( time * 6.238 );
    time = texture2DRect( tex1, vec2(0.5,0.5) ).x;

    if( amountX < 20 )
    {
      // scene 0
      // uv *= 1.0;
    }
    else if( amountX < 40 )
    {
      // scene 1

      uv.x += 100.55;
      uv *= 0.00005;
    }
    else if( amountX < 80 )
    {
      // scene 2
      uv *= 0.00045;
    }
    else if( amountX < 100 )
    {
      // scene 3
      uv *= 500000.0;
    }
    else if( amountX < 110 )
    {
      // scene 3
      uv *= 0.000045;
    }


    float fft = texture2DRect( tex1, vec2(uv.x,0.25) ).x;
    float ftf = texture2DRect( tex1, vec2(uv.x,0.15) ).x;
    float fty = texture2DRect( tex1, vec2(uv.x,0.35) ).x;
    uv *= 200.0 * sin( log( fft ) * 10.0 );

    if( sin( fty ) < 0.5 )
      uv.x += sin( fty ) * sin( cos( float(amountX) ) + uv.y * 40005.0 ) ;

    // mat2 m = mat2( cos( float(amountX) ), -sin( float(amountX) ), sin( float(amountX) ), cos( float(amountX) ) );
    // uv = uv * m;
    uv *= sin( float(amountX) * 1709.0 );

    vec3 p;
    p.x = uv.x;
    p.y = uv.y;
    p.z = sin( 0.0 * (float(amountY) * 100.0) * ftf );

    float no = noise(p);

    vec3 col = vec3(
        hash( no * 6.238  * cos( float(amountY) * 2800.0) ),
        hash( no * 6.2384 + 0.4 * cos( float(amountY) * 20.25 ) ),
        hash( no * 6.2384 + 0.8 * cos( float(amountY) * 120.8468 ) ) );

    float b = dot( uv, uv );
    b *= 1000.0;
    b = b * b;
    col.y *= b;

    outputColor = texel / vec4(col,1.0);
  }
  else {
    outputColor = vec4(float(amountY / 3) * texel.r, float(amountX / 3) * texel.g, float(amountY / 3) * texel.b, alpha);
  }
}
