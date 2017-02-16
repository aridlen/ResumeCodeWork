///////////////////////////////////////////
//                                       //
//       THIS IS THE WORK OF:            //
//     Programmer: Aaron Ridlen          //
//     Instructor: Larri Nori            //
//      Date:  AUGUST 2016               //
//                                       //
///////////////////////////////////////////
Texture2D m_texture : register(t0);
Texture2D m_texture2 : register(t1);
SamplerState filters[2] : register(s0);



cbuffer DirectionalBuffer : register(b0)
{
	float4 dir_direction;
	float4 dir_color;
};
cbuffer Point : register(b1)
{
	//float4 pnt_direction;
	float4 pnt_pos;
	float4 pnt_color;
	float4 pnt_radius;
};
cbuffer Spot : register(b2)
{
	float4 spt_direction;
	float4 spt_pos;
	float4 spt_color;
	float4 spt_radius;
	
};
struct PixelShaderInputLights
{
	float4 pos : SV_POSITION;
	float2 uv : COLOR0;
	float3 norm : NORMAL;
	float3 worldpos:WORLD;
};
float4 main(PixelShaderInputLights input) : SV_TARGET
{
	//Directional
	float ratio = clamp(dot(normalize(-dir_direction.xyz),normalize(input.norm)),0,1);
float4 text = m_texture.Sample(filters[0], input.uv).xyzw *m_texture2.Sample(filters[0], input.uv).xyzw*2.0f;
	text = saturate(text);
	float3 dir_col = ratio * dir_color.xyz * text.xyz;
	float4 dir_final;
	dir_final.xyz = dir_col.xyz;
	dir_final.w= text.w;
	//Point
	float pnt_ratio = clamp(dot(normalize(pnt_pos.xyz - input.worldpos), normalize(input.norm)), 0, 1);
	float atten_pnt = 1.0f-clamp(length(pnt_pos.xyz - input.worldpos) / pnt_radius.xyz,0,1);
	float3 pnt_col = pnt_ratio*pnt_color.xyz*text.xyz*atten_pnt;
	float4 pnt_final;
	pnt_final.xyz = pnt_col.xyz;
	pnt_final.w = text.w;
	//Spot
	float3 spt_lightdir = normalize(spt_pos.xyz - input.worldpos.xyz);
	float surfaceratio = clamp(dot(-spt_lightdir, spt_direction.xyz),0,1);
	float factor = (surfaceratio > spt_radius.z) ? 1 : 0;
	float spt_ratio = clamp(dot(spt_lightdir, input.norm), 0, 1);
	float atten1 = 1.0f - clamp(length(spt_pos.xyz - input.worldpos) / spt_radius.x,0,1);
	float atten2 = 1.0f - clamp((spt_radius.y - surfaceratio) / (spt_radius.y - spt_radius.z),0,1);
	float3 spt_col = factor*spt_ratio*spt_color.xyz*text.xyz*atten1*atten2;
	float4 spt_final;
	spt_final.xyz = spt_col.xyz;
	spt_final.w = text.w;

	return clamp(dir_final+pnt_final+spt_final,0,1);
}