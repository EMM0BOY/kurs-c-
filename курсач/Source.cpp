
#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include<iostream>
#include <cstring>
#include<iomanip>
#include <fstream>
using namespace std;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
#define rus setlocale(LC_ALL, "Russian");
#define _USE_MATH_DEFINES
#define PI 3.1413
void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}
void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

void keyboard_menu();
void menu();


void to_menu() {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 | BACKGROUND_INTENSITY);
	printf("\n\t\t\t\t\tНажимите любую клавишу, чтобы перейти в меню");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	_getch();
	return;
}

void to_keyboard_menu() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 | BACKGROUND_INTENSITY);
	printf("\n\nНажимите любую клавишу, чтобы перейти в меню раздела");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	_getch();
	keyboard_menu();

}

void about() {

	char str[][100] = { "~~# Об авторе #~~", "Курсовая работа", "Студент группы ИВТ-223", "Трубицын Дмитрий Александрович" };
	int w = 100;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	printf("\n");
	for (int j = 0; j < sizeof(str) / sizeof(str[0]); j++) {
		int n = strlen(str[j]);
		for (int i = 0; i < (w - n) / 2 + 10; i++) {
			if ((i == ((w - n) / 2) + 8) && j != 0) printf("|");
			else printf(" ");
		}

		for (int k = 0; k < n; k++) {
			printf("%c", str[j][k]);
			Sleep(20);
		}
		if (j != 0) printf(" |\n\n");
		else printf("\n\n");
		Sleep(700);
	}

	SetConsoleTextAttribute(hStdOut, 7);
	to_menu();
}




void intro() {

	HANDLE s_in = GetStdHandle(STD_INPUT_HANDLE);


	char vars[][100] = { "Обучающая программа для работы с клавиатурой и справочником музыканты", "Трубицын Д.А.", "ИВТ-223", "ОмГТУ, 2023" };
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	for (int i = 1; i < 10; i++) {
		printf("\n");
	}

	for (int i = 0; i < (sizeof(vars) / sizeof(vars[0])); i++) {

		for (int h = 0; h < 60 - strlen(vars[i]) / 2; h++) printf(" ");

		if (i == 4) {

			Sleep(500);
			printf("\n");
			for (int h = 0; h < 60 - strlen(vars[i]) / 2; h++) printf(" ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			printf("%s", vars[i]);

		}
		else {

			for (int j = 0; j < strlen(vars[i]); j++) {
				printf("-");
				Sleep(10);
			}
			for (int j = 0; j < strlen(vars[i]); j++) {
				printf("\b");
				Sleep(10);
			}
			for (int j = 0; j < strlen(vars[i]); j++) {
				printf("%c", vars[i][j]);
				Sleep(15);
			}
			printf("\n");
		}

	}

	Sleep(500);

	to_menu();

	for (int i = 0; i < 5; i++) {
		printf(".");
		Sleep(100);
	}
	for (int i = 0; i < 5; i++) {
		printf("\b \b");
		Sleep(100);
	}

	Sleep(50);

	return;

}


void interrupt(const char label[]) {
	HANDLE s_in = GetStdHandle(STD_INPUT_HANDLE);
	DWORD dr;
	INPUT_RECORD rec;

	printf("\n\t%s. Чтобы начать, нажмите ENTER", label);

	while (true) {

		do {
			ReadConsoleInput(s_in, &rec, 1, &dr);
		} while (rec.EventType == KEY_EVENT && !rec.Event.KeyEvent.bKeyDown);

		if (rec.EventType == KEY_EVENT) {
			if (rec.Event.KeyEvent.bKeyDown) {
				switch (rec.Event.KeyEvent.wVirtualKeyCode) {

				case VK_RETURN:
					return; break;

				case VK_ESCAPE:
					keyboard_menu(); break;
				default:
					system("cls");
					printf("\n\tНажмите ENTER, чтобы начать");
					FlushConsoleInputBuffer(s_in);
					Sleep(800);
					break;
				}
			}
		}

		else continue;
	}
}


char* get_string(int* len) {

	setbuf(stdin, NULL);

	*len = 0; // изначально строка пуста
	int capacity = 1; // ёмкость контейнера динамической строки (1, так как точно будет '\0')
	char* s = (char*)malloc(sizeof(char)); // динамическая пустая строка

	char c = getchar(); // символ для чтения данных

	// читаем символы, пока не получим символ переноса строки (\n)
	while (c != '\n') {
		s[(*len)++] = c; // заносим в строку новый символ

		// если реальный размер больше размера контейнера, то увеличим его размер
		if (*len >= capacity) {
			capacity *= 2; // увеличиваем ёмкость строки в два раза
			s = (char*)realloc(s, capacity * sizeof(char)); // создаём новую строку с увеличенной ёмкостью  
		}

		c = getchar(); // считываем следующий символ          
	}

	s[*len] = '\0'; // завершаем строку символом конца строки

	return s; // возвращаем указатель на считанную строку
}
void byblik()
{
	while (true) {
		system("cls");
		float A = 0, B = 0;
		float i, j;
		int k;
		float z[1760];
		char b[1760];
		printf("\x1b[2J");
		while (true)
		{
			memset(b, 32, 1760);
			memset(z, 0, 7040);
			for (j = 0; j < 6.28; j += 0.07)
			{
				for (i = 0; i < 6.28; i += 0.02)
				{
					float c = sin(i);
					float d = cos(j);
					float e = sin(A);
					float f = sin(j);
					float g = cos(A);
					float h = d + 2;
					float D = 1 / (c * h * e + f * g + 5);
					float l = cos(i);
					float m = cos(B);
					float n = sin(B);
					float t = c * h * g - f * e;
					int x = 40 + 30 * D * (l * h * m - t * n);
					int y = 12 + 15 * D * (l * h * n + t * m);
					int o = x + 80 * y;
					int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
					if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o])
					{
						z[o] = D;
						b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
					}
				}
			}
			printf("\x1b[H");
			for (k = 0; k < 1761; k++)
			{
				putchar(k % 80 ? b[k] : 10);
				A += 0.00004;
				B += 0.00002;
			}
			Sleep(10);
			GoToXY(0, 0);
			if (_kbhit()) {
				char code = _getch();
				if (code == 27) {
					menu(); // Проверяем, нажата ли клавиша Esc
					break; // Выходим из цикла и возвращаемся в главное меню
				}
			}
		}
	}
}
			
			




