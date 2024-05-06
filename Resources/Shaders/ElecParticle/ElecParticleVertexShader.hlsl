#include "ElecParticleHeader.hlsli"

//エントリーポイント
VSOutput main(float4 pos1 : POSITIONA, float4 pos2 : POSITIONB,float scale:SCALE, float frame : FRAME)
{
	//ピクセルシェーダに渡す値
	VSOutput output;
	output.pos1 = pos1;
    output.pos2 = pos2;
	output.scale = scale;
    output.frame = frame;

	return output;
}