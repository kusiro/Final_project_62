#include "gameover.h"

ALLEGRO_FONT *gameover_font = NULL;
ALLEGRO_BITMAP *gameover_background = NULL;

// function of menu
void gameover_init()
{
  gameover_font = al_load_ttf_font("./font/Comfortaa-Bold.ttf", 24, 0);
  gameover_background = al_load_bitmap("./image/cat_menu.jpg");
}

void gameover_process(ALLEGRO_EVENT event)
{
  if (event.type == ALLEGRO_EVENT_KEY_DOWN)
  {
    if (event.keyboard.keycode == ALLEGRO_KEY_R)
    {
      judge_next_window = true;
    }
    if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
      msg = GAME_TERMINATE;
    }
  }
}

void gameover_draw()
{
  char temp[2000];
  sprintf(temp, "Your score is: %lld", score);
  al_draw_bitmap(gameover_background, 0, 0, 0);
  al_draw_text(gameover_font, al_map_rgb(0, 0, 0), WIDTH / 2, HEIGHT / 2 - 200, ALLEGRO_ALIGN_CENTRE, temp);
  al_draw_text(gameover_font, al_map_rgb(0, 0, 0), WIDTH / 2, HEIGHT / 2 - 100, ALLEGRO_ALIGN_CENTRE, "Press ESC to quit.");
  al_draw_text(gameover_font, al_map_rgb(0, 0, 0), WIDTH / 2, HEIGHT / 2 - 50, ALLEGRO_ALIGN_CENTRE, "Press R to retry.");
  al_draw_text(gameover_font, al_map_rgb(0, 0, 0), 60, 10, ALLEGRO_ALIGN_LEFT, "Past score");
  for(int i = 1; i < 11; i++){
    sprintf(temp, "%d: %lld", i, scoreList[i-1]);
    al_draw_text(gameover_font, al_map_rgb(0, 0, 0), 60, 10 + 30 * i, ALLEGRO_ALIGN_LEFT, temp);
  }
}

void gameover_destroy()
{
  al_destroy_font(gameover_font);
  al_destroy_bitmap(gameover_background);
}
