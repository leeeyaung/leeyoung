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
	string car_number;     //车牌号
	int hour;              //到达的时间
	int minute;
	int second;
};
typedef struct stack       //定义顺序栈
{
	struct car T[MAX_SIZE];
	int top;
}st;
typedef struct sequence    //定义队节点
{
	struct car C[MAX_SIZE];
	struct sequence* next;
}node;
typedef struct linksequen  //定义链队
{
	node* front, * rear;
}sequen;
void creat_satck(stack& s){		//初始化一个顺序栈
	s.top = -1;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		s.T[i].car_number = "KONG";
	}
}
void creat_queue(sequen* se) {	//初始化一个链队
	se->front = se->rear = new node;
	if (!(se->front))
		cout << "error" << endl;
	else
		se->front->next = NULL;
}      
bool stack_isempty(stack& s) {	//判断栈是否为空
	if (s.top == -1)
		return true;
	else
		return false;
}
bool stack_isfull(stack& s) {	//判断栈是否为满
	if (s.top == MAX_SIZE - 1)
		return true;
	else
		return false;
}     
void push_stack(stack& s,string car_number, int hour, int minute, int second) {	//入栈
	if (stack_isfull(s)){
		cout << "停车场已满" << endl;
		return;
	}
	s.top++;
	s.T[s.top].car_number = car_number;
	s.T[s.top].hour = hour;
	s.T[s.top].minute = minute;
	s.T[s.top].second = second;
}
void pop_stack(stack& s, string&car_number,int& hour, int& minute, int& second) {	//出栈  
	if (stack_isempty(s)) {
		cout<<"停车场已空" << endl;               
		return;
	}
	car_number = s.T[s.top].car_number;
	s.T[s.top].car_number = "KONG";
	hour = s.T[s.top].hour;
	minute = s.T[s.top].minute;
	second = s.T[s.top].second;
	s.top--;
}
bool queue_isempty(sequen*se) {	//判断队是否为空
	if (se->front==se->rear)
		return true;
	else return false;
}
void push_queue(sequen* se,string car_number,int hour,int minute,int second){    //入队
	node* p = new node;
	p->C->car_number = car_number;                
	p->C->hour = hour;
	p->C->minute = minute;
	p->C->second = second;
	p->next = NULL;
	se->rear->next = p;
	se->rear = p;
}
string pop_queue(sequen* se) {	 //出队
	node* qs;
	string temp;
	if (queue_isempty(se))
	{
		cout << "队空" << endl;
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
void park_car(sequen *se,stack &s,string car_number,int hour,int minute,int second) {			//停车函数
	if (!stack_isfull(s)) {
		push_stack(s, car_number, hour, minute, second);                              //若停车场（栈）未满，则停入停车场（栈）
		cout<<"找到车位，" <<car_number<<"车已停入停车场" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	}
	else
	{
		push_queue(se, car_number, hour, minute, second);                             //若停车场（栈）已满，则停入便道（队）
		cout << "停车场已满，"<<car_number<<"车已停入便道" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	}
	}
void fpark_car(sequen* se, stack& s, string car_number, int hour, int minute, int second) {			//停车函数
	if (!stack_isfull(s)) {
		push_stack(s, car_number, hour, minute, second);                              //若停车场（栈）未满，则停入停车场（栈）
	}
	else
	{
		push_queue(se, car_number, hour, minute, second);                             //若停车场（栈）已满，则停入便道（队）
	}
}
void accounts(int start_hour, int start_minute, int start_second, int end_hour, int end_minute, int end_second) {           //算钱函数
	cout << "您停入停车场的时间是：" << start_hour << ":" << start_minute << ":" << start_second << endl;
	cout << "您离开停车场的时间是: " << end_hour << ":" << end_minute << ":" << end_second << endl;
	double money=0;
	if (start_hour < end_hour) {
		money = ((end_hour*1.0 - start_hour) * 60.0 + (end_minute - start_minute)) * 0.03;
		cout << "您需要支付" << money << "元" << endl;
	}
	else if (start_hour > end_hour) {
		money = ((24.0 + end_hour - start_hour) * 60.0 + (end_minute - start_minute))*0.03;
		cout << "您需要支付" << money << "元" << endl;
	}
	else
	{
			cout << "未停满一小时，不收费" << endl;
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "                                       欢迎下次光临" << endl;
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
void evacuate_car(sequen* se, stack& s, string car_number, int hour, int minute, int second) {     //取车函数
	stack temp;                                              //定义一个暂时存放让路的车的栈
	creat_satck(temp);                                       //初始化该栈
	string tempn;
	int temph, tempm, temps;
	if (!in_stack(s,car_number) && !in_queue(se,car_number))
	{
		cout << "没有在停车场和便道上找到您的车" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		return;
	}
	else if (!in_stack(s, car_number) && in_queue(se, car_number))
	{
		cout << "您的车停在便道上，此次停车不收费" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "                                       欢迎下次光临" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		return;
	}
	else if (in_stack(s, car_number) && !in_queue(se, car_number)) {
		while (car_number != s.T[s.top].car_number)              //从顶向低（从停车场南向北）遍历停车场（栈）内的车
		{
			pop_stack(s, tempn, temph, tempm, temps);            //不是目标的车均让出停车场
			push_stack(temp, tempn, temph, tempm, temps);        //停入暂时的栈
			cout << tempn << "已经挪出" << endl;
		}
		pop_stack(s, tempn, temph, tempm, temps);                //取出停车场最外（栈顶）的目标车辆
		accounts(temph, tempm, temps, hour, minute, second);     //计算所需价钱
		while (!stack_isempty(temp))
		{
			pop_stack(temp, tempn, temph, tempm, temps);         //将暂时的栈中的车出栈
			push_stack(s, tempn, temph, tempm, temps);           //停入停车场（栈）
		}
		if (!queue_isempty(se))                                  //如果便道上还有车
		{
			tempn = pop_queue(se);                                 //将其开出便道（出队）
			push_stack(s, tempn, hour, minute, second);          //停入停车场，由于在便道上不收费，因此取车的时间应为便道上的车停车的开始时间
			cout << tempn << "已经由便道停入停车场内，" << endl;
			cout << "停入时间为：" << hour << ":" << minute << ":" << second << endl;
		}
	}
}
void show_car(stack &s) {
	cout << endl;
	cout << "目前停车场车辆如下：" << endl;
	cout << endl;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (s.T[i].car_number == "KONG")
		{
			cout << "|| 空车位" ;
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
		cout << "                                        便道上未停车" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		return;
	}
	cout << endl;
	cout << "目前便道车辆如下：" << endl;
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
		cout << "没有在停车场和便道上找到您的车" << endl;
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
				cout << "您的车目前在便道上排第" << place << "的位置" << endl;
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
				cout << "您的车在停车场的第" << i + 1 << "个车位" << endl;
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				return;
			}
		}
	}
}
void Open2Read(string fn)//读方式打开文件
{
	myFile1.clear(); //清空文件
	myFile1.open(fn.c_str(), ios::in); //读打开，文件必须存在
	if (!myFile1) //打开有误
	{
		cout << "请检查目录及文件名!\n";
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
	string fn1 = "C:\\Users\\李爷爷\\source\\repos\\sujg_keshe\\sujg_keshe\\myFile1.txt";
	Open2Read(fn1); //读打开文件
	cout << "****************************************************************************************************" << endl;
	cout << "*****************************************欢迎光临停车场*********************************************" << endl;
	cout << "****************************************************************************************************" << endl;
	cout << "输入相应指令：1--停车；2--取车；3--查找车辆；4--查看停车场实时车辆；5--查看便道实时车辆；6--关闭系统" << endl;
	while(myFile1.peek()!=EOF) {
			myFile1 >> car_number >> hour >> minute >> second;
			if (car_number == "#")break;
			fpark_car(se, s, car_number, hour, minute, second);
	} 
	show_car(s);
	show_car(se);
	while (1)
	{
		cout << "请输入指令" << endl;
		cout << "----------------------------------------------------------------------------------------------------" << endl;
		cin >> operate;
		if (operate == 1)
		{
			cout<< "请依次输入车牌号，停车的时间" << endl;
			cin >> car_number >> hour >> minute >> second;
			park_car(se, s, car_number, hour, minute, second);
			show_car(s);
		}
		else if (operate == 2)
		{
			cout << "请依次输入车牌号，取车的时间" << endl;
			cin >> car_number >> hour >> minute >> second;
			evacuate_car(se, s, car_number, hour, minute, second);
			show_car(s);
		}
		else if (operate == 3)
		{
			cout << "请输入您要找的车的车牌号" << endl;
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
			cout << "系统已关闭" << endl;
			exit(0);
		}
		else
		{
			cout << "输入的指令有误，请重新输入" << endl;
		}
	}
	myFile1.close(); //文件用完必须关闭
	return 0;
}
