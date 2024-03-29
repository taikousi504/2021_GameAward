#pragma once
#include"Vector.h"
#include"Matrix.h"
#include"Quaternion.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"Library.h"
#include"CollisionType.h"
//GameにMathクラスがあったから名前をMathにするとエラーが出る
//Math意外だとエラー出なかったので、Mathという名前自体がいけないのかもしれない
//エラー出ないこともある
//includeすると確実にエラーが出る。includeしないと出ない
//lib(スタティックライブラリのプロジェクト)に作らなければエラー出ない?


class LibMath
{
private:

public:

	

	/// <summary>
	/// num1とnum2の値の差を求め、差 <= 基準の値だったらtrueを返します
	/// </summary>
	/// <param name="num1">値1</param>
	/// <param name="num2">値2</param>
	/// <param name="difference">基準の値</param>
	/// <returns></returns>
	static bool difference(const float& num1, const float& num2, const float& difference);

	/// <summary>
		/// 度数法の角度をラジアンに　ラジアンを度数法の角度に
		/// </summary>
		/// <param name="pattern">0 度数法の角度をラジアンに   1 ラジアンを度数法の角度に</param>
		/// <param name="angle">角度</param>
	static float angleConversion(int pattern, float angle);


	/// <summary>
	/// 円周率を取得します
	/// </summary>
	/// <returns></returns>
	static float getFloatPI();

	/// <summary>
	/// 円周率を取得します
	/// </summary>
	/// <returns></returns>
	static double getDoublePI();

#pragma region ベクトル


#pragma region vector2

	/// <summary>
	/// 左右判定を行います。点がベクトルより右の場合は1、左の場合は-1、ベクトル上の場合は0を返します。
	/// </summary>
	/// <param name="vector"></param>
	/// <param name="point"></param>
	/// <returns></returns>
	static char pointLeftRightCheck(const Vector2& vector, const Vector2& point);

	/// <summary>
	/// 2つのベクトルがなす角度を求めます
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
	/// <returns></returns>
	static float twoVector2Angle(const Vector2& v1, const Vector2& v2);

	/// <summary>
	/// ベクトルを角度に変換します
	/// </summary>
	/// <param name="v"></param>
	/// <param name="v3">3次元座標系かどうか</param>
	/// <returns></returns>
	static float vecto2ToAngle(const Vector2& v,const bool& v3 );

	/// <summary>
	/// 角度をVector2に変換します
	/// </summary>
	/// <param name="angle"></param>
	/// <param name="v3">3次元座標系かどうか</param>
	/// <returns></returns>
	static Vector2 angleToVector2(const float& angle, const bool& v3);

	/// <summary>
	/// Vector2のベクトルを指定した角度に応じて回転させます
	/// </summary>
	/// <param name="v"></param>
	/// <param name="angle"></param>
	/// <returns></returns>
	static Vector2 rotateVector2(const Vector2& v, const float& angle);
#pragma endregion

#pragma region Vector3

	/// <summary>
	/// 2つの座標の距離を取得します
	/// </summary>
	/// <param name="pos1">座標1</param>
	/// <param name="pos2">座標2</param>
	/// <returns></returns>
	static float calcDistance3D(Vector3 pos1, Vector3 pos2);

	/// <summary>
	/// vex1からvec2のベクトルを取得します(正規化は行う)
	/// </summary>
	/// <param name="myPos"></param>
	/// <param name="otherPos"></param>
	/// <returns></returns>
	static Vector3 otherVector(const Vector3& vec1, const Vector3& vec2);

	/// <summary>
	/// ベクトルを回転させます
	/// </summary>
	/// <param name="rotateV"></param>
	/// <param name="vec">軸のベクトル</param>
	/// <param name="angle"></param>
	/// <returns></returns>
	Vector3 rotateVector3(const Vector3& rotateV, const Vector3& vec ,const float& angle);
#pragma endregion


#pragma endregion

#pragma region 当たり判定

#pragma region 2D

	/// <summary>
	/// 四角の当たり判定です
	/// </summary>
	/// <param name="start1">1つ目の左上座標</param>
	/// <param name="end1">1つ目の右下上座標</param>
	/// <param name="start2">1つ目の左上座標</param>
	/// <param name="end2">1つ目の右下座標</param>
	/// <returns>当たったかどうか</returns>
	static bool rectCollision
	(
		const Vector2& pos1,
		const Vector2& size1, 
		const Vector2& pos2,
		const Vector2& size2
	);

