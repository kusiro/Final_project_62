#include "about.h"

ALLEGRO_FONT *about_font = NULL;
ALLEGRO_BITMAP *about_background = NULL;

// function of menu
void about_init()
{
  about_font = al_load_ttf_font("./font/Comfortaa-Bold.ttf", 24, 0);
  about_background = al_load_bitmap("./image/cat_menu.jpg");
}

void about_process(ALLEGRO_EVENT event)
{
  if (event.type == ALLEGRO_EVENT_KEY_DOWN)
  {
    if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
    {
      window = 1;
    }
  }
}

void about_draw()
{
  al_draw_bitmap(about_background, 0, 0, 0);
  al_draw_text(about_font, al_map_rgb(0, 0, 0), 200, 350, ALLEGRO_ALIGN_CENTRE, "Press ESC to go back");
  al_draw_text(about_font, al_map_rgb(0, 0, 0), 200, 100, ALLEGRO_ALIGN_CENTRE, "Members");
  al_draw_text(about_font, al_map_rgb(0, 0, 0), WIDTH / 2, HEIGHT / 2 - 100, ALLEGRO_ALIGN_CENTRE, "106034001 SOON, CHUN");
  al_draw_text(about_font, al_map_rgb(0, 0, 0), WIDTH / 2, HEIGHT / 2 - 50, ALLEGRO_ALIGN_CENTRE, "105072224 WU,CIH-EN");
}

void about_destroy()
{
  al_destroy_font(about_font);
  al_destroy_bitmap(about_background);
}
