
//�R���V�A�� �V�� �n�` ��
#pragma once
#include "ObjObject3D.h"
#include "vector"
#include "JSONLoader.h"

class Terrain
{
private:	//�G�C���A�X
	//Microsoft::WRL::���ȗ�
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:	//�ÓI�����o�֐�

	//�J�����Z�b�g
	static void SetCamera(Camera* camera) { Terrain::camera = camera; }

public:	//�����o�֐�

	//�f�X�g���N�^ �R���X�g���N�^
	Terrain() {};
	~Terrain();

	//������
	void Initialize(ID3D12Device* device);
	//�X�V
	void Update();
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//�`��
	void DrawTitle(ID3D12GraphicsCommandList* cmdList);
	//�R���C�_�[�擾
	std::vector<JSONLoader::ColliderData> GetColliderData() { return colliderData; }
	//�R���C�_�[�̐��擾
	int GetColliderNum() { return colliderNum; }

private:	//�ÓI�����o�ϐ�
	
	static Camera* camera;

private:	//�����o�ϐ�

	//�V�����f��
	ObjModel* skySphereModel = nullptr;
	//�V���I�u�W�F�N�g
	ObjObject3D* skySphereObject = nullptr;
	//�X�P�[��
	XMFLOAT3 skySphereScale = { 50.0f,50.0f,50.0f };
	//���W
	XMFLOAT3 skySpherePos = { 0.0f,0.0f,0.0f };
	//�p�x
	XMFLOAT3 skySphereRotation = { 0.0f,0.0f,0.0f };

	//�R���V�A�����f��
	ObjModel* coliseumModel = nullptr;
	//�R���V�A���I�u�W�F�N�g
	ObjObject3D* coliseumObject = nullptr;
	//�X�P�[��
	XMFLOAT3 coliseumScale = { 1.0f,1.0f,1.0f };
	//���W
	XMFLOAT3 coliseumPos = { 0.0f,0.0f,0.0f };
	//�p�x
	XMFLOAT3 coliseumRotation = { 0.0f,0.0f,0.0f };

	//�R���V�A�����f��2
	ObjModel* coliseum2Model = nullptr;
	//�R���V�A���I�u�W�F�N�g2
	ObjObject3D* coliseum2Object = nullptr;
	//�R���V�A���̔w�ʂ̃A���t�@
	float backAlpha = 0.5f;

	//�����f��
	ObjModel* pillerModel = nullptr;
	
	//�V���ȊO�̃I�u�W�F�N�g
	std::vector<ObjObject3D*> objects;

	//��������I�u�W�F�N�g���ׂẴR���C�_�[�f�[�^
	std::vector<JSONLoader::ColliderData>colliderData;
	//�R���C�_�[�̐�
	int colliderNum = 0;

	//json����󂯎�����I�u�W�F�N�g�̃f�[�^
	std::vector<JSONLoader::ObjectData>objectData;
};