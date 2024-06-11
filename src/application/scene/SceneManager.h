/**
 * @file SceneManager.h
 * @brief 各シーンを管理
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

	//初期化
	void Initialize();
	//シーン更新
	void Update();
	//シーン描画
	void Draw();
	//シーンライト目線描画
	void DrawFBXLightView();
	//次のシーンに移る
	void NextScene(Scene* pState);
	
	//シーン遷移
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