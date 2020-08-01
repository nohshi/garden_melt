#version 150

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
    uv.x -= sin(uv.y*PI*2.) * 1./u_resolution.y*5 * u_meltVal;
    
    vec4 color = texture(tex0, uv);
    vec4 col1 = texture(tex1, uv);
    
    color.rgb = mix(color.rgb, u_backColor.rgb, u_fadeVal);
    color = min(vec4(1.), color);
    
    outputColor = color;
}
