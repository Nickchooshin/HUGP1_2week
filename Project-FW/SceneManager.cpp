#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager() : m_nSceneIndex(0)
{
}
SceneManager::~SceneManager()
{
	const int num = m_SceneList.size() ;

	for(int i=0; i<num; i++)
		PopScene() ;
}

void SceneManager::StartScene(Scene *pScene)
{
	m_SceneList.push_back(pScene) ;
}

void SceneManager::InitScene()
{
	m_SceneList[m_nSceneIndex]->Init() ;
}

void SceneManager::UpdateScene(float dt)
{
	m_SceneList[m_nSceneIndex]->Update(dt) ;
}

void SceneManager::RenderScene()
{
	const int num = m_SceneList.size() ;
	
	for(int i=0; i<num; i++)
		m_SceneList[i]->Render() ;
}

void SceneManager::DestroyScene()
{
	m_SceneList[m_nSceneIndex]->Destroy() ;
	delete m_SceneList[m_nSceneIndex] ;
}

void SceneManager::ChangeScene(Scene *pScene)
{
	DestroyScene() ;

	m_SceneList[m_nSceneIndex] = pScene ;

	InitScene() ;
}

void SceneManager::PushScene(Scene *pScene)
{
	m_SceneList.push_back(pScene) ;
	++m_nSceneIndex ;

	InitScene() ;
}

void SceneManager::PopScene()
{
	DestroyScene() ;

	m_SceneList.pop_back() ;
	--m_nSceneIndex ;
}