#include "PhaseList.h"
#include "mathOriginal.h"
#include "ColliderManager.h"
#include "imgui.h"

void Phase1::DrawFBXLightView()
{
	//SRV���Z�b�g
	player->DrawLightView(dxCommon->GetCommandList());
	enemy->DrawLightView(dxCommon->GetCommandList());
}

void Phase1::SetSRV(ID3D12DescriptorHeap* SRV)
{
	//SRV���Z�b�g
	player->SetSRV(SRV);
	enemy->SetSRV(SRV);
	plane->SetSRV(SRV);
}

void Phase1::NextPhase(GameScene* gameScene)
{
	//�t�F�[�Y�`�F���W�t���O����������
	if (phaseChangeFlag == true)
	{
		//�^�C�}�[���Z�b�g
		phaseTimer = 0;
		//�v���C���[���Z�b�g
		player->SetGameScene();
		//�G���Z�b�g
		enemy->SetGameScene();
		//���̃t�F�[�Y��
		gameScene->ChangePhase(new Phase2());
	}
}

void Phase1::UpdateObject()
{
	//�J�����X�V
	camera->UpdatePlayer(player->GetPosition(), player->GetRotation0());
	camera->Update();

	//���C�g�X�V
	light->SetEye(XMFLOAT3(lightPos) + player->GetPosition());
	light->SetTarget(XMFLOAT3(lightTarget) + player->GetPosition());
	light->SetDir(XMFLOAT3(lightDir));
	/*light->SetEye(XMFLOAT3(debugLightPos));
	light->SetTarget(XMFLOAT3(debugLightTarget));
	light->SetDir(XMFLOAT3(debugLightDir));*/
	light->Update();

	//�G
	enemy->SetPlayerPos(player->GetPosition());
	enemy->UpdateGame1();

	//UI
	ui->SetPlayerForm(player->GetPlayerForm(), player->GetFormChangeFlag());
	ui->UpdateGame();

	//�v���C���[
	player->SetEnemyPos(enemy->GetPosition());
	player->UpdateGame();

	//��
	plane->Update();

	//�n�`
	terrain->Update();
}

void Phase1::UpdateCollider()
{
	//���O����
	ColliderManager::PreUpdate();

	//�v���C���[�����蔻��X�V
	player->SetObjectCollider(terrain->GetColliderData());
	player->UpdateCollider();

	//�G�̂����蔻��X�V
	enemy->SetObjectCollider(terrain->GetColliderData());
	enemy->UpdateCollider();

	//�G�̒e�Ǝ��@�̓����蔻��
	//if (player->GetInvincibleFlag() == false)
	//{
	//	for (int i = 0; i < enemy->GetBulletNum(); i++)
	//	{
	//		if (ColliderManager::CheckCollider(player->GetColliderData(), enemy->GetBulletColliderData(i)))
	//		{
	//			//���@�Ƀq�b�g�t���O���M
	//			player->HitEnemy();
	//		}
	//	}
	//}

	//�G�Ǝ��@�̓����蔻��
	if (player->GetInvincibleFlag() == false)
	{
		if (ColliderManager::CheckCollider(player->GetColliderData(), enemy->GetColliderData()))
		{
			////���@�Ƀq�b�g�t���O���M
			//player->HitEnemy();
		}
	}

	////���@�̒e(��)�ƓG�̓����蔻��
	//for (int i = 0; i < player->GetBullet1Num(); i++)
	//{
	//	if (ColliderManager::CheckCollider(enemy->GetColliderData(), player->GetBullet1ColliderData(i)))
	//	{
	//		//�G�Ƀq�b�g�t���O���M
	//		enemy->HitBullet1();
	//		//���@�Ƀq�b�g�t���O���M
	//		player->HitBullet1(i);
	//	}
	//}

	////���U��������������
	//if (player->GetHitElec())
	//{
	//	//�G�Ƀq�b�g�t���O���M
	//	enemy->HitElec();
	//}

	//���@�̃I�u�W�F�N�g�̓����蔻��
	/*for (int i = 0; i < terrain->GetColliderNum(); i++)
	{
		if (ColliderManager::CheckCollider(player->GetColliderData(), terrain->GetColliderData()[i]))
		{
		}
	}*/
	/*for (int i = 0; i < terrain->GetColliderNum(); i++)
	{
		if (ColliderManager::CheckCollider(player->GetColliderData(), terrain->GetColliderData()[i]))
		{
		}
	}*/

	//�G�̒e�ƕ��ʂ̔���
	//for (std::unique_ptr<FbxObject3D>& object1 : object)
	//{
	//	if (object1->GetFileName() == "plane")
	//	{
	//		for (int i = 0; i < enemy->GetBulletNum(); i++)
	//		{
	//			if (ColliderManager::CheckCollider(object1->GetColliderData(), enemy->GetBulletColliderData(i)))
	//			{
	//				//����������p�[�e�B�N������
	//				sparkParticle2->Add(XMFLOAT3(enemy->GetBulletColliderData(i).center));
	//				explosionParticle1->Add(XMFLOAT3(enemy->GetBulletColliderData(i).center));
	//				explosionParticle2->Add(XMFLOAT3(enemy->GetBulletColliderData(i).center));
	//			}
	//		}
	//	}
	//}

	//�㏈��
	ColliderManager::PostUpdate();
}

