#pragma once
#include "DirectXCommon.h"

class SrvManager {

public:	//�����o�֐�

	//DirecrXCommon���Z�b�g
	void SetDxCommon(DirectXCommon* directXCommon) { this->directXCommon = directXCommon; }

	//������
	void Initialize();

	//SRV����(�e�N�X�`���p)
	void CreateSRVForTexture2D(uint32_t srvIndex, ID3D12Resource* pResource, DXGI_FORMAT format, UINT mipLevel);

	//�`��O����
	void PreDraw();

	//�`��̂��߂̃n���h�����Z�b�g����֐�
	void SetGraphicsRootDescriptorTable(UINT RootParameterIndex, uint32_t srvIndex);

	//���Ɏg�p����SRV�C���f�b�N�X�̔ԍ����v�Z���ĕԂ�
	uint32_t Allocate();

	//CPU�n���h���v�Z�p�֐�
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(uint32_t index);
	//GPU�n���h���v�Z�p�֐�
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(uint32_t index);

private:	//�����o�ϐ�

	//DirectXCommon
	DirectXCommon* directXCommon = nullptr;

	//�ő�SRV��
	static const uint32_t kMaxSRVCount;
	//SRV�p�f�X�N���v�^�T�C�Y
	uint32_t descriptorSize;
	//SRV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descriptorHeap;
	//���Ɏg�p����SRV�C���f�b�N�X
	uint32_t useIndex = 0;
};