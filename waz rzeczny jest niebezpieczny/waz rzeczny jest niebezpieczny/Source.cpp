#include<iostream>
#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_image.h>
#include<fstream>
#include<string>
using namespace std;


// zrobic int level, zaczynajac od 0, zwieksza sie jak sie przejdzie dalej i w case'ach beda plansze
//predkosc zwieksza sie w czasie, dodatkowo po przejsciu wszystkich lvl zaczyna sie od nowa z wieksza predkoscia
//trzeba wymyslic funkcje pojawiania sie kolejnych cz³onow (easy), ale potem zmieniania polozenia przy skrecaniu


enum KEYS { DOWN, UP, LEFT, RIGHT };
int main(void)
{
	al_init();
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();

	int count = 0;
	int wynik = 0;
	int FPS = 4;

	bool keys[4] = { false, false, false, false };
	bool done = false;
	bool tytul = true;
	int pos_x = 640 / 2;
	int pos_y = 160;
	short poziom = 0;

	ALLEGRO_DISPLAY *okno = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	//ALLEGRO_FONT *czcionka = al_load_font("ALGER.ttf", 30, 0);
	//ALLEGRO_FONT *czcionka42 = al_load_font("ALGER.ttf", 42, 0);
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *stronatytulowa = al_load_bitmap("waz.png");

	if (!al_init())
	{
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);

	okno = al_create_display(640, 480);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(okno));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	ifstream plik;
	plik.open("poziom1.txt");
	short int poziom1[28][40];
	for (int i = 0; i < 28; i++)
	{
		for(int j = 0; j < 40; j++)
		{
			plik>> poziom1[i][j]; //zrobic od razu w jednej petli wszystkie poziomy
		}
	}

	if (!okno)
	{
		return -1;
	}

	al_start_timer(timer);

	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (tytul)
		{
			if (count == 0)
			{
				al_draw_bitmap(stronatytulowa, 0, 0, 0);
				al_flip_display();
			}
			if (count == 3)
			{
				tytul = false;
				poziom = 1;
			}
		}
		//poziomy w timerze
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				keys[DOWN] = false;
				keys[LEFT] = false;
				keys[RIGHT] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				keys[UP] = false;
				keys[LEFT] = false;
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				keys[UP] = false;
				keys[DOWN] = false;
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				keys[UP] = false;
				keys[LEFT] = false;
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[RIGHT] = false;
				keys[UP] = false;
				keys[LEFT] = false;
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			count++;
			pos_y -= keys[UP] * 16;
			pos_y += keys[DOWN] * 16;
			pos_x -= keys[LEFT] * 16;
			pos_x += keys[RIGHT] * 16;

			if (poziom == 1)
			{
				al_clear_to_color(al_map_rgb(255, 0, 0));
				for (int i = 0; i < 28; i++)
				{
					for (int j = 0; j < 40; j++)
					{
						if (poziom1[i][j] == 1)
							al_draw_filled_rectangle(j * 16, (i * 16)+32, (j*16)+16, (i*16)+48, al_map_rgb(0, 0, 0));
					}
				}
				al_draw_filled_rectangle(pos_x, pos_y, pos_x + 16, pos_y + 16, al_map_rgb(0, 255, 0));
				al_flip_display();

			}
		}

	}


	al_destroy_bitmap(stronatytulowa);
	al_destroy_event_queue(event_queue);
	al_destroy_display(okno);
	return 0;

}





