	// tests.cpp
#include "/home/dmitrii/eclipse-workspace/b+Trees/src/Tree.h"
#include <gtest/gtest.h>
#include <algorithm>
 
TEST(insert1, PositiveNos) {

	Tree<int>* f = new Tree<int>(nullptr,2);


	f->write_tree();
	f->insert(1);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(6);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(8);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(10);
	cout<<"insert"<<endl;
	f->write_tree();

	f->insert(11);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(-6);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(89);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(3);
	cout<<"insert"<<endl;
	f->write_tree();

	cout<<"lists "<<endl;
	f->write_lists();
	cout<<"find"<<endl;
	if(f->find(11)!=nullptr)
	{
		f->find(11)->write_node();
	}
	delete(f);
}
 

TEST(delete_size3_1, PositiveNos) {
	Tree<int>* f = new Tree<int>(nullptr,3);
	f->write_tree();
	f->insert(2);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(10);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(3);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(4);
	cout<<"insert"<<endl;
	f->write_tree();

	f->insert(6);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(7);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(9);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(12);
	cout<<"insert"<<endl;
	f->write_tree();

	f->delete_node(2);
	cout<<"delete"<<endl;
	f->write_tree();
	delete(f);
}

 
TEST(delete_unexist_and_the_same, PositiveNos) {
	Tree<int>* f = new Tree<int>(nullptr,3);
	f->write_tree();
	f->insert(2);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(10);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(3);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(4);
	cout<<"insert"<<endl;
	f->write_tree();

	f->insert(6);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(7);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(9);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(12);
	cout<<"insert"<<endl;
	f->write_tree();

	f->delete_node(2);
	cout<<"delete"<<endl;
	f->write_tree();
	f->delete_node(6);
	cout<<"delete"<<endl;
	f->write_tree();
	f->delete_node(7);
	cout<<"delete"<<endl;
	f->write_tree();
	f->delete_node(8);
	cout<<"delete"<<endl;
	f->write_tree();
	f->delete_node(6);
	cout<<"delete"<<endl;
	f->write_tree();
	f->delete_node(3);
	cout<<"delete"<<endl;
	f->write_tree();
	f->delete_node(0);
	cout<<"delete"<<endl;
	f->write_tree();
	delete(f);

}


TEST(delete_full, PositiveNos) {
	Tree<int>* f = new Tree<int>(nullptr,2);
	f->write_tree();
	f->insert(2);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(10);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(3);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(4);
	cout<<"insert"<<endl;
	f->write_tree();

	f->insert(6);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(7);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(9);
	cout<<"insert"<<endl;
	f->write_tree();
	f->insert(12);
	cout<<"insert"<<endl;
	f->write_tree();

	f->delete_node(2);
	cout<<"delete"<<endl;
	f->write_tree();
	f->delete_node(6);
	cout<<"delete"<<endl;
	f->write_tree();
	f->delete_node(7);
	cout<<"delete"<<endl;
	f->write_tree();
	f->delete_node(9);
	cout<<"delete"<<endl;
	f->write_tree();
	f->delete_node(6);
	cout<<"delete"<<endl;
	f->write_tree();
	f->delete_node(3);
	cout<<"delete"<<endl;
	f->write_tree();
	f->delete_node(4);
	cout<<"delete"<<endl;
	f->write_tree();
	f->delete_node(10);
	cout<<"delete"<<endl;
	f->write_tree();
	f->delete_node(12);
	cout<<"delete"<<endl;
	f->write_tree();
	delete(f);

}


TEST(delete_for_attention, PositiveNos) {
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
	delete(f);
}



TEST(Tree_power_7, PositiveNos) {
	Tree<int>* f = new Tree<int>(nullptr,7);

	for(int i = 0;i<35;i++)
	{
		f->insert(i);
	}

	vector<int>* ths=f->write_tree_in_arr();
	sort(ths->begin(),ths->end());
	vector<int>* exp=new vector<int>;
	for(int i=0;i<35;i++)
	{
		exp->push_back(i);
	}


	ASSERT_EQ(*exp==*ths,true);
	delete(f);
	delete(exp);
	delete(ths);

}

