#pragma once
class Input;

/// <summary>
/// カメラ
/// </summary>
class Camera
{
public:
	Camera();			// コンストラクタ.
	~Camera();			// デストラクタ.
	void Load();		// 初期化
	void Update(VECTOR playerPos);		// 更新
	void FixCameraPosition();			// カメラを元の位置に戻す
	// ポジションのgetter/setter.
	const VECTOR& GetPosition() const { return position; }
	const VECTOR& GetTarget()	const { return targetPosition; }
	const VECTOR& GetCameraDir() const { return camera_dir; }

private:
	static constexpr float   CameraTargetPlayerHeight = 0.650f;		// プレイヤーからカメラの注視点への高さ
	static constexpr float   ToPlayerLength = 1.30f;					// プレイヤーとの距離
	static constexpr float	 AngleSpeed = 0.02f;					// 向きが変わるスピード
	static constexpr float	 CameraPlayerTargetHeight = 1.8f;		// プレイヤー座標からどれだけ高い位置を注視点とするか

	float            angleVertical;					// カメラの垂直角度
	float            angleHorizontal;				// カメラの水平角度
	float            shakeOffset;					// カメラを揺らしたときのずらした値の保存

	float shakeTime;			// 揺れ時間
	bool isDamage;				// ダメージを受けているか
	bool isShake;				// 揺れているか
	Input* rightInput;			// 右スティック情報
	VECTOR Offset;				// 
	VECTOR OriginalOffset;		// 
	VECTOR AngleVec;			// 向きベクトル
	VECTOR position;			// ポジション.
	VECTOR targetPosition;		// カメラが注視するポジション
	// カメラの向き（ターゲット位置）
	VECTOR camera_dir;
};