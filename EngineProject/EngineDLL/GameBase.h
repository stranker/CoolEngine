#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Window.h"
#include <iostream>
class ENGINEDLL_API GameBase
{
private:
	Renderer* renderer;
	Window* window;
protected:
	virtual bool OnStart() = 0;
	virtual bool OnStop() = 0;
	virtual bool OnUpdate() = 0;		
	int screenHeight;
	int screenWidth;
	string screenName;
public:
	GameBase(int _screenHeight,int _screenWidht,string _screenName);
	virtual ~GameBase();
	bool Start();
	bool Stop();
	void Loop();
};

