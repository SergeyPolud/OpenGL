#include <iostream>
#include <conio.h>
#include <iomanip>
#include <cstdlib>
#include <math.h>

using namespace std;

int In(const char* text)
{
	int res;
	cout << text;
	while (!(cin >> res) || cin.get() != '\n')
	{
		cout << "Ошибка, введите целое число" << endl;
		cin.clear();
		while (cin.get() != '\n');
	}
	return res;
}

struct Queue
{
	int info;
	Queue* next;
	Queue* prev;
};

void Create(Queue** b, Queue** e, int in)
{
	Queue* t = new Queue;
	t->info = in;
	t->prev = NULL;
	t->next = NULL;
	*b = *e = t;
}

void Push(int kod1, Queue** b, Queue** e, int in)
{
	Queue* t = new Queue;
	t->info = in;
	if (kod1 == 0)
	{
		t->prev = NULL;
		t->next = *b;
		(*b)->prev = t;
		*b = t;
	}
	else
	{
		t->next = NULL;
		t->prev = *e;
		(*e)->next = t;
		*e = t;
	}
}

void Peek(int kod1, Queue* t)
{

	Queue* tmp = t;
	while (tmp!=nullptr)
	{
		cout << tmp->info << " ";
		if (kod1 == 0)
		{
			tmp = tmp->next;
		}
		else
		{
			tmp = tmp->prev;
		}

	}
}

void Del(Queue*& b)
{
	Queue* t = NULL;
	while (b)
	{
		t = b;
		b = b->next;
		delete t;
	}
}



void Task(Queue*& b, Queue*& e)
{
	Queue* max = b;
	Queue* current = b;
	for (; current; current = current->next)
	{
		if (current->info > max->info)
		{
			max = current;
		}
	}
	cout << "Максимальное: " << max->info << endl;
	if (max == b)
	{
		b = b->next;
		b->prev = NULL;
		delete max;
	}
	else if (max == e)
	{
		e = e->prev;
		e->next = NULL;
		delete max;
	}
	else
	{
		Queue* temp;
		temp = max;
		temp->prev->next = max->next;
		temp->next->prev = max->prev;
		delete max;
	}
}


int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "rus");
	Queue* begin = NULL;
	Queue* end = NULL;
	int in, kod = 0, kod1;
	while (true)
	{
		cout << "\n\tСоздать - 1\n\tДобавить - 2\n\tПросмотреть - 3\n\tЗадание - 4\n\tУдалить - 5\n\tВыход - 0 : ";
		kod = In("");
		switch (kod)
		{
		case 1:
			if (begin != NULL)
			{
				cout << "Очистите память!" << endl;
				break;
			}
			in = In("Элемент очереди = ");
			Create(&begin, &end, in);
			cout << "Создать в начале :" << begin->info << endl;
			break;
		case 2:
			if (begin == NULL)
			{
				cout << "\nСоздайте стек!" << endl;
				break;
			}
			in = In("Элемент очереди = ");
			cout << "Добавить в начало - 0, Добавить в конец - 1 : ";
			kod1 = In("");
			Push(kod1, &begin, &end, in);
			if (kod1 == 0)
				cout << begin->info << " добавлено в начало" << endl;
			else
				cout << end->info << " добавлено в конец" << endl;
			break;
		case 3:
			if (!begin)
			{
				cout << "Очередь пустая!" << endl;
				break;
			}
			cout << "— Начало —" << endl;
			Peek(0, begin);
			cout << "\n— Конец —" << endl;
			Peek(1, end);
			break;
		case 4:
			if (!begin)
			{
				cout << "Очередь пустая!" << endl;
				break;
			}
			else
			{
				Task(begin, end);
			}
			break;
		case 5:
			Del(begin);

			cout << "Память освободилась!" << endl;
			break;
		case 0: default:
			if (begin != NULL)
				Del(begin);
			return 0;
		}
	}
	delete begin;
	delete end;
}