#pragma once

namespace Infrastructure
{

template<class T>
class Singleton
{
private:
	static T * instance;

protected:
	Singleton() {}


public:
	static void CreateInstance()
	{
		if(instance == NULL)
		{
			instance = new T();
		}
	}

	static void DestroyInstance()
	{
		if(instance != NULL)
		{
			delete instance;
			instance = NULL;
		}
	}

	static T * Instance()
	{
		return instance;
	}
};

// Defaults for Statics
template<class T>
T* Singleton<T>::instance = NULL;

}