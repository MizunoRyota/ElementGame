#pragma once
#include <unordered_map>
#include <string>
#include <any>

// BT等で共有する簡易キーバリューストア
class Blackboard
{
public:
	// 値の設定
	template <class T>
	void Set(const std::string& key, T&& value)
	{
		data[key] = std::any(std::forward<T>(value));
	}

	// 値の取得（存在しない/型不一致なら false）
	template <class T>
	bool Get(const std::string& key, T& out) const
	{
		auto it = data.find(key);
		if (it == data.end()) return false;
		if (auto p = std::any_cast<T>(&it->second))
		{
			out = *p;
			return true;
		}
		return false;
	}

	// 指定キーの存在
	bool Has(const std::string& key) const { return data.find(key) != data.end(); }

	// クリア
	void Clear() { data.clear(); }

private:
	std::unordered_map<std::string, std::any> data; // 値の保管庫
};

