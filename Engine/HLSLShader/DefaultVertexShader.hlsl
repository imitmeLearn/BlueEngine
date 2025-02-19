struct VertexInput
{
	float3 position : POSITION;
	float3 color : COLOR;
	float2 texCoord : TEXTCOORD;
};

struct VertexOutput
{
	float4 position : SV_Position;
	float3 color : COLOR;
	float2 texCoord : TEXTCOORD;
};

VertexOutput main(VertexInput input )
{
	VertexOutput output;
	output.position = float4(input.position, 1);
	output.color = input.color;
	output.texCoord = input.texCoord;

	return output;
}