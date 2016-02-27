#ifndef __SORT_H__
#define __SORT_H__

namespace Algorithms {
    // Definition of base class.
    class Sort {
        private:
            const int COUNT;
            int* mNumbers;
        public:
            Sort(int count);
            virtual ~Sort();

            int count() const { return COUNT; }
            int compare(int i, int j) const
            {
                if (mNumbers[i] < mNumbers[j])
                    return -1;
                else if (mNumbers[i] == mNumbers[j])
                    return 0;
                else return 1;
            }
            void exch(int i, int j);
            void copyTo(int* target, int i, int count);
            // void copyFrom(int* source, int i, int count);

            void setValue(int i, int val) { mNumbers[i] = val; }
            int getValue(int i) const { return mNumbers[i]; }

            void dump();
            // aux function for shellsort
            void dump(int i, int count);
    };
    // Definition of InsertionSort
    class InsertionSort {
        // sort arrays using insertion sort.
        private:
            Sort mData;
        public:
            InsertionSort(int count);

            void sort();
            void dump();
    };
    // Definition of SelectionSort
    class SelectionSort {
        // sort arrays using selection sort.
        private:
            Sort mData;
        public:
            SelectionSort(int count);

            void sort();
            void dump();
    };
    // Definition of ShellSort
    class ShellSort {
        // sort arrays using selection sort.
        private:
            Sort mData;
        public:
            ShellSort(int count);

            void sort();
            void dump();
            // dump array data in step h
            void dump(int h);
    };
    // Definition of MergeSort
    class MergeSort {
        private:
            Sort mData;
            int * mAux;
            // sort from i to j.
            void sort(int lo, int hi);

            // merge [low, mid], [mid + 1, hi]
            void merge(int lo, int mid, int hi);
        public:
            MergeSort(int count);
            virtual ~MergeSort();

            void sort();
            void dump();
    };
    // Definition of QuickSort
    class QuickSort {
        private:
            Sort mData;
            void sort(int lo, int hi);
            int partition(int lo, int hi);
        public:
            QuickSort(int count);

            void sort();
            void dump();
    };
    // Definition of min-Heap
    class PriorityQueue{
        private:
            const int COUNT;
            int* mData;
            int mSize;
            void exch(int i, int j);
            void heapify(int i);
        public:
            PriorityQueue(int count);
            virtual ~PriorityQueue();

            bool empty() const { return mSize == 0; }
            void put(int val);
            int getMin() const { return mData[1]; }
            void delMin();
            void dump();
    };
    // definition of HeapSort
    class HeapSort {
        private:
            Sort mData;
            PriorityQueue mPq;
        public:
            HeapSort(int count);

            void sort();
            void dump();
    };
    // definition of Red-Black-Tree
    class RbTree {
        private:
            enum {
                E_NULL = 0,
                E_TRAVERSE_PREORDER,
                E_TRAVERSE_INORDER,
                E_TRAVERSE_POSTORDER,
            };
            // size of the static array
            const int COUNT;
            int * mNode;
            int * mParent;
            int * mLeft;
            int * mRight;
            int * mValue;
            // color of node, true: red, false, black
            bool * mRed;

            // head of free list, freelist is single-linked list
            int mfree;
            // root of the tree
            int mroot;

            // traverse order
            int mTraverseOrder;

            // alloc new node from free list
            int new_node();
            // free node and put it back to free list.
            void del_node(int);

            // insert value into the sub-tree and return the root of new sub-tree.
            int insert_val(int node, int value);
            // dump sub-tree
            void dump_subtree(int);
            // dump node
            void dump_node(int);
        public:
            RbTree(int reserve);
            virtual ~RbTree();

            void dump();

            // return node inserted.
            int insertValue(int value);
            bool contains(int value);
            void delValue(int value);
    };
}
#endif // end of __SORT_H__
