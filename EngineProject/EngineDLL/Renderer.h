#pragma once
#include "Exports.h"
#include <iostream>
using namespace std;
class ENGINEDLL_API Renderer
{
public:
	Renderer();
	~Renderer();
	bool Start();
	bool Stop();
};

