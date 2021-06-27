#include "scene.h"

ALLEGRO_FONT *font = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *menu_background = NULL;

// function of menu
void menu_init(){
  font = al_load_ttf_font("./font/Comfortaa-Medium.ttf", 48, 0);
}
void menu_process(ALLEGRO_EVENT event){
  if( event.type == ALLEGRO_EVENT_KEY_UP )
    if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
      judge_next_window = true;
}
void menu_draw(){
  menu_background = al_load_bitmap("./image/cat_menu.jpg");
  al_draw_bitmap(menu_background, 0, 0, 0);
  al_draw_text(font, al_map_rgb(0, 0, 0), WIDTH / 2, HEIGHT / 2 - 24 , ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
}
void menu_destroy(){
  al_destroy_font(font);
}

// function of game_scene
void game_scene_init(){
  character_init();
  background = al_load_bitmap("./image/stage.jpg");
}
void game_scene_draw(){
  al_draw_bitmap(background, 0, 0, 0);
  character_draw();
}
void game_scene_destroy(){
  al_destroy_bitmap(background);
  character_destory();
}
