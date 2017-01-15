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


// naprawic losowanie dla miejsc gdzie nie moze byc
//dodac baczki, moze jakies animacje, muzyczke
//dodatkowe punkty za czas

enum KEYS { DOWN, UP, LEFT, RIGHT };
enum GO {D, U, L, R};
int main(void)
{
		al_init();
		al_init_primitives_addon();
		al_install_keyboard();
		al_init_image_addon();
		al_init_font_addon();
		al_init_ttf_addon();
		ALLEGRO_DISPLAY *okno = NULL;
		ALLEGRO_EVENT_QUEUE *event_queue = NULL;
		ALLEGRO_FONT *czcionka = al_load_font("ALGER.ttf", 30, 0);
		ALLEGRO_FONT *malaczcionka = al_load_font("ALGER.ttf", 22, 0);
		ALLEGRO_TIMER *timer = NULL;
		ALLEGRO_BITMAP *stronatytulowa = al_load_bitmap("waz.jpg");
		ALLEGRO_BITMAP *serce1 = al_load_bitmap("serce1.png");
		ALLEGRO_BITMAP *serce2 = al_load_bitmap("serce2.png");
		ALLEGRO_BITMAP *serce3 = al_load_bitmap("serce3.png");
		ALLEGRO_BITMAP *serce4 = al_load_bitmap("serce4.png");
		ALLEGRO_BITMAP *serce5 = al_load_bitmap("serce5.png");
		ALLEGRO_BITMAP *wynikikoniec = al_load_bitmap("koniec.png");
		ALLEGRO_BITMAP *zegar1 = al_load_bitmap("zegar1.png");
		ALLEGRO_BITMAP *zegar2 = al_load_bitmap("zegar2.png");
		ALLEGRO_BITMAP *zegar3 = al_load_bitmap("zegar3.png");
		ALLEGRO_BITMAP *zegar4 = al_load_bitmap("zegar4.png");
		ALLEGRO_BITMAP *zegar5 = al_load_bitmap("zegar5.png");


	
	int count = 0;
	short int FPS = 60;
	short int zycie = 2;
	long long int punkty = 0;

	bool keys[4] = { false, false, false, false };
	bool go[4] = { false, false, false, false };
	bool done = false;
	bool koniec = false;
	bool losowanie=true; 
	bool tytul = true;
	bool graj = false;
	bool przegrales = true;
	bool sort = false;
	bool dane = true;
	bool czas = false;
	int sekundy = 0;
	int predkoscbazowa = 50;
	int predkosc=predkoscbazowa;
	short int p=0,p1=100,p2=110,p3=130,p4=100,p5=160,los,los2,i,j,najw,najm,im,jm,iw,jw; //120 130 150 100 180
	short poziom = 0;
	string imie="        ";
	int literka = 0;
	string player1, player2, player3, player4, player5, player6;
	int wynik1, wynik2, wynik3, wynik4, wynik5, wynik6;

	
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
	ifstream wyniki("scores.txt");
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
	
	wyniki >> player1;
	wyniki >> wynik1;
	wyniki >> player2;
	wyniki >> wynik2;
	wyniki >> player3;
	wyniki >> wynik3;
	wyniki >> player4;
	wyniki >> wynik4;
	wyniki >> player5;
	wyniki >> wynik5;
	wyniki >> player6;
	wyniki >> wynik6;

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
			if (dane)
			{
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_draw_text(malaczcionka, al_map_rgb(224, 58, 220), 246, 160, 0, "Podaj swoje imie");
					al_draw_textf(malaczcionka, al_map_rgb(224, 58, 220), 246, 200, 0, "%s", imie.c_str());
					al_flip_display();
				
			}
			if (count == 0 && !dane)
			{
				al_draw_bitmap(stronatytulowa, 0, 0, 0);
				al_flip_display();
			}
			if (count == 300 && !dane)
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
					if ((los != 26 && los2 != 20) && (los != 9 && los2 != 12) && (los != 18 && los2 != 12) && (los != 8 && los2 != 21) && (los != 19 && los2 != 21) && (los != 4 && los2 != 20) && (los != 4 && los2 != 19) && (los != 4 && los2 != 18) && (los != 4 && los2 != 17) && (los != 3 && los2 != 17))
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
					if ((los != 2 && los2 != 20) && (los != 3 && los2 != 20) && (los != 4 && los2 != 20) && (los != 4 && los2 != 19) && (los != 5 && los2 != 19) && (los!=25 && los2!=18) && (los != 25 && los2 != 21) && (los != 25 && los2 != 23) && (los != 26 && los2 != 17) && (los != 26 && los2 != 22) && (los != 25 && los2 != 16) && (los != 12 && los2 != 38) && (los != 15 && los2 != 38) && (los != 12 && los2 != 1) && (los != 15 && los2 != 1) && (los != 4 && los2 != 16) && (los != 4 && los2 != 23) && (los != 3 && los2 != 17) && (los != 3 && los2 != 22) && (los != 4 && los2 != 18) && (los != 4 && los2 != 21))
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
					if ((los != 4 && los2 != 20) && (los != 5 && los2 != 20) && (los != 6 && los2 != 20) && (los != 6 && los2 != 19) && (los != 6 && los2 != 18))
					{
						poziom4[los][los2] = 2;
						p++;
					}
				}
			}
			p = 0;
			while (p<p5)
			{
				los = rand() % 28;
				los2 = rand() % 40;

				if (poziom5[los][los2] == 0)
				{
					if ((los != 4 && los2 != 20) && (los != 4 && los2 != 19) && (los != 4 && los2 != 18) && (los != 4 && los2 != 17) && (los != 3 && los2 != 17) && (los != 6 && los2 != 3) && (los != 10 && los2 != 4) && (los != 17 && los2 != 4) && (los != 4 && los2 != 20) && (los != 4 && los2 != 19) && (los != 4 && los2 != 18) && (los != 4 && los2 != 17) && (los != 3 && los2 != 17))
					{
						poziom5[los][los2] = 2;
						p++;
					}
				}
			}
			p = 0;
			losowanie = false;
		}

		if (koniec)
		{
			//sortowanie
			if ((punkty > wynik6) && sort)
			{
				sort = false ;
				if (punkty > wynik1)
				{
					wynik6 = wynik5;
					wynik5 = wynik4;
					wynik4 = wynik3;
					wynik3 = wynik2;
					wynik2 = wynik1;
					wynik1 = punkty;
					player6 = player5;
					player5 = player4;
					player4 = player3;
					player3 = player2;
					player2 = player1;
					player1 = imie;
				}
				else if (punkty > wynik2)
				{
					wynik6 = wynik5;
					wynik5 = wynik4;
					wynik4 = wynik3;
					wynik3 = wynik2;
					wynik2 = punkty;
					player6 = player5;
					player5 = player4;
					player4 = player3;
					player3 = player2;
					player2 = imie;
				}
				else if (punkty > wynik3)
				{
					wynik6 = wynik5;
					wynik5 = wynik4;
					wynik4 = wynik3;
					wynik3 = punkty;
					player6 = player5;
					player5 = player4;
					player4 = player3;
					player3 = imie;
				}
				else if(punkty > wynik4)
				{ 
					wynik6 = wynik5;
					wynik5 = wynik4;
					wynik4 = punkty;
					player6 = player5;
					player5 = player4;
					player4 = imie;
				}
				else if (punkty > wynik5)
				{
					wynik6 = wynik5;
					wynik5 = punkty;
					player6 = player5;
					player5 = imie;
				}
				else if (punkty > wynik6)
				{
					wynik6 = punkty;
					player6 = imie;
				}
			
				wyniki.close();
				ofstream out("scores.txt");
				//zapisywanie
				out << player1 << " ";
				out << wynik1<<endl;
				out << player2 << " ";
				out << wynik2 << endl;
				out << player3 << " ";
				out << wynik3 << endl;
				out << player4 << " ";
				out << wynik4 << endl;
				out << player5 << " ";
				out << wynik5 << endl;
				out << player6 << " ";
				out << wynik6 << endl;
				
			}
			
			//wyswietlanie
			if (count % 60 == 0) //bo sie zawiesza, wywietlanie wynikow
			{
				al_draw_bitmap(wynikikoniec, 0, 0, 0);
				al_draw_textf(malaczcionka, al_map_rgb(224, 58, 220), 226, 160, 0, "%s", imie.c_str());
				al_draw_textf(malaczcionka, al_map_rgb(224, 58, 220), 360, 160, 0, "%i", punkty);
				al_draw_text(malaczcionka, al_map_rgb(224, 58, 220), 230, 200, 0, "1.");
				al_draw_textf(malaczcionka, al_map_rgb(224, 58, 220), 256, 200, 0, "%s", player1.c_str());
				al_draw_textf(malaczcionka, al_map_rgb(224, 58, 220), 395, 200, 0, "%i", wynik1);
				al_draw_text(malaczcionka, al_map_rgb(224, 58, 220), 230, 230, 0, "2.");
				al_draw_textf(malaczcionka, al_map_rgb(224, 58, 220), 256, 230, 0, "%s", player2.c_str());
				al_draw_textf(malaczcionka, al_map_rgb(224, 58, 220), 395, 230, 0, "%i", wynik2);
				al_draw_text(malaczcionka, al_map_rgb(224, 58, 220), 230, 260, 0, "3.");
				al_draw_textf(malaczcionka, al_map_rgb(224, 58, 220), 256, 260, 0, "%s", player3.c_str());
				al_draw_textf(malaczcionka, al_map_rgb(224, 58, 220), 395, 260, 0, "%i", wynik3);
				al_draw_text(malaczcionka, al_map_rgb(224, 58, 220), 230, 290, 0, "4.");
				al_draw_textf(malaczcionka, al_map_rgb(224, 58, 220), 256, 290, 0, "%s", player4.c_str());
				al_draw_textf(malaczcionka, al_map_rgb(224, 58, 220), 395, 290, 0, "%i", wynik4);
				al_draw_text(malaczcionka, al_map_rgb(224, 58, 220), 230, 320, 0, "5.");
				al_draw_textf(malaczcionka, al_map_rgb(224, 58, 220), 256, 320, 0, "%s", player5.c_str());
				al_draw_textf(malaczcionka, al_map_rgb(224, 58, 220), 395, 320, 0, "%i", wynik5);
				al_draw_text(malaczcionka, al_map_rgb(224, 58, 220), 230, 350, 0, "6.");
				al_draw_textf(malaczcionka, al_map_rgb(224, 58, 220), 256, 350, 0, "%s", player6.c_str());
				al_draw_textf(malaczcionka, al_map_rgb(224, 58, 220), 395, 350, 0, "%i", wynik6);


				al_flip_display();
			}
		
			
		}

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_CAPSLOCK:
				poziom++;
				break;
			case ALLEGRO_KEY_Q:
				if (dane && literka<8)
				{
					imie[literka] = 'Q';
					literka++;
				}
				break;
			case ALLEGRO_KEY_W:
				if (dane && literka<8)
				{
					imie[literka] = 'W';
					literka++;
				}
				break;
			case ALLEGRO_KEY_E:
				if (dane && literka<8)
				{
					imie[literka] = 'E';
					literka++;
				}
				break;
			case ALLEGRO_KEY_R:
				if (dane && literka<8)
				{
					imie[literka] = 'R';
					literka++;
				}
				break;
			case ALLEGRO_KEY_T:
				if (dane && literka<8)
				{
					imie[literka] = 'T';
					literka++;
				}
				break;
			case ALLEGRO_KEY_Y:
				if (dane && literka<8)
				{
					imie[literka] = 'Y';
					literka++;
				}
				break;
			case ALLEGRO_KEY_U:
				if (dane && literka<8)
				{
					imie[literka] = 'U';
					literka++;
				}
				break;
			case ALLEGRO_KEY_I:
				if (dane && literka<8)
				{
					imie[literka] = 'I';
					literka++;
				}
				break;
			case ALLEGRO_KEY_O:
				if (dane && literka<8)
				{
					imie[literka] = 'O';
					literka++;
				}
				break;
			case ALLEGRO_KEY_P:
				if (dane && literka<8)
				{
					imie[literka] = 'P';
					literka++;
				}
				break;
			case ALLEGRO_KEY_A:
				if (dane && literka<8)
				{
					imie[literka] = 'A';
					literka++;
				}
				break;
			case ALLEGRO_KEY_S:
				if (dane && literka<8)
				{
					imie[literka] = 'S';
					literka++;
				}
				break;
			case ALLEGRO_KEY_D:
				if (dane && literka<8)
				{
					imie[literka] = 'D';
					literka++;
				}
				break;
			case ALLEGRO_KEY_F:
				if (dane && literka<8)
				{
					imie[literka] = 'F';
					literka++;
				}
				break;
			case ALLEGRO_KEY_G:
				if (dane && literka<8)
				{
					imie[literka] = 'G';
					literka++;
				}
				break;
			case ALLEGRO_KEY_H:
				if (dane && literka<8)
				{
					imie[literka] = 'H';
					literka++;
				}
				break;
			case ALLEGRO_KEY_J:
				if (dane && literka<8)
				{
					imie[literka] = 'J';
					literka++;
				}
				break;
			case ALLEGRO_KEY_K:
				if (dane && literka<8)
				{
					imie[literka] = 'K';
					literka++;
				}
				break;
			case ALLEGRO_KEY_L:
				if (dane && literka<8)
				{
					imie[literka] = 'L';
					literka++;
				}
				break;
			case ALLEGRO_KEY_Z:
				if (dane && literka<8)
				{
					imie[literka] = 'Z';
					literka++;
				}
				break;
			case ALLEGRO_KEY_X:
				if (dane && literka<8)
				{
					imie[literka] = 'X';
					literka++;
				}
				break;
			case ALLEGRO_KEY_C:
				if (dane && literka<8)
				{
					imie[literka] = 'C';
					literka++;
				}
				break;
			case ALLEGRO_KEY_V:
				if (dane && literka<8)
				{
					imie[literka] = 'V';
					literka++;
				}
				break;
			case ALLEGRO_KEY_B:
				if (dane && literka<8)
				{
					imie[literka] = 'B';
					literka++;
				}
				break;
			case ALLEGRO_KEY_N:
				if (dane && literka<8)
				{
					imie[literka] = 'N';
					literka++;
				}
				break;
			case ALLEGRO_KEY_M:
				if (dane && literka<8)
				{
					imie[literka] = 'M';
					literka++;
				}
				break;

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
					czas = true;
					graj = true;
				go[R] = true;
				}
				break;
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_ENTER:
				if(dane)
				{
					dane = false;
					count = 0;
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
			if (czas && count%90==0)
			{
				sekundy++;
			}
			
			if (poziom == 1)
			{
				al_clear_to_color(al_map_rgb(255, 0, 0));
				al_draw_text(malaczcionka, al_map_rgb(255, 255, 255), 250, 4, ALLEGRO_ALIGN_CENTRE, "Poziom  1");
				al_draw_textf(malaczcionka, al_map_rgb(255, 255, 255), 620, 4, ALLEGRO_ALIGN_RIGHT, "%i",punkty);
				al_draw_bitmap(serce1, 10, 0, 0);
				al_draw_textf(malaczcionka, al_map_rgb(255, 255, 255), 60, 4, ALLEGRO_ALIGN_LEFT, " -   %i", zycie);
				al_draw_bitmap(zegar1, 400, 1, 0);
				al_draw_textf(malaczcionka, al_map_rgb(255, 255, 255), 480, 4, ALLEGRO_ALIGN_RIGHT, "%i", 120-sekundy);
				
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
					czas = false;
					keys[RIGHT] = false;
					keys[UP] = false;
					keys[LEFT] = false;
					keys[DOWN] = false;
					go[R] = false;
					go[L] = false;
					go[U] = false;
					go[D] = false;
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
					go[R] = false;
					go[L] = false;
					go[U] = false;
					go[D] = false;
					punkty += 2000;
					p = 0;
					predkosc = predkoscbazowa;
					punkty += (120 - sekundy) * 10;
					sekundy = 0;
				}
				
				//skrecanie
				if (count%(FPS - predkosc) == 0)
				{
					najw = -32000;
					najm = 1; //szukanie glowy i ogona
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
						if (poziom1[im][jm+1] == 0 || poziom1[im][jm+1] == 2)
						{
							go[R] = true;
							go[L] = false;
							go[D] = false;
							go[U] = false;
						}
					}
					else if (keys[LEFT])
					{
						if (poziom1[im][jm - 1] == 0 || poziom1[im][jm - 1] == 2)
						{
							go[L] = true;
							go[R] = false;
							go[D] = false;
							go[U] = false;
						}
					}
					else if (keys[UP])
					{
						if (poziom1[im-1][jm] == 0 || poziom1[im-1][jm] == 2)
						{
							go[U] = true;
							go[L] = false;
							go[D] = false;
							go[R] = false;
						}
					}
					else if (keys[DOWN])
					{
						if (poziom1[im+1][jm] == 0 || poziom1[im+1][jm] == 2)
						{
							go[D] = true;
							go[L] = false;
							go[R] = false;
							go[U] = false;
						}
					}
					if (go[R])
					{
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
							predkosc = predkoscbazowa;
						}
						else // juz wiadomo, ze nie ma przejscia
						{
							go[R] = false; // up,down, strata

							if ((poziom1[im - 1][jm] != 0) && (poziom1[im + 1][jm] != 2) && (poziom1[im - 1][jm] != 2) && (poziom1[im + 1][jm] != 0))
								{
									zycie -= 1;
									graj = false;
									predkosc = predkoscbazowa;
									keys[RIGHT] = false;
									keys[UP] = false;
									keys[LEFT] = false;
									keys[DOWN] = false;
									go[R] = false;
									go[L] = false;
									go[U] = false;
									go[D] = false;
								}
							else if (poziom1[im + 1][jm] != 0 && poziom1[im + 1][jm] != 2)
							{
								go[U] = true;
								if (poziom1[im - 1][jm] == 0)
								{
									poziom1[iw][jw] = 0;
									poziom1[im - 1][jm] = najm - 1;
								}
								else if (poziom1[im - 1][jm] == 2)
								{
									poziom1[im - 1][jm] = najm - 1;
									p++;
									punkty += 50;
									predkosc = predkoscbazowa;
								}
							}
							else if (poziom1[im - 1][jm] != 0 && poziom1[im - 1][jm] != 2)
							{
								go[D] = true;

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
									predkosc = predkoscbazowa;
								}
							}
						}
					}
					else if (go[L])
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
							predkosc = predkoscbazowa;
						}
						else // juz wiadomo, ze nie ma przejscia
						{
							go[L] = false; // up,down, strata

							if ((poziom1[im - 1][jm] != 0) && (poziom1[im + 1][jm] != 2) && (poziom1[im - 1][jm] != 2) && (poziom1[im + 1][jm] != 0))
							{
								zycie -= 1;
								graj = false;
								predkosc = predkoscbazowa;
								keys[RIGHT] = false;
								keys[UP] = false;
								keys[LEFT] = false;
								keys[DOWN] = false;
								go[R] = false;
								go[L] = false;
								go[U] = false;
								go[D] = false;
							}
							else if (poziom1[im + 1][jm] != 0 && poziom1[im + 1][jm] != 2)
							{
								go[U] = true;
								if (poziom1[im - 1][jm] == 0)
								{
									poziom1[iw][jw] = 0;
									poziom1[im - 1][jm] = najm - 1;
								}
								else if (poziom1[im - 1][jm] == 2)
								{
									poziom1[im - 1][jm] = najm - 1;
									p++;
									punkty += 50;
									predkosc = predkoscbazowa;
								}
							}
							else if (poziom1[im - 1][jm] != 0 && poziom1[im - 1][jm] != 2)
							{
								go[D] = true;

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
									predkosc = predkoscbazowa;
								}
							}
						}
					}
					else if (go[U])
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
							predkosc = predkoscbazowa;
						}
						else // juz wiadomo, ze nie ma przejscia
						{
							go[U] = false; // up,down, strata

							if ((poziom1[im][jm-1] != 0) && (poziom1[im][jm-1] != 2) && (poziom1[im][jm+1] != 2) && (poziom1[im][jm+1] != 0))
							{
								zycie -= 1;
								graj = false;
								predkosc = predkoscbazowa;
								keys[RIGHT] = false;
								keys[UP] = false;
								keys[LEFT] = false;
								keys[DOWN] = false;
								go[R] = false;
								go[L] = false;
								go[U] = false;
								go[D] = false;
							}
							else if (poziom1[im][jm-1] != 0 && poziom1[im][jm-1] != 2)
							{
								go[R] = true;
								if (poziom1[im][jm+1] == 0)
								{
									poziom1[iw][jw] = 0;
									poziom1[im][jm+1] = najm - 1;
								}
								else if (poziom1[im][jm+1] == 2)
								{
									poziom1[im][jm+1] = najm - 1;
									p++;
									punkty += 50;
									predkosc = predkoscbazowa;
								}
							}
							else if (poziom1[im][jm+1] != 0 && poziom1[im][jm+1] != 2)
							{
								go[L] = true;

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
									predkosc = predkoscbazowa;
								}
							}
						}
					}
					else if (go[D])
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
							predkosc = predkoscbazowa;
						}
						else // juz wiadomo, ze nie ma przejscia
						{
							go[D] = false; // up,down, strata

							if ((poziom1[im][jm - 1] != 0) && (poziom1[im][jm - 1] != 2) && (poziom1[im][jm + 1] != 2) && (poziom1[im][jm + 1] != 0))
							{
								zycie -= 1;
								graj = false;
								predkosc = predkoscbazowa;
								keys[RIGHT] = false;
								keys[UP] = false;
								keys[LEFT] = false;
								keys[DOWN] = false;
								go[R] = false;
								go[L] = false;
								go[U] = false;
								go[D] = false;
							}
							else if (poziom1[im][jm - 1] != 0 && poziom1[im][jm - 1] != 2)
							{
								go[R] = true;
								if (poziom1[im][jm + 1] == 0)
								{
									poziom1[iw][jw] = 0;
									poziom1[im][jm + 1] = najm - 1;
								}
								else if (poziom1[im][jm + 1] == 2)
								{
									poziom1[im][jm + 1] = najm - 1;
									p++;
									punkty += 50;
									predkosc = predkoscbazowa;
								}
							}
							else if (poziom1[im][jm + 1] != 0 && poziom1[im][jm + 1] != 2)
							{
								go[L] = true;

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
									predkosc = predkoscbazowa;
								}
							}
						}
					}


					
					
				}
				if ((count % 120 == 0) && graj)
				{
					if (predkosc < 59)
					{
						predkosc += 1;
					}
				}
			}
			else if (poziom == 2)
			{
				al_clear_to_color(al_map_rgb(255, 230, 128));
				al_draw_text(malaczcionka, al_map_rgb(255, 0, 128), 250, 4, ALLEGRO_ALIGN_CENTRE, "Poziom  2");
				al_draw_textf(malaczcionka, al_map_rgb(255, 0, 128), 620, 4, ALLEGRO_ALIGN_RIGHT, "%i", punkty);
				al_draw_bitmap(serce2, 10, 0, 0);
				al_draw_textf(malaczcionka, al_map_rgb(255, 0, 128), 60, 4, ALLEGRO_ALIGN_LEFT, " -   %i", zycie);
				al_draw_bitmap(zegar2, 400, 1, 0);
				al_draw_textf(malaczcionka, al_map_rgb(255, 0, 128), 480, 4, ALLEGRO_ALIGN_RIGHT, "%i", 120 - sekundy);

				for (i = 0; i < 28; i++)
				{
					for (j = 0; j < 40; j++)
					{
						if (poziom2[i][j] == 1)
							al_draw_filled_rectangle(j * 16, (i * 16) + 32, (j * 16) + 16, (i * 16) + 48, al_map_rgb(0, 0, 0));
						else if (poziom2[i][j] == 2)
							al_draw_filled_circle((j * 16) + 8, (i * 16) + 40, 4, al_map_rgb(255, 0, 128));
						else if (poziom2[i][j] == 0)
						{}
						else
						{
							al_draw_filled_rectangle(j * 16, (i * 16) + 32, (j * 16) + 16, (i * 16) + 48, al_map_rgb(80, 23, 255));
						}
					}
				}
				if (!graj)
				{
					czas = false;
					keys[RIGHT] = false;
					keys[UP] = false;
					keys[LEFT] = false;
					keys[DOWN] = false;
					go[R] = false;
					go[L] = false;
					go[U] = false;
					go[D] = false;
					al_draw_filled_rectangle(50, 200, 590, 280, al_map_rgb(255, 255, 255));
					al_draw_text(czcionka, al_map_rgb(0, 0, 0), 320, 220, ALLEGRO_ALIGN_CENTRE, "Wcisnij spacje, zeby rozpoczac");
					for (i = 0; i < 28; i++)
					{
						for (j = 0; j < 40; j++)
						{
							if (poziom2[i][j] != 1 && poziom2[i][j] != 0 && poziom2[i][j] != 2)
							{
								poziom2[i][j] = 0;
							}

						}
					}
					poziom2[4][20] = -5;
					poziom2[4][19] = -4;
					poziom2[4][18] = -3;
					poziom2[4][17] = -2;
					poziom2[3][17] = -1;
				}

				al_flip_display();
				if (p == p2)
				{
					poziom++;
					graj = false;
					keys[RIGHT] = false;
					keys[UP] = false;
					keys[LEFT] = false;
					keys[DOWN] = false;
					go[R] = false;
					go[L] = false;
					go[D] = false;
					go[U] = false;
					punkty += 2000;
					p = 0;
					predkosc = predkoscbazowa;
					punkty += (120 - sekundy) * 10;
					sekundy = 0;
				}
				
				//skrecanie
				if (count % (FPS - predkosc) == 0)
				{
					najw = -32000;
					najm = 1; //szukanie glowy i ogona
					for (i = 0; i < 28; i++)
					{
						for (j = 0; j < 40; j++)
						{
							if (poziom2[i][j] < 0)
							{
								if (poziom2[i][j] > najw)
								{
									najw = poziom2[i][j];
									iw = i;
									jw = j;
								}
								if (poziom2[i][j] < najm)
								{
									najm = poziom2[i][j];
									im = i;
									jm = j;
								}
							}
						}
					}

					if (keys[RIGHT])
					{
						if (poziom2[im][jm + 1] == 0 || poziom2[im][jm + 1] == 2)
						{
							go[R] = true;
							go[L] = false;
							go[D] = false;
							go[U] = false;
						}
					}
					else if (keys[LEFT])
					{
						if (poziom2[im][jm - 1] == 0 || poziom2[im][jm - 1] == 2)
						{
							go[L] = true;
							go[R] = false;
							go[D] = false;
							go[U] = false;
						}
					}
					else if (keys[UP])
					{
						if (poziom2[im - 1][jm] == 0 || poziom2[im - 1][jm] == 2)
						{
							go[U] = true;
							go[L] = false;
							go[D] = false;
							go[R] = false;
						}
					}
					else if (keys[DOWN])
					{
						if (poziom2[im + 1][jm] == 0 || poziom2[im + 1][jm] == 2)
						{
							go[D] = true;
							go[L] = false;
							go[R] = false;
							go[U] = false;
						}
					}
					
					if (go[R])
					{
						if (poziom2[im][jm + 1] == 0)
						{
							poziom2[iw][jw] = 0;
							poziom2[im][jm + 1] = najm - 1;
						}
						else if (poziom2[im][jm + 1] == 2)
						{
							poziom2[im][jm + 1] = najm - 1;
							punkty += 50;
							p++;
							predkosc = predkoscbazowa;
						}
						else // juz wiadomo, ze nie ma przejscia
						{
							go[R] = false; // up,down, strata

							if ((poziom2[im - 1][jm] != 0) && (poziom2[im + 1][jm] != 2) && (poziom2[im - 1][jm] != 2) && (poziom2[im + 1][jm] != 0))
							{
								zycie -= 1;
								graj = false;
								predkosc = predkoscbazowa;
								keys[RIGHT] = false;
								keys[UP] = false;
								keys[LEFT] = false;
								keys[DOWN] = false;
								go[R] = false;
								go[L] = false;
								go[U] = false;
								go[D] = false;
							}
							else if (poziom2[im + 1][jm] != 0 && poziom2[im + 1][jm] != 2)
							{
								go[U] = true;
								if (poziom2[im - 1][jm] == 0)
								{
									poziom2[iw][jw] = 0;
									poziom2[im - 1][jm] = najm - 1;
								}
								else if (poziom2[im - 1][jm] == 2)
								{
									poziom2[im - 1][jm] = najm - 1;
									p++;
									punkty += 50;
									predkosc = predkoscbazowa;
								}
							}
							else if (poziom2[im - 1][jm] != 0 && poziom2[im - 1][jm] != 2)
							{
								go[D] = true;

								if (poziom2[im + 1][jm] == 0)
								{
									poziom2[iw][jw] = 0;
									poziom2[im + 1][jm] = najm - 1;
								}
								else if (poziom2[im + 1][jm] == 2)
								{
									poziom2[im + 1][jm] = najm - 1;
									punkty += 50;
									p++;
									predkosc = predkoscbazowa;
								}
							}
						}
					}
					else if (go[L])
					{
						if (poziom2[im][jm - 1] == 0)
						{
							poziom2[iw][jw] = 0;
							poziom2[im][jm - 1] = najm - 1;
						}
						else if (poziom2[im][jm - 1] == 2)
						{
							poziom2[im][jm - 1] = najm - 1;
							punkty += 50;
							p++;
							predkosc = predkoscbazowa;
						}
						else // juz wiadomo, ze nie ma przejscia
						{
							go[L] = false; // up,down, strata

							if ((poziom2[im - 1][jm] != 0) && (poziom2[im + 1][jm] != 2) && (poziom2[im - 1][jm] != 2) && (poziom2[im + 1][jm] != 0))
							{
								zycie -= 1;
								graj = false;
								predkosc = predkoscbazowa;
								keys[RIGHT] = false;
								keys[UP] = false;
								keys[LEFT] = false;
								keys[DOWN] = false;
								go[R] = false;
								go[L] = false;
								go[U] = false;
								go[D] = false;
							}
							else if (poziom2[im + 1][jm] != 0 && poziom2[im + 1][jm] != 2)
							{
								go[U] = true;
								if (poziom2[im - 1][jm] == 0)
								{
									poziom2[iw][jw] = 0;
									poziom2[im - 1][jm] = najm - 1;
								}
								else if (poziom2[im - 1][jm] == 2)
								{
									poziom2[im - 1][jm] = najm - 1;
									p++;
									punkty += 50;
									predkosc = predkoscbazowa;
								}
							}
							else if (poziom2[im - 1][jm] != 0 && poziom2[im - 1][jm] != 2)
							{
								go[D] = true;

								if (poziom2[im + 1][jm] == 0)
								{
									poziom2[iw][jw] = 0;
									poziom2[im + 1][jm] = najm - 1;
								}
								else if (poziom2[im + 1][jm] == 2)
								{
									poziom2[im + 1][jm] = najm - 1;
									punkty += 50;
									p++;
									predkosc = predkoscbazowa;
								}
							}
						}
					}
					else if (go[U])
					{
						if (poziom2[im - 1][jm] == 0)
						{
							poziom2[iw][jw] = 0;
							poziom2[im - 1][jm] = najm - 1;
						}
						else if (poziom2[im - 1][jm] == 2)
						{
							poziom2[im - 1][jm] = najm - 1;
							punkty += 50;
							p++;
							predkosc = predkoscbazowa;
						}
						else // juz wiadomo, ze nie ma przejscia
						{
							go[U] = false; // up,down, strata

							if ((poziom2[im][jm - 1] != 0) && (poziom2[im][jm - 1] != 2) && (poziom2[im][jm + 1] != 2) && (poziom2[im][jm + 1] != 0))
							{
								zycie -= 1;
								graj = false;
								predkosc = predkoscbazowa;
								keys[RIGHT] = false;
								keys[UP] = false;
								keys[LEFT] = false;
								keys[DOWN] = false;
								go[R] = false;
								go[L] = false;
								go[U] = false;
								go[D] = false;
							}
							else if (poziom2[im][jm - 1] != 0 && poziom2[im][jm - 1] != 2)
							{
								go[R] = true;
								if (poziom2[im][jm + 1] == 0)
								{
									poziom2[iw][jw] = 0;
									poziom2[im][jm + 1] = najm - 1;
								}
								else if (poziom2[im][jm + 1] == 2)
								{
									poziom2[im][jm + 1] = najm - 1;
									p++;
									punkty += 50;
									predkosc = predkoscbazowa;
								}
							}
							else if (poziom2[im][jm + 1] != 0 && poziom2[im][jm + 1] != 2)
							{
								go[L] = true;

								if (poziom2[im][jm - 1] == 0)
								{
									poziom2[iw][jw] = 0;
									poziom2[im][jm - 1] = najm - 1;
								}
								else if (poziom2[im][jm - 1] == 2)
								{
									poziom2[im][jm - 1] = najm - 1;
									punkty += 50;
									p++;
									predkosc = predkoscbazowa;
								}
							}
						}
					}
					else if (go[D])
					{
						if (poziom2[im + 1][jm] == 0)
						{
							poziom2[iw][jw] = 0;
							poziom2[im + 1][jm] = najm - 1;
						}
						else if (poziom2[im + 1][jm] == 2)
						{
							poziom2[im + 1][jm] = najm - 1;
							punkty += 50;
							p++;
							predkosc = predkoscbazowa;
						}
						else // juz wiadomo, ze nie ma przejscia
						{
							go[D] = false; // up,down, strata

							if ((poziom2[im][jm - 1] != 0) && (poziom2[im][jm - 1] != 2) && (poziom2[im][jm + 1] != 2) && (poziom2[im][jm + 1] != 0))
							{
								zycie -= 1;
								graj = false;
								predkosc = predkoscbazowa;
								keys[RIGHT] = false;
								keys[UP] = false;
								keys[LEFT] = false;
								keys[DOWN] = false;
								go[R] = false;
								go[L] = false;
								go[U] = false;
								go[D] = false;
							}
							else if (poziom2[im][jm - 1] != 0 && poziom2[im][jm - 1] != 2)
							{
								go[R] = true;
								if (poziom2[im][jm + 1] == 0)
								{
									poziom2[iw][jw] = 0;
									poziom2[im][jm + 1] = najm - 1;
								}
								else if (poziom2[im][jm + 1] == 2)
								{
									poziom2[im][jm + 1] = najm - 1;
									p++;
									punkty += 50;
									predkosc = predkoscbazowa;
								}
							}
							else if (poziom2[im][jm + 1] != 0 && poziom2[im][jm + 1] != 2)
							{
								go[L] = true;

								if (poziom2[im][jm - 1] == 0)
								{
									poziom2[iw][jw] = 0;
									poziom2[im][jm - 1] = najm - 1;
								}
								else if (poziom2[im][jm - 1] == 2)
								{
									poziom2[im][jm - 1] = najm - 1;
									punkty += 50;
									p++;
									predkosc = predkoscbazowa;
								}
							}
						}
					}
					
				}
				if ((count % 120 == 0) && graj)
				{
					if (predkosc < 59)
					{
						predkosc += 1;
					}
				}
			}
			else if (poziom == 3)
			{
				al_clear_to_color(al_map_rgb(70, 255, 255));
				al_draw_text(malaczcionka, al_map_rgb(14, 0, 255), 250, 4, ALLEGRO_ALIGN_CENTRE, "Poziom  3");
				al_draw_textf(malaczcionka, al_map_rgb(14, 0, 255), 620, 4, ALLEGRO_ALIGN_RIGHT, "%i", punkty);
				al_draw_bitmap(serce3, 10, 0, 0);
				al_draw_textf(malaczcionka, al_map_rgb(14, 0, 255), 60, 4, ALLEGRO_ALIGN_LEFT, " -   %i", zycie);
				al_draw_bitmap(zegar3, 400, 1, 0);
				al_draw_textf(malaczcionka, al_map_rgb(14, 0, 255), 480, 4, ALLEGRO_ALIGN_RIGHT, "%i", 120 - sekundy);
				for ( i = 0; i < 28; i++)
				{
					for (j = 0; j < 40; j++)
					{
						if (poziom3[i][j] == 1)
							al_draw_filled_rectangle(j * 16, (i * 16) + 32, (j * 16) + 16, (i * 16) + 48, al_map_rgb(0, 0, 0));
						else if (poziom3[i][j] == 2)
							al_draw_filled_circle((j * 16) + 8, (i * 16) + 40, 4, al_map_rgb(14, 0, 255));
						else if(poziom3[i][j]==0)
						{}
						else
						{
						al_draw_filled_rectangle(j * 16, (i * 16) + 32, (j * 16) + 16, (i * 16) + 48, al_map_rgb(200, 23, 0));
						}

					}

				}
				if (!graj)
				{
					czas = false;
					keys[RIGHT] = false;
					keys[UP] = false;
					keys[LEFT] = false;
					keys[DOWN] = false;
					go[R] = false;
					go[L] = false;
					go[U] = false;
					go[D] = false;
					al_draw_filled_rectangle(50, 200, 590, 280, al_map_rgb(255, 255, 255));
					al_draw_text(czcionka, al_map_rgb(0, 0, 0), 320, 220, ALLEGRO_ALIGN_CENTRE, "Wcisnij spacje, zeby rozpoczac");
				
				for (i = 0; i < 28; i++)
				{
					for (j = 0; j < 40; j++)
					{
						if (poziom3[i][j] != 1 && poziom3[i][j] != 0 && poziom3[i][j] != 2)
						{
							poziom3[i][j] = 0;
						}

					}
				}
				poziom3[2][20] = -5;
				poziom3[3][20] = -4;
				poziom3[4][20] = -3;
				poziom3[4][19] = -2;
				poziom3[5][19] = -1;
				}
			
				al_flip_display();

				if (p == p3)
				{
					poziom++;
					graj = false;
					keys[RIGHT] = false;
					keys[UP] = false;
					keys[LEFT] = false;
					keys[DOWN] = false;
					go[R] = false;
					go[L] = false;
					go[U] = false;
					go[D] = false;
					punkty += 2000;
					p = 0;
					predkosc = predkoscbazowa;
					punkty += (120 - sekundy) * 10;
					sekundy = 0;
				}
				
				//skrecanie
				if (count % (FPS - predkosc) == 0)
				{
					najw = -32000;
					najm = 1; //szukanie glowy i ogona
					for (i = 0; i < 28; i++)
					{
						for (j = 0; j < 40; j++)
						{
							if (poziom3[i][j] < 0)
							{
								if (poziom3[i][j] > najw)
								{
									najw = poziom3[i][j];
									iw = i;
									jw = j;
								}
								if (poziom3[i][j] < najm)
								{
									najm = poziom3[i][j];
									im = i;
									jm = j;
								}
							}
						}
					}

					if (keys[RIGHT])
					{
						if (poziom3[im][jm + 1] == 0 || poziom3[im][jm + 1] == 2)
						{
							go[R] = true;
							go[L] = false;
							go[D] = false;
							go[U] = false;
						}
					}
					else if (keys[LEFT])
					{
						if (poziom3[im][jm - 1] == 0 || poziom3[im][jm - 1] == 2)
						{
							go[L] = true;
							go[R] = false;
							go[D] = false;
							go[U] = false;
						}
					}
					else if (keys[UP])
					{
						if (poziom3[im - 1][jm] == 0 || poziom3[im - 1][jm] == 2)
						{
							go[U] = true;
							go[L] = false;
							go[D] = false;
							go[R] = false;
						}
					}
					else if (keys[DOWN])
					{
						if (poziom3[im + 1][jm] == 0 || poziom3[im + 1][jm] == 2)
						{
							go[D] = true;
							go[L] = false;
							go[R] = false;
							go[U] = false;
						}
					}
					if (go[R])
					{
						if (poziom3[im][jm + 1] == 0)
						{
							poziom3[iw][jw] = 0;
							poziom3[im][jm + 1] = najm - 1;
						}
						else if (poziom3[im][jm + 1] == 2)
						{
							poziom3[im][jm + 1] = najm - 1;
							punkty += 50;
							p++;
							predkosc = predkoscbazowa;
						}
						else // juz wiadomo, ze nie ma przejscia
						{
							go[R] = false; // up,down, strata

							if ((poziom3[im - 1][jm] != 0) && (poziom3[im + 1][jm] != 2) && (poziom3[im - 1][jm] != 2) && (poziom3[im + 1][jm] != 0))
							{
								zycie -= 1;
								graj = false;
								predkosc = predkoscbazowa;
								keys[RIGHT] = false;
								keys[UP] = false;
								keys[LEFT] = false;
								keys[DOWN] = false;
								go[R] = false;
								go[L] = false;
								go[U] = false;
								go[D] = false;
							}
							else if (poziom3[im + 1][jm] != 0 && poziom3[im + 1][jm] != 2)
							{
								go[U] = true;
								if (poziom3[im - 1][jm] == 0)
								{
									poziom3[iw][jw] = 0;
									poziom3[im - 1][jm] = najm - 1;
								}
								else if (poziom3[im - 1][jm] == 2)
								{
									poziom3[im - 1][jm] = najm - 1;
									p++;
									punkty += 50;
									predkosc = predkoscbazowa;
								}
							}
							else if (poziom3[im - 1][jm] != 0 && poziom3[im - 1][jm] != 2)
							{
								go[D] = true;

								if (poziom3[im + 1][jm] == 0)
								{
									poziom3[iw][jw] = 0;
									poziom3[im + 1][jm] = najm - 1;
								}
								else if (poziom3[im + 1][jm] == 2)
								{
									poziom3[im + 1][jm] = najm - 1;
									punkty += 50;
									p++;
									predkosc = predkoscbazowa;
								}
							}
						}
					}
					else if (go[L])
					{
						if (poziom3[im][jm - 1] == 0)
						{
							poziom3[iw][jw] = 0;
							poziom3[im][jm - 1] = najm - 1;
						}
						else if (poziom3[im][jm - 1] == 2)
						{
							poziom3[im][jm - 1] = najm - 1;
							punkty += 50;
							p++;
							predkosc = predkoscbazowa;
						}
						else // juz wiadomo, ze nie ma przejscia
						{
							go[L] = false; // up,down, strata

							if ((poziom3[im - 1][jm] != 0) && (poziom3[im + 1][jm] != 2) && (poziom3[im - 1][jm] != 2) && (poziom3[im + 1][jm] != 0))
							{
								zycie -= 1;
								graj = false;
								predkosc = predkoscbazowa;
								keys[RIGHT] = false;
								keys[UP] = false;
								keys[LEFT] = false;
								keys[DOWN] = false;
								go[R] = false;
								go[L] = false;
								go[U] = false;
								go[D] = false;
							}
							else if (poziom3[im + 1][jm] != 0 && poziom3[im + 1][jm] != 2)
							{
								go[U] = true;
								if (poziom3[im - 1][jm] == 0)
								{
									poziom3[iw][jw] = 0;
									poziom3[im - 1][jm] = najm - 1;
								}
								else if (poziom3[im - 1][jm] == 2)
								{
									poziom3[im - 1][jm] = najm - 1;
									p++;
									punkty += 50;
									predkosc = predkoscbazowa;
								}
							}
							else if (poziom3[im - 1][jm] != 0 && poziom3[im - 1][jm] != 2)
							{
								go[D] = true;

								if (poziom3[im + 1][jm] == 0)
								{
									poziom3[iw][jw] = 0;
									poziom3[im + 1][jm] = najm - 1;
								}
								else if (poziom3[im + 1][jm] == 2)
								{
									poziom3[im + 1][jm] = najm - 1;
									punkty += 50;
									p++;
									predkosc = predkoscbazowa;
								}
							}
						}
					}
					else if (go[U])
					{
						if (poziom3[im - 1][jm] == 0)
						{
							poziom3[iw][jw] = 0;
							poziom3[im - 1][jm] = najm - 1;
						}
						else if (poziom3[im - 1][jm] == 2)
						{
							poziom3[im - 1][jm] = najm - 1;
							punkty += 50;
							p++;
							predkosc = predkoscbazowa;
						}
						else // juz wiadomo, ze nie ma przejscia
						{
							go[U] = false; // up,down, strata

							if ((poziom3[im][jm - 1] != 0) && (poziom3[im][jm - 1] != 2) && (poziom3[im][jm + 1] != 2) && (poziom3[im][jm + 1] != 0))
							{
								zycie -= 1;
								graj = false;
								predkosc = predkoscbazowa;
								keys[RIGHT] = false;
								keys[UP] = false;
								keys[LEFT] = false;
								keys[DOWN] = false;
								go[R] = false;
								go[L] = false;
								go[U] = false;
								go[D] = false;
							}
							else if (poziom3[im][jm - 1] != 0 && poziom3[im][jm - 1] != 2)
							{
								go[R] = true;
								if (poziom3[im][jm + 1] == 0)
								{
									poziom3[iw][jw] = 0;
									poziom3[im][jm + 1] = najm - 1;
								}
								else if (poziom3[im][jm + 1] == 2)
								{
									poziom3[im][jm + 1] = najm - 1;
									p++;
									punkty += 50;
									predkosc = predkoscbazowa;
								}
							}
							else if (poziom3[im][jm + 1] != 0 && poziom3[im][jm + 1] != 2)
							{
								go[L] = true;

								if (poziom3[im][jm - 1] == 0)
								{
									poziom3[iw][jw] = 0;
									poziom3[im][jm - 1] = najm - 1;
								}
								else if (poziom3[im][jm - 1] == 2)
								{
									poziom3[im][jm - 1] = najm - 1;
									punkty += 50;
									p++;
									predkosc = predkoscbazowa;
								}
							}
						}
					}
					else if (go[D])
					{
						if (poziom3[im + 1][jm] == 0)
						{
							poziom3[iw][jw] = 0;
							poziom3[im + 1][jm] = najm - 1;
						}
						else if (poziom3[im + 1][jm] == 2)
						{
							poziom3[im + 1][jm] = najm - 1;
							punkty += 50;
							p++;
							predkosc = predkoscbazowa;
						}
						else // juz wiadomo, ze nie ma przejscia
						{
							go[D] = false; // up,down, strata

							if ((poziom3[im][jm - 1] != 0) && (poziom3[im][jm - 1] != 2) && (poziom3[im][jm + 1] != 2) && (poziom3[im][jm + 1] != 0))
							{
								zycie -= 1;
								graj = false;
								predkosc = predkoscbazowa;
								keys[RIGHT] = false;
								keys[UP] = false;
								keys[LEFT] = false;
								keys[DOWN] = false;
								go[R] = false;
								go[L] = false;
								go[U] = false;
								go[D] = false;
							}
							else if (poziom3[im][jm - 1] != 0 && poziom3[im][jm - 1] != 2)
							{
								go[R] = true;
								if (poziom3[im][jm + 1] == 0)
								{
									poziom3[iw][jw] = 0;
									poziom3[im][jm + 1] = najm - 1;
								}
								else if (poziom3[im][jm + 1] == 2)
								{
									poziom3[im][jm + 1] = najm - 1;
									p++;
									punkty += 50;
									predkosc = predkoscbazowa;
								}
							}
							else if (poziom3[im][jm + 1] != 0 && poziom3[im][jm + 1] != 2)
							{
								go[L] = true;

								if (poziom3[im][jm - 1] == 0)
								{
									poziom3[iw][jw] = 0;
									poziom3[im][jm - 1] = najm - 1;
								}
								else if (poziom3[im][jm - 1] == 2)
								{
									poziom3[im][jm - 1] = najm - 1;
									punkty += 50;
									p++;
									predkosc = predkoscbazowa;
								}
							}
						}
					}
					
				}
				if ((count % 120 == 0) && graj)
				{
					if (predkosc < 59)
					{
						predkosc += 1;
					}
				}
			}		
			else if (poziom == 4)
			{
				al_clear_to_color(al_map_rgb(180, 0, 255));
				al_draw_text(malaczcionka, al_map_rgb(255, 195, 2), 250, 4, ALLEGRO_ALIGN_CENTRE, "Poziom  4");
				al_draw_textf(malaczcionka, al_map_rgb(255, 195, 2), 620, 4, ALLEGRO_ALIGN_RIGHT, "%i", punkty);
				al_draw_bitmap(serce4, 10, 0, 0);
				al_draw_textf(malaczcionka, al_map_rgb(255, 195, 2), 60, 4, ALLEGRO_ALIGN_LEFT, " -   %i", zycie);
				al_draw_bitmap(zegar4, 400, 1, 0);
				al_draw_textf(malaczcionka, al_map_rgb(255, 195, 2), 480, 4, ALLEGRO_ALIGN_RIGHT, "%i", 120 - sekundy);
				for ( i = 0; i < 28; i++)
				{
					for ( j = 0; j < 40; j++)
					{
						if (poziom4[i][j] == 1)
							al_draw_filled_rectangle(j * 16, (i * 16) + 32, (j * 16) + 16, (i * 16) + 48, al_map_rgb(0, 0, 0));
						else if (poziom4[i][j] == 2)
							al_draw_filled_circle((j * 16) + 8, (i * 16) + 40, 4, al_map_rgb(255, 195, 2));
						else if (poziom4[i][j] == 0)
						{}
						else
						{
							al_draw_filled_rectangle(j * 16, (i * 16) + 32, (j * 16) + 16, (i * 16) + 48, al_map_rgb(148, 233, 7));
						}
					}
				}
				if (!graj)
				{
					czas = false;
					keys[RIGHT] = false;
					keys[UP] = false;
					keys[LEFT] = false;
					keys[DOWN] = false;
					go[R] = false;
					go[L] = false;
					go[U] = false;
					go[D] = false;
					al_draw_filled_rectangle(50, 200, 590, 280, al_map_rgb(255, 255, 255));
					al_draw_text(czcionka, al_map_rgb(0, 0, 0), 320, 220, ALLEGRO_ALIGN_CENTRE, "Wcisnij spacje, zeby rozpoczac");
					for (i = 0; i < 28; i++)
					{
						for (j = 0; j < 40; j++)
						{
							if (poziom4[i][j] != 1 && poziom4[i][j] != 0 && poziom4[i][j] != 2)
							{
								poziom4[i][j] = 0;
							}

						}
					}
					poziom4[4][20] = -5;
					poziom4[5][20] = -4;
					poziom4[6][20] = -3;
					poziom4[6][19] = -2;
					poziom4[6][18] = -1;
				}
				al_flip_display();
				if (p == p4)
				{
					poziom++;
					graj = false;
					keys[RIGHT] = false;
					keys[UP] = false;
					keys[LEFT] = false;
					keys[DOWN] = false;
					go[R] = false;
					go[L] = false;
					go[U] = false;
					go[D] = false;
					punkty += 2000;
					p = 0;
					predkosc = predkoscbazowa;
					punkty += (120 - sekundy) * 10;
					sekundy = 0;
				}
				//skrecanie
				if (count % (FPS - predkosc) == 0)
				{
					najw = -32000;
					najm = 1; //szukanie glowy i ogona
					for (i = 0; i < 28; i++)
					{
						for (j = 0; j < 40; j++)
						{
							if (poziom4[i][j] < 0)
							{
								if (poziom4[i][j] > najw)
								{
									najw = poziom4[i][j];
									iw = i;
									jw = j;
								}
								if (poziom4[i][j] < najm)
								{
									najm = poziom4[i][j];
									im = i;
									jm = j;
								}
							}
						}
					}

					if (keys[RIGHT])
					{
						if (poziom4[im][jm + 1] == 0 || poziom4[im][jm + 1] == 2)
						{
							go[R] = true;
							go[L] = false;
							go[D] = false;
							go[U] = false;
						}
					}
					else if (keys[LEFT])
					{
						if (poziom4[im][jm - 1] == 0 || poziom4[im][jm - 1] == 2)
						{
							go[L] = true;
							go[R] = false;
							go[D] = false;
							go[U] = false;
						}
					}
					else if (keys[UP])
					{
						if (poziom4[im - 1][jm] == 0 || poziom4[im - 1][jm] == 2)
						{
							go[U] = true;
							go[L] = false;
							go[D] = false;
							go[R] = false;
						}
					}
					else if (keys[DOWN])
					{
						if (poziom4[im + 1][jm] == 0 || poziom4[im + 1][jm] == 2)
						{
							go[D] = true;
							go[L] = false;
							go[R] = false;
							go[U] = false;
						}
					}
					if (go[R])
					{
						if (poziom4[im][jm + 1] == 0)
						{
							poziom4[iw][jw] = 0;
							poziom4[im][jm + 1] = najm - 1;
						}
						else if (poziom4[im][jm + 1] == 2)
						{
							poziom4[im][jm + 1] = najm - 1;
							punkty += 50;
							p++;
							predkosc = predkoscbazowa;
						}
						else // juz wiadomo, ze nie ma przejscia
						{
							go[R] = false; // up,down, strata

							if ((poziom4[im - 1][jm] != 0) && (poziom4[im + 1][jm] != 2) && (poziom4[im - 1][jm] != 2) && (poziom4[im + 1][jm] != 0))
							{
								zycie -= 1;
								graj = false;
								predkosc = predkoscbazowa;
								keys[RIGHT] = false;
								keys[UP] = false;
								keys[LEFT] = false;
								keys[DOWN] = false;
								go[R] = false;
								go[L] = false;
								go[U] = false;
								go[D] = false;
							}
							else if (poziom4[im + 1][jm] != 0 && poziom4[im + 1][jm] != 2)
							{
								go[U] = true;
								if (poziom4[im - 1][jm] == 0)
								{
									poziom4[iw][jw] = 0;
									poziom4[im - 1][jm] = najm - 1;
								}
								else if (poziom4[im - 1][jm] == 2)
								{
									poziom4[im - 1][jm] = najm - 1;
									p++;
									punkty += 50;
									predkosc = predkoscbazowa;
								}
							}
							else if (poziom4[im - 1][jm] != 0 && poziom4[im - 1][jm] != 2)
							{
								go[D] = true;

								if (poziom4[im + 1][jm] == 0)
								{
									poziom4[iw][jw] = 0;
									poziom4[im + 1][jm] = najm - 1;
								}
								else if (poziom4[im + 1][jm] == 2)
								{
									poziom4[im + 1][jm] = najm - 1;
									punkty += 50;
									p++;
									predkosc = predkoscbazowa;
								}
							}
						}
					}
					else if (go[L])
					{
						if (poziom4[im][jm - 1] == 0)
						{
							poziom4[iw][jw] = 0;
							poziom4[im][jm - 1] = najm - 1;
						}
						else if (poziom4[im][jm - 1] == 2)
						{
							poziom4[im][jm - 1] = najm - 1;
							punkty += 50;
							p++;
							predkosc = predkoscbazowa;
						}
						else // juz wiadomo, ze nie ma przejscia
						{
							go[L] = false; // up,down, strata

							if ((poziom4[im - 1][jm] != 0) && (poziom4[im + 1][jm] != 2) && (poziom4[im - 1][jm] != 2) && (poziom4[im + 1][jm] != 0))
							{
								zycie -= 1;
								graj = false;
								predkosc = predkoscbazowa;
								keys[RIGHT] = false;
								keys[UP] = false;
								keys[LEFT] = false;
								keys[DOWN] = false;
								go[R] = false;
								go[L] = false;
								go[U] = false;
								go[D] = false;
							}
							else if (poziom4[im + 1][jm] != 0 && poziom4[im + 1][jm] != 2)
							{
								go[U] = true;
								if (poziom4[im - 1][jm] == 0)
								{
									poziom4[iw][jw] = 0;
									poziom4[im - 1][jm] = najm - 1;
								}
								else if (poziom4[im - 1][jm] == 2)
								{
									poziom4[im - 1][jm] = najm - 1;
									p++;
									punkty += 50;
									predkosc = predkoscbazowa;
								}
							}
							else if (poziom4[im - 1][jm] != 0 && poziom4[im - 1][jm] != 2)
							{
								go[D] = true;

								if (poziom4[im + 1][jm] == 0)
								{
									poziom4[iw][jw] = 0;
									poziom4[im + 1][jm] = najm - 1;
								}
								else if (poziom4[im + 1][jm] == 2)
								{
									poziom4[im + 1][jm] = najm - 1;
									punkty += 50;
									p++;
									predkosc = predkoscbazowa;
								}
							}
						}
					}
					else if (go[U])
					{
						if (poziom4[im - 1][jm] == 0)
						{
							poziom4[iw][jw] = 0;
							poziom4[im - 1][jm] = najm - 1;
						}
						else if (poziom4[im - 1][jm] == 2)
						{
							poziom4[im - 1][jm] = najm - 1;
							punkty += 50;
							p++;
							predkosc = predkoscbazowa;
						}
						else // juz wiadomo, ze nie ma przejscia
						{
							go[U] = false; // up,down, strata

							if ((poziom4[im][jm - 1] != 0) && (poziom4[im][jm - 1] != 2) && (poziom4[im][jm + 1] != 2) && (poziom4[im][jm + 1] != 0))
							{
								zycie -= 1;
								graj = false;
								predkosc = predkoscbazowa;
								keys[RIGHT] = false;
								keys[UP] = false;
								keys[LEFT] = false;
								keys[DOWN] = false;
								go[R] = false;
								go[L] = false;
								go[U] = false;
								go[D] = false;
							}
							else if (poziom4[im][jm - 1] != 0 && poziom4[im][jm - 1] != 2)
							{
								go[R] = true;
								if (poziom4[im][jm + 1] == 0)
								{
									poziom4[iw][jw] = 0;
									poziom4[im][jm + 1] = najm - 1;
								}
								else if (poziom4[im][jm + 1] == 2)
								{
									poziom4[im][jm + 1] = najm - 1;
									p++;
									punkty += 50;
									predkosc = predkoscbazowa;
								}
							}
							else if (poziom4[im][jm + 1] != 0 && poziom4[im][jm + 1] != 2)
							{
								go[L] = true;

								if (poziom4[im][jm - 1] == 0)
								{
									poziom4[iw][jw] = 0;
									poziom4[im][jm - 1] = najm - 1;
								}
								else if (poziom4[im][jm - 1] == 2)
								{
									poziom4[im][jm - 1] = najm - 1;
									punkty += 50;
									p++;
									predkosc = predkoscbazowa;
								}
							}
						}
					}
					else if (go[D])
					{
						if (poziom4[im + 1][jm] == 0)
						{
							poziom4[iw][jw] = 0;
							poziom4[im + 1][jm] = najm - 1;
						}
						else if (poziom4[im + 1][jm] == 2)
						{
							poziom4[im + 1][jm] = najm - 1;
							punkty += 50;
							p++;
							predkosc = predkoscbazowa;
						}
						else // juz wiadomo, ze nie ma przejscia
						{
							go[D] = false; // up,down, strata

							if ((poziom4[im][jm - 1] != 0) && (poziom4[im][jm - 1] != 2) && (poziom4[im][jm + 1] != 2) && (poziom4[im][jm + 1] != 0))
							{
								zycie -= 1;
								graj = false;
								predkosc = predkoscbazowa;
								keys[RIGHT] = false;
								keys[UP] = false;
								keys[LEFT] = false;
								keys[DOWN] = false;
								go[R] = false;
								go[L] = false;
								go[U] = false;
								go[D] = false;
							}
							else if (poziom4[im][jm - 1] != 0 && poziom4[im][jm - 1] != 2)
							{
								go[R] = true;
								if (poziom4[im][jm + 1] == 0)
								{
									poziom4[iw][jw] = 0;
									poziom4[im][jm + 1] = najm - 1;
								}
								else if (poziom4[im][jm + 1] == 2)
								{
									poziom4[im][jm + 1] = najm - 1;
									p++;
									punkty += 50;
									predkosc = predkoscbazowa;
								}
							}
							else if (poziom4[im][jm + 1] != 0 && poziom4[im][jm + 1] != 2)
							{
								go[L] = true;

								if (poziom4[im][jm - 1] == 0)
								{
									poziom4[iw][jw] = 0;
									poziom4[im][jm - 1] = najm - 1;
								}
								else if (poziom4[im][jm - 1] == 2)
								{
									poziom4[im][jm - 1] = najm - 1;
									punkty += 50;
									p++;
									predkosc = predkoscbazowa;
								}
							}
						}
					}

				
				}
				if ((count % 120 == 0) && graj)
				{
					if (predkosc < 59)
					{
						predkosc += 1;
					}
				}
			}	
			else if (poziom == 5)
			{
				al_clear_to_color(al_map_rgb(248, 160, 17));
				al_draw_text(malaczcionka, al_map_rgb(255, 0, 50), 250, 4, ALLEGRO_ALIGN_CENTRE, "Poziom  5");
				al_draw_textf(malaczcionka, al_map_rgb(255, 0, 50), 620, 4, ALLEGRO_ALIGN_RIGHT, "%i", punkty);
				al_draw_bitmap(serce5, 10, 0, 0);
				al_draw_textf(malaczcionka, al_map_rgb(255, 0, 50), 60, 4, ALLEGRO_ALIGN_LEFT, " -   %i", zycie);
				al_draw_bitmap(zegar5, 400, 1, 0);
				al_draw_textf(malaczcionka, al_map_rgb(255, 0, 50), 480, 4, ALLEGRO_ALIGN_RIGHT, "%i", 120 - sekundy);
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
						else if (poziom5[i][j] == 0)
						{}
						else
						{
							al_draw_filled_rectangle(j * 16, (i * 16) + 32, (j * 16) + 16, (i * 16) + 48, al_map_rgb(2, 3, 255));
						}
					}
				}
				if (!graj)
				{
					czas = false;
					keys[RIGHT] = false;
					keys[UP] = false;
					keys[LEFT] = false;
					keys[DOWN] = false;
					go[R] = false;
					go[L] = false;
					go[U] = false;
					go[D] = false;
					al_draw_filled_rectangle(50, 200, 590, 280, al_map_rgb(255, 255, 255));
					al_draw_text(czcionka, al_map_rgb(0, 0, 0), 320, 220, ALLEGRO_ALIGN_CENTRE, "Wcisnij spacje, zeby rozpoczac");
					for (i = 0; i < 28; i++)
					{
						for (j = 0; j < 40; j++)
						{
							if (poziom5[i][j] != 1 && poziom5[i][j] != 0 && poziom5[i][j] != 2)
							{
								poziom5[i][j] = 0;
							}

						}
					}
					poziom5[4][20] = -5;
					poziom5[4][19] = -4;
					poziom5[4][18] = -3;
					poziom5[4][17] = -2;
					poziom5[3][17] = -1;
				}
				al_flip_display();

				if (p == p5)
				{
					koniec = true;
					sort = true;
					graj = false;
					keys[RIGHT] = false;
					keys[UP] = false;
					keys[LEFT] = false;
					keys[DOWN] = false;
					go[R] = false;
					go[L] = false;
					go[D] = false;
					go[U] = false;
					punkty += 2000;
					p = 0;
					poziom = 6;
					predkosc = predkoscbazowa;
					punkty += (120 - sekundy) * 10;
					sekundy = 0;
				}
				//skrecanie
				if (count % (FPS - predkosc) == 0)
				{
					najw = -32000;
					najm = 1; //szukanie glowy i ogona
					for (i = 0; i < 28; i++)
					{
						for (j = 0; j < 40; j++)
						{
							if (poziom5[i][j] < 0)
							{
								if (poziom5[i][j] > najw)
								{
									najw = poziom5[i][j];
									iw = i;
									jw = j;
								}
								if (poziom5[i][j] < najm)
								{
									najm = poziom5[i][j];
									im = i;
									jm = j;
								}
							}
						}
					}

					if (keys[RIGHT])
					{
						if (poziom5[im][jm + 1] == 0 || poziom5[im][jm + 1] == 2)
						{
							go[R] = true;
							go[L] = false;
							go[D] = false;
							go[U] = false;
						}
					}
					else if (keys[LEFT])
					{
						if (poziom5[im][jm - 1] == 0 || poziom5[im][jm - 1] == 2)
						{
							go[L] = true;
							go[R] = false;
							go[D] = false;
							go[U] = false;
						}
					}
					else if (keys[UP])
					{
						if (poziom5[im - 1][jm] == 0 || poziom5[im - 1][jm] == 2)
						{
							go[U] = true;
							go[L] = false;
							go[D] = false;
							go[R] = false;
						}
					}
					else if (keys[DOWN])
					{
						if (poziom5[im + 1][jm] == 0 || poziom5[im + 1][jm] == 2)
						{
							go[D] = true;
							go[L] = false;
							go[R] = false;
							go[U] = false;
						}
					}

					if (go[R])
					{
						if (poziom5[im][jm + 1] == 0)
						{
							poziom5[iw][jw] = 0;
							poziom5[im][jm + 1] = najm - 1;
						}
						else if (poziom5[im][jm + 1] == 2)
						{
							poziom5[im][jm + 1] = najm - 1;
							punkty += 50;
							p++;
							predkosc = predkoscbazowa;
						}
						else // juz wiadomo, ze nie ma przejscia
						{
							go[R] = false; // up,down, strata

							if ((poziom5[im - 1][jm] != 0) && (poziom5[im + 1][jm] != 2) && (poziom5[im - 1][jm] != 2) && (poziom5[im + 1][jm] != 0))
							{
								zycie -= 1;
								graj = false;
								predkosc = predkoscbazowa;
								keys[RIGHT] = false;
								keys[UP] = false;
								keys[LEFT] = false;
								keys[DOWN] = false;
								go[R] = false;
								go[L] = false;
								go[U] = false;
								go[D] = false;
							}
							else if (poziom5[im + 1][jm] != 0 && poziom5[im + 1][jm] != 2)
							{
								go[U] = true;
								if (poziom5[im - 1][jm] == 0)
								{
									poziom5[iw][jw] = 0;
									poziom5[im - 1][jm] = najm - 1;
								}
								else if (poziom5[im - 1][jm] == 2)
								{
									poziom5[im - 1][jm] = najm - 1;
									p++;
									punkty += 50;
									predkosc = predkoscbazowa;
								}
							}
							else if (poziom5[im - 1][jm] != 0 && poziom5[im - 1][jm] != 2)
							{
								go[D] = true;

								if (poziom5[im + 1][jm] == 0)
								{
									poziom5[iw][jw] = 0;
									poziom5[im + 1][jm] = najm - 1;
								}
								else if (poziom5[im + 1][jm] == 2)
								{
									poziom5[im + 1][jm] = najm - 1;
									punkty += 50;
									p++;
									predkosc = predkoscbazowa;
								}
							}
						}
					}
					else if (go[L])
					{
						if (poziom5[im][jm - 1] == 0)
						{
							poziom5[iw][jw] = 0;
							poziom5[im][jm - 1] = najm - 1;
						}
						else if (poziom5[im][jm - 1] == 2)
						{
							poziom5[im][jm - 1] = najm - 1;
							punkty += 50;
							p++;
							predkosc = predkoscbazowa;
						}
						else // juz wiadomo, ze nie ma przejscia
						{
							go[L] = false; // up,down, strata

							if ((poziom5[im - 1][jm] != 0) && (poziom5[im + 1][jm] != 2) && (poziom5[im - 1][jm] != 2) && (poziom5[im + 1][jm] != 0))
							{
								zycie -= 1;
								graj = false;
								predkosc = predkoscbazowa;
								keys[RIGHT] = false;
								keys[UP] = false;
								keys[LEFT] = false;
								keys[DOWN] = false;
								go[R] = false;
								go[L] = false;
								go[U] = false;
								go[D] = false;
							}
							else if (poziom5[im + 1][jm] != 0 && poziom5[im + 1][jm] != 2)
							{
								go[U] = true;
								if (poziom5[im - 1][jm] == 0)
								{
									poziom5[iw][jw] = 0;
									poziom5[im - 1][jm] = najm - 1;
								}
								else if (poziom5[im - 1][jm] == 2)
								{
									poziom5[im - 1][jm] = najm - 1;
									p++;
									punkty += 50;
									predkosc = predkoscbazowa;
								}
							}
							else if (poziom5[im - 1][jm] != 0 && poziom5[im - 1][jm] != 2)
							{
								go[D] = true;

								if (poziom5[im + 1][jm] == 0)
								{
									poziom5[iw][jw] = 0;
									poziom5[im + 1][jm] = najm - 1;
								}
								else if (poziom5[im + 1][jm] == 2)
								{
									poziom5[im + 1][jm] = najm - 1;
									punkty += 50;
									p++;
									predkosc = predkoscbazowa;
								}
							}
						}
					}
					else if (go[U])
					{
						if (poziom5[im - 1][jm] == 0)
						{
							poziom5[iw][jw] = 0;
							poziom5[im - 1][jm] = najm - 1;
						}
						else if (poziom5[im - 1][jm] == 2)
						{
							poziom5[im - 1][jm] = najm - 1;
							punkty += 50;
							p++;
							predkosc = predkoscbazowa;
						}
						else // juz wiadomo, ze nie ma przejscia
						{
							go[U] = false; // up,down, strata

							if ((poziom5[im][jm - 1] != 0) && (poziom5[im][jm - 1] != 2) && (poziom5[im][jm + 1] != 2) && (poziom5[im][jm + 1] != 0))
							{
								zycie -= 1;
								graj = false;
								predkosc = predkoscbazowa;
								keys[RIGHT] = false;
								keys[UP] = false;
								keys[LEFT] = false;
								keys[DOWN] = false;
								go[R] = false;
								go[L] = false;
								go[U] = false;
								go[D] = false;
							}
							else if (poziom5[im][jm - 1] != 0 && poziom5[im][jm - 1] != 2)
							{
								go[R] = true;
								if (poziom5[im][jm + 1] == 0)
								{
									poziom5[iw][jw] = 0;
									poziom5[im][jm + 1] = najm - 1;
								}
								else if (poziom5[im][jm + 1] == 2)
								{
									poziom5[im][jm + 1] = najm - 1;
									p++;
									punkty += 50;
									predkosc = predkoscbazowa;
								}
							}
							else if (poziom5[im][jm + 1] != 0 && poziom5[im][jm + 1] != 2)
							{
								go[L] = true;

								if (poziom5[im][jm - 1] == 0)
								{
									poziom5[iw][jw] = 0;
									poziom5[im][jm - 1] = najm - 1;
								}
								else if (poziom5[im][jm - 1] == 2)
								{
									poziom5[im][jm - 1] = najm - 1;
									punkty += 50;
									p++;
									predkosc = predkoscbazowa;
								}
							}
						}
					}
					else if (go[D])
					{
						if (poziom5[im + 1][jm] == 0)
						{
							poziom5[iw][jw] = 0;
							poziom5[im + 1][jm] = najm - 1;
						}
						else if (poziom5[im + 1][jm] == 2)
						{
							poziom5[im + 1][jm] = najm - 1;
							punkty += 50;
							p++;
							predkosc = predkoscbazowa;
						}
						else // juz wiadomo, ze nie ma przejscia
						{
							go[D] = false; // up,down, strata

							if ((poziom5[im][jm - 1] != 0) && (poziom5[im][jm - 1] != 2) && (poziom5[im][jm + 1] != 2) && (poziom5[im][jm + 1] != 0))
							{
								zycie -= 1;
								graj = false;
								predkosc = predkoscbazowa;
								keys[RIGHT] = false;
								keys[UP] = false;
								keys[LEFT] = false;
								keys[DOWN] = false;
								go[R] = false;
								go[L] = false;
								go[U] = false;
								go[D] = false;
							}
							else if (poziom5[im][jm - 1] != 0 && poziom5[im][jm - 1] != 2)
							{
								go[R] = true;
								if (poziom5[im][jm + 1] == 0)
								{
									poziom5[iw][jw] = 0;
									poziom5[im][jm + 1] = najm - 1;
								}
								else if (poziom5[im][jm + 1] == 2)
								{
									poziom5[im][jm + 1] = najm - 1;
									p++;
									punkty += 50;
									predkosc = predkoscbazowa;
								}
							}
							else if (poziom5[im][jm + 1] != 0 && poziom5[im][jm + 1] != 2)
							{
								go[L] = true;

								if (poziom5[im][jm - 1] == 0)
								{
									poziom5[iw][jw] = 0;
									poziom5[im][jm - 1] = najm - 1;
								}
								else if (poziom5[im][jm - 1] == 2)
								{
									poziom5[im][jm - 1] = najm - 1;
									punkty += 50;
									p++;
									predkosc = predkoscbazowa;
								}
							}
						}
					}
					
				}
				if ((count % 120 == 0) && graj)
				{
					if (predkosc < 59)
					{
						predkosc += 1;
					}
				}
			}

			if ((zycie < 0) && poziom>0)
			{
				poziom = 0;
				koniec = true;
				sort = true;
				graj = false;
				keys[RIGHT] = false;
				keys[UP] = false;
				keys[LEFT] = false;
				keys[DOWN] = false;
				go[R] = false;
				go[L] = false;
				go[D] = false;
				go[U] = false;
				p = 0;
				predkosc = predkoscbazowa;
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