struct VSOut {
	float3 col:Color;
	float4 pos:SV_Position;
};


cbuffer CBuf
{
	matrix transform;
};

VSOut main( float3 pos : POSITION, float3 col:Color )
{
	VSOut vso;
	vso.pos = mul(float4(pos, 1.0f), transform);
	vso.col = col;
	return vso;
} 