#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_memfile.h>
#include <stdlib.h>


const int SCREEN_W =1000;
const int SCREEN_H =1000;

void modiifyBitMap(ALLEGRO_BITMAP *bmp)
{
    ALLEGRO_LOCKED_REGION *lr = al_lock_bitmap(bmp, ALLEGRO_PIXEL_FORMAT_RGB_888, ALLEGRO_LOCK_READWRITE);
    unsigned char*ptr = (unsigned char*) lr->data; //points to first pixel

    ptr-=SCREEN_W*(SCREEN_H-1)*3;
    double czas=al_get_time();
    printf("%lf\n",czas);
    julia(ptr,SCREEN_W,SCREEN_H,-1.5,-1.5,0.003,-0.4,0.6,4.0);
    czas=al_get_time();
    printf("%lf\n",czas);

    al_unlock_bitmap(bmp);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(bmp,0,0,0);

    al_flip_display();
}

int main(int argc, char **argv)
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_BITMAP *bmp = NULL;

    if (!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    if (!al_install_mouse())
    {
        fprintf(stderr, "failed to initialize the mouse!\n");
        return -1;
    }


    display = al_create_display(SCREEN_W, SCREEN_H);

    if (!display)
    {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    bmp = al_create_bitmap(SCREEN_W, SCREEN_H);

    if (!bmp)
    {
        fprintf(stderr, "failed to create  bitmap!");
        al_destroy_display(display);
        return -1;
    }

    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_draw_bitmap(bmp,0,0,0);

    al_flip_display();

    event_queue = al_create_event_queue();
    if (!event_queue)
    {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_display(display);
        return -1;
    }


    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_set_target_bitmap(al_get_backbuffer(display));

    while (1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            modiifyBitMap(bmp);
        }

    }

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(bmp);

    return 0;
}
