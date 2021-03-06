//This project is for making LRU Cache, Made by Hyunwoo,KOH DKU software Engineering, trghyunwoo@gmail.com

#include "pch.h"
#include <iostream>
using namespace std;
class Page {
	friend class Double_Linked_List;
private:
	int value;
	Page* pre;
	Page* next;
public:
	Page(int n) { value = n; next = pre = NULL; }
};
class Double_Linked_List{
	friend class LRU_Cache;
private:
	Page* head;
	Page* tail;
public:
	Double_Linked_List() { head = tail = NULL; }
	bool Is_Empty();
	void Add_Page(int value);
	void Move_page(Page *pg);
	void Remove_page();
	int Get_tail();
	Page* Find_page(int value);
};
class LRU_Cache
{
private:
	int size, capacity;
	Double_Linked_List *PageList;
public:
	LRU_Cache(int capacity) { this->capacity = capacity; size = 0; PageList = new Double_Linked_List(); }
	void Push(int value);
};
bool Double_Linked_List::Is_Empty()
{
	return tail == NULL;
}
void Double_Linked_List::Add_Page(int value)
{
	Page *pg = new Page(value);

	if (!head && !tail)
		head = tail = pg;
	else
	{
		pg->next = head;
		head->pre = pg;
		head = pg;
	}
	return;
}
void Double_Linked_List::Move_page(Page *pg)
{
	if (pg == head) return;
	else if(pg == tail)
	{
		tail = pg->pre;
		tail->next = NULL;
	}
	else
	{
		pg->pre->next = pg->next;
		pg->next->pre = pg->pre;
	}
	pg->next = head;
	head->pre = pg;
	head = pg;
	return;
}
void Double_Linked_List::Remove_page()
{
	if (Is_Empty()) return; //빈 경우에는 바로 return 시킴
	
	if (head == tail)
	{
		delete tail;
		head = tail = NULL;
	}
	else
	{
		Page *delpg = tail;
		tail = tail->pre;
		tail->next = NULL;
		delete delpg;
	}
	return;
}
int Double_Linked_List::Get_tail()
{
	return tail->value;
}
Page* Double_Linked_List::Find_page(int value)
{
	if (Is_Empty()) return NULL;
	if (head->value == value) return head;
	
	Page *fnpg = head->next;
	while (fnpg)
	{
		if (fnpg->value == value) return fnpg;
		fnpg = fnpg->next;
	}
	return NULL;
}
void LRU_Cache::Push(int value)
{
	Page *pg = PageList->Find_page(value);
	if (pg)
	{
		PageList->Move_page(pg);
		return;
	}
	
	if (size == capacity)
	{
		int Remove_page_num = PageList->Get_tail();
		cout << "Remove Page Number : " << Remove_page_num << endl;
		PageList->Remove_page();
		size--;
	}
	PageList->Add_Page(value);
	size++;
	return;
}
int main(int argc, char* argv[])
{
	int c_size, access;
	int *arr_order;
	cout << "Insert Cache size : ";
	cin >> c_size;

	LRU_Cache My_Cache(c_size);
	cout << "Input 0(zero) to finish!\n";
	for (int i = 0; 1 ; i++)
	{
		cout << "Input " << i + 1 << "access : ";
		cin >> access;
		if (!access) break;
		My_Cache.Push(access);
	}
	return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
