#pragma once
class AttackWeightManager
{
public:

	static AttackWeightManager& GetAttackWeightManager()
	{
		static AttackWeightManager instance; // ƒVƒ“ƒOƒ‹ƒgƒ“
		return instance;
	}

	void LoadFile(const std::string& filepath);

	 std::vector<int> GetWeights(const std::string& phase, const std::string& range)const;


private:

	AttackWeightManager() = default;
	~AttackWeightManager() = default;
	AttackWeightManager(const AttackWeightManager&) = delete;
	AttackWeightManager& operator=(const AttackWeightManager&) = delete;

	nlohmann::json jsonData;
};
