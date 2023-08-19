#include <allegro.h>
#include <iostream>
using namespace std;

const int alto=100;
const int ancho=60;
//esta estructura sirve para pasar coordenadas en el juego 
struct coord{
	int x;
	int y;
};
coord manejo[2][1] = {{50, 600},
                     {140, 600}};
coord pos[2][1] = {{55, -100},
				  {140, -100}};
coord camino[4][1] = {{40,0},
				     {40, -700},
					 {0, -60}, 
					 {220, -60}};
					 
//aqui se pinta en el buffer principal que es el "buffer" 
void pintar(BITMAP *buffer, BITMAP *carro, coord c)
{

	draw_sprite(buffer, carro, c.x, c.y);
}


/*cam es la funcion que pone en movimiento a todos los bitmaps, recibe las coordenadas de los bitmaps y una variable que lleva el tipo de dato
	por ejemplo si son de numero 0 entonces son carros y si son de tipo 1 son los otros objetos que dan realismo a carretera
*/
void cam(coord &c, int q)
{
	if(q==0)
	{
	   int r= rand()%2;
	   c=pos[r][0];	
	}
	if(q==1)
	{
	   int r= rand()%2+2;
	   c=camino[r][0];	
	}
		
}
//clase choque donde se tiene un metodo que recibe posiciones de los birmaps de carros y si llegan a coincidir los carros entonces lo cuenta como un choque 
class chocando{
public:
bool choque(coord &a, coord &b, int alto, int ancho)
{
	
	if((a.x<b.x+ancho) && (b.x<a.x+ancho) && (a.y<b.y+alto) && (b.y<a.y+alto))
		return true;
	else 
		return false;
}
};

