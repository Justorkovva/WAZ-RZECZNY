#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_image.h>
#include<allegro5/allegro_font.h>
#include<allegro5\allegro_ttf.h>
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<ctime>
using namespace std;

//predkosc zwieksza sie w czasie, dodatkowo po przejsciu wszystkich lvl zaczyna sie od nowa z wieksza predkoscia
//trzeba wymyslic funkcje pojawiania sie kolejnych cz³onow (easy), ale potem zmieniania polozenia przy skrecaniu


enum KEYS { DOWN, UP, LEFT, RIGHT };
int main(void)
{
	al_init();
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	int count = 0;
	int wynik = 0;
	int FPS = 4;

	bool keys[4] = { false, false, false, false };
	bool done = false;
	bool losowanie=true; //losuje elementy i wczytuje na nowo do tablicy, przydatne jak sie bedzie gralo na nowo
	bool tytul = true;
	bool graj = false;
	int pos_x = 304;
	int pos_y = 96;
	short int p=0,p1=2,p2=130,p3=150,p4=100,p5=180,los,los2,i,j;
	short poziom = 0;

	ALLEGRO_DISPLAY *okno = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_FONT *czcionka = al_load_font("ALGER.ttf", 30, 0);
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
	ifstream plik2;
	ifstream plik3;
	ifstream plik4;
	ifstream plik5;
	plik.open("poziom1.txt");
	plik2.open("poziom2.txt");
	plik3.open("poziom3.txt");
	plik4.open("poziom4.txt");
	plik5.open("poziom5.txt");
	short int poziom1[28][40];
	short int poziom2[28][40];
	short int poziom3[28][40];
	short int poziom4[28][40];
	short int poziom5[28][40];
	
	srand(time(NULL));

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
		
		if(losowanie) //wrzuca z pliku do tablicy, losuje elementy i liczy ile ich jest
		{
			p = 0;
			for ( i = 0; i < 28; i++)
			{
				for ( j = 0; j < 40; j++)
				{
					plik >> poziom1[i][j];
					plik2 >> poziom2[i][j];
					plik3 >> poziom3[i][j];
					plik4 >> poziom4[i][j];
					plik5 >> poziom5[i][j];
				}
			}
			while (p<p1)
			{
				los = rand() % 28;
				los2 = rand() % 40;
				if (poziom1[los][los2] == 0)
				{
					poziom1[los][los2] = 2;
					p++;
				}
			}
			p = 0;
			while (p<p2) //poziom2 elementy
			{
				los = rand() % 28;
				los2 = rand() % 40;
				if (poziom2[los][los2] == 0)
				{
					if (los != 20 && los2 != 28)
					{
						poziom2[los][los2] = 2;
						p++;
					}
				}
			}
			p = 0;
			while (p<p3)
			{
				los = rand() % 28;
				los2 = rand() % 40;
				if (poziom3[los][los2] == 0)
				{
					if ((los!=25 && los2!=18) && (los != 25 && los2 != 21) && (los != 25 && los2 != 23) && (los != 26 && los2 != 17) && (los != 26 && los2 != 22) && (los != 25 && los2 != 16) && (los != 12 && los2 != 38) && (los != 15 && los2 != 38) && (los != 12 && los2 != 1) && (los != 15 && los2 != 1) && (los != 4 && los2 != 16) && (los != 4 && los2 != 23) && (los != 3 && los2 != 17) && (los != 3 && los2 != 22) && (los != 4 && los2 != 18) && (los != 4 && los2 != 21))
					{
						poziom3[los][los2] = 2;
						p++;
					}
				}
			}
			p = 0;
			while (p<p4)
			{
				los = rand() % 28;
				los2 = rand() % 40;
				if (poziom4[los][los2] == 0)
				{
					poziom4[los][los2] = 2;
					p++;
				}
			}
			p = 0;
			while (p<p5)
			{
				los = rand() % 28;
				los2 = rand() % 40;

				if (poziom5[los][los2] == 0)
				{
					if ((los != 6 && los2 != 3) && (los != 10 && los2 != 4) && (los != 17 && los2 != 4))
					{
						poziom5[los][los2] = 2;
						p++;
					}
				}
			}
			p = 0;
			losowanie = false;
		}

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				if (graj)
				{
					keys[UP] = true;
					keys[DOWN] = false;
					keys[LEFT] = false;
					keys[RIGHT] = false;
				}
				break;

			case ALLEGRO_KEY_DOWN:
				if (graj)
				{
					keys[DOWN] = true;
					keys[UP] = false;
					keys[LEFT] = false;
					keys[RIGHT] = false;
				}
				break;
			case ALLEGRO_KEY_LEFT:
				if (graj)
				{
					keys[LEFT] = true;
					keys[UP] = false;
					keys[DOWN] = false;
					keys[RIGHT] = false;
				}
				break;
			case ALLEGRO_KEY_RIGHT:
				if (graj)
				{
					keys[RIGHT] = true;
					keys[UP] = false;
					keys[LEFT] = false;
					keys[DOWN] = false;
				}
				break;
			case ALLEGRO_KEY_SPACE:
				if (!graj)
				{
					graj = true;
					keys[RIGHT] = true;
					p = 0;
				}
				break;
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_ENTER:
				poziom++;
				if(poziom==6)
				{
					poziom = 1;
				}
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
				//element zastapiony przez drogê
				if (poziom1[((pos_y) / 16) - 2][(pos_x) / 16] == 2)
				{
					poziom1[((pos_y) / 16) - 2][(pos_x) / 16] = 0;
					p++;
					//waz rosnie
				}

				al_clear_to_color(al_map_rgb(255, 0, 0));
				for ( i = 0; i < 28; i++)
				{
					for ( j = 0; j < 40; j++)
					{
						if (poziom1[i][j] == 1)
						al_draw_filled_rectangle(j * 16, (i * 16) + 32, (j * 16) + 16, (i * 16) + 48, al_map_rgb(0, 0, 0));
						else if (poziom1[i][j] == 2)
						{
							al_draw_filled_circle((j * 16) + 8, (i * 16) + 40, 4, al_map_rgb(255, 255, 255));
						}
					}
				}
				if(!graj)
				{
						al_draw_filled_rectangle(50, 200, 590, 280, al_map_rgb(255, 255, 255));
						al_draw_text(czcionka, al_map_rgb(0, 0, 0), 70, 220, 0, "Wcisnij spacje, zeby rozpoczac");
				}
				if(p==p1)
				{ 
					poziom++;
					graj = false;
					keys[RIGHT] = false;
					keys[UP] = false;
					keys[LEFT] = false;
					keys[DOWN] = false;
					
				}
				al_draw_filled_rectangle(pos_x, pos_y, pos_x + 16, pos_y + 16, al_map_rgb(148, 233, 7));
				al_flip_display();

			}
			else if (poziom == 2)
			{
				if (poziom2[((pos_y) / 16) - 2][(pos_x) / 16] == 2)
				{
					poziom2[((pos_y) / 16) - 2][(pos_x) / 16] = 0;
					//jakis licznik ++
					//waz rosnie
				}


				al_clear_to_color(al_map_rgb(255, 255, 0));
				for (i = 0; i < 28; i++)
				{
					for ( j = 0; j < 40; j++)
					{
						if (poziom2[i][j] == 1)
							al_draw_filled_rectangle(j * 16, (i * 16) + 32, (j * 16) + 16, (i * 16) + 48, al_map_rgb(0, 0, 0));
						else if (poziom2[i][j] == 2)
							al_draw_filled_circle((j * 16) + 8, (i * 16) + 40, 4, al_map_rgb(255, 0, 255));
					}
				}
				if (!graj)
				{
					al_draw_filled_rectangle(50, 200, 590, 280, al_map_rgb(255, 255, 255));
					al_draw_text(czcionka, al_map_rgb(0, 0, 0), 70, 220, 0, "Wcisnij spacje, zeby rozpoczac");

				}
				al_draw_filled_rectangle(pos_x, pos_y, pos_x + 16, pos_y + 16, al_map_rgb(148, 233, 7));
				al_flip_display();
			}
			else if (poziom == 3)
			{
				if (poziom3[((pos_y) / 16) - 2][(pos_x) / 16] == 2)
				{
					poziom3[((pos_y) / 16) - 2][(pos_x) / 16] = 0;
					//jakis licznik ++
					//waz rosnie
				}

				al_clear_to_color(al_map_rgb(0, 255, 255));
				for ( i = 0; i < 28; i++)
				{
					for (j = 0; j < 40; j++)
					{
						if (poziom3[i][j] == 1)
							al_draw_filled_rectangle(j * 16, (i * 16) + 32, (j * 16) + 16, (i * 16) + 48, al_map_rgb(0, 0, 0));
						else if (poziom3[i][j] == 2)
							al_draw_filled_circle((j * 16) + 8, (i * 16) + 40, 4, al_map_rgb(14, 0, 255));
					}
				}
				if (!graj)
				{
					al_draw_filled_rectangle(50, 200, 590, 280, al_map_rgb(255, 255, 255));
					al_draw_text(czcionka, al_map_rgb(0, 0, 0), 70, 220, 0, "Wcisnij spacje, zeby rozpoczac");

				}
				al_draw_filled_rectangle(pos_x, pos_y, pos_x + 16, pos_y + 16, al_map_rgb(148, 233, 7));
				al_flip_display();
			}
			else if (poziom == 4)
			{
				if (poziom4[((pos_y) / 16) - 2][(pos_x) / 16] == 2)
				{
					poziom4[((pos_y) / 16) - 2][(pos_x) / 16] = 0;
					//jakis licznik ++
					//waz rosnie
				}

				al_clear_to_color(al_map_rgb(180, 0, 255));
				for ( i = 0; i < 28; i++)
				{
					for ( j = 0; j < 40; j++)
					{
						if (poziom4[i][j] == 1)
							al_draw_filled_rectangle(j * 16, (i * 16) + 32, (j * 16) + 16, (i * 16) + 48, al_map_rgb(0, 0, 0));
						else if (poziom4[i][j] == 2)
							al_draw_filled_circle((j * 16) + 8, (i * 16) + 40, 4, al_map_rgb(255, 195, 2));
					}
				}
				if (!graj)
				{
					al_draw_filled_rectangle(50, 200, 590, 280, al_map_rgb(255, 255, 255));
					al_draw_text(czcionka, al_map_rgb(0, 0, 0), 70, 220, 0, "Wcisnij spacje, zeby rozpoczac");

				}
				al_draw_filled_rectangle(pos_x, pos_y, pos_x + 16, pos_y + 16, al_map_rgb(148, 233, 7));
				al_flip_display();
			}
			else if (poziom == 5)
			{
				if (poziom5[((pos_y) / 16) - 2][(pos_x) / 16] == 2)
				{
					poziom5[((pos_y) / 16) - 2][(pos_x) / 16] = 0;
					//jakis licznik ++
					//waz rosnie
				}

				al_clear_to_color(al_map_rgb(248, 160, 17));
				for ( i = 0; i < 28; i++)
				{
					for ( j = 0; j < 40; j++)
					{
						if (poziom5[i][j] == 1)
						{
							al_draw_filled_rectangle(j * 16, (i * 16) + 32, (j * 16) + 16, (i * 16) + 48, al_map_rgb(0, 0, 0));
						}
						else if (poziom5[i][j] == 2)
						{
							al_draw_filled_circle((j * 16) + 8, (i * 16) + 40, 4, al_map_rgb(255, 0, 50));
						}
					}
				}
				if (!graj)
				{
					al_draw_filled_rectangle(50, 200, 590, 280, al_map_rgb(255, 255, 255));
					al_draw_text(czcionka, al_map_rgb(0, 0, 0), 70, 220, 0, "Wcisnij spacje, zeby rozpoczac");

				}
				al_draw_filled_rectangle(pos_x, pos_y, pos_x + 16, pos_y + 16, al_map_rgb(148, 233, 7));
				al_flip_display();
			}
		}
	}


	al_destroy_bitmap(stronatytulowa);
	al_destroy_event_queue(event_queue);
	al_destroy_display(okno);
	al_destroy_font(czcionka);
	return 0;

}