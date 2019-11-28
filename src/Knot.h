/*
 * Knot.h
 *
 *  Created on: 5 дек. 2018 г.
 *      Author: dmitrii
 */

#ifndef KNOT_H_
#define KNOT_H_
#include <iostream>
#include <list>
#include <vector>
using namespace std;

template <typename Keyvalue>
class Data;


template <typename Keyvalue>
class Node
{
	int am_notes;
	int power;
	list <Data<Keyvalue>* > content;

public:
	Node(int power_d)
	{
		power=power_d;
		am_notes=0;
	}
	Node(int power_d, list<Data<Keyvalue> > cont)
	{
		power=power_d;
		am_notes=0;
		content=cont;
	}
	~Node()
	{

	}

	void del_full()
	{
		for(auto x=content.begin(); x!=content.end();x++)
		{
			if((*x)->link!=nullptr)
				(*x)->link->del_full();
			delete(*x);
		}
		delete(this);
	}
	void write_node()const
	{
		for(auto &x : content)
		{
			cout<<x->key<<" ";
		}
		//cout<<"       "<<am_notes<<endl;
		cout<<endl;
	};

	void write_node_l()const
	{
		for(auto &x : content)
		{
			cout<<x->key<<" ";
		}
	};

	void write_node_in_arr(vector<Keyvalue>* vec)const
	{
		for(auto &x : content)
		{
			vec->push_back(x->key);
		}
	};


	Data<Keyvalue>* find_coffin()const
	{
		for(auto iter = content.begin();iter!=content.end();iter++)
		{
			if((*iter)->is_deleted==true)
			{
				return *(iter);
			}
		}
		return nullptr;
	}

	Node* find_child(Keyvalue value)const
	{
		auto iter=content.begin();
		iter++;
		for(;iter!=content.end();iter++)
		{
			if(value<(*iter)->key)
			{
				return(*(--iter))->link;
			}
		}
		return (*(--iter))->link;

	}

	Data<Keyvalue>* find_child_data(Keyvalue value)const
	{
		auto iter=content.begin();
		iter++;
		for(;iter!=content.end();iter++)
		{
			if(value<(*iter)->key)
			{
				return *(--iter);
			}
		}
		return *(--iter);

	}

	Data<Keyvalue>* find_child_data_next(Keyvalue value)const
	{
		auto iter=content.begin();
		iter++;
		for(;iter!=content.end();iter++)
		{
			if(value<(*iter)->key)
			{
				return *(iter);
			}
		}
		return nullptr;
	}


	//finds the previous data in the list to data with this value
	Data<Keyvalue>* find_child_data_prev(Keyvalue value)const
	{
		auto iter=content.begin();
		iter++;
		for(;iter!=content.end();iter++)
		{
			if(value<(*iter)->key)
			{
				if(iter==++content.begin())
				{
					return nullptr;
				}
				else
				{
					return *(--(--iter));
				}
			}
		}
		if(--iter!=content.begin())
		{
			return *((--iter));
		}
		return nullptr;
	}

	//write to begin of list
	void sign(Data<Keyvalue>* x)
	{
		am_notes++;
		content.push_front(*x);
	}


	//returns pointer to data if signed first
	void sign_right(Data<Keyvalue>* x)
	{

		am_notes++;
		for(auto iter=content.begin();iter!=content.end();iter++)
		{
			if(x->key<(*iter)->key)
			{
				if(x->link==nullptr)
				if(iter==content.begin())
				{
					if(content.size()!=0)
					{
						x->neibhor_l=content.front()->neibhor_l;
						content.front()->neibhor_l=nullptr;
						//if(x->neibhor_l!=nullptr)
							//x->neibhor_l->neibhor_r=x;
					}
				}
				content.insert(iter,x);
				return;
			}
		}

		if(x->link==nullptr)
		{
			if(content.size()!=0)
			{
				x->neibhor_r=content.back()->neibhor_r;
				content.back()->neibhor_r=nullptr;
				//if(x->neibhor_r!=NULL)
					//x->neibhor_r->neibhor_l=x;
			}
		}
		content.push_back(x);
	}


	//separates overloaded node, returns one half
	//another half stays in the node
	Node* separate()
	{
		Node* nnew = new Node(power);
		auto iter  = content.end();
		iter--;
		for(int i=0;i<power;i++)
		{
			iter = content.end();
			iter--;
			nnew->sign_right(*iter);

			if(iter==content.begin())
				break;
			iter--;
			content.pop_back();
		}
		nnew->am_notes = power;
		am_notes -= power;

		nnew->content.front()->neibhor_l=content.back();
		content.back()->neibhor_r=nnew->content.front();
		return nnew;
	}

	list<Data<Keyvalue>* > get_content()const
	{
		return content;
	}

	list<Data<Keyvalue>* >* get_content_ref()
	{
		return &content;
	}

	void set_am_notes(int am)const
	{
		am_notes=am;
	}

	int get_am_child()const
	{
		int sum=0;
		for (auto &x : content)
		{
			if (x->link!=nullptr)
				sum++;
		}
		return sum;
	}

	int get_am_notes()const
	{
		return am_notes;
	}

	//no memory cleaning
	void del_data(Data<Keyvalue>* ths_d)
	{
		Keyvalue key = ths_d->key;
		auto iter=content.begin();
		for(;iter!=content.end();iter++)
		{
			if((*iter)->key==key)
			{
				if((*iter)->link==nullptr)
				if((*iter)->neibhor_r!=nullptr)
				{
					if(iter!=content.begin())
					{
						//(*iter)->neibhor_r->neibhor_l=(*prev(iter));
						//(*prev(iter))=(*iter)->neibhor_r;
					}
				}

				if((*iter)->link==nullptr)
				if((*iter)->neibhor_l!=nullptr)
				{
					if(iter!=prev(content.end()))
					{
						//(*iter)->neibhor_l->neibhor_r=(*next(iter));
						//(*next(iter))=(*iter)->neibhor_l;
					}
				}
				content.erase(iter);
				am_notes--;
				return;
			}
		}
	}

