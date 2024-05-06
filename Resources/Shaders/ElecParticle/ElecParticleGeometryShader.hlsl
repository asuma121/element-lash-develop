#include "ElecParticleHeader.hlsli"

//�l�p�`�̒��_��
static const uint vnum = 24;

//�Z���^�[����I�t�Z�b�g
static const float4 offset_array[4] =
{
	float4(-0.1f,-0.1f,0.0f,0.0f),	//����
	float4(-0.1f,+0.1f,0.0f,0.0f),	//����
	float4(+0.1f,-0.1f,0.0f,0.0f),	//�E��
	float4(+0.1f,+0.1f,0.0f,0.0f),	//�E��
};

//uv
static const float2 uv_array[4] =
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
    float4 offset[4];
	//���_���W��8����
    for (int i = 0; i < 4;i++)
    {
        offset[i] = offset_array[i] * input[0].scale;
        //offset[i] = mul(matBillboard, offset[i]);
    }
    float4 pos[8] =
    {
        input[0].pos1 + offset[0], //�O����0
        input[0].pos1 + offset[1], //�O����1
        input[0].pos1 + offset[2], //�O�E��2
        input[0].pos1 + offset[3], //�O�E��3
        input[0].pos2 + offset[0], //������4
        input[0].pos2 + offset[1], //������5
        input[0].pos2 + offset[2], //���E��6
        input[0].pos2 + offset[3], //���E��7
    };
    //�C���f�b�N�X�f�[�^
    float indecs[24] =
    {
        0,4,5,0,1,5,   //����
        1,5,7,1,3,7,    //���
        3,7,6,3,1,7,    //�E��
        2,4,6,0,2,4, //����
    };
     //�C���f�b�N�X�f�[�^
    float indecs2[24] =
    {
        0, 0, 1, 0, 1, 1, //����
        1, 1, 3, 1, 3, 3, //���
        3, 3, 2, 3, 1, 3, //�E��
        2, 0, 2, 0, 2, 0, //����
    };
    for (uint i = 0; i < vnum; i++)
    {
        element.svpos = pos[indecs[i]];
		//�r���[�A�ˉe�ϊ�
        element.svpos = mul(mat, element.svpos);
        element.uv = uv_array[indecs2[i]];
        element.frame = input[0].frame;
        output.Append(element);
    }
	//for (uint i = 0; i < vnum; i++)
	//{
	//	if(i < 4)
 //       {
	//		////���S����̃I�t�Z�b�g���X�P�[�����O
 //  //         float4 offset = offset_array[i] * input[0].scale;
	//		////���S����̃I�t�Z�b�g���r���{�[�h��]
 //  //         offset = mul(matBillboard, offset);
	//		////���[���h���W�x�[�X�ł��炷
 //  //         element.svpos = pos[i] + offset;
 //           element.svpos = pos[i];
	//		//�r���[�A�ˉe�ϊ�
 //           element.svpos = mul(mat, element.svpos);
 //           element.uv = uv_array[0];
 //           element.frame = input[0].frame;
 //           output.Append(element);
 //       }
 //       else
 //       {
	//		////���S����̃I�t�Z�b�g���X�P�[�����O
 //  //         float4 offset = offset_array[i] * input[0].scale;
	//		////���S����̃I�t�Z�b�g���r���{�[�h��]
 //  //         offset = mul(matBillboard, offset);
	//		////���[���h���W�x�[�X�ł��炷
 //  //         element.svpos = pos[i] + offset;
 //           element.svpos = pos[i];
	//		//�r���[�A�ˉe�ϊ�
 //           element.svpos = mul(mat, element.svpos);
 //           element.uv = uv_array[0];
 //           element.frame = input[0].frame;
 //           output.Append(element);
 //       }
 //   }
}