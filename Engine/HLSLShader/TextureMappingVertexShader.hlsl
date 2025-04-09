struct VertexInput
{
	float3 position : POSITION;
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL;
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
};

struct VertexOutput
{
	float4 position : SV_POSITION;
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
	float3 normal : NORMAL;
};

VertexOutput main(VertexInput input )
{
	VertexOutput output;
	//output.position = float4(input.position, 1);	//그려짐.
	output.position = mul(float4(input.position,1), worldMatrix); //Transform 추가해서, 그려짐.
	output.position = mul(output.position,view);	//물체 위치제어 것에, 카메라 위치로! 위에는 world 변환이고, 지금 줄은 view 공간 // 이렇게 공간 변환 한 것을, 다음줄에서, 투영할거야!
	output.position = mul(output.position,projection);

	output.color = input.color;
	output.texCoord = input.texCoord;

	output.normal = mul(input.normal, (float3x3) worldMatrix );
	//쉐이더 모두 공간에서 이뤄진다? 기준은 계산에 해당하는 재료는 같은 공간 변환 처리가 끝나야 함.  조명방향은 공간이 어딜까?

	return output;
}