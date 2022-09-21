#pragma once
/*
线段树
*/
#include<xmemory>
#include<algorithm>
#include<iostream>
#include"SegTree_iterator.h"
using namespace std;


namespace bestdeary {
	template<typename T>
	void destroy(T* ptr) {
		ptr->~T();
	}

	template<typename T, class Alloc = std::allocator<TreeNode<T>>>
	class SegTree {
	public:

		using value_type = T;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using size_type = size_t;
		using deference_type = std::ptrdiff_t;

		using iterator = SegTree_iterator<T, T&, T*>;
		using const_iterator = SegTree_iterator<T, const T&, const T*>;

	private:
		using treenode = TreeNode<T>;
		using treenode_base = TreeNode_base;
		using iterator_base = SegTree_iterator_base;

		Alloc alc;

		treenode* creat_node(const value_type& x) {
			treenode* node = alc.allocate(sizeof(treenode));
			try {
				alc.construct(node, TreeNode<T>(0));
				node->lchild = nullptr;
				node->rchild = nullptr;
				node->feather = nullptr;
			}
			catch (std::bad_alloc& boc) {
				std::cerr << "内存分配失败\n";
				alc.deallocate(node, sizeof(treenode));
			}
			return node;
		}

		void destroy_node(treenode* node) {
			//---可能有问题
			//destroy(&node->value);
			//destroy(&node->l);
			//destroy(&node->r);
			//destroy(&node->high);
			//---
			alc.deallocate(node, sizeof(treenode));
		}

		void destroy_tree(treenode* node) {
			if (node == nullptr) return;
			destroy_tree(node->lchild);
			destroy_tree(node->rchild);
			destroy_node(node);
		}

		void set_node(treenode* fnode, treenode* node, const int& lhs, const int& rhs, const int& high) {
			node = creat_node(0);
			node->l = lhs;
			node->r = rhs;
			node->lchild = nullptr;
			node->rchild = nullptr;
			node->feather = fnode;
			node->high = high;
		}

		treenode* make_tree(treenode* fnode, treenode* node, const int& lhs, const int& rhs, const int& high) {
			if (lhs > rhs) return nullptr;
			//cout << high << endl;
			if (fnode->l == lhs && fnode->r == rhs) return nullptr;
			//cout << ++n << endl;
			//if (node == nullptr) return;
			//set_node(fnode, node, lhs, rhs, high + 1);
			node = creat_node(0);
			node->l = lhs;
			node->r = rhs;
			node->lchild = nullptr;
			node->rchild = nullptr;
			node->feather = fnode;
			node->high = high + 1;

			node->lchild =  make_tree(node, node->lchild, lhs, (lhs + rhs) / 2, high + 1);
			node->rchild = make_tree(node, node->rchild, ((lhs + rhs) / 2) + 1, rhs, high + 1);
			return node;

		}
	
		void _bianl(treenode* node) {
			if (node == nullptr) return ;
			//cout << ++n << endl;
			cout << node->l << " " << node->r << endl;
			_bianl(node->lchild);
			_bianl(node->rchild);
		}
	public:
		void bianl() {
			_bianl(head);
		}

	private:
		treenode* head;

	public:
		SegTree() {
			head->lchild = nullptr;
			head->rchild = nullptr;
			head->feather = nullptr;
			max_high = 0;
		}
		~SegTree() {
			destroy_tree(head);
		}

		//public member function
	private:
		size_type max_high;
		int n = 0;

	public:
		SegTree(const size_type& t) {
			max_high = log(t) + 1;
			head = creat_node(0);
			head->l = 0;
			head->r = t;
			head->lchild = make_tree(head, head->lchild, 0, t / 2, 1);
			head->rchild = make_tree(head, head->rchild, t / 2 + 1, t, 1);
		}

		void _insert(treenode* node, const int& place, const T& value) {

			if (node == nullptr) return;
			int lside = node->l;
			int rside = node->r;
			if (lside <= place && place <= rside) {
				node->value = std::max(node->value, value);
				int mid = (lside + rside) / 2;
				if (place <= mid) {
					_insert(node->lchild, place, value);
				}
				else {
					_insert(node->rchild, place, value);
				}
				
			}
		}
		void insert(const int& place, const T& value) {
			_insert(head, place, value);
		}

		int _find(treenode* node, const int& lhs, const int& rhs) {
			if (node == nullptr) return 0;
			int mid = (node->l + node->r) / 2;
			if (lhs == node->l && rhs == node->r) return node->value;
			if (lhs >= mid) {
				return _find(node->rchild, lhs, rhs);
			}
			else if (lhs < mid && mid < rhs) {
				int a = _find(node->rchild, mid + 1, rhs);
				int b = _find(node->lchild, lhs, mid);
				//using std::max;
				return std::max(_find(node->rchild, mid + 1, rhs),
				_find(node->lchild, lhs, mid));
				//using std::max;)
				//return std::max(a, b);
			}
			else if (rhs <= mid) {
				return _find(node->lchild, lhs, rhs);
			}
		}
		int find(const int& lhs, const int& rhs) {
			return _find(head, lhs, rhs);
		}
	};
}
