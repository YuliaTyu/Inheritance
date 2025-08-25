#include<iostream>
#include<Windows.h> //библиотека для создания рисования чем и на чем
using namespace std;

namespace Geometry//так как существует функция Rectangle в библиотке Windows.h , создаем доп пространство имен 
{

	enum Color//пользовательский тип данных
	{
		Red = 0x000000FF,
		Green = 0x0000FF00,
		Blue = 0x00FF0000,
		Yellow = 0x0000FFFF,
		Violet = 0x00FF00FF
	};

#define SHAPE_TAKE_PARAMETERS int start_x,int start_y,int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color

	class Shape        //фигура
	{
		static const int MIN_START_X = 100;
		static const int MIN_START_Y = 100;
		static const int MAX_START_X = 800;
		static const int MAX_START_Y = 600;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 32;
		static const int MIN_SIZE = 32;
		static const int MAX_SIZE = 800;
	protected:
		int start_x;
		int start_y;
		int line_width;
		Color color;   // цвет фигуры
		
	public:
		void set_start_x(int start_x)
		{
           this->start_x = 
			   start_x < MIN_START_X ? MIN_START_X :
			   start_x > MAX_START_X ? MAX_START_X :
		   start_x;
		}
		void set_start_y(int start_y)
		{
			this->start_y =
				start_y < MIN_START_Y ? MIN_START_Y :
				start_y > MAX_START_Y ? MAX_START_Y :
				start_y;
		}
		void set_line_width(int line_width)
		{
			this->line_width =
				line_width < MIN_LINE_WIDTH ? MIN_LINE_WIDTH :
				line_width > MAX_LINE_WIDTH ? MAX_LINE_WIDTH :
				line_width;
		}

		void set_color(Color color)
		{
			this->color = color;
		}
		int get_start_x()const
		{
			return start_x;
		}
		int get_start_y()const
		{
			return start_y;
		}
		int get_line_width()const
		{
			return line_width;
		}
		
		Color get_color()const
		{
			return color;
		}

		virtual double get_area()const = 0;      //Ч-В 
		virtual double get_perimeter()const = 0; //Ч-В 
		virtual void draw()const = 0;            //Ч-В 
		Shape(SHAPE_TAKE_PARAMETERS) : color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual void info()const
		{
			cout << " Площадь фигуры" << get_area() << endl;
			cout << " Периметр фигуры" << get_perimeter() << endl;
			draw();
		}
	};
	/*class Square : public Shape
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
		Square(double side, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << " Сторона квадрата" << get_side() << endl;
			Shape::info();
		}
	};*/

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
			HPEN hPen = CreatePen(PS_SOLID,line_width, color);//Pen - рисует контур фигуры
			//PS_SOLID - сплошная линия
			//1 - толщина линии 1 пиксель
			//RGB 255,0,0 - линия красного цвета

			//4)Создаем кисть, кот выполняет заливку фигуры
			HBRUSH hBrush = CreateSolidBrush(color);

			//5)Выбираем чем и на чем будем рисовать
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//6)Вызываем нужную функцию для рисования фигуры
			::Rectangle(hdc, start_x, start_y, start_x+side_1, start_y+side_2);//начальные координаты 200,200,400,400
			//:: глобальное пространство имен

			//7) Удаляем карандаш и кисть, поскольку они тоже занимает ресурсы
			DeleteObject(hBrush);
			DeleteObject(hPen);
			
			//8)Контескт устройства занимает ресурсы кот нужно освободить
			ReleaseDC(hwnd, hdc);

		}
		Rectangle(double side_1, double side_2, SHAPE_TAKE_PARAMETERS) : Shape(SHAPE_GIVE_PARAMETERS)
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
	class Square :public Rectangle
	{
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
	};
}


void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color :: Blue);//нельзя создать экземпляр абстр класса
	Geometry:: Square square(50,400,100,5, Geometry:: Color::Yellow);
	square.info();

	Geometry:: Rectangle rectangle(200,150,550,100,1, Geometry:: Color::Violet);
	rectangle.info();

}