/**
 * @file SceneManager.h
 * @brief �e�V�[�����Ǘ�
 * @author Asuma Syota
 * @date 2024/4
 */
#pragma once
#include "d3d12.h"


class SceneState;
class Scene
{
public:
	Scene();
	~Scene();

	//������
	void Initialize();
	//�V�[���X�V
	void Update();
	//�V�[���`��
	void Draw();
	//�V�[�����C�g�ڐ��`��
	void DrawFBXLightView();
	//���̃V�[���Ɉڂ�
	void NextScene(Scene* pState);
	
	//�V�[���J��
	void ChangeScene(SceneState* newState);

private:
	SceneState* sceneState;
};

class SceneState
{
public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void DrawFBXLightView() = 0;
	virtual void NextScene(Scene* pState) = 0;
};