TEST(Tree_power_5_del, PositiveNos) {
	Tree<int>* f = new Tree<int>(nullptr,5);

	vector<int>* exp=new vector<int>;

	for(int i = 0;i<35;i++)
	{
		f->insert(i);
		exp->push_back(i);
	}

	for(int i = 8;i<29;i+=2)
	{
		f->delete_node(i);
		for_tests::del_from_vec(*exp,i);
	}

	sort(exp->begin(),exp->end());
	vector<int>* ths=f->write_tree_in_arr();
	sort(ths->begin(),ths->end());
	ASSERT_EQ(*exp==*ths,true);
	delete(ths);
	delete(exp);
	delete(f);

}

TEST(mix_vec, Pos)
{
	srand(time(nullptr));
	vector<int> a;
	for(int i=0;i<10;i++)
	{
		a.push_back(i);
	}
	for(int i=0;i<100;i++)
	{
		for_tests::change_pos(a);
	}
	for_tests::write_vec(a);
}

TEST(mix_ins, Pos)
{
	srand(time(nullptr));

	Tree<int>* f = new Tree<int>(nullptr,2);


	vector<int>* exp=new vector<int>;
	vector<int> a;
	for(int i=0;i<1000;i++)
	{
		a.push_back(i);
		exp->push_back(a[i]);
	}
	for(int i=0;i<1000;i++)
	{
		for_tests::change_pos(a);
	}

	for(int i = 0;i<1000;i++)
	{
		f->insert(a[i]);
	}
	//f->write_tree();

	for(int i=0;i<1000;i++)
	{
		for_tests::change_pos(a);
	}
	for(int i = 0;i<998;i++)
	{
		f->delete_node(a[i]);
		for_tests::del_from_vec(*exp,a[i]);
	}

	vector<int>* ths=f->write_tree_in_arr();
	sort(ths->begin(),ths->end());
	sort(exp->begin(),exp->end());
	ASSERT_EQ(*exp==*ths,true);

	delete(ths);
	delete(exp);

	delete(f);
}


TEST(mix_ins_pow_6, Pos)
{
	srand(time(nullptr));

	Tree<int>* f = new Tree<int>(nullptr,6);


	vector<int>* exp=new vector<int>;
	vector<int> a;
	for(int i=0;i<1000;i++)
	{
		a.push_back(i);
		exp->push_back(a[i]);
	}
	for(int i=0;i<1000;i++)
	{
		for_tests::change_pos(a);
	}

	for(int i = 0;i<1000;i++)
	{
		f->insert(a[i]);
	}
	//f->write_tree();

	for(int i=0;i<1000;i++)
	{
		for_tests::change_pos(a);
	}
	for(int i = 0;i<998;i++)
	{
		f->delete_node(a[i]);
		for_tests::del_from_vec(*exp,a[i]);
	}

	vector<int>* ths=f->write_tree_in_arr();
	sort(ths->begin(),ths->end());
	sort(exp->begin(),exp->end());
	ASSERT_EQ(*exp==*ths,true);

	delete(ths);
	delete(exp);

	delete(f);
}

TEST(ins_del_ins_del, Pos)
{
	srand(time(nullptr));

	Tree<int>* f = new Tree<int>(nullptr,4);

	vector<int> a;
	vector<int>* exp=new vector<int>;

	for(int i=0;i<1000;i++)
	{
		a.push_back(i);
	}
	for(int i=0;i<1000;i++)
	{
		for_tests::change_pos(a);
	}

	for(int i = 0;i<500;i++)
	{
		f->insert(a[i]);
		exp->push_back(a[i]);
	}


	for(int i=0;i<1000;i++)
	{
		for_tests::change_pos(a);
	}
	for(int i = 0;i<500;i++)
	{
		f->delete_node(a[i]);
		for_tests::del_from_vec(*exp,a[i]);
	}

	for(int i=0;i<1000;i++)
	{
		for_tests::change_pos(a);
	}

	for(int i = 0;i<500;i++)
	{
		f->insert(a[i]);
		if(!for_tests::find(*exp,a[i]))
			exp->push_back(a[i]);
	}

	for(int i=0;i<1000;i++)
	{
		for_tests::change_pos(a);
	}
	for(int i = 0;i<500;i++)
	{
		f->delete_node(a[i]);
		for_tests::del_from_vec(*exp,a[i]);
	}


	vector<int>* ths=f->write_tree_in_arr();
	sort(ths->begin(),ths->end());
	sort(exp->begin(),exp->end());
	ASSERT_EQ(*exp==*ths,true);

	delete(ths);
	delete(exp);
	delete(f);
}

