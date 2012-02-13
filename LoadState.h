#ifndef LOADSTATE_H
#define LOADSTATE_H

#include <MyGUI.h>

#include "iCore.h"
#include "iLoadState.h"

class LoadState: public iLoadState
{
private:
	iCore *mCore;

	MyGUI::VectorWidgetPtr mCurrentLayoutWidgets;

	MyGUI::TextBox *mTextBox;
	MyGUI::ProgressBar *mProgressBar;

public:
	LoadState(iCore *xCore);
	~LoadState();

	virtual void show();
	virtual void hide();

	virtual void setProgress(int xProgressValue, std::string xText);
};

#endif
