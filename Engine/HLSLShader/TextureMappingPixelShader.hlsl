#include "Common.hlsli"

struct PixelInput
{
	float4 position : SV_POSITION;  // float3 position : POSITION;	 //화면엔 그려지나, 매프레임, 콘솔 오류남!  //https://learn.microsoft.com/ko-kr/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics //
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL;
	float3 cameraDirection : TEXCOORD1;
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



	//Phong (specular)
	 float specular = CalcPhong(worldNormal, lightDir, input.cameraDirection);
	// float specular = 0;
	// if(nDotl)
	// {
	// 	float3 reflection = reflect(lightDir, worldNormal);
	// 	float3 viewDirection = normalize(input.cameraDirection);
	// 	float 	rDotv = dot(reflection, -viewDirection);
	// 			rDotv = saturate(rDotv);
	// 	float shineness = 16.f;	//집중크기 : 작으면, 넓어짐 /크면 작아짐.
	// 	specular = pow(rDotv,shineness);
	// }

	//앰비언트 + 디퓨즈 + 하이라이트,스페큘러 = 퐁
	finalColor = float4(0.4f,0.6f,0.8f,1)*specular;
	return finalColor;

	finalColor = float4(0.4f,0.6f,0.8f,1)*specular;
	//return ambient;
	
	//스페큘러에 색 넣기
	finalColor = float4(0.4f,0.6f,0.8f,1)*specular;
	return finalColor;

	//finalColor += specular;
	finalColor += specular;
	return float4(specular,specular,specular,1);
//	return finalColor;
}