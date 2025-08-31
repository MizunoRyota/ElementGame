#pragma once
#include <string_view>

class SceneManager;
class SharedData;

/// @brief シーンの基底クラス
/// @remark SceneManager で管理するシーンはこのクラスを継承する必要があります。
class Scene
{
public:

    /// @brief SceneManager への参照を受け取ります。
    /// @param manager SceneManager への参照
    Scene(SceneManager& manager, SharedData& sharedData);

    /// @brief シーンを初期化します。
    /// @remark デフォルトでは何もしません。
    virtual void Initialize();

    /// @brief シーンを更新します。
    /// @remark デフォルトでは何もしません。
    virtual void Update();

    /// @brief シーンを描画します。
    /// @remark デフォルトでは何もしません。
    virtual void Draw() ;

protected:

    /// @brief アクティブなシーンを切り替えます。
    /// @param name 切り替え先のシーン名
    void ChangeScene(std::string_view name);

    SharedData& GetSharedData()
    {
        return m_sharedData;
    }

private:

    /// @brief SceneManager への参照
    /// @note ポインタを使うより安全です。
    SceneManager& m_manager;

    SharedData& m_sharedData;
};
