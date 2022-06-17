cbuffer	cBuffer : register(b0)
{
	row_major float4x4 mat;
};

Texture2D DiffuseMap : register(t0);
SamplerState Sampler : register(s0);

struct VS_INPUT
{
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
};

struct PS_IN
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
};

PS_IN VSMain(VS_INPUT input)
{
	PS_IN output = (PS_IN)0;

	output.pos = mul(float4(input.pos, 1.0), mat);
	output.uv = input.uv;

	return output;
}

float4 PSMain(PS_IN input) : SV_Target
{
	float4 color = DiffuseMap.Sample(Sampler, input.uv);
	//clip(color.a - 0.01f);
	return color;
}