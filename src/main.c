#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_memfile.h>
#include <stdlib.h>


const int SCREEN_W =2000;
const int SCREEN_H =2000;



void modiifyBitMap(ALLEGRO_BITMAP *bmp, double x0,double y0,double zoom, double real,double imaginary)
{
    ALLEGRO_LOCKED_REGION *lr = al_lock_bitmap(bmp, ALLEGRO_PIXEL_FORMAT_RGB_888, ALLEGRO_LOCK_READWRITE);
    unsigned char*ptr = (unsigned char*) lr->data; //points to first pixel

    ptr-=SCREEN_W*(SCREEN_H-1)*3; //it's get the last element

    julia(ptr,SCREEN_W,SCREEN_H,x0,y0,zoom,real,imaginary,4.0);

    al_unlock_bitmap(bmp);


    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(bmp,0,0,0);

    al_flip_display();
}

void changeIncrease(double *x0,double *y0,double *zoom,double clickX, double clickY,double howMuch)
{


    *x0+=clickX*(*zoom);
    *y0+=(SCREEN_H-clickY)*(*zoom);
    *zoom*=howMuch;

    *x0-=SCREEN_W*(*zoom)*0.5;
    *y0-=SCREEN_H*(*zoom)*0.5;

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

    if(!al_install_keyboard())
    {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return 1;
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
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_set_target_bitmap(al_get_backbuffer(display));

    double x0=-2.0;
    double y0=-2.0;
    double real=-0.4;
    double zoom=(-2.0)*x0/SCREEN_W;
    double imaginary=0.6;

    modiifyBitMap(bmp,x0,y0,zoom,real,imaginary);

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
            double clickX = ev.mouse.x;
            double clickY = ev.mouse.y;

            if(ev.mouse.button==1) //leftclick
            {
                changeIncrease(&x0,&y0,&zoom,clickX,clickY,0.5);
            }
            else if(ev.mouse.button==2)
            {
                changeIncrease(&x0,&y0,&zoom,clickX,clickY,2);
            }

            modiifyBitMap(bmp, x0, y0, zoom, real, imaginary);
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode ==ALLEGRO_KEY_R)
        {
            printf("Write real of complex\n");
            scanf("%lf",&real);
            x0=-2.0;
            y0=-2.0;
            zoom=(-2.0)*x0/SCREEN_W;
            modiifyBitMap(bmp,x0,y0,zoom,real,imaginary);
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode ==ALLEGRO_KEY_I)
        {
            printf("Write imaginary of complex\n");
            scanf("%lf",&imaginary);
            x0=-2.0;
            y0=-2.0;
            zoom=(-2.0)*x0/SCREEN_W;
            modiifyBitMap(bmp,x0,y0,zoom,real,imaginary);
        }

    }

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(bmp);

    return 0;
}
