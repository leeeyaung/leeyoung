#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<fstream>
using namespace std;
#define MAX_SIZE 50
ifstream myFile1; 
struct car
{
	string car_number;     //���ƺ�
	int hour;              //�����ʱ��
	int minute;
	int second;
};
typedef struct stack       //����˳��ջ
{
	struct car T[MAX_SIZE];
	int top;
}st;
typedef struct sequence    //����ӽڵ�
{
	struct car C[MAX_SIZE];
	struct sequence* next;
}node;
typedef struct linksequen  //��������
{
	node* front, * rear;
}sequen;
void creat_satck(stack& s){		//��ʼ��һ��˳��ջ
	s.top = -1;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		s.T[i].car_number = "KONG";
	}
}
void creat_queue(sequen* se) {	//��ʼ��һ������
	se->front = se->rear = new node;
	if (!(se->front))
		cout << "error" << endl;
	else
		se->front->next = NULL;
}      
bool stack_isempty(stack& s) {	//�ж�ջ�Ƿ�Ϊ��
	if (s.top == -1)
		return true;
	else
		return false;
}
bool stack_isfull(stack& s) {	//�ж�ջ�Ƿ�Ϊ��
	if (s.top == MAX_SIZE - 1)
		return true;
	else
		return false;
}     
void push_stack(stack& s,string car_number, int hour, int minute, int second) {	//��ջ
	if (stack_isfull(s)){
		cout << "ͣ��������" << endl;
		return;
	}
	s.top++;
	s.T[s.top].car_number = car_number;
	s.T[s.top].hour = hour;
	s.T[s.top].minute = minute;
	s.T[s.top].second = second;
}
void pop_stack(stack& s, string&car_number,int& hour, int& minute, int& second) {	//��ջ  
	if (stack_isempty(s)) {
		cout<<"ͣ�����ѿ�" << endl;               
		return;
	}
	car_number = s.T[s.top].car_number;
	s.T[s.top].car_number = "KONG";
	hour = s.T[s.top].hour;
	minute = s.T[s.top].minute;
	second = s.T[s.top].second;
	s.top--;
}
bool queue_isempty(sequen*se) {	//�ж϶��Ƿ�Ϊ��
	if (se->front==se->rear)
		return true;
	else return false;
}
void push_queue(sequen* se,string car_number,int hour,int minute,int second){    //���
	node* p = new node;
	p->C->car_number = car_number;                
	p->C->hour = hour;
	p->C->minute = minute;
	p->C->second = second;
	p->next = NULL;
	se->rear->next = p;
	se->rear = p;
}
string pop_queue(sequen* se) {	 //����
	node* qs;
	string temp;
	if (queue_isempty(se))
	{
		cout << "�ӿ�" << endl;
		return 0;
	}
	else
	{
		qs = se->front->next;
		temp = qs->C->car_number;
		se->front->next = qs->next;
		if (se->rear == qs) {
			se->rear = se->front;
		}
		delete qs;
		return temp;
	}

}      
void park_car(sequen *se,stack &s,string car_number,int hour,int minute,int second) {			//ͣ������
	if (!stack_isfull(s)) {
		push_stack(s, car_number, hour, minute, second);                              //��ͣ������ջ��δ������ͣ��ͣ������ջ��
		cout<<"�ҵ���λ��" <<car_number<<"����ͣ��ͣ����" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	}
	else
	{
		push_queue(se, car_number, hour, minute, second);                             //��ͣ������ջ����������ͣ�������ӣ�
		cout << "ͣ����������"<<car_number<<"����ͣ����" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	}
	}
