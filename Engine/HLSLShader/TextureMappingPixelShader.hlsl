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

///선택
	//Dot. Lambert
	float nDotl =saturate (dot(worldNormal, -lightDir));
	//Half Lambert.
	float maxLight =0.8f;
	nDotl = (nDotl * maxLight) + (1 - maxLight);	// 밝아짐 기본 0.5 / 0.8인경우,  0.2 더해줘야 해 그래서, 공식화 한다면,
	nDotl = pow(nDotl, 2);	//밝음 조절 가능.
	

	//final
	float4 finalColor = texColor * nDotl;


	//texColor *=float4(input.color, 1.0f); 
	//return texColor;

	//return float4(input.color, 1.0f);
	//return float4(input.texCoord, 0.0f,1.0f);
	//return float4(lightIntensity, lightIntensity, lightIntensity, 1);
	return finalColor;
}