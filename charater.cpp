#include "charater.h"

// the state of character
enum {STOP = 0, MOVE, JUMP};

typedef struct character
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    int state; // the state of character
    ALLEGRO_BITMAP *img_move[2];
    ALLEGRO_BITMAP *img_jump[2];
    ALLEGRO_SAMPLE_INSTANCE *jump_Sound;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
} Character;

Character cat;

ALLEGRO_SAMPLE *sample = NULL;

void character_init(){
    // load character images
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/cat_run%d.png", i );
        cat.img_move[i-1] = al_load_bitmap(temp);
    }
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/cat_run%d.png", i );
        cat.img_jump[i-1] = al_load_bitmap(temp);
    }
    // load effective sound
    sample = al_load_sample("./sound/jump.mp3");
    cat.jump_Sound  = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(cat.jump_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(cat.jump_Sound, al_get_default_mixer());

    // initial the geometric information of character
    cat.width = al_get_bitmap_width(cat.img_move[0]);
    cat.height = al_get_bitmap_height(cat.img_move[0]);
    cat.x = 50;
    cat.y = HEIGHT / 2;

    // initial the animation component
    cat.state = STOP;
    cat.anime = 0;
    cat.anime_time = 30;

}
void charater_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            cat.anime++;
            cat.anime %= cat.anime_time;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        cat.anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
}
void charater_update(){
    // use the idea of finite state machine to deal with different state
    if( key_state[ALLEGRO_KEY_W] ){
        if(cat.y >= 0) {
            cat.y -= 10;
            cat.state = MOVE;
        }
    }else if( key_state[ALLEGRO_KEY_S] ){
        if (cat.y <= HEIGHT - cat.height) {
            cat.y += 10;
            cat.state = MOVE;
        }
    }else if( key_state[ALLEGRO_KEY_SPACE] ){
        cat.state = JUMP;
      // cat is always runing, so turn STOP to MOVE
    }else if( cat.anime == cat.anime_time-1 ){
        cat.anime = 0;
        cat.state = MOVE;
    }else if ( cat.anime == 0 ){
        cat.state = MOVE;
    }
}
void character_draw(){
    // with the state, draw corresponding image
    if( cat.state == STOP ){
        al_draw_bitmap(cat.img_move[0], cat.x, cat.y, 0);
    }else if( cat.state == MOVE ){
        if (cat.anime < cat.anime_time / 2) {
            al_draw_bitmap(cat.img_move[0], cat.x, cat.y, 0);
        }
        else {
            al_draw_bitmap(cat.img_move[1], cat.x, cat.y, 0);
        }
    } else if ( cat.state == JUMP ){
        if (cat.anime < cat.anime_time / 2) {
            al_draw_bitmap(cat.img_jump[0], cat.x, cat.y, 0);
        }
        else {
            al_draw_bitmap(cat.img_jump[1], cat.x, cat.y, 0);
            al_play_sample_instance(cat.jump_Sound);
        }
    }
}
void character_destory(){
    al_destroy_bitmap(cat.img_jump[0]);
    al_destroy_bitmap(cat.img_jump[1]);
    al_destroy_bitmap(cat.img_move[0]);
    al_destroy_bitmap(cat.img_move[1]);
    al_destroy_sample_instance(cat.jump_Sound);
}
int get_character_position() {
  return cat.y;
}
