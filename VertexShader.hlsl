struct VSOut {
	float3 col:Color;
	float4 pos:SV_Position;
};

VSOut main( float2 pos : POSITION, float3 col:Color )
{
	VSOut vso;
	vso.pos = float4(pos,0.0f,1.0f);
	vso.col = col;
	return vso;
} 