int main() 
{
	chocando a;
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 500, 700, 0, 0);
	if (res != 0) 
	{
		allegro_message(allegro_error);
		exit(-1);
	}
	if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) {
       allegro_message("Error: inicializando sistema de sonido\n%s\n", allegro_error);
       return 1;
    }
   set_volume(100, 100);

	install_timer();
	install_keyboard();
	install_mouse();
	//declaracion de bitmaps para que las imagenes se suban al juego
	BITMAP *buffer = create_bitmap(260, 700);
	BITMAP *buffer2 = create_bitmap(240, 700);
	BITMAP *car= load_bitmap("carro1.bmp",NULL);
	BITMAP *car1= load_bitmap("carro2.bmp",NULL);
	BITMAP *car2= load_bitmap("carro3.bmp",NULL);
	BITMAP *car3= load_bitmap("carro4.bmp",NULL);
	BITMAP *camin= load_bitmap("camino.bmp",NULL);
	BITMAP *obstaculo1= load_bitmap("obstaculo1.bmp",NULL);
	BITMAP *obstaculo2= load_bitmap("obstaculo2.bmp",NULL);
	BITMAP *obstaculo3= load_bitmap("obstaculo3.bmp",NULL);
	BITMAP *titul= load_bitmap("titulo.bmp", NULL);
	SAMPLE *perreo=load_wav("musica.wav");
	
	//declaracion de variables para posiciones y movimientos
	int puntos=0,nivel=1, tope=50, cont=15,tem=0;
	int n1=0, n2=0;
	int t=rand()%3; 
	coord ca = manejo[0][0];
	coord c1;
	coord c2;
	coord c3;
	coord cami= camino[0][0], cami1=camino[1][0]; 
	coord ob1, ob2, ob3;
	coord t1 = {0, 100};
	cam(c1, 0);
	cam(ob1,1);
	cam(ob2,1);
	cam(ob3,1);
	play_sample(perreo, 100, 100, 1000, 1);
	//ciclo donde se corren todas las variables del juego
	while(!key[KEY_ESC]){
		
		clear_to_color(buffer,0x0000000);
		clear_to_color(buffer2,0x12A4F1);

		if(tem>=cont)
		{
			c1.y+=50;
			c2.y+=50;
			c3.y+=50;
			ob1.y+=50;
			ob2.y+=50;
			ob3.y+=50;
			cami.y+=50;
			cami1.y+=50;
			tem=0;
		}
		
		if(puntos >= tope)
		{
			tope +=50;
	
			if(cont >> 1)
			{
				cont--;
				nivel++;
			}
		}
	
		if(cami.y>=700)
		{
			cami= camino[1][0];
		}
	
		if(cami1.y>=700)
		{
			cami1= camino[1][0];
		}
	
		if(c1.y>=800){
		 puntos+=5;
		 cam(c1, 0); 
		 }
		 
	
		if(c2.y>=800)
		{
			puntos+=5;
		 cam(c2, 0);
		 }
	
		if(c3.y>=800)
		{
			puntos+=5;
		 cam(c3, 0);
		 }
	
		if(c1.y>=160 && n1==0)
		{
			cam(c2, 0);
			n1=1;
		}
	
		if(c1.y>=470 && n2==0)
		{
			cam(c3, 0);
			n2=1;
		}
	
		if(ob1.y>=700 && t==0)
		{
			cam(ob1, 1);
			t=rand()%3;
		}
	
		if(ob2.y>=700 && t==1)
		{
			cam(ob2, 1);
			t=rand()%3;
		}
	
		if(ob3.y>=700 && t==2)
		{
			cam(ob3, 1);
			t=rand()%3;
		}
		
		pintar(buffer2, titul, t1);
		pintar(buffer, camin, cami);
		pintar(buffer, camin, cami1);
		
		
		if(key[KEY_RIGHT]) ca = manejo[1][0];
		if(key[KEY_LEFT]) ca = manejo[0][0];
		
		
		pintar(buffer, car, ca);
		pintar(buffer, car1, c1);
		
		
		if(n1==1) pintar(buffer, car2, c2);
		if(n2==1) pintar(buffer, car3, c3);
		
		if(t==0) pintar(buffer, obstaculo1, ob1);
		if(t==1) pintar(buffer, obstaculo2, ob2);
		if(t==2) pintar(buffer, obstaculo3, ob3);
		
		
		textout_centre_ex(buffer2, font, "puntos", 120, 300, 0xFF0000, 0x000000);
		textprintf(buffer2, font, 115, 320, -1, "%d", puntos);
		textout_centre_ex(buffer2, font, "nivel", 120, 340, 0xFF0000, 0x000000);
		textprintf(buffer2, font, 115, 360, -1, "%d", nivel);
		
		
		
		blit(buffer, screen, 0,0,0,0, 260, 700);
		blit(buffer2, screen, 0,0,260,0, 240, 700);
		if(a.choque(ca, c1, alto, ancho) || a.choque(ca, c2, alto, ancho) || a.choque(ca, c3, alto, ancho))
		{
			do{
		textout_centre_ex(screen, font, "HAS PERDIDO", 250, 340, 0xFF0000, 0xFFFFFF);
		textout_centre_ex(screen, font, "PARA VOLVER A JUGAR PRESIONA 1\nPARA SALIR PRECIONA ESC", 250, 360, 0xFF0000, 0xFFFFFF);
		
			 tem=0;
			n1=0; n2=0;
			cam(c1, 0);
			cam(c2, 0);
			cam(c3, 0);
			cam(ob1, 1);
			cam(ob2, 1);
			cam(ob3, 1);
			t=rand()%3;
			puntos=0;
			nivel=1;
			cont=15;
			tope=50;
			
			if(key[KEY_ESC]) break;
		}while(!key[KEY_1]);
		}
		rest(10);
		tem++;
	}
	destroy_bitmap(buffer);
	destroy_bitmap(car);
	destroy_bitmap(car1);
	destroy_bitmap(car2);
	destroy_bitmap(car3);
	destroy_bitmap(camin);
	return 0;
}
END_OF_MAIN()