double symb_per_min(double res_time, int len) {

	double time_min = res_time / (double)60;
	double symb_per_min = (double)(len / time_min);
	return symb_per_min;
}


void countdown() {
	for (int i = 0; i < 3; i++) {
		printf(".");
		Sleep(500);
	}
	printf("\n");
}


void k_nums() {

	char number_str[10];
	int number = 0, size = 0, len_ans;
	srand(time(NULL));

	interrupt("Ввод чисел");
	system("cls");


	printf("Введите количество чисел для ввода, после начнется отсчет времени: ");
	scanf("%d", &size);

	if (size > 0) {

		char* current;
		current = (char*)malloc(6 * (size + 1));

		int pos = 0;
		for (int i = 0; i < size; i++) {
			number = rand() % 99999 + 10000;
			sprintf(number_str, "%d ", number);

			for (int j = 0; j < 6; j++) {
				current[pos] = number_str[j];
				pos++;
			}
		}


		current[(size * 6) - 1] = '\0';

		countdown();

		time_t t1 = clock();

		printf("Введите:\n%s\n", current);

		char* ans = get_string(&len_ans);

		time_t t2 = clock();


		double res_time = (double)(t2 - t1) / (double)CLOCKS_PER_SEC;

		printf("\nПотраченное время: %.3f секунд", res_time);

		int incorrect = 0;

		for (int i = 0; i < strlen(current); i++) {
			if (current[i] != ans[i]) incorrect++;
		}

		if (len_ans > strlen(current)) incorrect += (int)(len_ans - strlen(current));

		double spm = symb_per_min(res_time, len_ans);
		printf("\nКоличество ошибок: %d. Символов в минуту: %f", incorrect, spm);

		free(current);
	}

	to_keyboard_menu();

}
struct Writer {
	char name[100];
	char country[100];
	char years[100];
	char fame[100];
};
int ToWriters() {
	setlocale(LC_ALL, "RUS");
	system("chcp 1251");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	Writer writers[100];
	WORD active = FOREGROUND_INTENSITY | FOREGROUND_RED;
	WORD nactive = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle(L"Справочник музыкантов");
	setlocale(LC_ALL, "RUS");
	char code;
	int position = 0;
	system("cls");
	do {
		string menu[]{ "\n\n\n\t\t\t\t\tПоказать список\n","\t\t\t\t\tПоиск\n","\t\t\t\t\tДобавить исполнителя\n","\t\t\t\t\tВыход" };
		while (true) {
			system("cls");
			for (int i = 0; i < 4; i++) {
				if (i == position)
					SetConsoleTextAttribute(handle, active);
				else
					SetConsoleTextAttribute(handle, nactive);
				cout << menu[i] << endl;
			}
			code = _getch();
			if (code == 72) {
				position = (position + 3) % 4;
			}
			if (code == 80) {
				position = (position + 1) % 4;
			}
			system("cls");
			int counter = 1;
			Writer newWriter;
			bool found;
			FILE* f1;
			f1 = fopen("W.txt", "r");
			if (code == 13) {
				switch (position) {
				case 0:

					system("cls");
					f1 = fopen("W.txt", "r");

					cout << "---------------------------------------------------------------------------------------------" << endl;
					cout << "| " << setw(6) << left << "№" << "| "
						<< setw(18) << left << "Исполнитель" << "| "
						<< setw(15) << left << "Страна" << "| "
						<< setw(10) << left << "Год славы" << "| "
						<< setw(33) << left << "Популярный альбом" << "|" << endl;
					cout << "---------------------------------------------------------------------------------------------" << endl;

					

					for (int i = 0; i < 100 && !feof(f1); i++)
					{
						fscanf(f1, "%[^;];%[^;];%[^;];%[^\n]\n", writers[i].name, writers[i].country, writers[i].years, writers[i].fame);
						cout << "| " << setw(6) << left << counter << "| "
							<< setw(18) << left << writers[i].name << "| "
							<< setw(15) << left << writers[i].country << "| "
							<< setw(10) << left << writers[i].years << "| "
							<< setw(33) << left << writers[i].fame << "|" << endl;
						cout << "---------------------------------------------------------------------------------------------" << endl;
						counter++;
					}

					fclose(f1);

					_getch();
					break;

				case 1:
					system("cls");
					f1 = fopen("W.txt", "r");
					char search[50];
					cout << "Enter the writer: ";
					cin.getline(search, sizeof(search));
					found = false;
					for (int i = 0; i < 100 && !feof(f1); i++) {
						if (strcmp(writers[i].name, search) == 0) {
							printf("Artist:\n");
							printf("Name: %s\n", writers[i].name);
							printf("Country: %s\n", writers[i].country);
							printf("Years of popular: %s\n", writers[i].years);
							printf("popular albom: %s\n", writers[i].fame);
							printf("---------------------------\n");
							found = true;
							break;
						}
					}
					if (!found) {
						printf("Writer is not found.\n");
					}
					fclose(f1);
					_getch();
					break;
				case 2:
					system("cls");
					f1 = fopen("W.txt", "a");

					cout << "Enter the name of the artist: ";
					cin >> ws;
					cin.getline(newWriter.name, sizeof(newWriter.name));

					cout << "Enter the name of country: ";
					cin >> ws;
					cin.getline(newWriter.country, sizeof(newWriter.country));

					cout << "popular year: ";
					cin >> ws;
					cin.getline(newWriter.years, sizeof(newWriter.years));

					cout << "popular albom: ";
					cin >> ws;
					cin.getline(newWriter.fame, sizeof(newWriter.fame));

					fprintf(f1, "%s;%s;%s;%s\n", newWriter.name, newWriter.country, newWriter.years, newWriter.fame);
					fclose(f1);

					cout << "Artist name added!\n";;
					_getch();
					break;

				case 3:
					SetConsoleTextAttribute(hStdOut, 7);
					return 0;
					break;
				}
			}
			if (code == 27) {
				fclose(f1); // Закрываем файл перед выходом из программы
				break;
			}
		}
	} while (true);
	
}
void k_letters() {

	SetConsoleCP(1251);

	srand(time(NULL));

	interrupt("Ввод букв");
	system("cls");

	int size, len_ans;

	printf("Введите количество букв для ввода, после начнется отсчет времени: ");
	scanf("%d", &size);


	if (size > 0) {

		int* current;
		current = (int*)malloc(sizeof(int) * 2 * (size)-1);

		for (int i = 0; i < ((size * 2) - 1); i += 2) {
			current[i] = (193 + (rand() % (255 - 193)));
			if (i != (size * 2) - 2) current[i + 1] = 32;
		}

		countdown();

		time_t t1 = clock();

		printf("Введите:\n");

		for (int i = 0; i < (size * 2) - 1; i++) {
			printf("%c", (unsigned char)current[i]);

		}

		printf("\n");
		char* ans = get_string(&len_ans);

		time_t t2 = clock();


		double res_time = (double)(t2 - t1) / (double)CLOCKS_PER_SEC;

		printf("\nПотраченное время: %.3f секунд", res_time);

		int incorrect = 0;

		for (int i = 0; i < (size * 2) - 1; i++) {
			if ((unsigned char)current[i] != (unsigned char)ans[i]) incorrect++;

		}

		if (len_ans > ((size * 2) - 1)) incorrect += (int)(len_ans - ((size * 2) - 1));
		double spm = symb_per_min(res_time, len_ans);
		printf("\nКоличество ошибок: %d. Символов в минуту: %f", incorrect, spm);

		free(current);
	}

	to_keyboard_menu();


}

