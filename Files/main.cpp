#include<iostream>
#include<fstream>
using std::cin;
using std::cout;
using std::endl;

//#define WRITE_TO_FILE
#define READ_FROM_FILE


void main()
{
	setlocale(LC_ALL, "");

#ifdef WRITE_TO_FILE

	//1)создаем поток
	std::ofstream fout;
	//2)открываем поток
	fout.open("File.txt",std:: fstream::app);
	//3)пишем в поток
	fout << "Hello Files"<< endl;
	//4)потоки как холодильник если он был открыт его обязательно нужно закрыть
	fout.close();
	//5)
	system("notepad File.txt");
#endif // WRITE_TO_FILE

	//1) создаем и открываем поток
	std::ifstream fin("File.txt");

	//2)проверяем открылся ли поток
	if (fin.is_open())
	{
		while (!fin.eof())//пока не конец файла читаем дальше
		{
			const int SIZE = 256;
			char sz_buffer[SIZE] = {};
			//fin >> sz_buffer;//читает до пробела
			fin.getline(sz_buffer, SIZE);//читает всю строку
			cout << sz_buffer << endl;
		}
		fin.close(); 
	}
	else
	{
		std::cerr << "Error: file not foud" << endl;
	}

}