#pragma once

class PlayerBase;
class EnemyBase;

class Stage
{
public:
	Stage();
	~Stage();

	// 当たり判定をして、補正後のポジションを返す
	VECTOR CheckCollision(PlayerBase& playermove, const VECTOR& moveVector);
	VECTOR CheckEnemyCollision(EnemyBase& enemy, const VECTOR& moveVector);
	void Draw();
private:
	static const int MaxHitColl = 2048;		// 処理するコリジョンポリゴンの最大数

	static constexpr float Scale = 0.0125f;	//モデルの大きさの倍数
	static constexpr float	DefaultSize = 5.0f;	// 周囲のポリゴン検出に使用する球の初期サイズ
	static constexpr float	HitWidth = 0.20f;	// 当たり判定カプセルの半径
	static constexpr float	HitHeight = 0.70f;	// 当たり判定カプセルの高さ
	static constexpr int	HitTryNum = 16;		// 壁押し出し処理の最大試行回数
	static constexpr float	HitSlideLength = 0.010f;		// 一度の壁押し出し処理でスライドさせる距離

	int StageHandle;	//モデルハンドル

	VECTOR position;

	// HACK: 壁はXZ平面に垂直である前提で成り立っている。それ以外を置くとバグる
	int		wallNum;			// 壁ポリゴンと判断されたポリゴンの数
	int		floorNum;			// 床ポリゴンと判断されたポリゴンの数

	MV1_COLL_RESULT_POLY* wall[MaxHitColl];	// 壁ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY* floor[MaxHitColl];	// 床ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列

	// 検出されたポリゴンが壁ポリゴン( ＸＺ平面に垂直なポリゴン )か床ポリゴン( ＸＺ平面に垂直ではないポリゴン )かを判断し、保存する
	void AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition);

	// 壁ポリゴンとの当たりをチェックし、補正すべき移動ベクトルを返す
	VECTOR CheckHitWithWall(PlayerBase& playermove, const VECTOR& checkPosition);

	// 床ポリゴンとの当たりをチェックし、補正すべき移動ベクトルを返す
	VECTOR CheckHitWithFloor(PlayerBase& playermove, const VECTOR& checkPosition);

	// 壁ポリゴンとの当たりをチェックし、補正すべき移動ベクトルを返す
	VECTOR CheckEnemyHitWithWall(EnemyBase& enemymove, const VECTOR& checkPosition);

	// 床ポリゴンとの当たりをチェックし、補正すべき移動ベクトルを返す
	VECTOR CheckEnemyHitWithFloor(EnemyBase& enemymove, const VECTOR& checkPosition);

};