void k_words() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(time(NULL));

	interrupt("Ввод слов");
	system("cls");

	FILE* f;
	f = fopen("words.txt", "r");


	int size, len_ans = 0, word_cnt = 0, max_word_len = 0;
	char str[200];
	printf("Введите количество слов для ввода, после начнется отсчет времени: ");
	scanf("%d", &size);

	while (fscanf(f, "%s", str) == 1) word_cnt++;


	if (size > word_cnt) {
		printf("Превышено допустимое количество слов");
		to_keyboard_menu();
	}
	else if (size == 0) {
		printf("Количество слов не может быть равно нулю");
		to_keyboard_menu();

	}

	else {

		char s[200];

		rewind(f);


		for (int i = 0; i < word_cnt; i++) {
			fscanf(f, "%s", s);
			if (strlen(s) > max_word_len) max_word_len = strlen(s);
		}

		char* current;
		current = (char*)malloc(max_word_len * (size - 1) + (max_word_len - 1));

		int pos = 0;

		for (int i = 0; i < size; i++) {

			char s[200];

			rewind(f);

			int rand_pos = rand() % (word_cnt)+1;
			for (int k = 0; k < rand_pos; k++) fscanf(f, "%s", s);

			for (int j = 0; j < strlen(s); j++) {
				current[pos] = s[j];
				pos++;
			}

			if (i != (size - 1)) { current[pos] = 32; pos++; }


		}

		current[pos + 1] = '\0';

		fclose(f);

		countdown();

		time_t t1 = clock();

		printf("\nВведите: \n");

		for (int i = 0; i < pos; i++) {
			printf("%c", (unsigned char)current[i]);
		}

		printf("\n");
		char* ans = get_string(&len_ans);

		time_t t2 = clock();

		double res_time = (double)(t2 - t1) / (double)CLOCKS_PER_SEC;

		printf("\nПотраченное время: %.3f секунд", res_time);

		int incorrect = 0;

		for (int i = 0; i < pos; i++) {
			if ((unsigned char)current[i] != (unsigned char)ans[i]) incorrect++;

		}

		if (len_ans > pos) incorrect += (int)(len_ans - pos);
		double spm = symb_per_min(res_time, len_ans);
		printf("\nКоличество ошибок: %d. Символов в минуту: %f", incorrect, spm);

		free(current);

		to_keyboard_menu();

	}






}

