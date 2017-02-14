//#include "LightHelper.hlsli"

Texture2D shaderTexture;
SamplerState SampleType;
struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float4 color : COLOR;
    
};
cbuffer texturing : register(b0)
{
    float WhichTexture;
    float gammaRatio;
    float2 padding;
}


float4 main(PixelInputType input) : SV_TARGET
{
    float4 textureColor;
    float4 finalColor;

    textureColor = shaderTexture.Sample(SampleType, input.tex);
    finalColor = (textureColor * input.color);

    finalColor.x *= gammaRatio;

    finalColor.y *= gammaRatio;

    finalColor.z *= gammaRatio;

    return finalColor;
}