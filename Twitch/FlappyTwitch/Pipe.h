#ifndef TWITCH_PIPE
#define TWITCH_PIPE

#include "../Engine/Graphics/Sprite.h"
#include "../Engine/Physics/Rigidbody.h"
#include "../Engine/Math/Vector3.h"

class Pipe
{
public:
	static Sprite* pipeSprite;
	static void Initialize(bool obstacle);

	Pipe();
	Pipe(Vector3 _pos, int _points, bool _obstacle);

	void SetGap(float _gap);
	float GetPrevPos();

	void Update();
	void Render();

	void MoveTo(Vector3 to);
	void MoveBy(Vector3 by);

	float GetX();
	float GetWidth();

	Rigidbody GetTopRB();
	Rigidbody GetBotRB();

	float speed;

private:
	void UpdatePos();

	Sprite topSprite;
	Sprite botSprite;
	Rigidbody topRB;
	Rigidbody botRB;

	Vector3 pos;
	float prevPos;

	float gap;
};

#endif
