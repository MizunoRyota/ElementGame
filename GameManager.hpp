#pragma once
class GameManager
{
public:
	GameManager();
	~GameManager();
	void Initialize();
	void FadeOutToWhite(int duration);
	const bool& GetisWhiteOut() const { return isWhiteOut; }

private:
	bool isWhiteOut;
};

