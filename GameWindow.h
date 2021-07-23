#include "global.h"
#include "charater.h"
#include "object.h"
#include "background.h"
#include "scene.h"
#include "about.h"
#include "gameover.h"

int Game_establish();
void game_init();
void game_begin();
void game_update();
int process_event();
void game_draw();
int game_run();
void game_destroy();
