// https://cses.fi/problemset/task/1648
// https://usaco.guide/gold/PURS?lang=cpp#segment-tree
/* the difference between the minimum value in a range with update and the sum in an 
	interval is just some twists in the DAFAULT values and the sum*/
#include <bits/stdc++.h>
using namespace std;

template <class T> class SumSegmentTree
{
	private:
		const T DEFAULT=0;
		vector<T> segtree;
		int len;
	public:
		SumSegmentTree(int len):len(len), segtree(len*2, DEFAULT){}
		void set(int ind, T val)
		{
			ind+=len;
			segtree[ind]=val;
			for(;ind>1;ind/=2)
			{
				/* updating the parent node's value to be the sum of the values of its
				 left and right children

				 segtree[ind] is the current child, segtree[ind^1]is the opposite child
				 segtree[ind/2] is parent node

				 ind^1 gives the least significant bit in the binary representation
				 (the rightmost bit) ^1 will change it from 1 to 0 or 0 to 1
				 since the difference between that rightmost bit gives you the opposite
				 child in the tree, this will let you access the both sides of the children
				*/
				segtree[ind/2]=segtree[ind]+segtree[ind^1];
			}
		}

		T range_sum(int start, int end)
		{
			T sum=DEFAULT;
			for(start+=len, end+=len;start<end;start/=2, end/=2)
			{
				if(start%2==1) sum+=segtree[start++];
				if(end%2==1) sum+=segtree[--end];
			}
			return sum;
		}
};

int main() 
{
	int arr_len;	int query_num; cin >> arr_len >> query_num;
	SumSegmentTree<long long> segtree(arr_len);
	for(int i=0;i<arr_len;i++)
	{
		int tmp;	cin >> tmp;
		segtree.set(i, tmp);
	}
	for(int q=0;q<query_num;q++)
	{
		int type, arg1, arg2; cin >> type >> arg1 >> arg2;
		if(type==1)	segtree.set(arg1-1, arg2);
		else if(type==2) cout << segtree.range_sum(arg1-1, arg2) << '\n';
	}
}
