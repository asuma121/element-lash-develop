#include "ElecParticleHeader.hlsli"

//四角形の頂点数
static const uint vnum = 24;

//センターからオフセット
static const float4 offset_array[4] =
{
	float4(-0.1f,-0.1f,0.0f,0.0f),	//左下
	float4(-0.1f,+0.1f,0.0f,0.0f),	//左上
	float4(+0.1f,-0.1f,0.0f,0.0f),	//右下
	float4(+0.1f,+0.1f,0.0f,0.0f),	//右上
};

//uv
static const float2 uv_array[4] =
{
	float2(0.0f,1.0f),
	float2(0.0f,0.0f),
	float2(1.0f,1.0f),
	float2(1.0f,0.0f),
};

//点の入力から四角形を出力
[maxvertexcount(vnum)]
void main(
	point VSOutput input[1] : SV_POSITION, 
	inout TriangleStream< GSOutput > output
)
{
	GSOutput element;
    float4 offset[4];
	//頂点座標を8つ生成
    for (int i = 0; i < 4;i++)
    {
        offset[i] = offset_array[i] * input[0].scale;
        //offset[i] = mul(matBillboard, offset[i]);
    }
    float4 pos[8] =
    {
        input[0].pos1 + offset[0], //前左下0
        input[0].pos1 + offset[1], //前左上1
        input[0].pos1 + offset[2], //前右下2
        input[0].pos1 + offset[3], //前右上3
        input[0].pos2 + offset[0], //奥左下4
        input[0].pos2 + offset[1], //奥左上5
        input[0].pos2 + offset[2], //奥右下6
        input[0].pos2 + offset[3], //奥右上7
    };
    //インデックスデータ
    float indecs[24] =
    {
        0,4,5,0,1,5,   //左面
        1,5,7,1,3,7,    //上面
        3,7,6,3,1,7,    //右面
        2,4,6,0,2,4, //下面
    };
     //インデックスデータ
    float indecs2[24] =
    {
        0, 0, 1, 0, 1, 1, //左面
        1, 1, 3, 1, 3, 3, //上面
        3, 3, 2, 3, 1, 3, //右面
        2, 0, 2, 0, 2, 0, //下面
    };
    for (uint i = 0; i < vnum; i++)
    {
        element.svpos = pos[indecs[i]];
		//ビュー、射影変換
        element.svpos = mul(mat, element.svpos);
        element.uv = uv_array[indecs2[i]];
        element.frame = input[0].frame;
        output.Append(element);
    }
	//for (uint i = 0; i < vnum; i++)
	//{
	//	if(i < 4)
 //       {
	//		////中心からのオフセットをスケーリング
 //  //         float4 offset = offset_array[i] * input[0].scale;
	//		////中心からのオフセットをビルボード回転
 //  //         offset = mul(matBillboard, offset);
	//		////ワールド座標ベースでずらす
 //  //         element.svpos = pos[i] + offset;
 //           element.svpos = pos[i];
	//		//ビュー、射影変換
 //           element.svpos = mul(mat, element.svpos);
 //           element.uv = uv_array[0];
 //           element.frame = input[0].frame;
 //           output.Append(element);
 //       }
 //       else
 //       {
	//		////中心からのオフセットをスケーリング
 //  //         float4 offset = offset_array[i] * input[0].scale;
	//		////中心からのオフセットをビルボード回転
 //  //         offset = mul(matBillboard, offset);
	//		////ワールド座標ベースでずらす
 //  //         element.svpos = pos[i] + offset;
 //           element.svpos = pos[i];
	//		//ビュー、射影変換
 //           element.svpos = mul(mat, element.svpos);
 //           element.uv = uv_array[0];
 //           element.frame = input[0].frame;
 //           output.Append(element);
 //       }
 //   }
}