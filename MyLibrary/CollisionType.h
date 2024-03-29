#pragma once
#include"Vector.h"

//判定
struct CollisionFlag
{
	bool sphere;
	bool box;
	bool ray;
	bool lineSegment;
	bool plane;
	bool board;
};

enum CollisionType 
{
	COLLISION_RECT,
	COLLISION_CIRCLE,
	COLLISION_SPHERE,
	COLLISION_BOX,
	COLLISION_PLANE,
	COLLISION_BOARD,
	COLLISION_LINESEGMENT,
	COLLISION_RAY,

};

enum BoxHitDirection
{
	BOX_HIT_DIRECTION_NO_HIT,
	BOX_HIT_DIRECTION_UP,
	BOX_HIT_DIRECTION_DOWN,
	BOX_HIT_DIRECTION_LEFT,
	BOX_HIT_DIRECTION_RIGHT,
	BOX_HIT_DIRECTION_FRONT,
	BOX_HIT_DIRECTION_BACK,
};

#pragma region 2D

struct RectData
{
	//四角形の左上
	Vector2 position;
	//辺の長さ
	Vector2 size;
};

struct CircleData
{
	Vector2 position;
	float r;
};

#pragma endregion

#pragma region 3D

struct SphereData
{
	Vector3 position;

	//半径
	float r;

	//boxのどこにぶつかったか
	BoxHitDirection boxHitDistance;
};

struct BoxData
{
	Vector3 size;
	Vector3 position;

	//球がどこにぶつかったか
	BoxHitDirection boxHitDistance;
};

struct PlaneData
{
	Vector3 normal;
	float distance;
};

struct BoardData
{
	Vector3 normal;
	Vector3 position;
	Vector3 leftDownPos;
	Vector3 leftUpPos;
	Vector3 rightUpPos;
	Vector3 rightDownPos;

	Vector3 hitPos;
};

struct LineSegmentData
{
	Vector3 position[2];

	Vector3 hitPos;
};

struct RayData 
{
	Vector3 pos;
	Vector3 direction;
};



#pragma endregion

