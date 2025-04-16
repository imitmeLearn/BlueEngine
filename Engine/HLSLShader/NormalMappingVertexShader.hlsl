struct VertexInput
{
	float3 position : POSITION;
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL;
	
	float3 tangent : TANGENT;
    float3 bitangent : BITANGENT;
};

//ConstantBuffer
cbuffer Transform: register(b0)
{
	matrix worldMatrix;
};
//CameraBuffer
cbuffer Camera : register(b1)
{
	matrix view;
	matrix projection;
	float3 cameraDirection; //12+4 상수버퍼 강제 정렬 필요 ㅣ dx 의 경우.
	float padding; 
};

struct VertexOutput
{
	float4 position : SV_POSITION;
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL;
	float3 cameraDirection : TEXCOORD1;

	float3 tangent : TANGENT;
    float3 bitangent : BITANGENT;
};

VertexOutput main(VertexInput input )
{
	VertexOutput output;
	//output.position = float4(input.position, 1);	//그려짐.
	output.position = mul(float4(input.position,1), worldMatrix); //Transform 추가해서, 그려짐.
	float3 worldPosition = output.position.xyz;
	
	output.position = mul(output.position,view);	//물체 위치제어 것에, 카메라 위치로! 위에는 world 변환이고, 지금 줄은 view 공간 // 이렇게 공간 변환 한 것을, 다음줄에서, 투영할거야!
	output.position = mul(output.position,projection);

	output.color = input.color;
	output.texCoord = input.texCoord;


	output.normal = mul(input.normal, (float3x3) worldMatrix );
	output.tangent = mul(input.tangent, (float3x3) worldMatrix );
	output.bitangent = mul(input.bitangent, (float3x3) worldMatrix );

	output.cameraDirection = normalize(worldPosition - cameraDirection);
	return output;
}