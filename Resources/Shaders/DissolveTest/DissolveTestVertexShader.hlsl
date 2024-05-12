#include "DissolveTestHeader.hlsli"

//�X�L�j���O��̒��_�@��������
struct SkinOutput
{
	float4 pos;
	float3 normal;
};

//�X�L�j���O�v�Z
SkinOutput ComputeSkin(VSInput input)
{
	//�[���N���A
	SkinOutput output = (SkinOutput)0;

	uint iBone;	//�v�Z����{�[���ԍ�
	float weight;	//�{�[���E�F�C�g
	matrix m;	//�X�L�j���O�s��	

	//�{�[��0
	iBone = input.boneIndices.x;
	weight = input.boneWeights.x;
	m = matSkinning[iBone];
	output.pos += weight * mul(m, input.pos);
	output.normal += weight * mul((float3x3)m, input.normal);

	////�{�[��1
	//iBone = input.boneIndices.y;
	//weight = input.boneWeights.y;
	//m = matSkinning[iBone];
	//output.pos += weight * mul(m, input.pos);
	//output.normal += weight * mul((float3x3)m, input.normal);

	////�{�[��2
	//iBone = input.boneIndices.z;
	//weight = input.boneWeights.z;
	//m = matSkinning[iBone];
	//output.pos += weight * mul(m, input.pos);
	//output.normal += weight * mul((float3x3)m, input.normal);

	////�{�[��3
	//iBone = input.boneIndices.w;
	//weight = input.boneWeights.w; 
	//m = matSkinning[iBone];
	//output.pos += weight * mul(m, input.pos);
	//output.normal += weight * mul((float3x3)m, input.normal);

	return output;
}

//�G���g���[�|�C���g
VSOutput main(VSInput input)
{
	//�X�L�j���O�v�Z
	SkinOutput skinned = ComputeSkin(input);
	//�@���Ƀ��[���h�s��ɂ��X�P�[�����O ��]��K�p
	float4 wnormal = normalize(mul(world, float4(skinned.normal, 0)));
	float4 wpos = mul(world, skinned.pos);
	wpos = mul(world, wpos);
	//�s�N�Z���V�F�[�_�ɓn���l
	VSOutput output;
	//�s��ɂ����W�Ԋ�
	output.svpos = mul(mul(viewproj, world), skinned.pos);
	//���[���h�@�������̃X�e�[�W�ɓn��
	output.normal = wnormal.xyz;
	//���͒l�����̂܂܎��̃X�e�[�W�n��
	output.uv = input.uv;

	output.worldpos = wpos;

	output.tpos = mul(mul(lightviewproj, world), skinned.pos);
	//���[���h���Wx
	return output;
}