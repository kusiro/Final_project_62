#include "background.h"

typedef struct bgd {
  int x, y;
  int width, height;
  ALLEGRO_BITMAP *bg_move[2];
  int background;
  int background_time;

} Background;

// add speed and count, when count > 3, speed++
Background bg;
int speed = 7;
int count = 0;

void background_init(){
  speed = 7;
  count = 0;
  // load road images
  for(int i = 1 ; i <= 2 ; i++){
    char temp[50];
    sprintf( temp, "./image/road%d.png", i );
    bg.bg_move[i-1] = al_load_bitmap(temp);
  }

  // initial the geometric information of BG
  bg.width = al_get_bitmap_width(bg.bg_move[0]);
  bg.height = al_get_bitmap_height(bg.bg_move[0]);

  // initial the BG component
  bg.background = 0;
  bg.background_time = 800;

}

//移動的背景
void background_process(ALLEGRO_EVENT event){
  if (event.type == ALLEGRO_EVENT_TIMER) {
    if (event.timer.source == fps) {
      // use speed
      bg.background += speed;
      bg.background %= bg.background_time;
      if(bg.background >= bg.background_time - 6) {
        count++;
      }
      if(count > 1) {
        count = 0;
        speed++;
      }
    }
  }
}

void background_draw(){
  // loop the background
  if (bg.background < bg.background_time){
    al_draw_bitmap(bg.bg_move[0], 0 - bg.background, 0, 0);
    al_draw_bitmap(bg.bg_move[0], 800 - bg.background, 0, 0);
  }
}

void background_destroy(){
  al_destroy_bitmap(bg.bg_move[0]);
  al_destroy_bitmap(bg.bg_move[1]);
}
