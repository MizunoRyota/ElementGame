#include"DxLib.h"
#include"GameManager.hpp"

GameManager::GameManager()
	:isWhiteOut(false)
{
}

GameManager::~GameManager()
{
}

void GameManager::Initialize()
{
	isWhiteOut = false;
}

void GameManager::FadeOutToWhite(int duration)
{
    int startTime = GetNowCount();
    int endTime = startTime + duration;
    if (isWhiteOut==true)
    {
        isWhiteOut = false;
    }
    while (GetNowCount() < endTime)
    {
        int elapsedTime = GetNowCount() - startTime;
        float alpha = static_cast<float>(elapsedTime) / duration;

        // ‰æ–Ê‚ğ”’F‚Å“h‚è‚Â‚Ô‚·
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(alpha * 50));
        DrawBox(0, 0, 1920, 1080, GetColor(255, 255, 255), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        // ‰æ–Ê‚ğXV
        ScreenFlip();
    }
	isWhiteOut = true;
}