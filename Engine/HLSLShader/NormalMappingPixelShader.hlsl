#include "Common.hlsli"

struct PixelInput
{
	float4 position : SV_POSITION;  // float3 position : POSITION;	 //화면엔 그려지나, 매프레임, 콘솔 오류남!  //https://learn.microsoft.com/ko-kr/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics //
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL;
    float3 cameraDirection : TEXCOORD1;

	float3 tangent : TANGENT;	//정점의 픽셀은, 픽셀의 입력이다
    float3 bitangent : BITANGENT;
};

// Texture.
Texture2D diffuseMap : register(t0);
Texture2D normalMap : register(t1);
SamplerState diffuseSampler : register(s0);

float4 main(PixelInput input) : SV_TARGET
{
	// Sampling.
    float4 texColor = diffuseMap.Sample(diffuseSampler, input.texCoord);
	float4 tangentNormal = normalMap.Sample(diffuseSampler, input.texCoord);	//면을 기준으로 Z 축으로 정의하는 특별한 공간을 기준으로, 노멀 저장하기에, 노멀에서 읽어오면, 그 노멀은 탄젠트 공간 안에 있고, 이를 월드공간으로 변형해야, 조명과 계산이 가능하다. 혹은 반대로 : 같은공간 안에 있기만 하면 된다.
	tangentNormal = tangentNormal * 2 - 1;

	// Tangent to world transformation matrix.
	float3x3 tangentToWorld = float3x3(
		normalize(input.tangent)	/*T - X*/
		,normalize(input.bitangent)	/*B - Y*/
		,normalize(input.normal)	/*N - Z*/
	);	//공간 변환 행렬.

	//Light Dir
	float3 lightDir = -float3(500.f, 500.f, -500.f);	
	lightDir = normalize(lightDir);

	//World Normal
	float3 worldNormal =normalize(mul(tangentNormal.xyz, tangentToWorld));

	//Lambert
	float nDotl =CalcLambert(worldNormal, lightDir);

   	float4 ambient = texColor * float4(0.2f, 0.2f, 0.2f, 1);
    float4 diffuse = texColor * nDotl;
    float4 finalColor = ambient + diffuse;

	//final
	finalColor = texColor * nDotl;


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

	//Blinn-Phong (specular).
	specular = CalcBlinnPhong(worldNormal, lightDir, input.cameraDirection);

	//Phong (specular)//앰비언트 + 디퓨즈 + 하이라이트,스페큘러 = 퐁 //Phong (specular)
	finalColor += float4(0.4f, 0.6f, 0.8f, 1) * specular;
	return finalColor;

	finalColor += float4(0.4f,0.6f,0.8f,1)*specular;
	//return ambient;
	
	//스페큘러에 색 넣기
	finalColor += float4(0.4f,0.6f,0.8f,1)*specular;
	return finalColor;

	//finalColor += specular;
	finalColor += specular;
	return float4(specular,specular,specular,1);
	//return float4(specular, specular, specular, 1);
//	return finalColor;
}