struct PixelInput
{
	float4 position : SV_POSITION;  // float3 position : POSITION;	 //화면엔 그려지나, 매프레임, 콘솔 오류남!  //https://learn.microsoft.com/ko-kr/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics //
	float3 color : COLOR;
	float2 texCoord : TEXCOORD;
};



float4 main(PixelInput input) : SV_TARGET
{

	//return float4(input.color, 1.0f);
	return float4(input.texCoord, 0.0f,1.0f);
}