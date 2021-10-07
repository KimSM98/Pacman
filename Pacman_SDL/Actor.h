#pragma once
#include <vector>

#include "Math.h"

class Actor
{
public:
	enum State
	{
		EActive, // EActive일때만 Update
		EPaused,
		EDead // Game에 액터를 제거하라고 통지
	};

	Actor(class Game* game);
	virtual ~Actor();

	// Game에서 호출하는 Update
	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	// Game이 호출하는 ProcessInput 함수(재정의되지 않음)
	void ProcessInput(const uint8_t* keyState);
	// 특정 액터를 위한 입력 코드(재정의됨)
	virtual void ActorInput(const uint8_t* keyState);

	// Getters/Setters
	State GetState() const { return _State; }
	const Vector2& GetPosition() const { return _Position; }
	float GetScale() const { return _Scale; }
	float GetRotation() const { return _Rotation; }

	class Game* GetGame() { return _Game; }

	Vector2 GetForward() const { return Vector2(Math::Cos(_Rotation), -Math::Sin(_Rotation)); }

	void SetState(State state) { _State = state; }
	void SetPosition(const Vector2& pos) { _Position = pos; }
	void SetScale(float scale) { _Scale = scale; }
	void SetRotation(float rotation) { _Rotation = rotation; }

	// Add/Remove Components
	void AddComponents(class Component* comp);
	void RemoveComponents(class Component* comp);

private:
	State _State;

	Vector2 _Position;
	float _Scale;
	float _Rotation;

	std::vector<class Component*> _Components;
	class Game* _Game;
};
