#pragma once
#include "stdafx.hpp"

// 全ゲームオブジェクトの基底クラス
// 各シーンの更新/描画や位置・向き、HP などの共通プロパティを提供する
class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	// 初期化（リソース読み込みや変数の初期値設定）
	virtual void Initialize() abstract;
	// 毎フレームの更新
	virtual void Update() abstract;

	// シーン別描画
	virtual void DrawTitle() abstract;      // タイトル描画
	virtual void Draw() abstract;           // 通常描画
	virtual void DrawGameOver() abstract;   // ゲームオーバー描画
	virtual void DrawGameClear() abstract;  // ゲームクリア描画

	// シーン別更新（必要に応じて派生で実装）
	virtual void UpdateGameClear() abstract;
	virtual void UpdateGameOver() abstract;
	virtual void UpdateTitle() abstract;

	// 各種情報取得
	virtual const int& GetDamageStrength() const { return obj_damagestrength; } // 与ダメージ量
	virtual const int& GetHp() const { return obj_hp; }                          // 現在HP
	virtual const int& GetHandle() const { return obj_modelhandle; }             // 3Dモデルハンドル
	virtual const VECTOR& GetPosition() const { return obj_position; }           // ワールド座標
	virtual const VECTOR& GetDirection() const { return obj_direction; }         // 進行方向などに使用
	virtual VECTOR GetTarget() const { return VAdd(obj_position, VGet(0, TARGETHIGHT, 0)); } // 注視点（頭上）
	std::string GetNameTag() const { return obj_name; }                          // デバッグ用名札

	// オブジェクト参照を設定（必要なら派生で拡張）
	virtual const std::shared_ptr<GameObject> SetGameObject(const std::shared_ptr<GameObject>& set_object) { return set_object; }

	// 位置を設定
	virtual void Setposition(const VECTOR set) { obj_position = set; }

protected:
	static constexpr float TARGETHIGHT = 2.25f; // 注視点の高さ（頭頂の目安）

	std::string obj_name = "null";      // デバッグ名
	VECTOR obj_position = VGet(0,0,0);   // 位置
	VECTOR obj_direction = VGet(0,0,0);  // 向き
	int obj_modelhandle = 0;              // モデルハンドル
	int obj_effecthandle = 0;             // エフェクトハンドル
	int obj_hp = 0;                       // HP
	int obj_damagestrength = 0;           // 与ダメージ量の基礎値
	float obj_modelscale = 0;             // モデル拡大率
};