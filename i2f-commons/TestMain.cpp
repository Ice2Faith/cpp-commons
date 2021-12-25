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