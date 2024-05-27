#include "PlayerBulletParticleHeader.hlsli"

//0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> tex : register(t0);
//0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[
SamplerState smp : register(s0);
//�G���g���[�|�C���g
float4 main(GSOutput input) : SV_TARGET
{
	//�摜�̃f�[�^
	float4 texData = float4(tex.Sample(smp,input.uv));
	
    float f = 1.0f - input.frame;
    float r = 1.0f;
    float g = 0.3f;
    float b = 0.3f;

	//�A���t�@�l������
    return float4(texData.x, texData.y * (g * f), 0, 1);
}