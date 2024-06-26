#version 330

#variation HARDNESS 0

in vec3 inPosition;
in vec3 inWorldPosition;
in vec3 inOriginPosition;

out vec3 outPosition;
out float outPower;

uniform vec2 uBrushCenter;
uniform float uBrushRadius;
uniform float uBrushPressure;

void main(void)
{
    float distance = length(inWorldPosition.xy - uBrushCenter);
    float linearRate = min(distance / uBrushRadius, 1.0);
    float rate = linearRate;

#if HARDNESS == 0
    rate *= rate;
#elif HARDNESS == 1
    rate *= rate;
    rate *= rate;
#elif HARDNESS == 2
    rate *= rate;
    rate *= rate;
    rate *= rate;
#endif

    float power = uBrushPressure * (1.0 - rate);
    outPosition = inOriginPosition + (1.0 - power) * (inPosition - inOriginPosition);
    outPower = 1.0 - linearRate;
}