void fpark_car(sequen* se, stack& s, string car_number, int hour, int minute, int second) {			//ͣ������
	if (!stack_isfull(s)) {
		push_stack(s, car_number, hour, minute, second);                              //��ͣ������ջ��δ������ͣ��ͣ������ջ��
	}
	else
	{
		push_queue(se, car_number, hour, minute, second);                             //��ͣ������ջ����������ͣ�������ӣ�
	}
}
void accounts(int start_hour, int start_minute, int start_second, int end_hour, int end_minute, int end_second) {           //��Ǯ����
	cout << "��ͣ��ͣ������ʱ���ǣ�" << start_hour << ":" << start_minute << ":" << start_second << endl;
	cout << "���뿪ͣ������ʱ����: " << end_hour << ":" << end_minute << ":" << end_second << endl;
	double money=0;
	if (start_hour < end_hour) {
		money = ((end_hour*1.0 - start_hour) * 60.0 + (end_minute - start_minute)) * 0.03;
		cout << "����Ҫ֧��" << money << "Ԫ" << endl;
	}
	else if (start_hour > end_hour) {
		money = ((24.0 + end_hour - start_hour) * 60.0 + (end_minute - start_minute))*0.03;
		cout << "����Ҫ֧��" << money << "Ԫ" << endl;
	}
	else
	{
			cout << "δͣ��һСʱ�����շ�" << endl;
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "                                       ��ӭ�´ι���" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

}
bool in_stack(stack& s, string car_number) {
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (s.T[i].car_number == car_number)
			return true;
	}
	return false;
}
bool in_queue(sequen* se, string car_number) {
	node* p = new node;
	p = se->front->next;
	while (p!=NULL)
	{
		if (p->C->car_number == car_number)
			return true;
		p = p->next;
	}
	return false;
}
void evacuate_car(sequen* se, stack& s, string car_number, int hour, int minute, int second) {     //ȡ������
	stack temp;                                              //����һ����ʱ�����·�ĳ���ջ
	creat_satck(temp);                                       //��ʼ����ջ
	string tempn;
	int temph, tempm, temps;
	if (!in_stack(s,car_number) && !in_queue(se,car_number))
	{
		cout << "û����ͣ�����ͱ�����ҵ����ĳ�" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		return;
	}
	else if (!in_stack(s, car_number) && in_queue(se, car_number))
	{
		cout << "���ĳ�ͣ�ڱ���ϣ��˴�ͣ�����շ�" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "                                       ��ӭ�´ι���" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		return;
	}
	else if (in_stack(s, car_number) && !in_queue(se, car_number)) {
		while (car_number != s.T[s.top].car_number)              //�Ӷ���ͣ���ͣ�������򱱣�����ͣ������ջ���ڵĳ�
		{
			pop_stack(s, tempn, temph, tempm, temps);            //����Ŀ��ĳ����ó�ͣ����
			push_stack(temp, tempn, temph, tempm, temps);        //ͣ����ʱ��ջ
			cout << tempn << "�Ѿ�Ų��" << endl;
		}
		pop_stack(s, tempn, temph, tempm, temps);                //ȡ��ͣ�������⣨ջ������Ŀ�공��
		accounts(temph, tempm, temps, hour, minute, second);     //���������Ǯ
		while (!stack_isempty(temp))
		{
			pop_stack(temp, tempn, temph, tempm, temps);         //����ʱ��ջ�еĳ���ջ
			push_stack(s, tempn, temph, tempm, temps);           //ͣ��ͣ������ջ��
		}
		if (!queue_isempty(se))                                  //�������ϻ��г�
		{
			tempn = pop_queue(se);                                 //���俪����������ӣ�
			push_stack(s, tempn, hour, minute, second);          //ͣ��ͣ�����������ڱ���ϲ��շѣ����ȡ����ʱ��ӦΪ����ϵĳ�ͣ���Ŀ�ʼʱ��
			cout << tempn << "�Ѿ��ɱ��ͣ��ͣ�����ڣ�" << endl;
			cout << "ͣ��ʱ��Ϊ��" << hour << ":" << minute << ":" << second << endl;
		}
	}
}
void show_car(stack &s) {
	cout << endl;
	cout << "Ŀǰͣ�����������£�" << endl;
	cout << endl;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (s.T[i].car_number == "KONG")
		{
			cout << "|| �ճ�λ" ;
			continue;
		}
		cout <<"|| " << s.T[i].car_number<<" ";
	}
	cout << "||" << endl;
	cout << endl;
}
void show_car(sequen *se) {
	node* p = new node;
	p = se->front->next;
	if (queue_isempty(se))
	{
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "                                        �����δͣ��" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		return;
	}
	cout << endl;
	cout << "Ŀǰ����������£�" << endl;
	cout << endl;
	while (p != NULL)
	{
		cout << "|| " << p->C->car_number<<" ";
		p = p->next;
	}
	cout << "||" << endl;
	cout << endl;
}
void search_car(sequen* se, stack &s,string car_number ) {
	if (!in_stack(s, car_number) && !in_queue(se, car_number))
	{
		cout << "û����ͣ�����ͱ�����ҵ����ĳ�" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		return;
	}
	else if (!in_stack(s, car_number) && in_queue(se, car_number))
	{
		node* p = new node;
		p = se->front->next;
		int place = 1;
		while (p != NULL)
		{
			if (p->C->car_number == car_number) {
				cout << "���ĳ�Ŀǰ�ڱ�����ŵ�" << place << "��λ��" << endl;
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				return;
			}
			p = p->next;
			place++;
		}
	}
	else if (in_stack(s, car_number) && !in_queue(se, car_number))
	{
		for (int i = 0; i < MAX_SIZE; i++)
		{
			if (s.T[i].car_number == car_number)
			{
				cout << "���ĳ���ͣ�����ĵ�" << i + 1 << "����λ" << endl;
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				return;
			}
		}
	}
}
void Open2Read(string fn)//����ʽ���ļ�
{
	myFile1.clear(); //����ļ�
	myFile1.open(fn.c_str(), ios::in); //���򿪣��ļ��������
	if (!myFile1) //������
	{
		cout << "����Ŀ¼���ļ���!\n";
	}
}
int main() {
	stack s;
	sequen* se = new sequen;
	creat_satck(s);
	creat_queue(se);
	string car_number;
	int operate;
	int hour, minute, second;
	string fn1 = "C:\\Users\\��үү\\source\\repos\\sujg_keshe\\sujg_keshe\\myFile1.txt";
	Open2Read(fn1); //�����ļ�
	cout << "****************************************************************************************************" << endl;
	cout << "*****************************************��ӭ����ͣ����*********************************************" << endl;
	cout << "****************************************************************************************************" << endl;
	cout << "������Ӧָ�1--ͣ����2--ȡ����3--���ҳ�����4--�鿴ͣ����ʵʱ������5--�鿴���ʵʱ������6--�ر�ϵͳ" << endl;
	while(myFile1.peek()!=EOF) {
			myFile1 >> car_number >> hour >> minute >> second;
			if (car_number == "#")break;
			fpark_car(se, s, car_number, hour, minute, second);
	} 
	show_car(s);
	show_car(se);
	while (1)
	{
		cout << "������ָ��" << endl;
		cout << "----------------------------------------------------------------------------------------------------" << endl;
		cin >> operate;
		if (operate == 1)
		{
			cout<< "���������복�ƺţ�ͣ����ʱ��" << endl;
			cin >> car_number >> hour >> minute >> second;
			park_car(se, s, car_number, hour, minute, second);
			show_car(s);
		}
		else if (operate == 2)
		{
			cout << "���������복�ƺţ�ȡ����ʱ��" << endl;
			cin >> car_number >> hour >> minute >> second;
			evacuate_car(se, s, car_number, hour, minute, second);
			show_car(s);
		}
		else if (operate == 3)
		{
			cout << "��������Ҫ�ҵĳ��ĳ��ƺ�" << endl;
			cin >> car_number;
			search_car(se, s, car_number);
		}
		else if(operate == 4)
		{
			show_car(s);
		}
		else if (operate == 5)
		{
			show_car(se);
		}
		else if (operate == 6)
		{
			cout << "ϵͳ�ѹر�" << endl;
			exit(0);
		}
		else
		{
			cout << "�����ָ����������������" << endl;
		}
	}
	myFile1.close(); //�ļ��������ر�
	return 0;
}
