struct PixelInput
{
	float4 position : SV_POSITION;  // float3 position : POSITION;	 //화면엔 그려지나, 매프레임, 콘솔 오류남!  //https://learn.microsoft.com/ko-kr/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics //
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
};

// Texture.
Texture2D diffuseMap : register(t0);
SamplerState diffuseSampler : register(s0);

float4 main(PixelInput input) : SV_TARGET
{
	// Sampling.
    	float4 texColor = diffuseMap.Sample(diffuseSampler, input.texCoord);

	texColor *=float4(input.color, 1.0f); 
	return texColor;

	//return float4(input.color, 1.0f);
	return float4(input.texCoord, 0.0f,1.0f);
}