struct VertexInput
{
	float3 position : POSITION;
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
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
};

VertexOutput main(VertexInput input )
{
	VertexOutput output;
	//output.position = float4(input.position, 1);	//출력 4개로 그냥 확장시켜 전달말 했었는데,
	output.position = mul(float4(input.position,1), worldMatrix); // 확장시키고, 곱해줌worldMatrix는 열우선행렬로 보낼거임. //행렬정보 넘어와 될거임
	output.position = mul(output.position,view);
	output.position = mul(output.position,projection);

	output.color = input.color;
	output.texCoord = input.texCoord;

	return output;
}