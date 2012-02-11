#ifndef MAINCLASS_H
#define MAINCLASS_H

#include "MainSystem.h"

class MainClass
{
private:
	MainSystem *mMainSystem;
public:
	MainClass();
	~MainClass();

	void start();
};

#endif

