#pragma once
#include <cstdint>

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();

	virtual void Update(float deltaTime);

	virtual void ProcessInput(const uint8_t* keyState) {}

	int GetUpdateOrder() const { return _UpdateOrder; }

protected:
	class Actor* _Owner;
	
	int _UpdateOrder;
};