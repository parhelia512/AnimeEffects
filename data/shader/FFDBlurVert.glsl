#version 330

in vec3 inPosition;
in float inWeight;
in vec3 inOriginPosition;
in ivec2 inIndexRange;

out vec3 outPosition;

uniform sampler1D uConnections;
uniform int uConnectionCount;
uniform float uBlurPressure;

void main(void)
{
    vec3 pos = inPosition - inOriginPosition;
    int indexBegin = inIndexRange.x;
    int indexCount = inIndexRange.y;

#if 1

    vec3 blurPos = pos * (1.0 - uBlurPressure);

    for (int i = 0; i < indexCount; ++i)
    {
        vec2 connect = texture(uConnections, (indexBegin + i + 0.5) / uConnectionCount).xy;
        blurPos += vec3(connect * (uBlurPressure / indexCount), 0.0);
    }

#endif

    outPosition = blurPos * inWeight + pos * (1 - inWeight) + inOriginPosition;
}