TEST(into_arr, Pos)
{
	srand(time(nullptr));

	Tree<int>* f = new Tree<int>(nullptr,6);

	vector<int> a;
	for(int i=0;i<1000;i++)
	{
		a.push_back(i);
	}
	for(int i=0;i<1000;i++)
	{
		for_tests::change_pos(a);
	}

	for(int i = 0;i<1000;i++)
	{
		f->insert(a[i]);
	}

	vector<int>* ths=f->write_tree_in_arr();
	sort(ths->begin(),ths->end());
	vector<int> exp;
	for(int i=0;i<1000;i++)
	{
		exp.push_back(i);
	}

	ASSERT_EQ(exp,*ths);
	delete(f);
	delete(ths);
}


TEST(insert_lazy, PositiveNos) {

	Tree<int>* f = new Tree<int>(nullptr,3);


	f->insert(1);
	f->insert(6);
	f->insert(8);
	f->insert(10);
	f->insert(11);
	f->insert(-6);
	f->insert(89);
	f->insert(3);

	f->lazy_delete(89);
	f->lazy_delete(-6);
	f->write_tree();

	f->lazy_insert(4);
	f->write_tree();
	delete(f);
}

TEST(insert_lazy2, PositiveNos) {

	Tree<int>* f = new Tree<int>(nullptr,2);


	f->insert(1);
	f->insert(6);
	f->insert(8);
	f->insert(10);
	f->insert(11);
	f->insert(-6);
	f->insert(89);
	f->insert(3);
	f->insert(5);
	f->insert(2);
	f->insert(22);
	f->insert(-89);
	f->insert(33);

	f->write_tree();
	f->lazy_delete(89);
	f->lazy_delete(-6);
	f->lazy_delete(11);
	f->lazy_delete(10);
	f->lazy_delete(8);
	f->lazy_delete(6);

	f->lazy_insert(4);
	f->lazy_insert(41);
	f->lazy_insert(-23);
	f->lazy_insert(12);
	f->write_tree();
	delete(f);
}


TEST(delete_lazy_fix1, PositiveNos) {

	Tree<int>* f = new Tree<int>(nullptr,2);
	f->insert(1);
	f->insert(6);
	f->insert(8);
	f->insert(10);
	f->insert(11);
	f->insert(-6);
	f->insert(89);
	f->insert(3);
	f->insert(5);
	f->insert(2);
	f->insert(22);
	f->insert(-89);
	f->insert(33);

	f->write_tree();

	cout<<endl<<"  after delete  "<<endl;

	f->lazy_delete(89);
	f->lazy_delete(-6);
	f->lazy_delete(11);
	f->lazy_delete(10);
	f->lazy_delete(8);
	f->lazy_delete(6);


	f->throw_coffins();
	f->write_tree();
	delete(f);
}


TEST(delete_lazy_fix2	, PositiveNos) {

	Tree<int>* f = new Tree<int>(nullptr,2);
	f->insert(1);
	f->insert(6);
	f->insert(8);
	f->insert(10);
	f->insert(11);
	f->insert(-6);
	f->insert(89);
	f->insert(3);
	f->insert(5);
	f->insert(2);
	f->insert(22);
	f->insert(-89);
	f->insert(33);

	f->write_tree();

	cout<<endl<<"  after delete  "<<endl;

	f->lazy_delete(89);
	f->lazy_delete(-6);
	f->lazy_delete(11);
	f->lazy_delete(10);
	f->lazy_delete(8);
	f->lazy_delete(6);

	f->lazy_fix();
	f->write_tree();
	delete(f);
}

TEST(write_test, PositiveNos) {

	Tree<int>* f = new Tree<int>(nullptr,2);

	f->insert(5);
	f->insert(7);
	f->insert(4);
	f->insert(3);
	f->insert(6);
	f->insert(18);
	f->insert(8);
	f->insert(1);

	f->write_tree();

	delete(f);
}

TEST(fun1, Pos)
{
	srand(time(nullptr));

	Tree<int>* f = new Tree<int>(nullptr,2);

	vector<int> a;
	for(int i=0;i<1000;i++)
	{
		a.push_back(i);
	}
	for(int i=0;i<10000;i++)
	{
		for_tests::change_pos(a);
	}

	for(int i = 0;i<1000;i++)
	{
		f->insert(a[i]);
	}

	f->write_tree();
	delete(f);

}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
