#include<iostream>
#include<Windows.h>
using namespace std;

namespace Geometry
{

	enum Color//пользовательский тип данных
	{
		Red = 0x000000FF,
		Green = 0x0000FF00,
		Blue = 0x00FF0000,
		Yellow = 0x0000FFFF,
		Violet = 0x00FF00FF
	};

	class Shape        //фигура
	{
		Color color;   // цвет фигуры
	public:
		void set_color(Color color)
		{
			this->color = color;
		}
		Color get_color()const
		{
			return color;
		}

		virtual double get_area()const = 0;      //Ч-В 
		virtual double get_perimeter()const = 0; //Ч-В 
		virtual void draw()const = 0;            //Ч-В 
		Shape(Color color) : color(color) {}
		virtual void info()const
		{
			cout << " Площадь фигуры" << get_area() << endl;
			cout << " Периметр фигуры" << get_perimeter() << endl;
			draw();
		}
	};
	class Square : public Shape
	{
		double side; //длина стороны
	public:
		void set_side(double side)
		{
			this->side = side;
		}
		double get_side()const
		{
			return side;
		}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return side * 4;
		}
		void draw()const override
		{
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
		}
		Square(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << " Сторона квадрата" << get_side() << endl;
			Shape::info();
		}
	};

	class Rectangle : public Shape
	{
		double side_1;
		double side_2;
	public:
		void set_side_1(double side_1)
		{
			this->side_1 = side_1;
		}
		void set_side_2(double side_2)
		{
			this->side_2 = side_2;
		}

		double get_side_1()const
		{
			return side_1;
		}
		double get_side_2() const
		{
			return side_2;
		}
		double get_area() const override
		{
			return side_1 * side_2;
		}
		double get_perimeter() const override
		{
			return (side_1 + side_2) * 2;
		}
		void draw()const override
		{
			/*for (int i = 0; i < side_1; i++)
				{
					for (int j = 0; j < side_2; j++)
					{
						cout << "* ";
					}
					cout << endl;
			}*/

            //1)получаем окно консоли
			HWND hwnd = GetConsoleWindow();

			//2)получаем контекст консольного окна
			HDC hdc = GetDC(hwnd);//контекст устройсвта - это на чем мы будем рисовать

			//3)создаем то, чем мы будем рисовать - карандаш
			HPEN hPen = CreatePen(PS_SOLID,1,RGB(255,0,0));//Pen - рисует контур фигуры
			//PS_SOLID - сплошная линия
			//1 - толщина линии 1 пиксель
			//RGB 255,0,0 - линия красного цвета

			//4)Создаем кисть, кот выполняет заливку фигуры
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));

			//5)Выбираем чем и на чем будем рисовать
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//6)Вызываем нужную функцию для рисования фигуры
			::Rectangle(hdc, 200, 200, 400, 400);//начальные координаты 200,200,400,400
			//:: глобальное пространство имен

			
			//7) Удаляем карандаш и кисть, поскольку они тоже занимает ресурсы
			DeleteObject(hBrush);
			DeleteObject(hPen);
			
			//8)Контескт устройства занимает ресурсы кот нужно освободить
			ReleaseDC(hwnd, hdc);

		}
		Rectangle(double side_1, double side_2, Color color) : Shape(color)
		{
			set_side_1(side_1);
			set_side_2(side_2);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона 1 " << get_side_1() << endl;
			cout << "Сторона 2 " << get_side_2() << endl;
			Shape::info();
		}
	};
}


void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color :: Blue);//нельзя создать экземпляр абстр класса
	Geometry:: Square square(5, Geometry:: Color::Red);
	square.info();

	Geometry:: Rectangle rectangle(20, 15, Geometry:: Color::Red);
	rectangle.info();

}