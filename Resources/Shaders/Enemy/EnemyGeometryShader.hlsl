#include "EnemyHeader.hlsli"

//�l�p�`�̒��_��
static const uint vnum = 4;

//�Z���^�[����I�t�Z�b�g
static const float4 offset_array[vnum] =
{
	float4(-20.5f,-20.5f,10.1f,0.0f),	//����
	float4(-20.5f,+20.1f,10.1f,0.0f),	//����
	float4(+20.5f,-20.5f,10.1f,0.0f),	//�E��
	float4(+20.5f,+20.5f,10.1f,0.0f),	//�E��
};

//uv
static const float2 uv_array[vnum] =
{
	float2(0.0f,1.0f),
	float2(0.0f,0.0f),
	float2(1.0f,1.0f),
	float2(1.0f,0.0f),
};

//�_�̓��͂���l�p�`���o��
[maxvertexcount(vnum)]
void main(
	point VSOutput input[1] : SV_POSITION, 
	inout TriangleStream< GSOutput > output
)
{
	GSOutput element;

	for (uint i = 0; i < vnum; i++)
	{
		if(input[0].flag == 1)
		{
			//���S����̃I�t�Z�b�g���X�P�[�����O
			float4 offset = offset_array[i] * 5.0f;
			//���S����̃I�t�Z�b�g���r���{�[�h��]
			//offset = mul(viewproj, offset);
			//���[���h���W�x�[�X�ł��炷
			element.svpos = input[0].svpos + offset;
			element.worldpos = input[0].worldpos + offset;
			element.normal = input[0].normal;
			element.tpos = input[0].tpos+ offset;
			//�r���[�A�ˉe�ϊ�
			// element.svpos = mul(world, element.svpos);
			element.uv = input[0].uv;
			element.flag = 1;
			output.Append(element);
		}
		else
		{
			element.svpos = input[0].svpos;
			element.worldpos = input[0].worldpos;
			element.normal = input[0].normal;
			element.uv = input[0].uv;
			element.tpos = input[0].tpos;
			element.flag = 0;
			output.Append(element);
		}
	}
}