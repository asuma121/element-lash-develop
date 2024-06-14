#include "EnemyHeader.hlsli"

//スキニング後の頂点法線が入る
struct SkinOutput
{
	float4 pos;
	float3 normal;
	bool flag;
};

//スキニング計算
SkinOutput ComputeSkin(VSInput input)
{
	//ゼロクリア
	SkinOutput output = (SkinOutput)0;

	uint iBone;	//計算するボーン番号
	float weight;	//ボーンウェイト
	matrix m;	//スキニング行列	

	//ボーン0
	iBone = input.boneIndices.x;
	weight = input.boneWeights.x;
	m = matSkinning[iBone];
	output.pos += weight * mul(m, input.pos);
	output.normal += weight * mul((float3x3)m, input.normal);

	//ボーン1
	iBone = input.boneIndices.y;
	weight = input.boneWeights.y;
	m = matSkinning[iBone];
	output.pos += weight * mul(m, input.pos);
	output.normal += weight * mul((float3x3)m, input.normal);

	//ボーン2
	iBone = input.boneIndices.z;
	weight = input.boneWeights.z;
	m = matSkinning[iBone];
	output.pos += weight * mul(m, input.pos);
	output.normal += weight * mul((float3x3)m, input.normal);

	//ボーン3
	iBone = input.boneIndices.w;
	weight = input.boneWeights.w; 
	m = matSkinning[iBone];
	output.pos += weight * mul(m, input.pos);
	output.normal += weight * mul((float3x3)m, input.normal);

	output.flag = false;
	if(input.boneIndices.x == 5)
	{
		//左目
		if(input.uv.x >= 0.088 && input.uv.x <= 0.09)
		{
			output.flag = true;
		}
		//右目
		if(input.uv.x >= 0.66 && input.uv.x <= 0.69)
		{
			output.flag = true;
		}
	}

	return output;
}

//エントリーポイント
VSOutput main(VSInput input)
{
	//スキニング計算
	SkinOutput skinned = ComputeSkin(input);
	//法線にワールド行列によるスケーリング 回転を適用
	float4 wnormal = normalize(mul(world, float4(skinned.normal, 0)));
	float4 wpos = mul(world, skinned.pos);
	wpos = mul(world, wpos);
	//ピクセルシェーダに渡す値
	VSOutput output;
	//行列による座標返還
	output.svpos = mul(mul(viewproj, world), skinned.pos);
	//ワールド法線を次のステージに渡す
	output.normal = wnormal.xyz;
	//入力値をそのまま次のステージ渡す
	output.uv = input.uv;

	output.worldpos = wpos;

	output.tpos = mul(mul(lightviewproj, world), skinned.pos);

	if(skinned.flag == true)
	{
		output.flag = 1;
	}
	if(skinned.flag == false)
	{
		output.flag = 0;
	}

	if(timer1 == 0)
	{
		output.texFlag = false;
	}
	if(timer1 == 1000.0f)
	{
		output.texFlag = true;
	}

	//ワールド座標x
	return output;
}