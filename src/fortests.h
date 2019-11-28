/*
 * fortests.h
 *
 *  Created on: 14 дек. 2018 г.
 *      Author: dmitrii
 */

#ifndef FORTESTS_H_
#define FORTESTS_H_
#include <time.h>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <iostream>

namespace for_tests
{


template<typename Type>
void change_pos(std::vector<Type>& vec)
{

	int sz = vec.size();
	int fst_pos = rand() % sz;
	int snd_pos = rand() % sz;
	Type temp = vec[fst_pos];
	vec[fst_pos]=vec[snd_pos];
	vec[snd_pos]=temp;

}

template<typename T>
void write_vec(std::vector<T>& vec)
{
	for(int i = 0; i<vec.size();i++)
	{
		std::cout<<vec[i]<<" ";
	}
	std::cout<<endl;
}

template<typename T>
void del_from_vec(std::vector<T>& vec, T value)
{
	for(auto i = vec.begin(); i!=vec.end();i++)
	{
		if(*i==value)
		{
			vec.erase(i);
			return;
		}
	}
}


template<typename T>
bool find(std::vector<T>& vec, T value)
{
	for(auto i = vec.begin(); i!=vec.end();i++)
	{
		if(*i==value)
		{
			return true;
		}
	}
	return false;
}


}//end of namespace

#endif /* FORTESTS_H_ */
