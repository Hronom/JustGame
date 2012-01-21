#ifndef ICORE_H
#define ICORE_H

class iCore
{
public:
	iCore() {};
	virtual ~iCore() {};

	virtual void needShutdown() = 0;
};

#endif
