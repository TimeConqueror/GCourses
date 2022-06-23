struct TransformData {
	row_major float4x4 worldXLightViewProj;
};

cbuffer TransformBuffer : register(b0)
{
TransformData Transform;
}

Texture2D DiffuseMap : register(t0);

SamplerState Sampler {
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VS_IN {
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
};

struct PS_IN {
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
};

PS_IN VSMain(VS_IN input) {
	PS_IN output = (PS_IN)0;

	output.pos = mul(float4(input.pos, 1.0), Transform.worldXLightViewProj);
	output.uv = input.uv;

	return output;
}

void PSMain(PS_IN input) {
	float4 diffuse = DiffuseMap.Sample(Sampler, input.uv);
	clip(diffuse.a - 0.15f);
}
