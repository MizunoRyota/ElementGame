#pragma once

class SceneManager;
class SharedData;

/// @brief シーン基底クラス
/// SceneManager で管理される各シーンはこのクラスを継承して実装する。
class Scene
{
public:

	/// @brief SceneManager への参照を受け取ります。
	/// @param manager SceneManager への参照
	Scene(SceneManager& manager, SharedData& sharedData);

	/// @brief シーンを初期化します。
	/// @remark デフォルトでは何もしません。
	virtual void Initialize();

	virtual void WhiteOut();

	/// @brief シーンを更新します。
	/// @remark デフォルトでは何もしません。
	virtual void Update();

	/// @brief シーンを描画します。
	/// @remark デフォルトでは何もしません。
	virtual void Draw();

protected:
	/// @brief アクティブなシーンを切り替えます。
	/// @param name 切り替え先のシーン名
	void ChangeScene(std::string_view name);

	SharedData& GetSharedData()
	{
		return m_sharedData;
	}

private:
	static constexpr int  WHITEOUT_TIME = 2300;          //ホワイトアウトの時間
	static constexpr int  WHITEOUT_TIMESPEED = 35;     //ホワイトアウトの時間速度調整

	float alpha;

	SceneManager& m_manager;  /// @brief SceneManager への参照
	SharedData& m_sharedData; /// @brief 共有データへの参照

	bool whiteout_is_end; /// @brief ホワイトアウト完了フラグ
};
