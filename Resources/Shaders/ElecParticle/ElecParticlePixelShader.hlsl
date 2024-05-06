#include "ElecParticleHeader.hlsli"

//0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> tex : register(t0);
//0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[
SamplerState smp : register(s0);
//�G���g���[�|�C���g
float4 main(GSOutput input) : SV_TARGET
{
	//�摜�̃f�[�^ �����ۂ��F
    float4 color = float4(0.74f, 0.2f, 0.74f, 1.0f);
    
    float f = 1.0f - input.frame;

	//�A���t�@�l������
    return float4(color.x * f, color.y * f, color.z * f, 1.0f);
}