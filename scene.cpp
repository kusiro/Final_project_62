#include "scene.h"

ALLEGRO_FONT *font = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *menu_background = NULL;

ALLEGRO_BITMAP *menu_items[10];

float centerX = WIDTH / 2;
float centerY = HEIGHT / 2;
float hovered_Y[2] = {centerY - 105, centerY - 100 + 29};
int hovered = 0;

// function of menu
void menu_init(){
  font = al_load_ttf_font("./font/Comfortaa-Bold.ttf", 24, 0);
  background = al_load_bitmap("./image/cat_menu.png");
  menu_background = al_load_bitmap("./image/cat_menu.jpg");
}
void menu_process(ALLEGRO_EVENT event){
  if( event.type == ALLEGRO_EVENT_KEY_DOWN ) {
    if (event.keyboard.keycode == ALLEGRO_KEY_ENTER){
      if(hovered == 0) {
        window = 1;
        judge_next_window = true;
      } else if(hovered == 1) {
        window = 0;
      } else {
        msg = GAME_TERMINATE;
      }
    }
    else if (event.keyboard.keycode == ALLEGRO_KEY_W) {
      if(hovered > 0) {
        hovered--;
        hovered_Y[0] -= 50;
        hovered_Y[1] -= 50;
      }
    }
    else if (event.keyboard.keycode == ALLEGRO_KEY_S) {
      if(hovered < 2) {
        hovered++;
        hovered_Y[0] += 50;
        hovered_Y[1] += 50;
      }
    }
  }
}
void menu_draw(){
  al_draw_bitmap(menu_background, 0, 0, 0);
  al_draw_text(font, al_map_rgb(0, 0, 0), centerX, centerY - 100, ALLEGRO_ALIGN_CENTRE, "START");
  al_draw_text(font, al_map_rgb(0, 0, 0), centerX, centerY - 50, ALLEGRO_ALIGN_CENTRE, "ABOUT");
  al_draw_text(font, al_map_rgb(0, 0, 0), centerX, centerY, ALLEGRO_ALIGN_CENTRE, "EXIT");
  al_draw_rectangle(centerX - 50, hovered_Y[0], centerX + 50, hovered_Y[1], al_map_rgb(0, 0, 0), 2);
}

void menu_destroy(){
  al_destroy_font(font);
  al_destroy_bitmap(menu_background);
}

// function of game_scene
void game_scene_init(){
  character_init();
  background_init();
  cone_init();

  for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
    key_state[i] = false;
  }
}
void game_scene_draw(){
  background_draw();
  character_draw();
  cone_draw();
}
void game_scene_destroy(){
  background_destroy();
  character_destory();
}
