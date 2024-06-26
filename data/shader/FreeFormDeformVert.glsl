#version 330

#variation HARDNESS 0

#define BLUR_GRID 5
#define BLUR_GET_GRID 4
#define BLUR_RANGE (5.0 / 4.0)

in vec3 inPosition;
in vec3 inWorldPosition;
in vec3 inXArrow;
in vec3 inYArrow;

out vec3 outPosition;
out float outWeight;

uniform vec2 uBrushCenter;
uniform vec2 uBrushVel;
uniform float uBrushRadius;
uniform float uBrushPressure;
uniform float uDividable;

void main(void)
{
    vec3 worldPos = inWorldPosition;

    float distance = length(worldPos.xy - uBrushCenter);
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

    vec3 vel;
    {
        float lenX = max(length(inXArrow.xy), uDividable);
        float lenY = max(length(inYArrow.xy), uDividable);
        vel.x = dot(uBrushVel, inXArrow.xy) / (lenX * lenX);
        vel.y = dot(uBrushVel, inYArrow.xy) / (lenY * lenY);
        vel.z = 0.0;
    }

    float power = uBrushPressure * (1.0 - rate);
    outPosition = inPosition + power * vel;
    float blurRate = min(max(distance - uBrushRadius, 0.0) / (0.5 * uBrushRadius), 1.0);
    outWeight = (1.0 - blurRate);
}
