#include "GameWindow.h"

bool draw = false;
int window = 1;
long long int score = 0;
char scoreText[1000005];

const char *title = "Final Project Team 62";

// ALLEGRO Variables
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_SAMPLE *song=NULL;
ALLEGRO_SAMPLE_INSTANCE *sample_instance;
ALLEGRO_FONT *score_font = NULL;

int Game_establish() {
  int msg = 0;

  game_init();
  game_begin();

  while ( msg != GAME_TERMINATE ) {
    msg = game_run();
    if ( msg == GAME_TERMINATE )
      printf( "Game Over\n" );
  }

  game_destroy();
  return 0;
}

void game_init() {
  printf( "Game Initializing...\n" );
  al_init();
  // init audio
  al_install_audio();
  al_init_acodec_addon();

  // Create display
  display = al_create_display(WIDTH, HEIGHT);

  // create event queue
  event_queue = al_create_event_queue();

  // Initialize Allegro settings
  al_set_window_position(display, 0, 0);
  al_set_window_title(display, title);
  al_init_primitives_addon();
  al_init_font_addon(); // initialize the font addon
  al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
  al_init_image_addon(); // initialize the image addon
  al_init_acodec_addon(); // initialize acodec addon
  al_install_keyboard(); // install keyboard event
  al_install_mouse();    // install mouse event
  al_install_audio();    // install audio event

  // Register event
  al_register_event_source(event_queue, al_get_display_event_source( display ));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_mouse_event_source());
  fps  = al_create_timer( 1.0 / FPS );
  al_register_event_source(event_queue, al_get_timer_event_source( fps )) ;

  // 換成貓貓 icon
  ALLEGRO_BITMAP *icon = al_load_bitmap("./image/icon.png");
  score_font = al_load_ttf_font("./font/Comfortaa-Bold.ttf", 40, 0);
  al_set_display_icon(display, icon);
}

void game_begin() {
  // Load sound
  song = al_load_sample("./sound/Aqua Cat Song.mp3");
  al_reserve_samples(20);
  sample_instance = al_create_sample_instance(song);
  // Loop the song until the display closes
  al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_LOOP);
  al_restore_default_mixer();
  al_attach_sample_instance_to_mixer(sample_instance, al_get_default_mixer());
  // set the volume of instance
  al_set_sample_instance_gain(sample_instance, 1) ;
  al_play_sample_instance(sample_instance);
  al_start_timer(fps);
  // initialize the menu before entering the loop
  menu_init();
}
void game_update(){
  if( judge_next_window ){
    if( window == 1 ){
      // not back menu anymore, therefore destroy it
      menu_destroy();
      // initialize next scene
      game_scene_init();
      judge_next_window = false;
      window = 2;
    }
  }
  if( window == 2 ){
    charater_update();
  }
}
int process_event(){
  ALLEGRO_EVENT event;

  // 計算 score
  score++;
  sprintf(scoreText, "%lld", score);

  al_wait_for_event(event_queue, &event);

  if( window == 1 ){
    menu_process(event);
  }else if( window == 2 ){
    background_process(event);
    charater_process(event);
    cone_process(event);
  }

  // 偵測有沒有撞到路障
  int cat_position = get_character_position();
  int cone_x = get_cone_x();
  int cone_y = get_cone_y();
  if(cone_x < 200 && cone_x + 128 > 50 && cone_y < cat_position + 151 && cone_y + 128 > cat_position) {
    return GAME_TERMINATE;
  }

  // Shutdown our program
  if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    return GAME_TERMINATE;
  else if(event.type == ALLEGRO_EVENT_TIMER)
    if(event.timer.source == fps)
      draw = true;

  game_update();
  return 0;
}

void game_draw() {
  if( window == 1 ){
    menu_draw();
  }else if( window == 2 ){
    game_scene_draw();

    // 分數
    al_draw_text(score_font, al_map_rgb(255, 255, 255), WIDTH / 2, 35, ALLEGRO_ALIGN_CENTRE, scoreText);
  }
  al_flip_display();
}

int game_run() {
  int error = 0;
  if( draw ){
    game_draw();
    draw = false;
  }
  if ( !al_is_event_queue_empty(event_queue) ) {
    error = process_event();
  }
  return error;
}

void game_destroy() {
  // Make sure you destroy all things
  al_destroy_event_queue(event_queue);
  al_destroy_display(display);
  game_scene_destroy();
}
