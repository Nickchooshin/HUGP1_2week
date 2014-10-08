#pragma once

#include "Singleton.h"
#include <vector>

class Scene ;

class SceneManager : public Singleton<SceneManager>
{
private :
	std::vector<Scene*> m_SceneList ;
	int m_nSceneIndex ;

public :
	SceneManager() ;
	~SceneManager() ;

	void StartScene(Scene *pScene) ;
	void InitScene() ;

	void UpdateScene(float dt) ;
	void RenderScene() ;

	void DestroyScene() ;

	void ChangeScene(Scene *pScene) ;
	void PushScene(Scene *pScene) ;
	void PopScene() ;
} ;

#define g_SceneManager SceneManager::GetInstance()