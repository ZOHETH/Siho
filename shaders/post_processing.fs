#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D u_ScreenTexture;

const float offset = 1.0 / 300.0;  

void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // ����
        vec2( 0.0f,    offset), // ����
        vec2( offset,  offset), // ����
        vec2(-offset,  0.0f),   // ��
        vec2( 0.0f,    0.0f),   // ��
        vec2( offset,  0.0f),   // ��
        vec2(-offset, -offset), // ����
        vec2( 0.0f,   -offset), // ����
        vec2( offset, -offset)  // ����
    );

    float kernel[9] = float[](
        0.,0.,0.,
        0.,1,0.,
        0.,0.,0.);

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(u_ScreenTexture, TexCoords.st + offsets[i]));
    }
    vec3 color = vec3(0.0);
    for(int i = 0; i < 9; i++)
        color += sampleTex[i] * kernel[i];

    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));  
    FragColor = vec4(color, 1.0);
}