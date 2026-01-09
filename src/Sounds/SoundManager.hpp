#pragma once

class SoundManager
{
public:
	// インスタンス取得用
	static SoundManager& GetSoundManager()
	{
		static SoundManager instance; // シングルトン
		return instance;
	}

	// コピーコンストラクタと代入演算子を削除
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;

	void PlayTitleBgm() { PlaySoundMem(title_bgm, DX_PLAYTYPE_LOOP); }
	void PlayGameBgm() { PlaySoundMem(game_bgm, DX_PLAYTYPE_LOOP); }
	void PlayGameClearBgm() { PlaySoundMem(gameclear_bgm, DX_PLAYTYPE_LOOP); }
	void PlayGameOverBgm() { PlaySoundMem(gameover_bgm, DX_PLAYTYPE_LOOP); }
	void PlayButtonSe() { PlaySoundMem(button_se, DX_PLAYTYPE_BACK); }
	void PlayFireSe() { PlaySoundMem(fire_se, DX_PLAYTYPE_BACK); }
	void PlayExplosionSe() { PlaySoundMem(explosion_se, DX_PLAYTYPE_BACK); }
	void PlayOnPlayerSe() { PlaySoundMem(on_player_se, DX_PLAYTYPE_BACK); }
	void PlayOnEnemySe() { PlaySoundMem(on_enemy_se, DX_PLAYTYPE_BACK); }
	void PlayFireLaserSe() { PlaySoundMem(fire_laser_se, DX_PLAYTYPE_BACK); }
	void PlayBreakCrystalSe() { PlaySoundMem(break_crystal_se, DX_PLAYTYPE_BACK); }
	void PlayTutorialBgm() { PlaySoundMem(tutorial_bgm, DX_PLAYTYPE_LOOP); }
	void PlayChargeSpecialSe() { PlaySoundMem(charge_special_se, DX_PLAYTYPE_BACK); }


	void StopAllSound() { StopSoundMem(title_bgm); StopSoundMem(game_bgm); StopSoundMem(gameclear_bgm); StopSoundMem(gameover_bgm); StopSoundMem(tutorial_bgm); }

	void StopSoundCharge() { StopSoundMem(charge_special_se); }

private:

	SoundManager();
	~SoundManager();
	
	int title_bgm;			//タイトルBGM
	int tutorial_bgm;		//チュートリアルBGM
	int game_bgm;			//ゲームBGM
	int gameclear_bgm;		//クリアBGM
	int gameover_bgm;		//ゲームオーバーBGM
	int button_se;			//ボタンサウンド
	int fire_se;			//弾発射サウンド
	int explosion_se;		//爆発サウンド
	int on_player_se;		//プレイヤーダメージサウンド
	int on_enemy_se;		//敵ダメージサウンド
	int fire_laser_se;		//レーザー発射サウンド
	int break_crystal_se;	//クリスタル破壊サウンド
	int charge_special_se;	//チャージサウンド
};
