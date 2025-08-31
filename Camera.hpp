#pragma once
#include <memory>
#include "GameObject.hpp" 

class Input;
class GameObject;
class Player;
/// <summary>
/// カメラ
/// </summary>
class Camera : public GameObject
{
public:
	Camera();			// コンストラクタ.
	~Camera();			// デストラクタ.
	void Initialize()override;		// 初期化
	void Update()override;		// 更新
	void Draw()override;		//描画
	void UpdateClear(const VECTOR& enemypos);	// ゲームオーバー時の更新
	void UpdateTitle(const VECTOR& enemypos);	// ゲームオーバー時の更新
	void UpdateGameOver(const VECTOR& enemypos);	// ゲームオーバー時の更新

	void FixCameraPosition();			// カメラを元の位置に戻す
	// ポジションのgetter/setter.
	const VECTOR& GetPosition() const { return camera_position; }
	const VECTOR& GetTarget()	const { return camera_targetpos; }
	const VECTOR& GetCameraDir() const { return camera_dirction; }

	void SetPlayer(const std::shared_ptr<Player>& setplayer) { player = setplayer; }

private:
	static constexpr float   CAMERA_TARGET_PLAYERHIGHT = 0.650f;		// プレイヤーからカメラの注視点への高さ
	static constexpr float   TOPLAYER_LENGTH = 1.30f;					// プレイヤーとの距離
	static constexpr float	 ANGLE_SPEED = 0.02f;					// 向きが変わるスピード
	static constexpr float	 CAMERA_PLAYERTARGET_HIGHT = 1.8f;		// プレイヤー座標からどれだけ高い位置を注視点とするか

	float            angleVertical;					// カメラの垂直角度
	float            angleHorizontal;				// カメラの水平角度
	float            shakeOffset;					// カメラを揺らしたときのずらした値の保存

	float shakeTime;			// 揺れ時間
	bool isDamage;				// ダメージを受けているか
	bool isShake;				// 揺れているか
	Input* rightInput;			// 右スティック情報
	VECTOR OriginalOffset;		// 
	VECTOR camera_angle;			// 向きベクトル
	VECTOR camera_position;			// ポジション.
	VECTOR camera_targetpos;		// カメラが注視するポジション
	// カメラの向き（ターゲット位置）
	VECTOR camera_dirction;

	std::shared_ptr<Player> player = nullptr;

};