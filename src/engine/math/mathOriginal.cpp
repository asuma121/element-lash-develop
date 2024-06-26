/**
 * @file mathOriginal.cpp
 * @brief 自作した数学関数
 * @author Asuma Syota
 * @date 2023/4
 */

#include "mathOriginal.h"
#include "cmath"
#include "Matrix4.h"
#include <iostream>
#include <random>

float easeOutQuart(float x)
{ 
	return (float)(1.0f - pow(1.0f - x, 4));
}

float easeInOutQuart(float x)
{
	return x < 0.5 ? 8 * x * x * x * x : 1 - (float)(pow(-2.0f * x + 2.0f, 4) / 2.0f); 
}

float easeInQuint(float x)
{
	return x * x * x * x * x;
}

float easeOutQuint(float x)
{
	return (float)(1.0f - pow(1.0f - x, 5));
}

float easeInOutQuint(float x)
{
	return x < 0.5 ? 16 * x * x * x * x * x : 1.0f - (float)(pow(-2.0f * x + 2.0f, 5) / 2.0f);
}

float easeInExpo(float x)
{
	return x == 0 ? 0 : pow(2.0f, 10 * x - 10);
}

float easeOutExpo(float x)
{
	return x == 1 ? 1 : 1.0f - (float)(pow(2.0f, -10 * x));
}

float easeInOutExpo(float x)
{
	return x == 0
		? 0
		: x == 1
		? 1
		: x < 0.5 ? (float)(pow(2.0f, 20 * x - 10) / 2.0f)
		: (2.0f - (float)(pow(2.0f, -20 * x + 10)) / 2.0f);
}

float easeInCirc(float x)
{
	return 1.0f - (float)sqrt(1.0f - pow(x, 2));
}

float easeOutCirc(float x)
{
	return (float)sqrt(1.0 - pow(x - 1.0f, 2));
}

float easeInOutCirc(float x)
{
	return x < 0.5
		? (1.0f - (float)sqrt(1.0 - pow(2.0f * x, 2))) / 2.0f
		: ((float)sqrt(1.0 - pow(-2.0f * x + 2.0f, 2)) + 1.0f) / 2.0f;
}

float easeInBack(float x)
{
	float c1 = 1.70158f;
	float c3 = c1 + 1;

	return c3 * x * x * x - c1 * x * x;
}

float easeOutBack(float x)
{
	float c1 = 1.70158f;
	float c3 = c1 + 1;

	return 1.0f + c3 * (float)pow(x - 1.0f, 3) + c1 * (float)pow(x - 1.0f, 2);
}

