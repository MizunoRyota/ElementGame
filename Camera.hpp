#pragma once
#include "GameObject.hpp" 

class Input;
class GameObject;
class Player;
class Enemy;

/// <summary>
/// カメラ
/// </summary>
class Camera : public GameObject
{
public:
	Camera();			// コンストラクタ.
	~Camera();			// デストラクタ.
	void Initialize()override; 		// 初期化

	// シーン別更新
	void UpdateTitle() override;		// 追加: 引数無しタイトル更新
	void Update()override; 				// 更新
	void UpdateGameClear() override ;	// ゲームクリア時の更新(位置指定)
	void UpdateGameOver() override { UpdateGameClear(); }// タイトル時の更新(位置指定)

	// シーン別描画 (カメラ自体は描画不要)
	void DrawTitle() override {};
	void Draw()override {}; 			// 描画
	void DrawGameOver() override {};
	void DrawGameClear() override {};

	// ------------- 追加: 汎用 Lerp 関数 -------------
	VECTOR Lerp(const VECTOR& a, const VECTOR& b, float t);

	void FixCameraPosition(); 			// カメラを元の位置に戻す
	// ポジションのgetter/setter.
	const VECTOR& GetPosition() const { return camera_position; }
	// GameObject の仮想関数をオーバーライドしない (別名メソッド) に変更しコンパイルエラー回避
	const VECTOR& GetCameraTarget() const { return camera_targetpos; }
	const VECTOR& GetCameraDir() const { return camera_dirction; }

	void SetPlayer(const std::shared_ptr<Player>& setplayer) { player = setplayer; }
	void SetEnemy(const std::shared_ptr<Enemy>& setenemy) { enemy = setenemy; }

private:
	static constexpr float   CAMERA_NEAR = 0.1f; 		// カメラのNEAR
	static constexpr float   CAMERA_FAR = 300.0f; 		// カメラのFAR
	static constexpr float   CAMERA_TARGET_PLAYERHIGHT = 0.650f; 		// プレイヤーからカメラの注視点への高さ
	static constexpr float   TOPLAYER_LENGTH = 1.30f; 				// プレイヤーとの距離
	static constexpr float	 ANGLE_SPEED = 0.02f; 					// 向きが変わるスピード
	static constexpr float	 CAMERA_PLAYERTARGET_HIGHT = 1.8f; 		// プレイヤー座標からどれだけ高い位置を注視点とするか

	float            angleVertical; 				// カメラの垂直角度
	float            angleHorizontal; 				// カメラの水平角度
	float            shakeOffset; 					// カメラを揺らしたときのずらした値の保存

	float shakeTime; 			// 揺れ時間
	bool isDamage; 				// ダメージを受けているか
	bool isShake; 				// 揺れているか
	Input* rightInput; 			// 右スティック情報
	VECTOR OriginalOffset; 		// 
	VECTOR camera_angle; 		// 向きベクトル
	VECTOR camera_position; 	// ポジション.
	VECTOR camera_targetpos; 	// カメラが注視するポジション

	VECTOR camera_dirction; 	// カメラの向き（ターゲット位置）

	std::shared_ptr<Player> player; 	//参照
	std::shared_ptr<Enemy> enemy; 	//参照

};