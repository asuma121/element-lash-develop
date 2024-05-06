#include "ElecParticleHeader.hlsli"

//0番スロットに設定されたテクスチャ
Texture2D<float4> tex : register(t0);
//0番スロットに設定されたサンプラー
SamplerState smp : register(s0);
//エントリーポイント
float4 main(GSOutput input) : SV_TARGET
{
	//画像のデータ 雷っぽい色
    float4 color = float4(0.74f, 0.2f, 0.74f, 1.0f);
    
    float f = 1.0f - input.frame;

	//アルファ値を合成
    return float4(color.x * f, color.y * f, color.z * f, 1.0f);
}