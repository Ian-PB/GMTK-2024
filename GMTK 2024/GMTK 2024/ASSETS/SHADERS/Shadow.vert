#version 120  // Replace with the appropriate version for your needs


void main()
{
    // Offset value
    float offset = 20.0;

    // Original vertex position
    vec4 originalPosition = gl_Vertex;
    
    // Offset the vertex position
    vec4 offsetPosition = originalPosition + vec4(offset, offset, 0.0, 0.0);



    // transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * offsetPosition;

    // transform the texture coordinates
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;



    // forward the vertex color
    gl_FrontColor = gl_Color;
}