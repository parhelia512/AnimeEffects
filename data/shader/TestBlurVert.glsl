#version 330

in vec3 inPosition;
in float inIndex;
out vec3 outPosition;

uniform sampler1D uTexture;
uniform int uCount;

void main(void)
{
    outPosition = inPosition + texture(uTexture, (inIndex + 0.5) / uCount).xyz;
}
