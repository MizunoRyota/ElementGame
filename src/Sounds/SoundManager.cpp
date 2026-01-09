#include "../stdafx.hpp"
#include "SoundManager.hpp"

SoundManager::SoundManager()
{
	title_bgm = LoadSoundMem("./data/sounds/TitleBgm.mp3");
	game_bgm = LoadSoundMem("./data/sounds/GameBgm.mp3");
	gameclear_bgm = LoadSoundMem("./data/sounds/GameClearBgm.mp3");
	gameover_bgm = LoadSoundMem("./data/sounds/GameOverBgm.mp3");
	button_se = LoadSoundMem("./data/sounds/ButtonSe.mp3");
	fire_se = LoadSoundMem("./data/sounds/FireSe.mp3");
	explosion_se = LoadSoundMem("./data/sounds/ExplosionSe.mp3");
	on_enemy_se = LoadSoundMem("./data/sounds/OnEnemySe.mp3");
	on_player_se = LoadSoundMem("./data/sounds/OnPlayerSe.mp3");
	break_crystal_se = LoadSoundMem("./data/sounds/BreakCrystalSe.mp3");
	fire_laser_se = LoadSoundMem("./data/sounds/FireLaserSe.mp3");
	tutorial_bgm = LoadSoundMem("./data/sounds/TutorialBgm.mp3");
	charge_special_se = LoadSoundMem("./data/sounds/ChargeSpecialSe.mp3");
	// âπó ÇÃê›íË
	ChangeVolumeSoundMem(130, title_bgm);
	ChangeVolumeSoundMem(130, game_bgm);
	ChangeVolumeSoundMem(130, gameclear_bgm);
	ChangeVolumeSoundMem(130, gameover_bgm);
	ChangeVolumeSoundMem(130, tutorial_bgm);
	ChangeVolumeSoundMem(250, break_crystal_se);
	ChangeVolumeSoundMem(200, fire_se);

}

SoundManager::~SoundManager()
{
}