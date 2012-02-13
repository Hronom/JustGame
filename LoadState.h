#ifndef LOADSTATE_H
#define LOADSTATE_H

#include "iCore.h"
#include "iLoadState.h"

class LoadState: public iLoadState
{
private:
	iCore *mCore;

public:
	LoadState();
	~LoadState();

	virtual void show();
	virtual void hide();

	virtual void setProgress(int xProgressValue, std::string xText);
};

#endif
