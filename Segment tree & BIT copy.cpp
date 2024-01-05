// https://cses.fi/problemset/task/1649
// https://usaco.guide/gold/PURS?lang=cpp#segment-tree
// https://csacademy.com/app/graph_editor/ 
/* Segmemnt tree & BIT: both are data structures that can update a point 
in a given index or get the 
sum of consecutive subarray in O(log N), other consecutive operations can also be done
in O(log N)
Usually we memorize how to set up either a BIT or segment tree if we are tyring to use
these algorithms during contests
*/

#include <bits/stdc++.h>
using namespace std;

// template of the segment tree to update the array and find the minimum value
template <class T> class MinSegmentTree
{
	private:
		const T DEFAULT=1e18; // a constant to prevent int overflow
		vector<T> segtree;    // our segment tree
		int len; 			  // stores the length of an input array
	public:
		/*the segment tree is initialized to the length of twice the input array because
		in the standard segment tree, each node had two children, so if you have n leaves
		in the tree(corresponding to the elements in the array), the total number of nodes
		in the tree is roughly 2n-1, thus, to represent the segment tree in a single array,
		we need the array size to be at least 2n.

		The leaves of the tree coressponds to the elements of the input array. So, 
		the first len elements of the array segtree represents the leaves

		The parents of the leaf at index i is usually at index i+len in segtree array

		The left child of a node at index i is simply at 2*i, the right child is simply
		at 2*i+1
		*/

		//constructor
		MinSegmentTree(int len):len(len), segtree(len*2, DEFAULT){}

		//update the value at a specific index
		void set(int ind, T val)
		{
			/* since the first len indexes of the segtree are reserved for the 
			leaves(which corresponds to the elements of the input array) 
			of the segment tree, so we do ind+=len. This will ensure the the correct 
			internal nodes(which represents the parents of leaves) are updated 
			 */
			ind+=len;

			// This step corresponds to updating the leaf node in the segment tree
			segtree[ind]=val;

			/* This initiates a loop that updates the parent nodes in the segment tree, 
			moving from the leaf node towards the root.
			The loop continues as long as ind is greater than 1.
			The loop condition ensures that the loop terminates when the root of the 
			segment tree is reached.

			Since each internal node stores the min value of its 2 children, we need to 
			ensure their parents can all recalculate and store the min value for their 
			updated children

			the update operation is also O(log N) since its the height of the tree
			*/
			for(;ind>1;ind/=2)
			{
				segtree[ind/2]=min(segtree[ind], segtree[ind^1]);
			}
		}

		// return the min in the given range [start end)
		/*
		ex:
		      1
     		 / \
    		2   3
   		   / \ / \
  		  4  5 6  7
 		 / \
		8   9
		*/
		T range_min(int start, int end)
		{
			T sum=DEFAULT;
			for(start+=len, end+=len; start<end; start/=2, end /=2)
			{
				/*So, in the traversal loop, if the current node is a 
				right child (odd index), 
				the minimum value of its subtree is considered for the query range. 
				This ensures that the traversal takes into account the 
				appropriate nodes based on the binary representation of the indices 
				in the segment tree.

				ex: A node at index k represents a range of elements [L, R) from the 
				original array.
				The left child of a node at index k represents the range [L, (L+R)/2).
				The right child of a node at index k represents the range [(L+R)/2, R).
				*/
				if(start%2==1) sum=min(sum, segtree[start++]);

				/*This code is part of the range_min method and is used to update 
				the sum variable 
				when the end index corresponds to a right child in t
				he binary tree representation 
				of the segment tree.
				
				This effectively moves the end index to the parent node in the
				binary tree representation.

				 	1
       		   	  /   \
              	 2     3
             	/ \   / \
               4   5 6   7
              / \
          	 8   9
				Node 1 represents the range [1, 8) (the entire array).
				Nodes 2 and 3 represent the ranges [1, 4) and [4, 8), respectively.
				Nodes 4 and 5 represent the ranges [1, 2) and [2, 4), respectively.
				Nodes 6 and 7 represent the ranges [4, 6) and [6, 8), respectively.
				Nodes 8 and 9 represent the ranges [1, 1) and [1, 2), respectively.
				Now, let's consider the effect of --end when end is pointing to a 
				right child. 
				Suppose end initially points to Node 7 (right child of its parent Node 3):
				// Suppose end is initially pointing to a right child with an odd index.
				int end = 7;  // Example right child index

				// Pre-decrement operation
					--end;

				// Now, end is pointing to the parent node (Node 3, next even index)
				// end = 6
				After the --end operation, end moves from Node 7 to its parent Node 3.

				In the context of the range_min method, this allows the traversal to 
				consider the parent node after updating the sum variable for 
				the right child. 
				The traversal then continues towards the root of the segment tree.
				*/

				/*!!!Implicit Handling of Left Children:
				Since the loop continues with the updated start and end, 
				even indices (left children) are implicitly 
				considered in the next iteration.*/
				if(end%2==1) sum=min(sum, segtree[--end]);
			}
			return sum;
		}

};

int main() 
{
	int arr_len;	int query_num;	cin >> arr_len >> query_num;
	MinSegmentTree<long long> segtree(arr_len);
	for(int i=0;i<arr_len;i++)
	{
		int tmp; cin>>tmp;
		segtree.set(i, tmp);
	}

	//arg1-1 is just to handle the 0-based array instead of 1 based in the prompt
	for(int q=0;q<query_num;q++)
	{
		int type, arg1, arg2;	cin >> type >> arg1 >> arg2;
		if(type==1)
			segtree.set(arg1-1, arg2);
		else if(type==2)
			cout << segtree.range_min(arg1-1, arg2) << '\n';
	}
}