void k_phrases() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(time(NULL));

	interrupt("Ввод фраз");
	system("cls");

	FILE* f;
	f = fopen("phrases.txt", "r");


	int len_ans = 0, phr_cnt = 0;

	char str[500];

	while (!feof(f)) {

		if (fgetc(f) == '\n') {
			phr_cnt++;
		}
	}

	rewind(f);

	int rand_pos = rand() % (phr_cnt)+1;

	for (int i = 0; i < rand_pos; i++) fgets(str, 500, f);

	fclose(f);


	printf("После нажатия ENTER начнется отсчет времени для ввода строки");
	char a = _getch();
	if (a == 13) countdown();
	else keyboard_menu();

	time_t t1 = clock();

	printf("\nВведите: \n");

	for (int i = 0; i < strlen(str); i++) {
		printf("%c", str[i]);
	}

	str[strlen(str) - 1] = '\0';

	char* ans = get_string(&len_ans);

	time_t t2 = clock();


	double res_time = (double)(t2 - t1) / (double)CLOCKS_PER_SEC;

	printf("\nПотраченное время: %.3f секунд", res_time);

	int incorrect = 0;

	for (int i = 0; i < strlen(str); i++) {
		if ((unsigned char)str[i] != (unsigned char)ans[i]) incorrect++;
	}

	if (len_ans > strlen(str)) incorrect += (int)(len_ans - strlen(str));
	double spm = symb_per_min(res_time, len_ans);
	printf("\nКоличество ошибок: %d. Символов в минуту: %f", incorrect, spm);

	to_keyboard_menu();

}


