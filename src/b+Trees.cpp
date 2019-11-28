//============================================================================
// Name        : b+Trees.cpp
// Author      : dmitrii
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Knot.h"
#include "Tree.h"
using namespace std;

int main() {


/*
	Node<int>* a=new Node<int>(2);
	Node<int>* b=new Node<int>(2);
	Node<int>* c=new Node<int>(2);


	Data<int>* aa=new Data<int>(0,a) ;
	Data<int>* bb=new Data<int>(5,b) ;

	Data<int>* cc=new Data<int>(2,nullptr) ;
	Data<int>* dd=new Data<int>(5,nullptr) ;


		a->sign_right(*cc);
	b->sign_right(*dd);

	c->sign_right(*aa);
	c->sign_right(*bb);
*/

	Tree<int>* f = new Tree<int>(nullptr,3);

	f->insert(3);
	f->insert(4);
	f->insert(6);
	f->insert(8);
	f->insert(10);
	f->insert(12);

	f->write_tree();
	cout<<"delete"<<endl;
	f->delete_node(8);
	f->write_tree();




	cout<<endl<<endl<<endl<<endl<<endl;

	delete(f);
	return 0;
}
