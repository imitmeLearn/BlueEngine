struct VertexInput
{
	float3 position : POSITION;
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
};

//ConstantBuffer
cbuffer Transfrom: register(b0)
{
	matrix worldMatrix;
};

struct VertexOutput
{
	float4 position : SV_Position;
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
};

VertexOutput main(VertexInput input )
{
	VertexOutput output;
	//output.position = float4(input.position, 1);	//그려짐.
	output.position = mul(float4(input.position,1), worldMatrix); //Transform 추가해서, 그려짐.
	output.color = input.color;
	output.texCoord = input.texCoord;

	return output;
}