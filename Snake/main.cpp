#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

//Размеры поля N,M , размер текстуры 16 , w и h размеры окна ,
//dir отвечаетза направление движения , num - размер змейки
int N = 30, M = 20;	   
int size = 16;
int w = size * N;
int h = size * M;
int dir, num = 4;

struct Snake
{
	int x, y;
} s[100];
struct Fruct { int x, y;} f;

//Метод Тик для смены координат и проверки условий игры
void Tick()
{
	//Движения всего тела. Начинается с головы
	for (int i = num; i > 0; --i) {
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	//Условия движения по сторонам
	if (dir == 0)
		s[0].y += 1;
	if (dir == 1)
		s[0].x -= 1;
	if (dir == 2)
		s[0].x += 1;
	if (dir == 3)
		s[0].y -= 1;

	//Координаты еды
	if ((s[0].x == f.x) && (s[0].y == f.y)) {
		num++;
		f.x = rand() % N;
		f.y = rand() % M;
	}

	//Движение при выходе за рамки поля
	if (s[0].x > N)
		s[0].x = 0;
	if (s[0].x < 0)
		s[0].x = N;
	if (s[0].y > M)
		s[0].y = 0;
	if (s[0].y < 0)
		s[0].y= M;

	//Условие при котором змейка съедает хвост
	for (int i = 1; i < num; i++)
		if (s[0].x == s[i].x && s[0].y == s[i].y)
			num = i;

}

int main() {
	
	//Отображение окна и загрузка текстур , инициализация спрайтов
	RenderWindow window(VideoMode(w, h), "Snake Gane");
	Texture t1, t2,t3;
	t1.loadFromFile("images/white.png");
	t2.loadFromFile("images/red.png");
	t3.loadFromFile("images/green.png");
	Sprite sprite1(t1) , sprite2(t2) , sprite3(t3);

	//Инициализация рандомайзера
	srand(time(0));

	//Класс clock для измерения времени. Запуск таймера
	Clock clock;

	//Счетчик для времени и переменная для сравнения временного интервала
	float timer=0 , delay = 0.1;

	//Начальные координаты еды
	f.x = 10;
	f.y = 10;

	while (window.isOpen())
	{
		//Получаем время , прошедшее с запуска часов в секундах. Перезапускаем часы.
		//Складываем разницу с запуска до текущего момента.
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		//Закрытие игры
		Event e;
		while (window.pollEvent(e))
			if (e.type == Event::Closed)
				window.close();

		//Управление направлением змейки
		if (Keyboard::isKeyPressed(Keyboard::Left)&&dir!=2)
			dir = 1;
		if (Keyboard::isKeyPressed(Keyboard::Right)&&dir!=1)
			dir = 2;
		if (Keyboard::isKeyPressed(Keyboard::Up) && dir!=0)
			dir = 3;
		if (Keyboard::isKeyPressed(Keyboard::Down)&& dir!=3)
			dir = 0;

	
		//Если разница по времени больше 1/10 секунды, то обновить счетчик и произвести вычисления координат и проверку условий
		if(timer>delay)
		{
			timer = 0;
			Tick();
		}

		

		 //Рисовка поля
		for(int i=0;i<N;i++)
			for (int j = 0; j < M; j++) {

				sprite1.setPosition(i * size, j * size);
				window.draw(sprite1);
			}

		//Рисовка змейки
		for (int i = 0; i < num; i++)
		{
			sprite2.setPosition(s[i].x*size, s[i].y*size);
			window.draw(sprite2);
		}

		//Рисовка еды
		sprite3.setPosition(f.x * size, f.y * size);
		window.draw(sprite3);

		window.display();
	}

	return 0;

}