void Phase1::DrawFBX()
{
	//FBX�`��
	player->Draw(dxCommon->GetCommandList());
	enemy->Draw(dxCommon->GetCommandList());
	plane->Draw(dxCommon->GetCommandList());
	terrain->Draw(dxCommon->GetCommandList());

	//�R���C�_�[�`��
	ColliderManager::Draw(dxCommon->GetCommandList());

	//ImGui
	//ImGui::Begin("Phase1");
	//ImGui::SetWindowPos(ImVec2(500, 300));
	//ImGui::SetWindowSize(ImVec2(500, 150));
	////ImGui::InputFloat2("debugPos", debugPos);
	//ImGui::InputFloat3("lightPos", debugLightPos);
	//ImGui::InputFloat3("lightTarget", debugLightTarget);
	//ImGui::InputFloat3("lightDir", debugLightDir);
	//ImGui::End();
}

void Phase1::DrawSprite()
{
	//UI�`��
	ui->DrawGame(dxCommon->GetCommandList());

	//�v���C���[�̃X�v���C�g�`��
	player->DrawSpriteGame(dxCommon->GetCommandList());
	//�G
	enemy->DrawSpriteGame1(dxCommon->GetCommandList());
}

void Phase1::DrawParticle()
{
	//�v���C���[�̃p�[�e�B�N���`��
	player->DrawParticle(dxCommon->GetCommandList());
	//�G�̃p�[�e�B�N���`��
	enemy->DrawParticle(dxCommon->GetCommandList());
}

void Phase2::DrawFBXLightView()
{
	player->DrawLightView(dxCommon->GetCommandList());
	enemy->DrawLightView(dxCommon->GetCommandList());
	miniEnemy->DrawLightView(dxCommon->GetCommandList());
}

void Phase2::SetSRV(ID3D12DescriptorHeap* SRV)
{
	player->SetSRV(SRV);
	enemy->SetSRV(SRV);
	miniEnemy->SetSRV(SRV);
	plane->SetSRV(SRV);
}

void Phase2::NextPhase(GameScene* gameScene)
{
	//�t�F�[�Y�`�F���W�t���O����������
	if (phaseChangeFlag == true)
	{
		//�^�C�}�[���Z�b�g
		phaseTimer = 0;
		//�N���A�V�[����
		gameScene->SetMoveClearFlag(true);
	}
}

void Phase2::UpdateObject()
{
	//�J�����X�V
	camera->UpdatePlayer(player->GetPosition(), player->GetRotation0());
	camera->Update();

	//���C�g�X�V
	light->SetEye(XMFLOAT3(lightPos) + player->GetPosition());
	light->SetTarget(XMFLOAT3(lightTarget) + player->GetPosition());
	light->SetDir(XMFLOAT3(lightDir));
	light->Update();

	//�G
	enemy->SetPlayerPos(player->GetPosition());
	enemy->UpdateGame2();

	//�������G
	//�f�o�b�O�p
	if (input->TriggerKey(DIK_SPACE))
	{
		miniEnemy->AddEnemy(XMFLOAT3(0.0f, 0.0f, 0.0f));
	}
	if (enemy->GetCallEnemyFlag())
	{
		miniEnemy->AddEnemy(enemy->GetCallEnemyPos());
	}
	miniEnemy->SetPlayerPos(player->GetPosition());
	miniEnemy->Update();

	//�v���C���[
	player->SetEnemyPos(enemy->GetPosition());
	player->UpdateGame();

	//��
	plane->Update();

	//�n�`
	terrain->Update();
}

