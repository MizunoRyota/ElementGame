#pragma once

#include <memory>
#include <vector>
#include <algorithm>

// 汎用UI要素インターフェース
class IUiElement
{
public:
    virtual ~IUiElement() = default;
    virtual void Update(float dt) = 0;
    virtual void Draw() const = 0;
    int GetZ() const { return zOrder_; }                 // 描画順序(小さいほど奥)
    void SetZ(int z) { zOrder_ = z; dirty_ = true; }      // 描画順序設定
    bool IsVisible() const { return visible_; }
    void SetVisible(bool v) { visible_ = v; }
protected:
    int  zOrder_ = 0;   // 旧: z_  描画順序
    bool visible_ = true;
    bool dirty_ = false; // Z変更時ソート要求
};

class UiManager
{
public:
    UiManager();
    ~UiManager();

    // 要素登録/削除
    void AddElement(const std::shared_ptr<IUiElement>& element);
    void RemoveElement(const std::shared_ptr<IUiElement>& element);

    // 更新/描画
    void Update(float dt = 0.0f);
    void Draw() const;

private:
    std::vector<std::shared_ptr<IUiElement>> elements_;
    mutable bool needSort_ = false;
};