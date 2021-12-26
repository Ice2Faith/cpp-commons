#ifndef _I2F_ROUTE_H_
#define _I2F_ROUTE_H_
#include"../container/ArrayList.hpp"
#include"../container/Matrix2.hpp"

class RouteResult;
class Step;

class Route 
{
public:
	/*
	������Ӿ���map,����������sp���յ�ep
	ʹ�����·���㷨���ó�·�ɽ����RouteResult������
	������Ӿ���Ϊ��
	mtx={
	//a b c d e
	{0,1,0,1,0}, //a
	{0,0,1,0,0}, //b
	{0,0,0,1,1}, //c
	{0,1,0,0,0}, //d
	{0,0,1,0,0}  //e
	}
	���룺
	sp=0,ep=4,map=mtx
	�ͱ�ʾ��A�㿪ʼ����·�ɵ�E���Ƿ�ɴ�ɴ���õ�·��
	*/
	static RouteResult route(int sp, int ep, Matrix2<int> map);

};

class RouteResult {
public:
	bool isPass;
	List<int>& route= ArrayList<int>();
	RouteResult()
	{

	}
};

class Step {
public:
	int pre;
	int loc;
	Step(){

	}
	Step(int pre, int loc){
		this->pre = pre;
		this->loc = loc;
	}
};

RouteResult Route::route(int sp, int ep, Matrix2<int> map) {
	RouteResult ret;
	ret.isPass = false;
	Step p(-1, sp);
	List<Step>& queue =  ArrayList<Step>();
	queue.add(p);
	int cp = 0;
	while (true){
		if (cp >= queue.size()){
			ret.isPass = false;
			break;
		}
		p = queue.get(cp);
		if (p.loc == ep){
			ret.isPass = true;
			Stack<int>& routes = ArrayList<int>();
			while (true){
				routes.push(p.loc);
				if (p.pre == -1){
					break;
				}
				p = queue.get(p.pre);
			}
			ret.route = ArrayList<int>();
			while (!routes.isEmpty()){
				ret.route.add(routes.pop());
			}
			break;
		}
		Array<int> nextRoutes = map.row(p.loc);
		for (int i = 0; i<nextRoutes.size(); i += 1){
			if (nextRoutes[i] == 1){
				Step np;
				np.loc = i;
				np.pre = cp;
				queue.add(np);
			}
		}
		cp++;
	}
	return ret;
}

#endif // _I2F_ROUTE_H_
