#include "object.h"


typedef struct object
{
  int x, y;
  int width, height;
  ALLEGRO_BITMAP *img;
  int cnt;
  int cnt_time;
} Object;

Object cone;

int newPos = 1;
int cone_speed = 7;
int cone_count = 0;

void cone_init(){
  // load cone images
  cone.img = al_load_bitmap("./image/cone.png");
  cone.height = al_get_bitmap_height(cone.img);
  cone.width = al_get_bitmap_width(cone.img);

  cone.cnt = 0;
  cone.cnt_time = 800;
}

void cone_process(ALLEGRO_EVENT event){
  if( event.type == ALLEGRO_EVENT_TIMER ){
    if( event.timer.source == fps ){
      cone.cnt += cone_speed;
      cone.cnt %= cone.cnt_time + 130;
      if(cone.cnt >= cone.cnt_time + 120) {
        cone_count++;
      }
      if(cone_count > 3) {
        cone_count = 0;
        cone_speed++;
      }
    }
  }
}

//待完成: Cone move的細節
void cone_draw(){
  if(cone.cnt < cone.cnt_time + 100) {
    al_draw_bitmap(cone.img, 800 - cone.cnt, HEIGHT / 3 * newPos, 0);
  } else {
    newPos = rand() % 3;
  }
}
void cone_destory(){
  al_destroy_bitmap(cone.img);
}
int get_cone_x() {
  return 800 - cone.cnt;
}
int get_cone_y() {
  return HEIGHT / 3 * newPos;
}
