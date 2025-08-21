#include"DxLib.h"
#include"Sound.hpp"

Sound::Sound()
	:TitleHandle(0)
	, TutorialHandle(0)
	, GameHandle(0)
	, GameOverHandle(0)
	, GameClearHandle(0)
	, DecideHandle(0)
	, ExplosionHandle(0)
	, OnenemyHandle(0)
	, OnPlayerHandle(0)
	, firehandle(0)
{
}

Sound::~Sound()
{
}

void Sound::Load()
{
	TitleHandle = LoadSoundMem("data/sound/Title.mp3");
	TutorialHandle = LoadSoundMem("data/sound/Tutorial.mp3");
	GameHandle = LoadSoundMem("data/sound/Game.mp3");
	GameOverHandle = LoadSoundMem("data/sound/GameOver.mp3");
	GameClearHandle = LoadSoundMem("data/sound/GameClear.mp3");
	DecideHandle = LoadSoundMem("data/sound/Decide.mp3");
	ExplosionHandle = LoadSoundMem("data/sound/Explosion.mp3");
	OnenemyHandle = LoadSoundMem("data/sound/Onenemy.mp3");
	OnPlayerHandle = LoadSoundMem("data/sound/Onplayer.mp3");
	firehandle = LoadSoundMem("data/sound/Fire.mp3");
	ChangeVolumeSoundMem(255 * 50 / 100, TitleHandle);
	ChangeVolumeSoundMem(255 * 50 / 100, TutorialHandle);
	ChangeVolumeSoundMem(255 * 50 / 100, GameHandle);
	ChangeVolumeSoundMem(255 * 50 / 100, GameOverHandle);
	ChangeVolumeSoundMem(255 * 50 / 100, GameClearHandle);
	ChangeVolumeSoundMem(255 * 100 / 100, DecideHandle);
	ChangeVolumeSoundMem(255 * 50 / 100, ExplosionHandle);
	ChangeVolumeSoundMem(255 * 50 / 100, OnenemyHandle);
	ChangeVolumeSoundMem(255 * 50 / 100, OnPlayerHandle);
}

void Sound::PlayTitle()
{
	PlaySoundMem(TitleHandle, DX_PLAYTYPE_LOOP, false);
}

void Sound::PlayTutorial()
{
	PlaySoundMem(TutorialHandle, DX_PLAYTYPE_LOOP, false);
}
void Sound::PlayGame()
{
	PlaySoundMem(GameHandle, DX_PLAYTYPE_LOOP, false);
}

void Sound::PlayGameOver()
{
	PlaySoundMem(GameOverHandle, DX_PLAYTYPE_LOOP, false);
}

void Sound::PlayGameClear()
{
	PlaySoundMem(GameClearHandle, DX_PLAYTYPE_LOOP, false);
}
void Sound::PlayDecide()
{
	PlaySoundMem(DecideHandle, DX_PLAYTYPE_BACK, true);          //kettei
}


void Sound::PlayExplosion()
{
	PlaySoundMem(ExplosionHandle, DX_PLAYTYPE_BACK, true);       //kettei
}

void Sound::PlayOnenemy()
{
	PlaySoundMem(OnenemyHandle, DX_PLAYTYPE_BACK, true);           //kettei
}

void Sound::PlayOnplayer()
{
	PlaySoundMem(OnPlayerHandle, DX_PLAYTYPE_BACK, true);           //kettei
}

void Sound::PlaySlash()
{
	PlaySoundMem(firehandle, DX_PLAYTYPE_BACK, true);           //kettei
}
void Sound::StopTitle()
{
	StopSoundMem(TitleHandle);
}

void Sound::StopTutorial()
{
	StopSoundMem(TutorialHandle);
}
void Sound::StopGame()
{
	StopSoundMem(GameHandle);
}

void Sound::StopGameOver()
{
	StopSoundMem(GameOverHandle);
}

void Sound::StopGameClear()
{
	StopSoundMem(GameClearHandle);
}

void Sound::Delete()
{
	DeleteSoundMem(TitleHandle);
	DeleteSoundMem(TutorialHandle);
	DeleteSoundMem(GameHandle);
	DeleteSoundMem(GameOverHandle);
	DeleteSoundMem(GameClearHandle);
}