struct PixelInput
{
	float3 position : POSITION;
	float3 color : COLOR;
	float2 texCoord : TEXTCOORD;
};


float4 main(PixelInput input) : SV_TARGET
{
	//return float4(input.color, 1.0f);
	return float4(input.texCoord, 0.0f,1.0f);
}