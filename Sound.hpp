#pragma once
#pragma once

class Sound
{
public:
	Sound();
	~Sound();
	void Load();
	void PlayTitle();
	void PlayTutorial();
	void PlayGame();
	void PlayGameOver();
	void PlayGameClear();
	void PlayDecide();
	void PlayExplosion();
	void PlayOnenemy();
	void PlayOnplayer();
	void PlaySlash();
	void StopTitle();
	void StopTutorial();
	void StopGame();
	void StopGameOver();
	void StopGameClear();
	void Delete();
private:
	int TitleHandle;
	int TutorialHandle;
	int GameHandle;
	int GameOverHandle;
	int GameClearHandle;
	int DecideHandle;
	int ExplosionHandle;
	int OnenemyHandle;
	int OnPlayerHandle;
	int firehandle;
};