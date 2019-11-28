/*
 * Tree.h
 *
 *  Created on: 5 дек. 2018 г.
 *      Author: dmitrii
 */

#ifndef TREE_H_
#define TREE_H_
#include "Knot.h"
#include "fortests.h"

template<typename Keyvalue>
class Tree {
public:
	Node<Keyvalue>* root;
	int power;

public:
	Tree();
	Tree(Node<Keyvalue>* rt,int pow)
	{
		root=rt;
		power=pow;
	};

	~Tree()
	{
		if(root!=nullptr)
			root->del_full();

	};

	void insert(Keyvalue value)
	{
		if(root==nullptr)
		{
			Node<Keyvalue>* rt=new Node<Keyvalue>(power);
			root=rt;
		}
		if(find(value)!=nullptr)
			return;
		Node<Keyvalue>* new_el=ins_rec(root, value);
		if(new_el!=nullptr)
		{
			Node<Keyvalue>* new_rt=new Node<Keyvalue>(power);

			Data<Keyvalue>* ndata1=new Data<Keyvalue>(root->get_content().front()->key,root);
			Data<Keyvalue>* ndata2=new Data<Keyvalue>(new_el->get_content().front()->key,new_el);
			new_rt->sign_right(ndata1);
			new_rt->sign_right(ndata2);

			root=new_rt;
		}
	}

	void lazy_insert(Keyvalue value)
	{
		if(root==nullptr)
		{
			Node<Keyvalue>* rt=new Node<Keyvalue>(power);
			root=rt;
		}

		Data<Keyvalue>* ths = find_data(value);
		if(ths!=nullptr)
		{
			if(ths->get_is_del())
			{
				return;
			}
			else
			{
				ths->set_del_false();
			}
		}
		Node<Keyvalue>* new_el=ins_rec_lazy(root, value);
		if(new_el!=nullptr)
		{
			Node<Keyvalue>* new_rt=new Node<Keyvalue>(power);
			Data<Keyvalue>* ndata1=new Data<Keyvalue>(root->get_content().front()->key,root);
			Data<Keyvalue>* ndata2=new Data<Keyvalue>(new_el->get_content().front()->key,new_el);
			new_rt->sign_right(ndata1);
			new_rt->sign_right(ndata2);

			root=new_rt;
		}

	}

	Node<Keyvalue>* find(Keyvalue value)const
	{
		if(root==nullptr)
			return nullptr;

		return find_rec(root,value);
	}

	Data<Keyvalue>* find_data(Keyvalue value)const
	{
		if(root==nullptr)
			return nullptr;

		return find_rec_data(root,value);
	}

	vector<Keyvalue>* write_tree_in_arr()const
	{
		vector<Keyvalue>* ret = new vector<Keyvalue>;
		if(root!=nullptr)
			write_tree_in_arr_rec(root,ret);
		return ret;
	}

	void write_tree()const
	{
		if(root!=nullptr)
			write_tree_rec(root,0);
	}

	void throw_coffins()
	{
		if(root!=nullptr)
		{
			throw_coffins_rec(root);
		}
	}

	void write_lists()const
	{
		Node<Keyvalue>* cur = root;
		if(cur!=nullptr)
		{
			while(cur->get_am_child()!=0)
			{
				cur=cur->get_content().front()->link;
			}

			Data<Keyvalue>* cur_d;
			do
			{
				cur->write_node_l();
				cur_d=cur->get_content().back()->neibhor_r;
				if(cur_d==nullptr)
					break;
				cur=find(cur_d->key);
			}while(cur_d!=nullptr);
		}
		cout<<endl;
	}

	void lazy_delete(Keyvalue value)
	{
		if(root!=nullptr)
		{
			Data<Keyvalue>* ths = find_data(value);
			ths->set_del();
		}
	}

	void lazy_fix()
	{
		if(root!=nullptr)
		{
			throw_coffins();
			lazy_fix_rec(root);
		}

		if(root->get_am_notes()==1)
		{
			Node<Keyvalue>* temp = root;
			root = root->get_content().front()->link;
			delete(temp->get_content().front());
			delete(temp);
		}

	}


	void delete_node(Keyvalue value)
	{
		if(root!=nullptr)
		{
			if(find(value)==nullptr)
				return;
			Node<Keyvalue>* broken=delete_node_rec(root, value);
			if(broken!=nullptr)
			{

				for(auto x : root->get_content())
				{
					delete(x);
				}
				delete(root);
				root=broken;

			}

		}
	}
private:


	Node<Keyvalue>* lazy_fix_rec(Node<Keyvalue>* cur)
	{
		if(cur==nullptr)
		{
			return nullptr;
		}

		if(cur->get_am_child()==0)
		{
			return nullptr;
		}
		else
		{
			for(auto &iter : cur->get_content())
			{
				if(iter->link!=nullptr)
					lazy_fix_rec(iter->link);
			}
			while(cur->fix_children()){};
			for(auto &iter : cur->get_content())
			{
				if(iter->link!=nullptr)
				{
					iter->key = iter -> link -> get_content().front()->key;
				}
			}
		}
		return nullptr;

	}

	void throw_coffins_rec(Node<Keyvalue>* cur)
	{
		if(cur!=nullptr)
		{
			if(cur->get_am_child()!=0)
				for(auto &x : cur->get_content())
				{
					if(x->link!=nullptr)
						throw_coffins_rec(x->link);
				}
			else
			{
				for(auto &x : cur->get_content())
				{
					if(x->is_deleted)
					{
						cur->del_data(x);
						delete(x);
					}
				}
			}
		}
	}

