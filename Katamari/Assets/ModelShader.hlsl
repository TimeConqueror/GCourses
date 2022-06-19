cbuffer	cBuffer : register(b0)
{
	row_major float4x4 world;
	row_major float4x4 worldProjTransform;
	row_major float4x4 invertedWorldTransform;
};

cbuffer materialBuf : register(b1)
{
	float ambientFactor;
	float specularFactor;
	float shineFactor;
}

cbuffer lightBuf : register(b2)
{
	float3 viewerPos;
	float dummy1;
	float3 lightDirection;
	float dummy2;
	float3 lightColor;
	float dummy3;
}

Texture2D DiffuseMap : register(t0);
SamplerState Sampler : register(s0);

struct VS_INPUT
{
	float3 pos : POSITION0;
	float3 normal: NORMAL0;
	float2 uv : TEXCOORD0;
};

struct PS_IN
{
	float4 pos : SV_POSITION;
	float4 norm : NORMAL;
	float2 uv : TEXCOORD0;
	float4 worldPos: TEXCOORD1;
};

PS_IN VSMain(VS_INPUT input)
{
	PS_IN output = (PS_IN) 0;

	output.pos = mul(float4(input.pos, 1.0), worldProjTransform);
	output.norm = mul(float4(input.normal, 0.0), invertedWorldTransform);
	output.uv = input.uv;
	output.worldPos = mul(float4(input.pos, 1.0), world);

	return output;
}

float4 PSMain(PS_IN input) : SV_Target
{
	float4 color = DiffuseMap.Sample(Sampler, input.uv);
	//clip(color.a - 0.01f);
	//return color;
	//color = float4(1.0F, 1.0F, 1.0F, 1.0F);

	//float3 myColor = float3(1.0F, 1.0F, 1.0F)

	//const float3 ambient = 0.4 * float3(1.0F, 1.0F, 1.0F);
	const float3 ambient = ambientFactor * lightColor;

	const float3 normal = normalize(input.norm.xyz);
	const float diff = max(0.0, dot(-lightDirection, normal));
	const float3 diffuse = diff * lightColor;

	const float3 viewDirection = normalize(viewerPos - input.worldPos.xyz);
	const float3 reflectDirection = normalize(reflect(lightDirection, normal));
	const float spec = pow(max(0.0, dot(viewDirection, reflectDirection)), shineFactor);
	const float3 specular = specularFactor * spec * lightColor;

	float3 result = (ambient + diffuse + specular) * color.rgb;
	return float4(result,1.0F);
}