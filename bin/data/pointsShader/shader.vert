#version 150

// these are from the programmable pipeline system
uniform mat4 modelViewProjectionMatrix;
in vec4 position;
in vec2 texcoord;

in float pointsize;
in vec4 color;


out vec2 texCoordVarying;
out vec4 colorVarying;

void main()
{
    
    // this is the resulting vertex position
    gl_Position = modelViewProjectionMatrix * position;;
    gl_PointSize = pointsize;
    colorVarying = color;
    // pass the texture coordinates to the fragment shader
    //texCoordVarying = texcoord;
}
