#include "GameBase.h"



GameBase::GameBase()
{		
}
GameBase::~GameBase()
{
}
bool GameBase::Start()
{
	cout << "GameBase::Start()" << endl;
	renderer = new Renderer();	
	if (!renderer->Start())
	{
		return false;
	}
	return OnStart();	
}
bool GameBase::Stop()
{
	cout << "GameBase::Stop()" << endl;
	OnStop();
	renderer->Stop();
	return true;	
}
void GameBase::Loop()
{
	cout << "GameBase::Loop()" << endl;
	bool aux = true;
	do
	{
		aux = OnUpdate();
	} while (aux);
}
