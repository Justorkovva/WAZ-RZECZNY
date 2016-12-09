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
//jakas bitmapa na zakonczenie gry dla przegrales i dla 5 poziomow ukonczonych
//zeby sie nie zatrzymywalo na prostej, chyba ze kosztem predkosci. jakas funkcja w czasie, ze rysuje co % iles, a potem % mniej

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
	short int FPS = 60;
	short int zycie = 3;
	long long int punkty = 0;

	bool keys[4] = { false, false, false, false };
	bool done = false;
	bool losowanie=true; //losuje elementy i wczytuje na nowo do tablicy, przydatne jak sie bedzie gralo na nowo
	bool tytul = true;
	bool graj = false;
	bool przegrales = true;
	int pos_x = 288;
	int pos_y = 96;
	int predkoscbazowa = 45;
	int predkosc=predkoscbazowa;
	short int p=0,p1=120,p2=130,p3=150,p4=100,p5=180,los,los2,i,j,najw,najm,im,jm,iw,jw; //120 130 150 100 180
	short poziom = 0;

	ALLEGRO_DISPLAY *okno = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_FONT *czcionka = al_load_font("ALGER.ttf", 30, 0);
	ALLEGRO_FONT *malaczcionka = al_load_font("ALGER.ttf", 22, 0);
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *stronatytulowa = al_load_bitmap("waz.png");
	ALLEGRO_BITMAP *serce1 = al_load_bitmap("serce1.png");
	ALLEGRO_BITMAP *serce2 = al_load_bitmap("serce2.png");
	ALLEGRO_BITMAP *serce3 = al_load_bitmap("serce3.png");
	ALLEGRO_BITMAP *serce4 = al_load_bitmap("serce4.png");
	ALLEGRO_BITMAP *serce5 = al_load_bitmap("serce5.png");

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
					if ((los !=4 && los2 != 20) && (los != 5 && los2 != 20) && (los != 6 && los2 != 20) && (los != 6 && los2 != 19) && (los != 7 && los2 != 19))
					{
						poziom1[los][los2] = 2;
						p++;
					}
				}
			}
			p = 0;
			while (p<p2) //poziom2 elementy
			{
				los = rand() % 28;
				los2 = rand() % 40;
				if (poziom2[los][los2] == 0)
				{
					if ((los != 26 && los2 != 20) && (los != 9 && los2 != 12) && (los != 18 && los2 != 12) && (los != 8 && los2 != 21) && (los != 19 && los2 != 21))
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
			
			if (poziom == 1)
			{

				al_clear_to_color(al_map_rgb(255, 0, 0));
				al_draw_text(malaczcionka, al_map_rgb(255, 255, 255), 320, 4, ALLEGRO_ALIGN_CENTRE, "Poziom  1");
				al_draw_textf(malaczcionka, al_map_rgb(255, 255, 255), 620, 4, ALLEGRO_ALIGN_RIGHT, "%i",punkty);
				al_draw_bitmap(serce1, 10, 0, 0);
				al_draw_textf(malaczcionka, al_map_rgb(255, 255, 255), 60, 4, ALLEGRO_ALIGN_LEFT, " -   %i", zycie);
				
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
						else if (poziom1[i][j]==0)
						{ }
						else
						{ 
							al_draw_filled_rectangle(j * 16, (i * 16) + 32, (j * 16) + 16, (i * 16) + 48, al_map_rgb(148, 233, 7));
						}
					}
				}
				if (!graj) // komunikat i zerowanie pozycji weza
				{
					al_draw_filled_rectangle(50, 200, 590, 280, al_map_rgb(255, 255, 255));
					al_draw_text(czcionka, al_map_rgb(0, 0, 0), 320, 220, ALLEGRO_ALIGN_CENTRE, "Wcisnij spacje, zeby rozpoczac");
					for (i = 0; i < 28; i++)
					{
						for (j = 0; j < 40; j++)
						{
							if (poziom1[i][j] != 1 && poziom1[i][j] != 0 && poziom1[i][j] != 2)
							{
								poziom1[i][j] = 0;
							}

						}
					}
					poziom1[4][20] = -5;
					poziom1[5][20] = -4;
					poziom1[6][20] = -3;
					poziom1[6][19] = -2;
					poziom1[7][19] = -1;
				}

				al_flip_display();

				if (p == p1)
				{
					poziom++;
					graj = false;
					keys[RIGHT] = false;
					keys[UP] = false;
					keys[LEFT] = false;
					keys[DOWN] = false;
					punkty += 2000;
					p = 0;
				}
				//skrecanie
				if (count%(FPS - predkosc) == 0)
				{
					najw = -10000;
					najm = 1;
					for (i = 0; i < 28; i++)
					{
						for (j = 0; j < 40; j++)
						{
							if (poziom1[i][j] < 0)
							{
								if (poziom1[i][j] > najw)
								{
									najw = poziom1[i][j];
									iw = i;
									jw = j;
								}
								if (poziom1[i][j] < najm)
								{
									najm = poziom1[i][j];
									im = i;
									jm = j;
								}
							}
						}
					}
					if (keys[RIGHT])
					{
						if (poziom1[im][jm+1] != 0 && poziom1[im][jm+1] != 2)
						{
							keys[RIGHT] = false;

							if ((poziom1[im-1][jm] != 0) && (poziom1[im+1][jm] != 2) && (poziom1[im - 1][jm] != 2) && (poziom1[im + 1][jm] != 0))
							{
								zycie -= 1;
								graj = false;

							}
							else if (poziom1[im+1][jm] != 0 && poziom1[im + 1][jm] != 2)
							{
								keys[UP] = true;

								if (poziom1[im - 1][jm] == 0)
								{
									poziom1[iw][jw]=0;
									poziom1[im - 1][jm] = najm - 1;
								}
								else if (poziom1[im - 1][jm] == 2)
								{
									poziom1[im - 1][jm] = najm - 1;
									p++;
									punkty += 50;
								}
							}
							else if (poziom1[im-1][jm] != 0 && poziom1[im - 1][jm] != 2)
							{
								keys[DOWN] = true;

								if (poziom1[im + 1][jm] == 0)
								{
									poziom1[iw][jw] = 0;
									poziom1[im + 1][jm] = najm - 1;
								}
								else if (poziom1[im + 1][jm] == 2)
								{
									poziom1[im + 1][jm] = najm - 1;
									punkty += 50;
									p++;
								}
							}
						}
						else
						{
							if (poziom1[im][jm+1] == 0)
							{
								poziom1[iw][jw] = 0;
								poziom1[im][jm+1] = najm - 1;
							}
							else if (poziom1[im][jm+1] == 2)
							{
								poziom1[im][jm+1] = najm - 1;
								punkty += 50;
								p++;
							}
						}
					}
					else if (keys[LEFT])
					{
						if (poziom1[im][jm-1] != 2 && poziom1[im][jm-1] != 0)
						{
							keys[LEFT] = false;

							if ((poziom1[im+1][jm] != 0) && (poziom1[im-1][jm] != 0) && (poziom1[im + 1][jm] != 2) && (poziom1[im - 1][jm] != 2))
							{
								zycie -= 1;
								graj = false;
							}
							else if (poziom1[im+1][jm] != 0 && poziom1[im+1][jm]!=2)
							{
								keys[UP] = true;

									if (poziom1[im - 1][jm] == 0)
									{
										poziom1[iw][jw] = 0;
										poziom1[im - 1][jm] = najm - 1;
									}
									else if (poziom1[im - 1][jm] == 2)
									{
										poziom1[im - 1][jm] = najm - 1;
										punkty += 50;
										p++;
									}
							}
							else if (poziom1[im - 1][jm] != 0 && poziom1[im - 1][jm] != 2)
							{
								keys[DOWN] = true;
								if (poziom1[im + 1][jm] == 0)
								{
									poziom1[iw][jw] = 0;
									poziom1[im + 1][jm] = najm - 1;
								}
								else if (poziom1[im + 1][jm] == 2)
								{
									poziom1[im + 1][jm] = najm - 1;
									punkty += 50;
									p++;
								}
							}
						}
						else
						{
							if (poziom1[im][jm - 1] == 0)
							{
								poziom1[iw][jw] = 0;
								poziom1[im][jm - 1] = najm - 1;
							}
							else if (poziom1[im][jm - 1] == 2)
							{
								poziom1[im][jm - 1] = najm - 1;
								punkty += 50;
								p++;
							}
						}
					}
					else if (keys[UP])
					{
						if ((poziom1[im-1][jm] != 2) && (poziom1[im-1][jm] != 0))
						{
							keys[UP] = false;

							if ((poziom1[im][jm-1] != 0) && (poziom1[im][jm+1] != 0) && (poziom1[im ][jm-1] != 2) && (poziom1[im][jm+1] != 2))
							{
								zycie -= 1;
								graj = false;
							}
							else if (poziom1[im][jm+1] != 0 && poziom1[im][jm+1] != 2)
							{
								keys[LEFT] = true;

								if (poziom1[im][jm-1] == 0)
								{
									poziom1[iw][jw] = 0;
									poziom1[im][jm-1] = najm - 1;
								}
								else if (poziom1[im][jm-1] == 2)
								{
									poziom1[im][jm-1] = najm - 1;
									punkty += 50;
									p++;
								}
							}
							else if (poziom1[im][jm-1] != 0 && poziom1[im][jm-1] != 2)
							{
								keys[RIGHT] = true;
								if (poziom1[im][jm+1] == 0)
								{
									poziom1[iw][jw] = 0;
									poziom1[im][jm+1] = najm - 1;
								}
								else if (poziom1[im][jm+1] == 2)
								{
									poziom1[im][jm+1] = najm - 1;
									punkty += 50;
									p++;
								}
							}
						}
						else
						{
							if (poziom1[im-1][jm] == 0)
							{
								poziom1[iw][jw] = 0;
								poziom1[im-1][jm] = najm - 1;
							}
							else if (poziom1[im-1][jm] == 2)
							{
								poziom1[im-1][jm] = najm - 1;
								punkty += 50;
								p++;
							}
						}
					}
					else if (keys[DOWN])
					{
						if (poziom1[im + 1][jm] != 2 && poziom1[im+1][jm] != 0)
						{
							keys[DOWN] = false;

							if ((poziom1[im][jm - 1] != 0) && (poziom1[im][jm + 1] != 0) && (poziom1[im][jm - 1] != 2) && (poziom1[im][jm + 1] != 2))
							{
								zycie -= 1;
								graj = false;
							}
							else if (poziom1[im][jm + 1] != 0 && poziom1[im][jm + 1] != 2)
							{
								keys[LEFT] = true;

								if (poziom1[im][jm - 1] == 0)
								{
									poziom1[iw][jw] = 0;
									poziom1[im][jm - 1] = najm - 1;
								}
								else if (poziom1[im][jm - 1] == 2)
								{
									poziom1[im][jm - 1] = najm - 1;
									punkty += 50;
									p++;
								}
							}
							else if (poziom1[im][jm - 1] != 0 && poziom1[im][jm - 1] != 2)
							{
								keys[RIGHT] = true;
								if (poziom1[im][jm + 1] == 0)
								{
									poziom1[iw][jw] = 0;
									poziom1[im][jm + 1] = najm - 1;
								}
								else if (poziom1[im][jm + 1] == 2)
								{
									poziom1[im][jm + 1] = najm - 1;
									punkty += 50;
									p++;
								}
							}
						}
						else
						{
							if (poziom1[im + 1][jm] == 0)
							{
								poziom1[iw][jw] = 0;
								poziom1[im + 1][jm] = najm - 1;
							}
							else if (poziom1[im + 1][jm] == 2)
							{
								poziom1[im + 1][jm] = najm - 1;
								punkty += 50;
								p++;
							}
						}
					}
					

				}

			}
			else if (poziom == 2)
			{
				if (poziom2[((pos_y) / 16) - 2][(pos_x) / 16] == 2)
				{
					poziom2[((pos_y) / 16) - 2][(pos_x) / 16] = 0;
					p++;
					punkty += 50;
					//waz rosnie
				}

				al_clear_to_color(al_map_rgb(255, 230, 128));
				al_draw_text(malaczcionka, al_map_rgb(255, 0, 128), 320, 4, ALLEGRO_ALIGN_CENTRE, "Poziom  2");
				al_draw_textf(malaczcionka, al_map_rgb(255, 0, 128), 620, 4, ALLEGRO_ALIGN_RIGHT, "%i", punkty);
				al_draw_bitmap(serce2, 10, 0, 0);
				al_draw_textf(malaczcionka, al_map_rgb(255, 0, 128), 60, 4, ALLEGRO_ALIGN_LEFT, " -   %i", zycie);
				for (i = 0; i < 28; i++)
				{
					for ( j = 0; j < 40; j++)
					{
						if (poziom2[i][j] == 1)
							al_draw_filled_rectangle(j * 16, (i * 16) + 32, (j * 16) + 16, (i * 16) + 48, al_map_rgb(0, 0, 0));
						else if (poziom2[i][j] == 2)
							al_draw_filled_circle((j * 16) + 8, (i * 16) + 40, 4, al_map_rgb(255, 0, 128));
					}
				}
				if (!graj)
				{
					al_draw_filled_rectangle(50, 200, 590, 280, al_map_rgb(255, 255, 255));
					al_draw_text(czcionka, al_map_rgb(0, 0, 0), 320, 220, ALLEGRO_ALIGN_CENTRE, "Wcisnij spacje, zeby rozpoczac");

				}
				al_draw_filled_rectangle(pos_x, pos_y, pos_x + 16, pos_y + 16, al_map_rgb(148, 233, 7));
				al_flip_display();
				if (p == p2)
				{
					poziom++;
					graj = false;
					keys[RIGHT] = false;
					keys[UP] = false;
					keys[LEFT] = false;
					keys[DOWN] = false;
					pos_x = 272;
					pos_y = 48;
					punkty += 2000;
					p = 0;
				}
				if (keys[RIGHT])
				{
					if (poziom2[((pos_y) / 16) - 2][((pos_x) / 16) + 1] == 1)
					{
						keys[RIGHT] = false;

						if ((poziom2[((pos_y) / 16) - 3][((pos_x) / 16)] == 1) && (poziom2[((pos_y) / 16) - 1][((pos_x) / 16)] == 1))
						{
							zycie -= 1;
							graj = false;
							pos_x = 16;
							pos_y = 112;

						}
						else if (poziom2[((pos_y) / 16) - 3][((pos_x) / 16)] == 1)
						{
							keys[DOWN] = true;
						}
						else if (poziom2[((pos_y) / 16) - 1][((pos_x) / 16)] == 1)
						{
							keys[UP] = true;
						}
					}
					pos_x += keys[RIGHT] * 16;
					pos_x -= keys[LEFT] * 16;
					pos_y -= keys[UP] * 16;
					pos_y += keys[DOWN] * 16;
				}
				else if (keys[LEFT])
				{
					if (poziom2[((pos_y) / 16) - 2][((pos_x) / 16) - 1] == 1)
					{
						keys[LEFT] = false;

						if ((poziom2[((pos_y) / 16) - 3][((pos_x) / 16)] == 1) && (poziom2[((pos_y) / 16) - 1][((pos_x) / 16)] == 1))
						{
							zycie -= 1;
							graj = false;
							pos_x = 16;
							pos_y = 112;
						}
						else if (poziom2[((pos_y) / 16) - 3][((pos_x) / 16)] == 1)
						{
							keys[DOWN] = true;
						}
						else if (poziom2[((pos_y) / 16) - 1][((pos_x) / 16)] == 1)
						{
							keys[UP] = true;
						}
					}
					pos_x += keys[RIGHT] * 16;
					pos_x -= keys[LEFT] * 16;
					pos_y -= keys[UP] * 16;
					pos_y += keys[DOWN] * 16;
				}
				else if (keys[UP])
				{
					if (poziom2[((pos_y) / 16) - 3][((pos_x) / 16)] == 1)
					{
						keys[UP] = false;

						if ((poziom2[((pos_y) / 16) - 2][((pos_x) / 16) + 1] == 1) && (poziom2[((pos_y) / 16) - 2][((pos_x) / 16) - 1] == 1))
						{
							zycie -= 1;
							graj = false;
							pos_x = 16;
							pos_y = 112;
						}
						else if (poziom2[((pos_y) / 16) - 2][((pos_x) / 16) + 1] == 1)
						{
							keys[LEFT] = true;
						}
						else if (poziom2[((pos_y) / 16) - 2][((pos_x) / 16) - 1] == 1)
						{
							keys[RIGHT] = true;
						}
					}
					pos_x += keys[RIGHT] * 16;
					pos_x -= keys[LEFT] * 16;
					pos_y -= keys[UP] * 16;
					pos_y += keys[DOWN] * 16;
				}
				else if (keys[DOWN])
				{
					if (poziom2[((pos_y) / 16) - 1][((pos_x) / 16)] == 1)
					{
						keys[DOWN] = false;

						if ((poziom2[((pos_y) / 16) - 2][((pos_x) / 16) + 1] == 1) && (poziom2[((pos_y) / 16) - 2][((pos_x) / 16) - 1] == 1))
						{
							zycie -= 1;
							graj = false;
							pos_x = 16;
							pos_y = 112;
						}
						else if (poziom2[((pos_y) / 16) - 2][((pos_x) / 16) + 1] == 1)
						{
							keys[LEFT] = true;
						}
						else if (poziom2[((pos_y) / 16) - 2][((pos_x) / 16) - 1] == 1)
						{
							keys[RIGHT] = true;
						}
					}
					pos_x += keys[RIGHT] * 16;
					pos_x -= keys[LEFT] * 16;
					pos_y -= keys[UP] * 16;
					pos_y += keys[DOWN] * 16;
				}
			}
			else if (poziom == 3)
			{
				if (poziom3[((pos_y) / 16) - 2][(pos_x) / 16] == 2)
				{
					poziom3[((pos_y) / 16) - 2][(pos_x) / 16] = 0;
					p++;
					punkty += 50;
					//waz rosnie
				}

				al_clear_to_color(al_map_rgb(70, 255, 255));
				al_draw_text(malaczcionka, al_map_rgb(14, 0, 255), 320, 4, ALLEGRO_ALIGN_CENTRE, "Poziom  3");
				al_draw_textf(malaczcionka, al_map_rgb(14, 0, 255), 620, 4, ALLEGRO_ALIGN_RIGHT, "%i", punkty);
				al_draw_bitmap(serce3, 10, 0, 0);
				al_draw_textf(malaczcionka, al_map_rgb(14, 0, 255), 60, 4, ALLEGRO_ALIGN_LEFT, " -   %i", zycie);
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
					al_draw_text(czcionka, al_map_rgb(0, 0, 0), 320, 220, ALLEGRO_ALIGN_CENTRE, "Wcisnij spacje, zeby rozpoczac");

				}
				al_draw_filled_rectangle(pos_x, pos_y, pos_x + 16, pos_y + 16, al_map_rgb(148, 233, 7));
				al_flip_display();
				if (p == p3)
				{
					poziom++;
					graj = false;
					keys[RIGHT] = false;
					keys[UP] = false;
					keys[LEFT] = false;
					keys[DOWN] = false;
					pos_x = 256;
					pos_y = 128;
					punkty += 2000;
					p = 0;
				}
				if (keys[RIGHT])
				{
					if (poziom3[((pos_y) / 16) - 2][((pos_x) / 16) + 1] == 1)
					{
						keys[RIGHT] = false;

						if ((poziom3[((pos_y) / 16) - 3][((pos_x) / 16)] == 1) && (poziom3[((pos_y) / 16) - 1][((pos_x) / 16)] == 1))
						{
							zycie -= 1;
							graj = false;
							pos_x = 256;
							pos_y = 128;

						}
						else if (poziom3[((pos_y) / 16) - 3][((pos_x) / 16)] == 1)
						{
							keys[DOWN] = true;
						}
						else if (poziom3[((pos_y) / 16) - 1][((pos_x) / 16)] == 1)
						{
							keys[UP] = true;
						}
					}
					pos_x += keys[RIGHT] * 16;
					pos_x -= keys[LEFT] * 16;
					pos_y -= keys[UP] * 16;
					pos_y += keys[DOWN] * 16;
				}
				else if (keys[LEFT])
				{
					if (poziom3[((pos_y) / 16) - 2][((pos_x) / 16) - 1] == 1)
					{
						keys[LEFT] = false;

						if ((poziom3[((pos_y) / 16) - 3][((pos_x) / 16)] == 1) && (poziom3[((pos_y) / 16) - 1][((pos_x) / 16)] == 1))
						{
							zycie -= 1;
							graj = false;
							pos_x = 256;
							pos_y = 128;
						}
						else if (poziom3[((pos_y) / 16) - 3][((pos_x) / 16)] == 1)
						{
							keys[DOWN] = true;
						}
						else if (poziom3[((pos_y) / 16) - 1][((pos_x) / 16)] == 1)
						{
							keys[UP] = true;
						}
					}
					pos_x += keys[RIGHT] * 16;
					pos_x -= keys[LEFT] * 16;
					pos_y -= keys[UP] * 16;
					pos_y += keys[DOWN] * 16;
				}
				else if (keys[UP])
				{
					if (poziom3[((pos_y) / 16) - 3][((pos_x) / 16)] == 1)
					{
						keys[UP] = false;

						if ((poziom3[((pos_y) / 16) - 2][((pos_x) / 16) + 1] == 1) && (poziom3[((pos_y) / 16) - 2][((pos_x) / 16) - 1] == 1))
						{
							zycie -= 1;
							graj = false;
							pos_x = 256;
							pos_y = 128;
						}
						else if (poziom3[((pos_y) / 16) - 2][((pos_x) / 16) + 1] == 1)
						{
							keys[LEFT] = true;
						}
						else if (poziom3[((pos_y) / 16) - 2][((pos_x) / 16) - 1] == 1)
						{
							keys[RIGHT] = true;
						}
					}
					pos_x += keys[RIGHT] * 16;
					pos_x -= keys[LEFT] * 16;
					pos_y -= keys[UP] * 16;
					pos_y += keys[DOWN] * 16;
				}
				else if (keys[DOWN])
				{
					if (poziom3[((pos_y) / 16) - 1][((pos_x) / 16)] == 1)
					{
						keys[DOWN] = false;

						if ((poziom3[((pos_y) / 16) - 2][((pos_x) / 16) + 1] == 1) && (poziom3[((pos_y) / 16) - 2][((pos_x) / 16) - 1] == 1))
						{
							zycie -= 1;
							graj = false;
							pos_x = 256;
							pos_y = 128;
						}
						else if (poziom3[((pos_y) / 16) - 2][((pos_x) / 16) + 1] == 1)
						{
							keys[LEFT] = true;
						}
						else if (poziom3[((pos_y) / 16) - 2][((pos_x) / 16) - 1] == 1)
						{
							keys[RIGHT] = true;
						}
					}
					pos_x += keys[RIGHT] * 16;
					pos_x -= keys[LEFT] * 16;
					pos_y -= keys[UP] * 16;
					pos_y += keys[DOWN] * 16;
				}

			}
			else if (poziom == 4)
			{
				if (poziom4[((pos_y) / 16) - 2][(pos_x) / 16] == 2)
				{
					poziom4[((pos_y) / 16) - 2][(pos_x) / 16] = 0;
					p++;
					punkty += 50;
					//waz rosnie
				}

				al_clear_to_color(al_map_rgb(180, 0, 255));
				al_draw_text(malaczcionka, al_map_rgb(255, 195, 2), 320, 4, ALLEGRO_ALIGN_CENTRE, "Poziom  4");
				al_draw_textf(malaczcionka, al_map_rgb(255, 195, 2), 620, 4, ALLEGRO_ALIGN_RIGHT, "%i", punkty);
				al_draw_bitmap(serce4, 10, 0, 0);
				al_draw_textf(malaczcionka, al_map_rgb(255, 195, 2), 60, 4, ALLEGRO_ALIGN_LEFT, " -   %i", zycie);
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
					al_draw_text(czcionka, al_map_rgb(0, 0, 0), 320, 220, ALLEGRO_ALIGN_CENTRE, "Wcisnij spacje, zeby rozpoczac");

				}
				al_draw_filled_rectangle(pos_x, pos_y, pos_x + 16, pos_y + 16, al_map_rgb(148, 233, 7));
				al_flip_display();
				if (p == p4)
				{
					poziom++;
					graj = false;
					keys[RIGHT] = false;
					keys[UP] = false;
					keys[LEFT] = false;
					keys[DOWN] = false;
					pos_x = 304;
					pos_y = 64;
					punkty += 2000;
					p = 0;
				}
				if (keys[RIGHT])
				{
					if (poziom4[((pos_y) / 16) - 2][((pos_x) / 16) + 1] == 1)
					{
						keys[RIGHT] = false;

						if ((poziom4[((pos_y) / 16) - 3][((pos_x) / 16)] == 1) && (poziom4[((pos_y) / 16) - 1][((pos_x) / 16)] == 1))
						{
							zycie -= 1;
							graj = false;
							pos_x = 304;
							pos_y = 64;

						}
						else if (poziom4[((pos_y) / 16) - 3][((pos_x) / 16)] == 1)
						{
							keys[DOWN] = true;
						}
						else if (poziom4[((pos_y) / 16) - 1][((pos_x) / 16)] == 1)
						{
							keys[UP] = true;
						}
					}
					pos_x += keys[RIGHT] * 16;
					pos_x -= keys[LEFT] * 16;
					pos_y -= keys[UP] * 16;
					pos_y += keys[DOWN] * 16;
				}
				else if (keys[LEFT])
				{
					if (poziom4[((pos_y) / 16) - 2][((pos_x) / 16) - 1] == 1)
					{
						keys[LEFT] = false;

						if ((poziom4[((pos_y) / 16) - 3][((pos_x) / 16)] == 1) && (poziom4[((pos_y) / 16) - 1][((pos_x) / 16)] == 1))
						{
							zycie -= 1;
							graj = false;
							pos_x = 304;
							pos_y = 64;
						}
						else if (poziom4[((pos_y) / 16) - 3][((pos_x) / 16)] == 1)
						{
							keys[DOWN] = true;
						}
						else if (poziom4[((pos_y) / 16) - 1][((pos_x) / 16)] == 1)
						{
							keys[UP] = true;
						}
					}
					pos_x += keys[RIGHT] * 16;
					pos_x -= keys[LEFT] * 16;
					pos_y -= keys[UP] * 16;
					pos_y += keys[DOWN] * 16;
				}
				else if (keys[UP])
				{
					if (poziom4[((pos_y) / 16) - 3][((pos_x) / 16)] == 1)
					{
						keys[UP] = false;

						if ((poziom4[((pos_y) / 16) - 2][((pos_x) / 16) + 1] == 1) && (poziom4[((pos_y) / 16) - 2][((pos_x) / 16) - 1] == 1))
						{
							zycie -= 1;
							graj = false;
							pos_x = 304;
							pos_y = 64;
						}
						else if (poziom4[((pos_y) / 16) - 2][((pos_x) / 16) + 1] == 1)
						{
							keys[LEFT] = true;
						}
						else if (poziom4[((pos_y) / 16) - 2][((pos_x) / 16) - 1] == 1)
						{
							keys[RIGHT] = true;
						}
					}
					pos_x += keys[RIGHT] * 16;
					pos_x -= keys[LEFT] * 16;
					pos_y -= keys[UP] * 16;
					pos_y += keys[DOWN] * 16;
				}
				else if (keys[DOWN])
				{
					if (poziom4[((pos_y) / 16) - 1][((pos_x) / 16)] == 1)
					{
						keys[DOWN] = false;

						if ((poziom4[((pos_y) / 16) - 2][((pos_x) / 16) + 1] == 1) && (poziom4[((pos_y) / 16) - 2][((pos_x) / 16) - 1] == 1))
						{
							zycie -= 1;
							graj = false;
							pos_x = 304;
							pos_y = 64;
						}
						else if (poziom4[((pos_y) / 16) - 2][((pos_x) / 16) + 1] == 1)
						{
							keys[LEFT] = true;
						}
						else if (poziom4[((pos_y) / 16) - 2][((pos_x) / 16) - 1] == 1)
						{
							keys[RIGHT] = true;
						}
					}
					pos_x += keys[RIGHT] * 16;
					pos_x -= keys[LEFT] * 16;
					pos_y -= keys[UP] * 16;
					pos_y += keys[DOWN] * 16;
				}
			}
			else if (poziom == 5)
			{
				if (poziom5[((pos_y) / 16) - 2][(pos_x) / 16] == 2)
				{
					poziom5[((pos_y) / 16) - 2][(pos_x) / 16] = 0;
					p++;
					punkty += 50;
					//waz rosnie
				}

				al_clear_to_color(al_map_rgb(248, 160, 17));
				al_draw_text(malaczcionka, al_map_rgb(255, 0, 50), 320, 4, ALLEGRO_ALIGN_CENTRE, "Poziom  5");
				al_draw_textf(malaczcionka, al_map_rgb(255, 0, 50), 620, 4, ALLEGRO_ALIGN_RIGHT, "%i", punkty);
				al_draw_bitmap(serce5, 10, 0, 0);
				al_draw_textf(malaczcionka, al_map_rgb(255, 0, 50), 60, 4, ALLEGRO_ALIGN_LEFT, " -   %i", zycie);
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
					al_draw_text(czcionka, al_map_rgb(0, 0, 0), 320, 220, ALLEGRO_ALIGN_CENTRE, "Wcisnij spacje, zeby rozpoczac");

				}
				al_draw_filled_rectangle(pos_x, pos_y, pos_x + 16, pos_y + 16, al_map_rgb(148, 233, 7));
				al_flip_display();

				if (p == p5)
				{
					//cos na zasadzie strony tytulowej, ale gratulacje przejscia gry zrobic, i dopiero wtedy poziom=1
					// i losowanie na nowo zrobic
					losowanie = true;
					poziom=1;
					graj = false;
					keys[RIGHT] = false;
					keys[UP] = false;
					keys[LEFT] = false;
					keys[DOWN] = false;
					pos_x = 288;
					pos_y = 96;
					punkty += 2000;
					p = 0;
				}
				if (keys[RIGHT])
				{
					if (poziom5[((pos_y) / 16) - 2][((pos_x) / 16) + 1] == 1)
					{
						keys[RIGHT] = false;

						if ((poziom5[((pos_y) / 16) - 3][((pos_x) / 16)] == 1) && (poziom5[((pos_y) / 16) - 1][((pos_x) / 16)] == 1))
						{
							zycie -= 1;
							graj = false;
							pos_x = 288;
							pos_y = 96;

						}
						else if (poziom5[((pos_y) / 16) - 3][((pos_x) / 16)] == 1)
						{
							keys[DOWN] = true;
						}
						else if (poziom5[((pos_y) / 16) - 1][((pos_x) / 16)] == 1)
						{
							keys[UP] = true;
						}
					}
					pos_x += keys[RIGHT] * 16;
					pos_x -= keys[LEFT] * 16;
					pos_y -= keys[UP] * 16;
					pos_y += keys[DOWN] * 16;
				}
				else if (keys[LEFT])
				{
					if (poziom5[((pos_y) / 16) - 2][((pos_x) / 16) - 1] == 1)
					{
						keys[LEFT] = false;

						if ((poziom5[((pos_y) / 16) - 3][((pos_x) / 16)] == 1) && (poziom5[((pos_y) / 16) - 1][((pos_x) / 16)] == 1))
						{
							zycie -= 1;
							graj = false;
							pos_x = 288;
							pos_y = 96;
						}
						else if (poziom5[((pos_y) / 16) - 3][((pos_x) / 16)] == 1)
						{
							keys[DOWN] = true;
						}
						else if (poziom5[((pos_y) / 16) - 1][((pos_x) / 16)] == 1)
						{
							keys[UP] = true;
						}
					}
					pos_x += keys[RIGHT] * 16;
					pos_x -= keys[LEFT] * 16;
					pos_y -= keys[UP] * 16;
					pos_y += keys[DOWN] * 16;
				}
				else if (keys[UP])
				{
					if (poziom5[((pos_y) / 16) - 3][((pos_x) / 16)] == 1)
					{
						keys[UP] = false;

						if ((poziom5[((pos_y) / 16) - 2][((pos_x) / 16) + 1] == 1) && (poziom5[((pos_y) / 16) - 2][((pos_x) / 16) - 1] == 1))
						{
							zycie -= 1;
							graj = false;
							pos_x = 288;
							pos_y = 96;
						}
						else if (poziom5[((pos_y) / 16) - 2][((pos_x) / 16) + 1] == 1)
						{
							keys[LEFT] = true;
						}
						else if (poziom5[((pos_y) / 16) - 2][((pos_x) / 16) - 1] == 1)
						{
							keys[RIGHT] = true;
						}
					}
					pos_x += keys[RIGHT] * 16;
					pos_x -= keys[LEFT] * 16;
					pos_y -= keys[UP] * 16;
					pos_y += keys[DOWN] * 16;
				}
				else if (keys[DOWN])
				{
					if (poziom5[((pos_y) / 16) - 1][((pos_x) / 16)] == 1)
					{
						keys[DOWN] = false;

						if ((poziom5[((pos_y) / 16) - 2][((pos_x) / 16) + 1] == 1) && (poziom5[((pos_y) / 16) - 2][((pos_x) / 16) - 1] == 1))
						{
							zycie -= 1;
							graj = false;
							pos_x = 288;
							pos_y = 96;
						}
						else if (poziom5[((pos_y) / 16) - 2][((pos_x) / 16) + 1] == 1)
						{
							keys[LEFT] = true;
						}
						else if (poziom5[((pos_y) / 16) - 2][((pos_x) / 16) - 1] == 1)
						{
							keys[RIGHT] = true;
						}
					}
					pos_x += keys[RIGHT] * 16;
					pos_x -= keys[LEFT] * 16;
					pos_y -= keys[UP] * 16;
					pos_y += keys[DOWN] * 16;
				}
			}

			if (zycie == 0)
			{
				przegrales = true;
			}
		}
	}


	al_destroy_bitmap(stronatytulowa);
	al_destroy_bitmap(serce1);

	al_destroy_bitmap(serce2);
	al_destroy_bitmap(serce3);
	al_destroy_bitmap(serce4);
	al_destroy_bitmap(serce5);
	al_destroy_event_queue(event_queue);
	al_destroy_display(okno);
	al_destroy_font(czcionka);
	al_destroy_font(malaczcionka);
	return 0;

}