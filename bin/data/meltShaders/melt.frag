#version 150

#pragma include "noise.glsl"
#define PI 3.14159265358979

// these are our textures
uniform sampler2D tex0;//this is the background texture
uniform sampler2D tex1;

uniform vec2 u_mouse;
uniform vec2 u_resolution;
uniform float u_meltVal;
uniform float u_fadeVal;
uniform vec3 u_backColor;

// this comes from the vertex shader
in vec2 texCoordVarying;

// this is the output of the fragment shader
out vec4 outputColor;

void main()
{
    // Get color values from the background and foreground
    vec2 uv = texCoordVarying;
    //uv *= 5.;
    uv.x -= sin(uv.y*PI*2.) * 1./u_resolution.y*5 * u_meltVal;
    //uv.x += snoise(vec2(uv)) * 0.005;
    //uv = fract(uv);
    vec4 color = texture(tex0, uv);
    vec4 col1 = texture(tex1, uv);
    
    color.rgb = mix(color.rgb, u_backColor.rgb, u_fadeVal);
    //color.rgb += col1.rgb*0.05;
    color = min(vec4(1.), color);
    
    //mix colors from background and foreground based on the mask value
    outputColor = color;
}
