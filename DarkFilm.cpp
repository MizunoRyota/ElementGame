#include "stdafx.hpp"
#include "DarkFilm.hpp"
#include "UiManager.hpp"
#include "Enemy.hpp"

DarkFilm::DarkFilm(const std::shared_ptr<Enemy>& enemy)
    : enemy_(enemy)
{
    zOrder_ = 0; // HUDëw
    film_alpha = 0;
    film_isblackout = false;
}

void DarkFilm::Update()
{
    if (auto enemy_locked = enemy_.lock())
    {
        if (enemy_locked->GetEnemyState() == STATE_SPECIALATTACK || enemy_locked->GetEnemyState() == STATE_FLOAT || enemy_locked->GetEnemyState() == STATE_GROUNDATTACK)
        {
            if (film_isblackout == true)
            {
                film_isblackout = false;
                film_alpha = 0;
            }
             if (film_alpha >= 100.0f)
            {
                 //èàóùÇµÇ»Ç¢
            }
            else if (!film_isblackout)
            {
                film_alpha += ALPHA_CHANGESPEED;
            }
        }
        else
        {
            if (film_alpha >= 0)
            {
                film_alpha -= ALPHA_CHANGESPEED;
            }
        }
    }
}

void DarkFilm::Draw() const 
{
    //if (!film_isblackout)
    //{
    //        // âÊñ ÇçïêFÇ≈ìhÇËÇ¬Ç‘Ç∑
    //        SetDrawBlendMode(DX_BLENDMODE_ALPHA, film_alpha);
    //        DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Pallet::Black.GetHandle(), TRUE);
    //        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    //}
}