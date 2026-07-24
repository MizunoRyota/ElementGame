#include "stdafx.hpp"
#include "AttackWeightManager.hpp"

void AttackWeightManager::LoadFile(const std::string& filepath)
{
    std::ifstream file(filepath);

    if (!file.is_open())
    {
        return;
    }
     jsonData = json::parse(file);

}

std::vector<int> AttackWeightManager::GetWeights(
    const std::string& phase,
    const std::string& range) const
{
    auto attackWeights = jsonData.at(phase).at(range);
    std::vector<int> weights;

    std::vector<std::string> keys;

    if (phase == "PhaseOne")
    {
        keys = { "FireAttack", "WaterAttack" };
    }
    else if (phase == "PhaseTwo"|| phase == "PhaseThree")
    {
        if (range == "LongRange")
        {
            keys = {"FireAttack", "JumpAttack", "WindAttack", "Float"};
        }
        else if (range == "ShortRange")
        {
            keys = {"FireAttack", "WaterAttack", "WindAttack", "Float"};
        }
    }
    
    for (const auto& key : keys)
    {
        if (attackWeights.contains(key))
        {
            weights.push_back(attackWeights.at(key).get<int>());
        }
    }
    
    return weights;
}