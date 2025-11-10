#include "stdafx.hpp"
#include "DarkFilm.hpp"
#include "UiManager.hpp"
#include "Enemy.hpp"

DarkFilm::DarkFilm(const std::shared_ptr<Enemy>& enemy)
    : enemy_(enemy)
{
    order_z = 0; // HUDëw
    film_alpha = 0;
    film_is_blackout = false;
}

void DarkFilm::Update()
{
    if (auto enemy_locked = enemy_.lock())
    {
        if (enemy_locked->GetEnemyState() == STATE_SPECIALATTACK || enemy_locked->GetEnemyState() == STATE_FLOAT || enemy_locked->GetEnemyState() == STATE_SPECIAL_CHARGE)
        {
            if (film_is_blackout == true)
            {
                film_is_blackout = false;
                film_alpha = 0;
            }
             if (film_alpha >= 100.0f)
            {
                 //èàóùÇµÇ»Ç¢
            }
            else if (!film_is_blackout)
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
    //if (!film_is_blackout)
    //{
    //        // âÊñ ÇçïêFÇ≈ìhÇËÇ¬Ç‘Ç∑
    //        SetDrawBlendMode(DX_BLENDMODE_ALPHA, film_alpha);
    //        DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Pallet::Black.GetHandle(), TRUE);
    //        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    //}
}