	//0 - fix completed, 1 fix impossible
	//use from the ancestor of for_com
	int try_to_fix(Node<Keyvalue>* for_com,Keyvalue value)
	{

		if(for_com==nullptr)
		{
			cout<<"wrong fix behavior"<<endl;
			return 1;
		}

		Keyvalue key;
		if(for_com->content.size()==0)
		{
			key=value;
		}
		else
		{
			key=for_com->content.front()->key;
		}


		Data<Keyvalue>* next = find_child_data_next(key);
		if(next!=nullptr)
		{
			if(next->link!=nullptr)
			{
				if(next->link->am_notes > power)
				{
					if(next->link->content.size()!=0)
					{
						for_com->sign_right(next->link->content.front());

						next->link->content.pop_front();
						next->link->am_notes--;
						if(next->link->content.size()!=0)
							next->key=next->link->content.front()->key;
						//cout<<"    fix    "<<endl;
						return 0;
					}
				}
			}
			else
			{
				cout<<"wrong fix behavior fix_1"<<endl;
			}
		}
		Data<Keyvalue>* prev = find_child_data_prev(key);
		if(prev!=nullptr)
		{
			if(prev->link!=nullptr)
			{
				if(prev->link->am_notes > power)
				{
					//donor is the data with for_com
					Data<Keyvalue>* donor=find_child_data(key);
					if(prev->link->content.size()!=0)
					{
						for_com->sign_right(prev->link->content.back());

						prev->link->content.pop_back();
						prev->link->am_notes--;

						if(donor->link->content.size()!=0)
							donor->key = donor->link->content.front()->key;
						//cout<<"    fix"<<endl;
						return 0;
					}
				}
			}
			else
			{
				cout<<"wrong fix behavior fix_2"<<endl;
			}

		}
		return 1;
	}


	//0 - fix completed, 1 fix impossible
	//use from the ancestor of for_com
	int try_to_fix_l(Node<Keyvalue>* for_com, Keyvalue value)
	{
		while((for_com->get_am_notes()<power)&&(try_to_fix(for_com,value)==0))	{	};
		if (for_com->get_am_notes()<power)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

//1 combination failed, 0 combination succeeded
	int combine(Node<Keyvalue>* for_com, Keyvalue value)
	{
		if(for_com==nullptr)
		{
			cout<<"wrong combine behavior 1";
			return 1;
		}
		Keyvalue key;
		if(for_com->content.size()==0)
		{
			key=value;
		}
		else
		{
			key=for_com->content.front()->key;
		}

		Data<Keyvalue>* next_d = find_child_data_next(key);

		if((next_d!=nullptr)&&(next_d->link!=nullptr))
		{
			for(auto x : next_d->link->content)
			{
				for_com->content.push_back(x);
				for_com->am_notes++;
			}


			delete(next_d->link);
			del_data(next_d);
			delete(next_d);
			return 0;
		}

		Data<Keyvalue>* prev_d = find_child_data_prev(key);
		if((prev_d!=nullptr)&&(prev_d->link!=nullptr))
		{

			if(prev_d->link->content.size()==0)
			{
				return 1;
			}
			auto x=prev_d->link->content.end();
			x--;
			for(;x!=prev_d->link->content.begin();x--)
			{
				for_com->content.push_front(*x);
				for_com->am_notes++;
			}
			for_com->content.push_front(prev_d->link->content.front());
			for_com->am_notes++;

			delete(prev_d->link);
			del_data(prev_d);
			delete(prev_d);

			return 0;
		}
		return 1;
	}

	int combine_l(Node<Keyvalue>* for_com, Keyvalue value)
	{
		while((for_com->get_am_notes()<power)&&(combine(for_com,value)==0))	{	};
		if (for_com->get_am_notes()<power)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}


	//1 - fix not completed; 0 - fix completed
	int fix_children()
	{
		for(auto iter = content.begin();iter != content.end();iter++)
		{
			if(content.size()==0)
				return 0;
			if((*iter)->link->get_am_notes()<power)
			{
				if(try_to_fix_l((*iter)->link, (*iter)->key))
				{
					combine_l((*iter)->link, (*iter)->key);
				}
				return 1;
			}
		}
		return 0;
	}
};

template <typename Keyvalue>
bool operator<(const Data<Keyvalue>& fst, const Data<Keyvalue>& snd)
{
	return fst.key < snd.key;
}

template <typename Keyvalue>
bool operator==(const Node<Keyvalue>& fst, const Node<Keyvalue>& snd)
{
	return fst.get_content()==snd.get_content();
}

//supportive class
template <typename Keyvalue>
class Data
{
public:
	Keyvalue key;
	Node<Keyvalue>* link;
	Data<Keyvalue>* neibhor_r;
	Data<Keyvalue>* neibhor_l;
	bool is_deleted;

	~Data(){};

	Data(Keyvalue kkey,Node<Keyvalue>* node)
	{
		link=node;
		key=kkey;
		neibhor_r=nullptr;
		neibhor_l=nullptr;
		is_deleted=false;
	};

	bool get_is_del()
	{
		return is_deleted;
	}
	void set_del()
	{
		is_deleted=true;
	}

	void set_del_false()
	{
		is_deleted=false;
	}

};

#endif /* KNOT_H_ */
