void menu() {

	int k = 0;

	HANDLE s_in = GetStdHandle(STD_INPUT_HANDLE);
	DWORD dr;
	INPUT_RECORD rec;

	char vars[][200] = { "1. Сведения об авторе", "2. Работа с клавиатурой", "3. Посмотреть заставку","4. справочник музыканты"};



	while (true)
	{

		system("cls");

		for (int i = 1; i < 10; i++) {
			printf("\n");
		}
		printf("\t\t\t\t\t\tВыберите значение меню:\n\n");
		for (int i = 0; i < (sizeof(vars) / sizeof(vars[0])); i++) {
			for (int h = 0; h < 14; h++) printf(" ");
			if (k == i) printf("\t\t\t\t\t%s [*]\n", vars[i]);
			else printf("\t\t\t\t\t%s\n", vars[i]);
		}

		do {
			ReadConsoleInput(s_in, &rec, 1, &dr);
		} while (rec.EventType == KEY_EVENT && !rec.Event.KeyEvent.bKeyDown);

		if (rec.EventType == KEY_EVENT) {
			if (rec.Event.KeyEvent.bKeyDown) {
				switch (rec.Event.KeyEvent.wVirtualKeyCode) {

				case VK_UP:
					if (k >= 0) k--;
					if (k < 0) k = ((sizeof(vars) / sizeof(vars[0])) - 1);

					break;

				case VK_DOWN:
					if (k <= ((sizeof(vars) / sizeof(vars[0])) - 1)) k++;
					if (k == ((sizeof(vars) / sizeof(vars[0])))) k = 0;
					break;


				case VK_RETURN:
					switch (k) {
					case 0: system("cls"); about(); break;
					case 1: system("cls"); keyboard_menu(); break;
					case 2: system("cls"); SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); byblik(); break; 
					case 3:system("cls"); ToWriters(); break;
					}

					break;

				case VK_ESCAPE:

					system("cls");
					printf("Выйти? Нажмите ESC повторно\nВернуться в меню? Нажмите любую клавишу...");

					do {
						ReadConsoleInput(s_in, &rec, 1, &dr);
						FlushConsoleInputBuffer(s_in);
					} while (rec.EventType == KEY_EVENT && !rec.Event.KeyEvent.bKeyDown);

					if (rec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) exit(0);
					else break;

					break;


				default:
					system("cls");
					printf("Используйте стрелки ВВЕРХ и ВНИЗ для выбора в меню");
					FlushConsoleInputBuffer(s_in);
					Sleep(800);
					break;
				}
			}
		}

		else continue;
	}
}


void keyboard_menu() {


	int k = 0;

	HANDLE s_in = GetStdHandle(STD_INPUT_HANDLE);
	DWORD dr;
	INPUT_RECORD rec;

	char vars[][200] = { "1. Числа", "2. Буквы", "3. Слова", "4. Фразы" };



	while (true)
	{

		system("cls");

		for (int i = 1; i < 10; i++) {
			printf("\n");
		}
		printf("\t\t\t\t\t\tВыберите значение меню:\n\n");
		for (int i = 0; i < (sizeof(vars) / sizeof(vars[0])); i++) {
			for (int h = 0; h < 14; h++) printf(" ");
			if (k == i) printf("\t\t\t\t\t\t%s [*]\n", vars[i]);
			else printf("\t\t\t\t\t\t%s\n", vars[i]);
		}

		do {
			ReadConsoleInput(s_in, &rec, 1, &dr);
		} while (rec.EventType == KEY_EVENT && !rec.Event.KeyEvent.bKeyDown);

		if (rec.EventType == KEY_EVENT) {
			if (rec.Event.KeyEvent.bKeyDown) {
				switch (rec.Event.KeyEvent.wVirtualKeyCode) {

				case VK_UP:
					if (k >= 0) k--;
					if (k < 0) k = ((sizeof(vars) / sizeof(vars[0])) - 1);

					break;

				case VK_DOWN:
					if (k <= ((sizeof(vars) / sizeof(vars[0])) - 1)) k++;
					if (k == ((sizeof(vars) / sizeof(vars[0])))) k = 0;
					break;


				case VK_RETURN:
					switch (k) {
					case 0: system("cls"); k_nums(); break;
					case 1: system("cls"); k_letters(); break;
					case 2: system("cls"); k_words(); break;
					case 3: system("cls"); k_phrases(); break;
					}

					break;

				case VK_ESCAPE:
					menu();
					break;

				default:
					system("cls");
					printf("Используйте стрелки ВВЕРХ и ВНИЗ для выбора в меню");
					FlushConsoleInputBuffer(s_in);
					Sleep(800);
					break;
				}
			}
		}

		else continue;
	}

}


int main()
{
	ConsoleCursorVisible(false, 100);
	bool dev_mode = false;

	rus
		if (!dev_mode) {
			intro();
			menu();
		}
		else menu();
	return 0;
}
