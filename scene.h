#include "global.h"
#include "background.h"
#include "object.h"
#include "charater.h"
#include "gameover.h"

void menu_init();
void menu_process(ALLEGRO_EVENT event);
void menu_draw();
void menu_destroy();

void game_scene_init();
void game_scene_draw();
void game_scene_destroy();

void gameover_scene_init();
void gameover_scene_draw();
void gameover_scene_destroy();
