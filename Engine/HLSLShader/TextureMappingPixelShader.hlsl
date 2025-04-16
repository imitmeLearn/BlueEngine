#include "Common.hlsli"

struct PixelInput
{
	float4 position : SV_POSITION;  // float3 position : POSITION;	 //화면엔 그려지나, 매프레임, 콘솔 오류남!  //https://learn.microsoft.com/ko-kr/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics //
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL;
};

// Texture.
Texture2D diffuseMap : register(t0);
SamplerState diffuseSampler : register(s0);

float4 main(PixelInput input) : SV_TARGET
{
	// Sampling.
    	float4 texColor = diffuseMap.Sample(diffuseSampler, input.texCoord);

	//Light Dir
	float3 lightDir = -float3(500.f, 500.f, -500.f);	
	lightDir = normalize(lightDir);
	//World Normal
	float3 worldNormal = normalize(input.normal);

	//Lambert
	float nDotl =CalcLambert(worldNormal, lightDir);

	//final
	float4 finalColor = texColor * nDotl;


	return finalColor;
}