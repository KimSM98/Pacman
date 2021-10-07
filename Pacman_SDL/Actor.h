#pragma once
#include <vector>

#include "Math.h"

class Actor
{
public:
	enum State
	{
		EActive, // EActive�϶��� Update
		EPaused,
		EDead // Game�� ���͸� �����϶�� ����
	};

	Actor(class Game* game);
	virtual ~Actor();

	// Game���� ȣ���ϴ� Update
	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	// Game�� ȣ���ϴ� ProcessInput �Լ�(�����ǵ��� ����)
	void ProcessInput(const uint8_t* keyState);
	// Ư�� ���͸� ���� �Է� �ڵ�(�����ǵ�)
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