	void write_tree_rec(const Node<Keyvalue>* cur,int dpth)const
	{
		if(cur!=nullptr)
		{
			dpth++;
			for(int i = 0;i<dpth; i++)
				cout<<"   ";
			cur->write_node();
			if(cur->get_am_child()!=0)
				for(auto &x : cur->get_content())
				{
					if(x->link!=nullptr)
					{
						write_tree_rec(x->link,dpth);
					}
				}
		}
	}

	void write_tree_in_arr_rec(const Node<Keyvalue>* cur, vector<Keyvalue>* ret)const
	{
		if(cur!=nullptr)
		{
			if(cur->get_am_child()==0)
				cur->write_node_in_arr(ret);
			if(cur->get_am_child()!=0)
				for(auto &x : cur->get_content())
				{
					if(x->link!=nullptr)
						write_tree_in_arr_rec(x->link,ret);
				}
		}
	}

	Node<Keyvalue>* ins_rec(Node<Keyvalue>* cur,Keyvalue value)
	{
		if(cur->get_am_child()==0)
		{
			Data<Keyvalue>* ndata = new Data<Keyvalue>(value, nullptr);
			cur->sign_right(ndata);


			if(cur->get_am_notes() > 2 * power - 1)
			{
				return cur->separate();
			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			Node<Keyvalue>* nnew = ins_rec(cur->find_child(value),value);
			cur->get_content_ref()->front()->key=cur->get_content().front()->link->get_content().front()->key;

			if(nnew!=nullptr)
			{
				Data<Keyvalue>* ndata=new Data<Keyvalue>(nnew->get_content().front()->key,nnew);
				cur->sign_right(ndata);

				if(cur->get_am_notes() > 2 * power - 1)
				{
					return cur->separate();
				}
				else
				{
					return nullptr;
				}
			}
			return nullptr;
		}
	}

	Node<Keyvalue>* ins_rec_lazy(Node<Keyvalue>* cur,Keyvalue value)
	{
		if(cur->get_am_child()==0)
		{

			Data<Keyvalue>* ndata = new Data<Keyvalue>(value, nullptr);
			cur->sign_right(ndata);
			if(cur->get_am_notes() > 2 * power - 1)
			{
				return cur->separate();
			}
			else
			{
				return nullptr;
			}
		}
		else
		{
			if(cur->get_content().front()->link->get_am_child()==0)
			{
				Node<Keyvalue>* with_cof = cur->find_child_data(value)->link;
				Data<Keyvalue>* coffin = with_cof->find_coffin();
				if(coffin!=nullptr)
				{
					with_cof->del_data(coffin);
					delete(coffin);
					Data<Keyvalue>* nnew=new Data<Keyvalue>(value,nullptr);
					with_cof->sign_right(nnew);
					cur->get_content_ref()->front()->key=cur->get_content().front()->link->get_content().front()->key;
					return nullptr;
				}
			}
			Node<Keyvalue>* nnew = ins_rec_lazy(cur->find_child(value),value);
			cur->get_content_ref()->front()->key=cur->get_content().front()->link->get_content().front()->key;

			if(nnew!=nullptr)
			{
				Data<Keyvalue>* ndata=new Data<Keyvalue>(nnew->get_content().front()->key,nnew);
				cur->sign_right(ndata);

				if(cur->get_am_notes() > 2 * power - 1)
				{
					return cur->separate();
				}
				else
				{
					return nullptr;
				}
			}
			return nullptr;
		}
	}

	Node<Keyvalue>* find_rec(Node<Keyvalue>* cur,Keyvalue value)const
	{
		if(cur->get_am_child()==0)
		{
			for(auto &x : cur->get_content())
			{
				if(x->key==value)
					return cur;
			}
			return nullptr;
		}
		else
		{
			return find_rec(cur->find_child(value),value);
		}
	}

	//returns data with key = value
	Data<Keyvalue>* find_rec_data(Node<Keyvalue>* cur,Keyvalue value)const
	{
		if(cur->get_am_child()==0)
		{
			for(auto &x : cur->get_content())
			{
				if(x->key==value)
					return x;
			}
			return nullptr;
		}
		else
		{
			return find_rec_data(cur->find_child(value),value);
		}
	}

	//returns node which should be fixed or combined
	Node<Keyvalue>* delete_node_rec(Node<Keyvalue>* cur, Keyvalue value)
	{
		if(cur->get_am_child()==0)
		{

			Data<Keyvalue>* ndata=cur->find_child_data(value);
			cur->del_data(ndata);
			if(ndata->link!=nullptr)
			{
				for(auto x : ndata->link->get_content())
				{
					delete(x);
				}
				delete(ndata->link);
			}
			delete(ndata);
			if(cur->get_am_notes() < power)
			{
				if(cur!=root)
					return cur;
			}
			else
			{
				return nullptr;
			}
			return nullptr;


		}
		else
		{

			Node<Keyvalue>* broken = delete_node_rec(cur->find_child(value),value);
			if(broken!=nullptr)
			{
				if(cur->try_to_fix(broken, value))
				{
					cur->combine(broken,value);

				}
				if(cur->find_child_data(value)->link!=nullptr)
				{
					if(cur->find_child_data(value)->link->get_content().size()!=0)
						cur->find_child_data(value)->key=cur->find_child_data(value)->link->get_content().front()->key;
				}
				if(cur->get_am_notes() < power)
				{
					if(*cur==*root)
					{
						if(cur->get_am_child()==1)
						{
							return broken;
						}
						else
						{
							return nullptr;
						}
					}
					return cur;

				}
				else
				{
					return nullptr;
				}
			}
			else
			{
				if(cur->find_child_data(value)->link!=nullptr)
				{
					if(cur->find_child_data(value)->link->get_content().size()!=0)
						cur->find_child_data(value)->key=cur->find_child_data(value)->link->get_content().front()->key;
				}
			}

			return nullptr;
		}

	}

};

#endif /* TREE_H_ */
