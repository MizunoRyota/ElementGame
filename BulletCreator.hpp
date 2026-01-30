#pragma once
#include <functional>

class Bullet;

// 弾プール管理。生成/更新/描画とクールダウンの制御を担当
class BulletCreator
{
private:
    BulletCreator(const BulletCreator&) = delete;
    BulletCreator();
    ~BulletCreator();

public:
    void CreateBullet(const VECTOR& pos, const VECTOR& dir, const float& speed, int effectTypeIndex); // 基本弾生成
    void CreateHomingBullet(const VECTOR& pos, const VECTOR& dir, const float& speed, std::function<VECTOR()> targetGetter, float homingDuration, float turnSpeedRad, int effectTypeIndex);

    void Initialize(); // プール初期化
    void Update();     // 全弾更新
    void Draw();       // デバッグ描画

    void StopBulletEffect();

    std::shared_ptr<Bullet> GetBullet(int index) const { return bullets[index]; }

    int GetBulletCount()    const { return static_cast<int>(bullets.size()); }

    static BulletCreator& GetBulletCreator()
    {
        static BulletCreator bullet_creator;
        return bullet_creator;
    }

private:
    static const int BULLET_NUM = 150;                 // プール最大数
    static constexpr float BULLET_COOLDOWN_TIME = 20;  // 発射クール時間
    float bullet_cooldowntimer = 0;                    // クールタイマ
    std::vector<std::shared_ptr<Bullet>> bullets;      // 弾配列
};
