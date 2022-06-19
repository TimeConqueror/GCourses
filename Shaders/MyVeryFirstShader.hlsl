cbuffer cBuffer : register(b0) {
	row_major float4x4 world;
	row_major float4x4 worldProjTransform;
	row_major float4x4 invertedWorldTransform;
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
{//1
	PS_INPUT output;
	output.pos = mul(input.pos, worldProjTransform);
	output.col = input.col;
	return output;
	//2
	////input.pos.x = mat[0][3];
	//input.pos.y = mat[1][3];
	
	// return input;
	//3
	// PS_INPUT output = (PS_INPUT)0;
	// output.pos.x = input.pos.x + mat[0][3];
	// output.pos.y = input.pos.y + mat[1][3];
	// output.pos.z = input.pos.z + mat[2][3];
	//
	// output.pos.z = input.pos.z;
	// output.pos.w = input.pos.w;
	// output.col = input.col;
	// return output;
}

float4 PSMain(PS_INPUT input) : SV_Target
{

//#ifdef TEST
	//if (input.pos.x > 300) { input.col = float4(0.0F, 1.0F, 0.0F, 1.0F); return input.col; }
//#endif
	//return input.col;
float4 col = input.col;
return col;
}