void Phase2::UpdateCollider()
{
	//���O����
	ColliderManager::PreUpdate();

	//�G�̒e�Ǝ��@�̓����蔻��
	//if (player->GetInvincibleFlag() == false)
	//{
	//	for (int i = 0; i < enemy->GetBulletNum(); i++)
	//	{
	//		if (ColliderManager::CheckCollider(player->GetColliderData(), enemy->GetBulletColliderData(i)))
	//		{
	//			//���@�Ƀq�b�g�t���O���M
	//			player->HitEnemy();
	//		}
	//	}
	//}

	////�G�Ǝ��@�̓����蔻��
	//if (player->GetInvincibleFlag() == false)
	//{
	//	if (ColliderManager::CheckCollider(player->GetColliderData(), enemy->GetColliderData()))
	//	{
	//		//���@�Ƀq�b�g�t���O���M
	//		player->HitEnemy();
	//	}
	//}

	////���@�̒e(��)�ƓG�̓����蔻��
	//for (int i = 0; i < player->GetBullet1Num(); i++)
	//{
	//	if (ColliderManager::CheckCollider(enemy->GetColliderData(), player->GetBullet1ColliderData(i)))
	//	{
	//		//�G�Ƀq�b�g�t���O���M
	//		enemy->HitBullet1();
	//		//���@�Ƀq�b�g�t���O���M
	//		player->HitBullet1(i);
	//	}
	//}

	////���U��������������
	//if (player->GetHitElec())
	//{
	//	//�G�Ƀq�b�g�t���O���M
	//	enemy->HitElec();
	//}

	////���@�Ə������G�̓����蔻��
	//for (int i = 0; i < miniEnemy->GetEnemyNum(); i++)
	//{
	//	for (int j = 0; j < player->GetBullet1Num(); j++)
	//	{
	//		if (ColliderManager::CheckCollider(miniEnemy->GetColliderData(i), player->GetBullet1ColliderData(j)))
	//		{
	//			//�G�Ƀq�b�g�t���O���M
	//			miniEnemy->HitFire(i);
	//			//���@�Ƀq�b�g�t���O���M
	//			player->HitBullet1(j);
	//		}
	//	}
	//}

	//�G�̒e�ƕ��ʂ̔���
	//for (std::unique_ptr<FbxObject3D>& object1 : object)
	//{
	//	if (object1->GetFileName() == "plane")
	//	{
	//		for (int i = 0; i < enemy->GetBulletNum(); i++)
	//		{
	//			if (ColliderManager::CheckCollider(object1->GetColliderData(), enemy->GetBulletColliderData(i)))
	//			{
	//				//����������p�[�e�B�N������
	//				sparkParticle2->Add(XMFLOAT3(enemy->GetBulletColliderData(i).center));
	//				explosionParticle1->Add(XMFLOAT3(enemy->GetBulletColliderData(i).center));
	//				explosionParticle2->Add(XMFLOAT3(enemy->GetBulletColliderData(i).center));
	//			}
	//		}
	//	}
	//}

	//�㏈��
	ColliderManager::PostUpdate();
}

void Phase2::DrawFBX()
{
	player->Draw(dxCommon->GetCommandList());
	enemy->Draw(dxCommon->GetCommandList());
	miniEnemy->Draw(dxCommon->GetCommandList());
	plane->Draw(dxCommon->GetCommandList());
	terrain->Draw(dxCommon->GetCommandList());
}

void Phase2::DrawSprite()
{
	//�v���C���[�̃X�v���C�g�`��
	player->DrawSpriteGame(dxCommon->GetCommandList());
	//�G
	enemy->DrawSpriteGame2(dxCommon->GetCommandList());
	//�������G
	miniEnemy->DrawSprite(dxCommon->GetCommandList());
}

void Phase2::DrawParticle()
{
	//�v���C���[�̃p�[�e�B�N���`��
	player->DrawParticle(dxCommon->GetCommandList());
	//�G�̃p�[�e�B�N���`��
	enemy->DrawParticle(dxCommon->GetCommandList());
}
