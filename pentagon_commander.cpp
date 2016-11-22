#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#ifndef STRING
#include <string>
#define STRING
#endif // STRING

#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <Box2D/Box2D.h>
#include <pentagon_commander.hpp>

using namespace std;

int main()
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_SAMPLE *som=NULL;

    Level *thelevel;

    if(initAllegro(&display, &event_queue, &timer, &font, &som) == -1)
        return -1;

    thelevel = Level::loadLevel("test.txt");

    Cameraman thecameraman(thelevel);

    thecameraman.setNIndependentElements(0);
    thecameraman.setCameraPositionToPlayer();
    thecameraman.playLevel(display);

    Sleep(100);

    destroyAllegro(&display, &event_queue, &timer, &font, &som);
}

int initAllegro(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue, ALLEGRO_TIMER **timer, ALLEGRO_FONT **font, ALLEGRO_SAMPLE **som)
{
    if(!al_init()) {
      cout << "failed to initialize allegro!\n";
      return -1;
   }
   if(!al_install_keyboard()) {
      cout << "failed to initialize the keyboard!\n";
      return -1;
   }
   al_init_font_addon(); // initialize the font addon
   al_init_ttf_addon();// initialize the ttf (True Type Font) addon

   if(!al_init_image_addon()) {
      cout << "failed to initialize the al_init_image_addon!\n";
      return -1;
   }


   if(!al_install_audio()){
      comAudio = false;
      cout << "failed to initialize audio!\n";
      //return -1;
   }

   if(comAudio && !al_init_acodec_addon()){
      cout << "failed to initialize audio codecs!\n";
      return -1;
   }
    //Reserves a number of sample instances, and creates a default mixer if one doesn't exist. This allows us to decide how many audio samples we will be creating for now we are only creating one.
   if (comAudio && !al_reserve_samples(1)){
      cout << "failed to reserve samples!\n";
      return -1;
   }

   //carregamos o som
   /*if(comAudio)
   {
       *som = al_load_sample("ponto.wav");
       if (!*som) {
           cout << "Audio clip sample not loaded!\n";
           // -1;
       }
   }*/

   *font = al_load_ttf_font("DroidSans.ttf",10,0 );

   if (!*font){
      cout << "Could not load 'DroidSans.ttf'.\n";
      return -1;
   }

   //Criamos o timer
   *timer = al_create_timer(1.0 / FPS);
   if(!*timer) {
      cout << "failed to create timer!\n";
      return -1;
   }
   *display = al_create_display(SCREEN_W, SCREEN_H);
   if(!*display) {
      cout << "failed to create display!\n";
      return -1;
   }

    // Torna apto o uso de mouse na aplicação
    if (!al_install_mouse())
    {
        cout << "Falha ao inicializar o mouse.\n";
        return -1;
    }

    // Atribui o cursor padrão do sistema para ser usado
    if (!al_set_system_mouse_cursor(*display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
        cout << "Falha ao atribuir ponteiro do mouse.\n";
        return -1;
    }

    // Configura o título da janela
    al_set_window_title(*display, "Meu Jogo");

    ///


   *event_queue = al_create_event_queue();
   if(*event_queue==0) {
      cout << "failed to create event_queue!\n";
      al_destroy_display(*display);
      al_destroy_timer(*timer);
      return -1;
   }
   al_register_event_source(*event_queue, al_get_display_event_source(*display));
   al_register_event_source(*event_queue, al_get_timer_event_source(*timer));
   al_register_event_source(*event_queue, al_get_keyboard_event_source());
   al_register_event_source(*event_queue, al_get_mouse_event_source());

   //Voltamos a alterar o display e limpamos a tela
   al_set_target_bitmap(al_get_backbuffer(*display));
   al_clear_to_color(al_map_rgb(0,0,0));
   al_flip_display();
   ////

   al_start_timer(*timer);
   return 1;
}

void destroyAllegro(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue, ALLEGRO_TIMER **timer, ALLEGRO_FONT **font, ALLEGRO_SAMPLE **som)
{
    al_destroy_font(*font);
    al_destroy_timer(*timer);
    al_destroy_display(*display);
    al_destroy_event_queue(*event_queue);
    if(comAudio)
        al_destroy_sample(*som);
}
