#include<stdio.h>
#include"i2f\commons\base\Base.hpp"
#include"i2f\commons\container\MultiList.h"
#include"i2f\commons\container\ArrayList.hpp"
#include"i2f\commons\interface\IExecutor.h"
#include"i2f\commons\container\LinkList.hpp"
#include"i2f\commons\container\Array.hpp"
#include"i2f\commons\interface\impl\PrintExecutor.hpp"
#include"i2f\commons\algorithm\Function.hpp"
#include"i2f\commons\interface\impl\DefaultComparator.hpp"
#include"i2f\commons\container\Matrix2.hpp"
#include"i2f\commons\graphics\g2d\g2d.h"
#include"i2f\commons\graphics\g3d\g3d.h"
#include"i2f\commons\algorithm\Route.hpp"

void showList(IIterable<Base<int>>& list)
{
	list.each(PrintExecutor<Base<int>>(",%d"));
	printf("\n");
}

LinkList<Base<int>> getList()
{
	LinkList<Base<int>> ret;
	for (int i = 1; i < 20; i += i){
		ret.add((Base<int>)i);
	}
	return ret;
}


int main()
{

	int map[][5] = {
		//a b c d e
		{ 0, 1, 0, 1, 0 }, //a
		{ 0, 0, 1, 0, 0 }, //b
		{ 0, 0, 0, 1, 1 }, //c
		{ 0, 1, 0, 0, 0 }, //d
		{ 0, 0, 1, 0, 0 }  //e
	};
	char* mapDict[] = { "A", "B", "C", "D", "E" };
	Matrix2<int> mtxp((int *)map, 5, 5);
	for (int i = 0; i < mtxp.height(); i++){
		for (int j = 0; j < mtxp.width(); j++){
			printf("%d,", mtxp.get(j, i));
		}
		printf("\n");
	}
	//A->E
	RouteResult result = Route::route(0, 4, mtxp);
	printf("A->E可达性：%d\n" , result.isPass);
	if (result.isPass){
		printf("可达最少经过：%d\n" , (result.route.size() - 2));
		printf("可达最短路径为：");
		for (int i = 0; i < result.route.size(); i++)
		{
			int item = result.route.get(i);
			printf("->%s" ,mapDict[item]);
		}
	}

	PointI p21(1, 2);
	PointI p22(1, 7);
	PointD3 p31(1.0, 2.0, 3.0);
	PointD3 p32(4.0, 2.6, 7.0);

	LineI l2(p21, p22);
	LineD3 l3(p31, p32);

	int len2 = l2.distance();
	double len3 = l3.distance();

	Matrix2<int> mtx(10, 5);
	for (int i = 0; i < mtx.width(); i++){
		for (int j = 0; j < mtx.height(); j++){
			mtx.set(i,j, i*10+j);
		}
	}

	for (int i = 0; i < mtx.height(); i++){
		for (int j = 0; j < mtx.width(); j++){
			printf("%d,", mtx.get(j,i));
		}
		printf("\n");
	}

	Array<int> row = mtx.row(1);
	for (int i = 0; i < row.size(); i++){
		printf("%d,", row.get(i));
	}
	printf("\n");

	Array<int> col = mtx.col(1);
	for (int i = 0; i < col.size(); i++){
		printf("%d,", col.get(i));
	}
	printf("\n");


	Integer adv = 1 + Integer(2);
	adv = Integer(2) + 1;
	adv = 1 + 2;
	adv = Integer(1) + Base<int>(2);
	int i = 1;
	i += adv;

	bool rs = (1 == Integer(1)) && (Integer(1) == 1) && (Integer(1) == Integer(1));

	Byte ch = (byte)(int)(Integer)5<<2;

	LinkList<Base<int>> rcvlist = getList();
	showList(rcvlist);
	rcvlist.head2Tail();
	showList(rcvlist);
	rcvlist.tail2Head();
	showList(rcvlist);
	rcvlist.swapHeadTail();
	showList(rcvlist);

	int min=Function::min(rcvlist, DefaultComparator<Base<int>>());
	int max = Function::max(rcvlist, DefaultComparator<Base<int>>());
	int avg = Function::avg(rcvlist);
	int sum = Function::sum(rcvlist);

	Array<int> arr1(20);
	for (int i = 0; i < arr1.size(); i++){
		arr1[i] = i;
		arr1.set(i,i);
	}
	//showList(arr1);

	LinkList<Base<int>>& list = LinkList<Base<int>>();
	
	for (int i = 0; i < 10; i++){
		list.add((Base<int>)i);
	}

	LinkList<Base<int>> cplist = list;
	showList(cplist);

	ListIterator<Base<int>>* it = list.iterator();
	while (it->hasNext()){
		int val = it->get();
		printf("=>%d", val);
		if (val % 2){
			it->remove();
		}
		else{
			it->insert((Base<int>)99);
			it->next();
		}
		
	}
	printf("\n");

	showList(list);
	while (list.size()>5){
		int rv=list.remove(0);
		showList(list);
	}
	list.set(-1, (Base<int>)-1);
	showList(list);
	list.insert(0, (Base<int>)0);
	showList(list);
	list.clear();
	showList(list);

	Base<int> arr[] = { 1, 3, 5, 7, 9 };
	List<Base<int>>& list2 = LinkList<Base<int>>();
	list2.addAll(arr, sizeof(arr) / sizeof(arr[0]));
	showList(list2);

	list.addAll(list2, 2, -1);
	showList(list);

	int fst=list.removeFirst();
	showList(list);
	int lst=list.removeLast();
	showList(list);

	list.addFirst((Base<int>)11);
	showList(list);
	list.addLast((Base<int>)22);
	showList(list);

	list.enque((Base<int>)99);
	showList(list);
	int dq=list.deque();
	showList(list);

	int hd=list.head();
	showList(list);

	int tl=list.tail();
	showList(list);

	list.push((Base<int>)88);
	showList(list);
	int tp=list.top();
	showList(list);

	int pp=list.pop();
	showList(list);

	while (!list.isEmpty()){
		pp=list.pop();
		showList(list);
	}
	showList(list);
	getchar();
	return 0;
}