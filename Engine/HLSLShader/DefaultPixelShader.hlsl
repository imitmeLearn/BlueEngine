struct PixelInput
{
	float3 position : POSITION;
	float3 color : COLOR;
};


float4 main(PixelInput input) : SV_TARGET
{
	return float4(input.color, 1.0f);
}