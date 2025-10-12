#pragma once

// UI 要素ベースインターフェース
class IUiElement
{
public:
    virtual ~IUiElement() = default;

    virtual void UpdateTitle()abstract;
    virtual void Update() abstract;      // 値更新
    virtual void UpdateGameClear()abstract;
    virtual void UpdateGameOver()abstract;

    virtual void DrawTitle() const abstract;  // 描画
    virtual void DrawTutorial() const abstract;
    virtual void Draw() const abstract;  // 描画
    virtual void DrawGameOver() const abstract;  // 描画
    virtual void DrawGameClear() const abstract;  // 描画

    int GetZ() const { return order_z; }            // Z ソートキー
    void SetZ(int z) { order_z = z; dirty_ = true; } // Z 変更
    bool IsVisible() const { return uielement_visible; }      // 表示切替
    void SetVisible(bool v) { uielement_visible = v; }
protected:
    static constexpr float DISPLAY_ = 1.0f / 60.0f; // 1 フレーム時間(遅延計算用)
    int  order_z = 0;   // 描画優先度(小さい→背面)
    bool uielement_visible = true; // 表示フラグ
    bool dirty_ = false;  // ソート再要求
    int graph_handle = 0; //画像ハンドル
};

// UI 管理クラス: 要素登録・更新・描画および Z ソート
class UiManager
{
public:
    UiManager();
    ~UiManager();

    void AddElement(const std::shared_ptr<IUiElement>& element);    // 追加
    void RemoveElement(const std::shared_ptr<IUiElement>& element); // 削除
    

    void UpdateTitle();
    void UpdateTutorial(); // 全要素更新

    void Update(); // 全要素更新
    void UpdateGameClear();
    void UpdateGameOver();

    void DrawTitle() const; // 全要素描画
    void DrawTutorial()const;
    void Draw() const; // 全要素描画
    void DrawGameClear() const; // 全要素描画
    void DrawGameOver() const; // 全要素描画
private:
    std::vector<std::shared_ptr<IUiElement>> elements_; // 管理配列
    mutable bool needSort_ = false; // ソート必要フラグ
};