float easeInOutBack(float x)
{
	float c1 = 1.70158f;
	float c2 = c1 * 1.525f;

	return x < 0.5f
		? ((float)pow(2.0f * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2.0f
		: ((float)pow(2.0f * x - 2.0f, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2.0f;
}

float easeInElastic(float x)
{
	float c4 = (2.0f * (float)PI) / 3.0f;

	return x == 0.0f
		? 0.0f
		: x == 1.0f
		? 1.0f
		: (float)-pow(2.0f, 10 * x - 10) * (float)sin((x * 10.0f - 10.75f) * c4);
}

float easeOutElastic(float x)
{
	float c4 = (2.0f * (float)PI) / 3.0f;

	return x == 0.0f
		? 0.0f
		: x == 1.0f
		? 1.0f
		: (float)pow(2.0f, -10 * x) * (float)sin((x * 10.0 - 0.75) * c4) + 1.0f;
}

float easeInOutElastic(float x)
{
	float c5 = (2.0f * (float)PI) / 4.5f;

	return x == 0.0f
		? 0.0f
		: x == 1.0f
		? 1.0f
		: x < 0.5f
		? (float)-(pow(2.0f, 20 * x - 10) * (float)sin((20.0 * x - 11.125) * c5)) / 2.0f
		: (float)(pow(2.0f, -20 * x + 10) * (float)sin((20.0 * x - 11.125) * c5)) / 2.0f + 1.0f;
}

float easeInBounce(float x)
{
	return 1 - easeOutBounce(1 - x);
}

float easeOutBounce(float x)
{
	float n1 = 7.5625;
	float d1 = 2.75;

	if (x < 1 / d1) {
		return n1 * x * x;
	}
	else if (x < 2 / d1) {
		return n1 * (x -= 1.5f / d1) * x + 0.75f;
	}
	else if (x < 2.5 / d1) {
		return n1 * (x -= 2.25f / d1) * x + 0.9375f;
	}
	else {
		return n1 * (x -= 2.625f / d1) * x + 0.984375f;
	}
}

float easeInOutBounce(float x)
{
	return x < 0.5
		? (1 - easeOutBounce(1 - 2 * x)) / 2
		: (1 + easeOutBounce(2 * x - 1)) / 2;
}

int RNG(int min, int max, bool preciseMode)
{
	if (!preciseMode) {
		//return (rand() % (max + 1 - min) + min);
		return rand() / RAND_MAX * max;
	}

	int ret = 0;
	do {
		ret = rand();
	} while (ret >= RAND_MAX - RAND_MAX % (max + 1 - min));
	ret = ret % (max + 1 - min) + min;
	return 0;
}

float GetRand(float min, float max)
{
	// 乱数生成器の初期化
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);

	// 乱数生成
	return dis(gen);
}

//uint64_t GetRand(uint64_t minVal, uint64_t maxVal) {
//	// 乱数生成器
//	static std::mt19937_64 mt64(0);
//
//	// [min_val, max_val] の一様分布整数 (int) の分布生成器
//	std::uniform_int_distribution<uint64_t> get_rand_uni_int(minVal, maxVal);
//
//	// 乱数を生成
//	return get_rand_uni_int(mt64);
//}

float shake(int num, int strength)
{
	// -strengthからstrengthの範囲でランダムな値を生成
	float shake = ((float)rand() / RAND_MAX) * 2 * strength - strength;
	return num + shake;
}

float comparisonMax(float num1, float num2)
{
	if (num1 >= num2)
	{
		return num1;
	}

	return num2;
}

float comparisonMin(float num1, float num2)
{
	if (num1 <= num2)
	{
		return num1;
	}

	return num2;
}

float easeInSine(float x)
{
	return 1 - (float)cos((x * (float)PI) / 2.0f);
}

float easeOutSine(float x)
{
	return (float)sin((x * (float)PI) / 2.0f);
}

float easeInOutSine(float x)
{
	return (float)-(cos((float)PI * x) - 1.0f) / 2.0f;
}

float easeInQuad(float x)
{
	return x * x;
}

float easeOutQuad(float x)
{
	return 1 - (1 - x) * (1 - x);
}

float easeInOutQuad(float x)
{
	return x < 0.5 ? 2 * x * x : 1 - (float)pow(-2 * x + 2, 2) / 2;
}

float easeInCubic(float x)
{
	return x * x * x;
}

float easeInQuart(float x)
{
	return x * x * x * x;
}

float easeOutCubic(float x)
{
	return 1 - (float)pow(1 - x, 3);
}

float easeInOutCubic(float x)
{
	return x < 0.5 ? 4 * x * x * x : 1 - (float)pow(-2 * x + 2, 3) / 2;
}

const DirectX::XMFLOAT3 operator+(DirectX::XMFLOAT3 v1, DirectX::XMFLOAT3 v2)
{
	return DirectX::XMFLOAT3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

const DirectX::XMFLOAT3 operator-(DirectX::XMFLOAT3 v1, DirectX::XMFLOAT3 v2)
{
	return DirectX::XMFLOAT3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

const DirectX::XMFLOAT3 operator*(DirectX::XMFLOAT3 v, float s)
{
	return DirectX::XMFLOAT3(v.x * s, v.y * s, v.z * s);
}

const DirectX::XMFLOAT3 operator/(DirectX::XMFLOAT3 v, float s)
{
	return DirectX::XMFLOAT3(v.x / s, v.y / s, v.z / s);
}

float dot(DirectX::XMFLOAT3 v1, DirectX::XMFLOAT3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

DirectX::XMFLOAT3 cross(DirectX::XMFLOAT3 v1, DirectX::XMFLOAT3 v2)
{
	return DirectX::XMFLOAT3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

float length(DirectX::XMFLOAT3 v)
{
	float x2 = v.x * v.x;
	float y2 = v.y * v.y;
	float z2 = v.z * v.z;
	return sqrt(x2 + y2 + z2);
}

DirectX::XMFLOAT3 normalize(DirectX::XMFLOAT3 v)
{
	if (v.x == 0 && v.y == 0 && v.z == 0)
	{
		return DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	float len = length(v);

	return v / len;
}

float LenSegOnSeparateAxis(DirectX::XMFLOAT3 Sep, DirectX::XMFLOAT3 e1, DirectX::XMFLOAT3 e2, DirectX::XMFLOAT3 e3)
{
	float r1 = fabs(dot(Sep, e1));
	float r2 = fabs(dot(Sep, e2));
	float r3 = fabs(dot(Sep, e3));
	return r1 + r2 + r3;
}

DirectX::XMFLOAT3 rollRotation(DirectX::XMFLOAT3 vector, DirectX::XMFLOAT3 rotation)
{
	Matrix4 matRotX, matRotY, matRotZ;
	matRotX = rotationX(rotation.x);
	matRotY = rotationY(rotation.y);
	matRotZ = rotationZ(rotation.z);

	matRotZ *= matRotX;
	matRotZ *= matRotY;

	DirectX::XMFLOAT3 v;

	v.x = vector.x * matRotZ.m[0][0] + vector.y * matRotZ.m[1][0] + vector.z * matRotZ.m[2][0];
	v.y = vector.x * matRotZ.m[0][1] + vector.y * matRotZ.m[1][1] + vector.z * matRotZ.m[2][1];
	v.z = vector.x * matRotZ.m[0][2] + vector.y * matRotZ.m[1][2] + vector.z * matRotZ.m[2][2];

	return v;
}

DirectX::XMFLOAT3 getVectorRotation(DirectX::XMFLOAT3 vec)
{
	float rotX = 0.0f;
	float rotY = 0.0f;
	float rotZ = 0.0f;

	//0の場合0
	if (vec.x == 0 && vec.z == 0)
	{
		rotY = 0.0f;
	}
	//正規化して代入
	rotY = normalize(vec.x, vec.z).y;
	//ステックのXの値を代入
	rotX = vec.x;
	//0~180の場合
	if (rotX >= 0.0f)
	{
		//-1する
		rotY -= 1.0f;
		//-を外す
		rotY *= -1.0f;
		//度数法に変換
		rotY *= 90.0f;
		//ラジアンに変換
		rotY *= (float(PI) / 180.0f);
	}
	//180~360の場合
	else
	{
		//+1する
		rotY += 1.0f;
		//度数法に変換
		rotY *= 90.0f;
		//180度追加
		rotY += 180.0f;
		//ラジアンに変換
		rotY *= (float(PI) / 180.0f);
	}
	return DirectX::XMFLOAT3(0.0f,rotY,0.0f);
}

const DirectX::XMFLOAT3 lerp(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, const float t)
{
	return start * (1.0f - t) + end * t;
}

const DirectX::XMFLOAT2 operator+(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2)
{
	return DirectX::XMFLOAT2(v1.x + v2.x,v1.y + v2.y);
}

const DirectX::XMFLOAT2 operator-(DirectX::XMFLOAT2 v1, DirectX::XMFLOAT2 v2)
{
	return DirectX::XMFLOAT2(v1.x - v2.x, v1.y - v2.y);
}

const DirectX::XMFLOAT2 operator*(DirectX::XMFLOAT2 v, float s)
{
	return DirectX::XMFLOAT2(v.x * s,v.y * s);
}

const DirectX::XMFLOAT2 operator/(DirectX::XMFLOAT2 v, float s)
{
	return DirectX::XMFLOAT2(v.x / s, v.y / s);
}

float length(DirectX::XMFLOAT2 v)
{
	float x = v.x * v.x;
	float y = v.y * v.y;
	return sqrt(x + y);
}

float length(float x, float y)
{
	float x2 = x * x;
	float y2 = y * y;
	return sqrt(x2 + y2);
}

float length(int x, int y)
{
	float x2 = (float)x * (float)x;
	float y2 = (float)y * (float)y;
	return sqrt(x2 + y2);
}

DirectX::XMFLOAT2 normalize(DirectX::XMFLOAT2 v)
{
	if (v.x == 0 && v.y == 0)
	{
		return DirectX::XMFLOAT2(0.0f, 0.0f);
	}
	float len = length(v);

	return v / len;
}

DirectX::XMFLOAT2 normalize(float x, float y)
{
	if (x == 0 && y == 0)
	{
		return DirectX::XMFLOAT2(0.0f,0.0f);
	}
	float len = length(x,y);

	return DirectX::XMFLOAT2(x,y) / len;
}

DirectX::XMFLOAT2 WorldToScreen(DirectX::XMFLOAT3 worldPos)
{
	return DirectX::XMFLOAT2();
}