	/// <summary>
	/// 円の当たり判定です
	/// </summary>
	/// <param name="centerPosition1">1つ目の座標</param>
	/// <param name="r1">1つ目の半径</param>
	/// <param name="centerPosition2">1つ目の座標</param>
	/// <param name="r2">1つ目の円</param>
	/// <returns>当たったかどうか</returns>
	static bool circleCollision(Vector2 centerPosition1, float r1, Vector2 centerPosition2, float r2);

#pragma endregion

#pragma region 3D
	/// <summary>
	/// 球同士の当たり判定
	/// </summary>
	/// <param name="centerPosition1">1つ目の座標</param>
	/// <param name="r1">1つ目の半径</param>
	/// <param name="centerPosition2">1つ目の座標</param>
	/// <param name="r2">1つ目の円</param>
	/// <returns>当たったかどうか</returns>
	static bool sphereCollision(Vector3 centerPosition1, float r1, Vector3 centerPosition2, float r2);

	/// <summary>
	/// 球と平面の座標
	/// </summary>
	/// <param name="spherePos"></param>
	/// <param name="r"></param>
	/// <param name="normal">平面の法線ベクトル</param>
	/// <param name="planeDist">平面の原点から平面の距離(マイナス可能)</param>
	/// <param name="hitPos"></param>
	/// <returns></returns>
	static bool sphereAndPlaneCollision
	(
		Vector3 spherePos,
		float r,
		Vector3 normal,
		float planeDist,
		Vector3* hitPos
	);

	/// <summary>
	/// 球と平らな三角形の判定
	/// </summary>
	/// <param name="spherePos"></param>
	/// <param name="r"></param>
	/// <param name="triPos1"></param>
	/// <param name="triPos2"></param>
	/// <param name="triPos3"></param>
	/// <param name="normal"></param>
	/// <param name="hitPos"></param>
	/// <returns></returns>
	static bool sphereAndTryangleCollision
	(
		Vector3 spherePos,
		float r,
		Vector3 triPos1,
		Vector3 triPos2,
		Vector3 triPos3,
		Vector3 normal,
		Vector3* hitPos
	);

	/// <summary>
	/// 球と立方体(AABB)の判定
	/// </summary>
	/// <param name="spherePos"></param>
	/// <param name="r"></param>
	/// <param name="minPos"></param>
	/// <param name="maxPos"></param>
	/// <param name="direction"></param>
	/// <returns></returns>
	static bool sphereAndBoxCollision
	(
		const Vector3& spherePos,
		const float& r,
		const Vector3& centerPos,
		const Vector3& size,
		BoxHitDirection* direction
	);

	/// <summary>
	/// 線分と板の当たり判定
	/// </summary>
	/// <param name="linePos1">線1</param>
	/// <param name="linePos2">線2</param>
	/// <param name="normal">板の法線ベクトル</param>
	/// <param name="pointPos">板の座標</param>
	/// <param name="vertexPoint">頂点の座標4つ(回転など適応後)(回転前の左下、左上、右下、右上の順で配列に入れる)</param>
	/// <param name="crossPos">線とポリゴンがぶつかった場所</param>
	/// /// <returns></returns>
	static bool lineSegmentAndBoardCollision
	(
		Vector3 linePos1,
		Vector3 linePos2,
		Vector3 normal,
		Vector3 pointPos,
		std::vector<Vector3>vertexPoint,
		Vector3* crossPosition
	);

	/// <summary>
	/// 半直線と平面の
	/// </summary>
	/// <param name="layStartPos"></param>
	/// <param name="layDirection"></param>
	/// <param name="normal"></param>
	/// <param name="planeDist"></param>
	/// <param name="distance"></param>
	/// <param name="crossPos"></param>
	/// <returns></returns>
	static bool rayAndPlaneCollision
	(
		Vector3 layStartPos,
		Vector3 layDirection,
		Vector3 normal,
		float planeDistance,
		float* distance,
		Vector3* crossPos
	);

	static bool rayAndTryangleCollision
	(
		Vector3 layStartPos,
		Vector3 layDirection,
		Vector3 triPos1,
		Vector3 triPos2,
		Vector3 triPos3,
		Vector3 normal,
		float* distance,
		Vector3* crossPos
	);

	/// <summary>
	/// 半直線と球の当たり判定
	/// </summary>
	static bool rayAndSphereCollision
	(
		Vector3 layStartPos,
		Vector3 layDirection,
		Vector3 spherePos,
		float r,
		float* distance,
		Vector3* crossPos
	);
#pragma endregion

#pragma endregion


};

