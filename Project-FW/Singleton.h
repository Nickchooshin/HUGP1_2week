#pragma once

template <class T>
class Singleton
{
protected :
	bool m_bInit ;

public :
	static T* GetInstance()
	{
		static T Instance ;

		return &Instance ;
	}

	Singleton() : m_bInit(false)
	{
	}
} ;