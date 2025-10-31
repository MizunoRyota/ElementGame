#pragma once

#include "Scene.hpp"
#include "SharedData.hpp"

// シーンマネージャ
// 追加・切替・更新・描画の制御を行う
class SceneManager
{
public:

	SceneManager();  // 共有データなどの初期化
	~SceneManager();

	// アクティブシーンの更新
	void Update() const;

	// アクティブシーンの描画
	void Draw() const;

	// シーンの追加
	template <class SceneType>
	void Add(const std::string_view name)
	{
		m_scenes[name] = new SceneType{ *this, *m_sharedData };
		if (m_nowScene == nullptr)
		{
			m_nowScene = m_scenes[name];
			m_nowScene->Initialize();
		}
	}

	// アクティブシーンを切り替え
	void ChangeScene(std::string_view name);

private:
	std::unordered_map<std::string_view, Scene*> m_scenes; // 登録シーン
	Scene* m_nowScene;                                     // 現在シーン
	SharedData* m_sharedData;                              // 共有データ
};
