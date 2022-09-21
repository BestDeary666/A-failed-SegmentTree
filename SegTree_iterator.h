#pragma once
/*
实现一个线段树模板SegmentTree
*/
#include<iterator>


namespace bestdeary {
    struct TreeNode_base {
        TreeNode_base* feather;

    };

    template<typename T>
    struct TreeNode : TreeNode_base {
        T value;
        int l, r, high;
        TreeNode* lchild;
        TreeNode* rchild;

        TreeNode() : value(0) {}
        TreeNode(const int& x) : value(x) { }
    };

    struct SegTree_iterator_base {
        using iterator_category = std::random_access_iterator_tag;
        using diference_type = std::ptrdiff_t;

        TreeNode_base* node;

        SegTree_iterator_base(TreeNode_base* x) : node(x) { }

        //TreeNode_base* next_node() noexcept {
        //    return node->next;
        //}
        TreeNode_base* pre_node() noexcept {
            return node->feather;
        }

        //void node_back() noexcept {
        //    node = node->next;
        //}
        void node_front() noexcept {
            node = node->feather;
        }

        bool operator==(const SegTree_iterator_base& rhs) noexcept {
            return node == rhs.node;
        }
        bool operator!=(const SegTree_iterator_base& rhs) noexcept {
            return node != rhs.node;
        }

    };

    template<typename T, typename ref, typename ptr>
    struct SegTree_iterator : SegTree_iterator_base {
        using value_type = T;
        using pointer = ptr;
        using reference = ref;
        using treenode = TreeNode<T>;

        using iterator = SegTree_iterator<T, T&, T*>;
        using const_iterator = SegTree_iterator<T, const T&, const T*>;
        using self_iterator = SegTree_iterator<T, ref, ptr>;

        SegTree_iterator(treenode* x) : SegTree_iterator_base(x) { }
        SegTree_iterator() : SegTree_iterator_base(nullptr) { }
        SegTree_iterator(const iterator& x) : SegTree_iterator_base(x) { }

        ref operator*() const {
            return ((treenode*)node)->value;
        }
        ptr operator->() const {
            return &(operator*());
        }

        //self_iterator& operator++() {
        //    node_back();
        //    return *this;
        //}
        //const self_iterator operator++(int) {
        //    self_iterator tmp = this;
        //    node_back();
        //    return tmp;
        //}

        self_iterator& operator--() {
            node_front();
            return *this;
        }
        const self_iterator operator--(int) {
            self_iterator tmp = this;
            node_front();
            return tmp;
        }

    };
}


