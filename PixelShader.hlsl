float4 main(float3 col:Color) : SV_TARGET
{
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
	return float4(col,1.0f);
}