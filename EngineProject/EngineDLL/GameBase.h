#pragma once
#include "Exports.h"
#include "Renderer.h"
#include <iostream>
class ENGINEDLL_API GameBase
{
private:
	Renderer* renderer;
protected:
	virtual bool OnStart() = 0;
	virtual bool OnStop() = 0;
	virtual bool OnUpdate() = 0;		
public:
	GameBase();
	virtual ~GameBase();
	bool Start();
	bool Stop();
	void Loop();
};

