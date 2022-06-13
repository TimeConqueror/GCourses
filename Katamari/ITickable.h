#pragma once
class ITickable
{
public:
	virtual ~ITickable() = default;
	virtual void tick() = 0;
};

