#version 330

in vec3 inWorldPosition;

out vec3 outPosition;
out float outWeight;

uniform vec2 uBrushCenter;
uniform float uBrushRadius;

void main(void)
{
    float distance = length(inWorldPosition.xy - uBrushCenter);
    outPosition = inWorldPosition;
    outWeight = 1.0 - min(distance / uBrushRadius, 1.0);
}
