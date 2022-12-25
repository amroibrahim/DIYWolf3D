#pragma once
#include "Configuration.h"

class GameObject
{
public:
	GameObject(Configuration* configuration) : configuration_(configuration) {};
	virtual void Initialize() = 0;
	virtual void Update(float elapsed_time) = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;

protected:
	Configuration* configuration_;
};
