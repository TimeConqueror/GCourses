cbuffer cBuffer : register(b0) {
	float x;
	float y;
}

struct VS_INPUT
{
	float4 pos : POSITION;
	float4 col : COLOR;
};

struct PS_INPUT
{
	float4 pos : SV_POSITION;
 	float4 col : COLOR;
};

PS_INPUT VSMain(VS_INPUT input)
{
	input.pos.x += x;
	input.pos.y += y;
	
//	output.pos = float4(input.pos, 1.0f);
	//output.col.rgba = float4(input.col.rgb, 1.0F);
	//input.col.rgb = float4(0.0F, 0.0F, 1.0F, 1.0F);

	//printf("%s", output.pos.x);
	
	return input;
}

float4 PSMain(PS_INPUT input) : SV_Target
{

//#ifdef TEST
	//if (input.pos.x > 300) { input.col = float4(0.0F, 1.0F, 0.0F, 1.0F); return input.col; }
//#endif
	return input.col;
}