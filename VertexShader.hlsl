struct VSOut {
	float3 col:Color;
	float4 pos:SV_Position;
};


cbuffer CBuf
{
	row_major matrix transform;
};

VSOut main( float2 pos : POSITION, float3 col:Color )
{
	VSOut vso;
	//vso.pos = float4(pos,0.0f,1.0f);
	vso.pos = mul(float4(pos.x, pos.y, 0.0f, 1.0f), transform);
	vso.col = col;
	return vso;
} 