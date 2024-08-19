#version 120  // Replace with the appropriate version for your needs

uniform float speed;
uniform float time;
uniform float fullDistance;

void main()
{
    // Calculate the total time to reach the target
    float timeTillTarget = fullDistance / speed;

    // Normalize time (0 at start, 1 at the target)
    float normalizedTime = time / (timeTillTarget / 60.0);

    // Scaling logic: smoothly grow and shrink across the entire timeline
    float scale = 1.0 + sin(normalizedTime * 3.14159) * 1.0; // Smooth growth and shrink with a single sinusoidal wave

    // Y-offset for the arc effect
    float arcHeight = -75.0; // Adjust as needed for the height of the arc
    float yOffset = sin(normalizedTime * 3.14159) * arcHeight; // Single sinusoidal arc

    // Original vertex position
    vec4 originalPosition = gl_Vertex;

    // Apply the scaling transformation and Y-axis offset
    vec4 scaledPosition = originalPosition * vec4(scale, scale, scale, 1.0);
    scaledPosition.y += yOffset;

    // Transform the vertex position with the model-view-projection matrix
    gl_Position = gl_ModelViewProjectionMatrix * scaledPosition;

    // Transform the texture coordinates
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // Forward the vertex color
    gl_FrontColor = gl_Color;
}
