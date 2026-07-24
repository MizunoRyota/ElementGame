#pragma once
#include "../EnemyStateBase.hpp"

// EnemyStateChoseAttack:
// 次に行う攻撃を選択するステート。
// - 敵HP割合（フェーズ）とプレイヤー距離（短/長）によって候補を切り替える
// - `AttackWeightManager` に定義された重みで確率選択し、`enemy_attack_state` を決定する
// - 選択が完了したら `STATE_CHARGE` に遷移して行動開始へ繋げる
class EnemyStateChoseAttack : public EnemyStateBase
{
public:
    EnemyStateChoseAttack();
    ~EnemyStateChoseAttack();

    // HP割合による行動パターン段階
    enum class ChoseRaito : int
    {
        PhaseOne = 1,
        PhaseTWO = 2,
        PhaseTHREE = 3,
    };

    // 選択開始（Enter で必ず攻撃を選ぶ）
    void Enter() override;

    // 選択は Enter 時に完了する想定のため Update は空
    void Update() override {};

    // 選択完了フラグをリセット
    void Exit() override ;

    // 攻撃選択の入口
    void ChoseAttackState();

    // フェーズ別の選択ロジック
    void ChoseNextAttackPhaseOne(const VECTOR& keepDistance, const float& checkDistance);

    void ChoseNextAttackPhaseTwo(const VECTOR& keepDistance, const float& checkDistance);

    void ChoseNextAttackPhaseThree(const VECTOR& keepDistance, const float& checkDistance);

    // HP割合と距離判定から、フェーズ関数へ分岐
    void CheckEnemyPhase();

    // 遷移：選択が終わったら Charge へ
    EnemyStateKind GetNextState()override;

private:
    // HP割合によるフェーズ分岐しきい値
    static constexpr float ENEMY_HP_PHASE1_RAITO = 1.0f;
    static constexpr float ENEMY_HP_PHASE2_RAITO = 0.8f;
    static constexpr float ENEMY_HP_PHASE3_RAITO = 0.3f;

    // 距離判定（注意：VSquareSize を使っているため二乗距離比較）
    static constexpr float SHORT_RANGE = 0.10f;
    static constexpr float LONG_RANGE = 300.0f;

    // Enter 時に true → Exit で false（選択完了の判定に使用）
    bool attack_is_chose;

    // 重み付き乱数用
    std::mt19937 gen{ std::random_device{}() };
};

