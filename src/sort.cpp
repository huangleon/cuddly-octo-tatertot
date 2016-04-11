#include "sort.h"
#include <iostream>

#include <time.h>
#include <stdlib.h>
#include <algorithm>

namespace Algorithms {
    // Base class of Sort
    Sort::Sort(int count)
        : COUNT(count)
    {
        // generate a random shuffled array.
        srand(time(NULL));
        mNumbers = new int[COUNT];
        for (int i = 0; i < COUNT; i++)
            mNumbers[i] = i;
        std::random_shuffle(mNumbers, mNumbers + COUNT);
    }
    Sort::~Sort()
    {
        // release array of numbers.
        delete[] mNumbers;
    }
    void Sort::dump()
    {
        for (int i = 0; i < COUNT; i++)
            std::cout << mNumbers[i] << " ";
        std::cout << std::endl;
    }
    void Sort::dump(int i, int count)
    {
        for (int j = i; j < i + count && j < COUNT; j++)
            std::cout << mNumbers[j] << " ";
        std::cout << std::endl;
    }
    void Sort::exch(int i, int j)
    {
        if ( i != j )
        {
            int val = mNumbers[i];
            mNumbers[i] = mNumbers[j];
            mNumbers[j] = val;
        }
    }
    void Sort::copyTo(int* target, int i, int count)
    {
        for (int j = i; j < COUNT && j < i + count; j++)
            target[j] = mNumbers[j];
    }
//    void Sort::copyFrom(int* source, int i, int count)
//    {
//        for (int j = i; j < COUNT && j < count; j++)
//            mNumbers[j] = source[j];
//    }

    // Implementation of InsertionSort
    InsertionSort::InsertionSort(int count)
        : mData(count)
    {
    }
    void InsertionSort::sort()
    {
        for (int i = 0; i < mData.count() - 1; i++)
        {
            for (int j = i + 1; j > 0; j--)
            {
                // compare j with j - 1
                if ( mData.compare(j, j - 1) < 0 )
                {
                    mData.exch(j, j - 1);
                }
                else
                {
                    // array[0]..array[i] are sorted
                    // array[i + 1] >= array[i], goto next number(i++) to process.
                    break;
                }
                // print out numbers.
                dump();
            }
        }
    }
    void InsertionSort::dump()
    {
        mData.dump();
    }

    // Implementation of SelectionSort
    SelectionSort::SelectionSort(int count)
        : mData(count)
    {
    }
    void SelectionSort::sort()
    {
        for (int i = 0; i < mData.count() - 1; i++)
        {
            // q is min val in array[i]..array[N]
            int q = i;
            for (int j = i; j < mData.count(); j++)
            {
                // select min val in array[i..j]
                if ( mData.compare(j, q) < 0 )
                    q = j;
            }
            // after this exchange, array[0]..array[i] are sorted.
            mData.exch(i, q);

            // print out numbers.
            dump();
        }
    }
    void SelectionSort::dump()
    {
        mData.dump();
    }
    // Implementation of ShellSort
    ShellSort::ShellSort(int count)
        : mData(count)
    {
    }
    void ShellSort::sort()
    {
        // h-sorted, step h, use insertion sort to sort sub-array.
        int h = 1;
        while ( h < mData.count() / 3 )
            h = 3 * h + 1;
        while (h > 0)
        {
            for (int i = h; i < mData.count(); i++)
            {
                for (int j = i; j >= h; j -= h)
                {
                    if ( mData.compare(j, j - h) < 0 )
                        mData.exch(j - h, j);
                    else
                        break;
                }
            }
            dump(h);
            h /= 3;
        }
    }
    void ShellSort::dump()
    {
        mData.dump();
    }
    void ShellSort::dump(int h)
    {
        for (int i = 0; i < mData.count(); i += h)
        {
            mData.dump(i, h);
        }
    }
    // Implementation of MergeSort
    MergeSort::MergeSort(int count)
        : mData(count)
    {
        mAux = new int[count];
    }
    MergeSort::~MergeSort()
    {
        delete[] mAux;
    }
    void MergeSort::sort()
    {
        if (mData.count() > 0)
            sort(0, mData.count() - 1);
    }
    void MergeSort::sort(int lo, int hi)
    {
        if (lo < hi)
        {
            int mid = (lo + hi) / 2;
            sort(lo, mid);
            sort(mid + 1, hi);
            merge(lo, mid, hi);
        }
    }
    void MergeSort::merge(int lo, int mid, int hi)
    {
        // use aux array to do merge
        mData.copyTo(mAux, lo, hi - lo + 1);

        int j = lo, k = mid + 1;
        for (int i = lo; i <= hi; i++)
        {
            if (j > mid)
                mData.setValue(i, mAux[k++]);
            else if (k > hi)
                mData.setValue(i, mAux[j++]);
            else if (mAux[j] < mAux[k])
                mData.setValue(i, mAux[j++]);
            else
                mData.setValue(i, mAux[k++]);
        }
        dump();
    }
    void MergeSort::dump()
    {
        mData.dump();
    }
    // Implementation of QuickSort
    QuickSort::QuickSort(int count)
        : mData(count)
    {
    }
    void QuickSort::sort()
    {
        if (mData.count() > 0)
            sort(0, mData.count() - 1);
    }
    void QuickSort::sort(int lo, int hi)
    {
        std::cout << "sort: " << lo << ", " << hi << std::endl;
        if (lo < hi)
        {
            // partition
            int mid = partition(lo, hi);
            dump();
            sort(lo, mid - 1);
            sort(mid + 1, hi);
        }
    }
    int QuickSort::partition(int lo, int hi)
    {
        // take hi as pivot
        // [lo, q) less than pivot
        // [q ~ i) larger than or equal to  pivot
        int pivot = hi;
        int q = lo;
        for (int i = lo; i < hi; i++)
        {
            if ( mData.compare(i, pivot) < 0 )
            {
                mData.exch(q++, i);
            }
        }
        mData.exch(q, pivot);
        return q;
    }
    void QuickSort::dump()
    {
        mData.dump();
    }
    // Implementation of PriorityQueue
    PriorityQueue::PriorityQueue(int count)
        : COUNT(count)
          , mSize(0)
    {
        mData = new int[count];
        // generate a random shuffled array.
//        srand(time(NULL));
//        int * nums = new int[COUNT - 1];
//        for (int i = 0; i < COUNT - 1; i++)
//            nums[i] = i;
//        std::random_shuffle(nums, nums + COUNT - 1);
//        for (int i = 0; i < COUNT - 1; i++)
//            put(nums[i]);
//        delete[] nums;
    }
    PriorityQueue::~PriorityQueue()
    {
        delete[] mData;
    }
    void PriorityQueue::exch(int i, int j)
    {
        if ( i != j )
        {
            int val = mData[i];
            mData[i] = mData[j];
            mData[j] = val;
        }
    }
    void PriorityQueue::put(int val)
    {
        // use 1..n as index, index 0 is useless.
        if ( mSize < COUNT - 1 )
        {
            mData[1 + mSize++] = val;
            int i = mSize;
            int parent = i / 2;
            while (parent > 0)
            {
                if (mData[i] < mData[parent])
                {
                    exch(i, parent);
                    i = parent;
                    parent = i / 2;
                }
                else
                    break;
            }
        }
    }
    void PriorityQueue::delMin()
    {
        if ( mSize > 0 )
        {
            exch(1, mSize);
            mSize --;
            heapify(1);
        }
    }
    void PriorityQueue::heapify(int i)
    {
        int left = i * 2, right = i * 2 + 1;
        if ( left < mSize && right <= mSize )
        {
            int min = i;
            if (mData[left] < mData[right])
                min = left;
            else
                min = right;
            if (mData[i] < mData[min])
                min = i;
            if (min != i)
            {
                exch(min, i);
                heapify(min);
            }
        }
        else if ( left <= mSize && right > mSize )
        {
            if (mData[left] < mData[i])
            {
                exch(left, i);
                heapify(left);
            }
        }
    }
    void PriorityQueue::dump()
    {
        for (int i = 1; i < COUNT; i++)
            std::cout << mData[i] << " ";
        std::cout << std::endl;
    }
    // Implementation of HeapSort
    HeapSort::HeapSort(int count)
        : mData(count)
          , mPq(count + 1)
    {
    }
    void HeapSort::sort()
    {
        for (int i = 0; i < mData.count(); i++)
            mPq.put(mData.getValue(i));
        for (int i = 0; i < mData.count(); i++)
        {
            mData.setValue(i, mPq.getMin());
            mPq.delMin();
        }
    }
    void HeapSort::dump()
    {
        mData.dump();
    }
    // Implementation of Red-Black-Tree
    RbTree::RbTree(int reserve)
        : COUNT(reserve)
    {
        mNode = new int[COUNT];
        mParent = new int[COUNT];
        mLeft = new int[COUNT];
        mRight = new int[COUNT];
        mValue = new int[COUNT];
        mRed = new bool[COUNT];
        mDepth = new int[COUNT];

        // put 0 as null node.
        mroot = mNode[0] = mParent[0] = mLeft[0] = mRight[0] = mValue[0] = E_NULL;
        // null node is black
        mRed[E_NULL] = false;

        // prepare the free list
        for (int i = 1; i < COUNT; i++)
            mNode[i] = i - 1;
        mfree = COUNT - 1;

        mTraverseOrder = E_TRAVERSE_PREORDER;
    }
    RbTree::~RbTree()
    {
        delete[] mNode;
        delete[] mParent;
        delete[] mLeft;
        delete[] mRight;
        delete[] mRed;
        delete[] mDepth;
    }
    int RbTree::new_node()
    {
        int result = mfree;

        if (mfree != E_NULL)
        {
            // set new node value
            mParent[mfree] = E_NULL;
            mLeft[mfree] = E_NULL;
            mRight[mfree] = E_NULL;
            mRed[mfree] = true;
        }

        // forward the free head.
        mfree = mNode[mfree];
        return result;
    }
    void RbTree::del_node(int node)
    {
        mNode[node] = mfree;
        mfree = node;
    }
    void RbTree::dump_node(int node)
    {
        for (int i = 0; i < mDepth[node]; i++)
            std::cout << "    ";

        std::cout << "node ( " << node <<
            ", " << mParent[node] <<
            ", " << mLeft[node] <<
            ", " << mRight[node] <<
            ", " << mValue[node] <<
            ", " << mRed[node] <<
            " )" << std::endl;
    }
    void RbTree::dump_subtree(int node)
    {
        if (node != E_NULL)
        {
            if ( E_TRAVERSE_PREORDER == mTraverseOrder )
                dump_node(node);
            dump_subtree(mLeft[node]);
            if ( E_TRAVERSE_INORDER == mTraverseOrder )
                dump_node(node);
            dump_subtree(mRight[node]);
            if ( E_TRAVERSE_POSTORDER == mTraverseOrder )
                dump_node(node);
        }
    }
    void RbTree::dump()
    {
        dump_subtree(mroot);
    }
    void RbTree::updateDepth()
    {
        update_depth(mroot, 0);
    }
    void RbTree::update_depth(int node, int depth)
    {
        if ( E_NULL != node )
        {
            mDepth[node] = depth;
            update_depth(mLeft[node], depth + 1);
            update_depth(mRight[node], depth + 1);
        }
    }

    int RbTree::rotate_left(int node)
    {
        // rotate counter-clock wise
        // up-rise the right child
        // only rotate to left-lean red node

        // before rotation, be sure A, C 's not NULL
        //     P
        //      \
        //       A
        //      / \
        //     B   C
        //    / \ / \

        //     P
        //      \
        //       C
        //      / \
        //     A

        // changes:
        // P's child
        // A's parent
        // A's right
        // C's parent
        // C's left

        const int parent = mParent[node];
        const int left = mLeft[node];
        const int right = mRight[node];

        // P's child
        if (E_NULL != parent)
            if ( node == mLeft[parent] )
                mLeft[parent] = right;
            else
                mRight[parent] = right;

        // A's parent and right
        mParent[node] = right;
        mRight[node] = mLeft[right];
        if ( E_NULL != mRight[node] )
            mParent[mRight[node]] = node;

        // C's parent and left
        mLeft[right] = node;
        mParent[right] = parent;

        // color part is special trick in RB-tree
        // change color
        // in this sit, C's color is red, after, change A's color red
        int color = mRed[node];
        mRed[node] = mRed[right];
        mRed[right] = color;

        return right;
    }
    int RbTree::rotate_right(int node)
    {
        // rotate clock wise
        // up-rise the left child
        // only rotate to left-lean red node

        // before rotation, be sure A, B 's not NULL
        //     P
        //      \
        //       A
        //      / \
        //     B   C
        //    / \ / \

        //     P
        //      \
        //       B
        //      / \
        //         A

        // changes:
        // P's child
        // A's parent
        // A's left
        // B's parent
        // B's right

        const int parent = mParent[node];
        const int left = mLeft[node];
        const int right = mRight[node];

        // P's child
        if (E_NULL != parent)
            if ( node == mLeft[parent] )
                mLeft[parent] = left;
            else
                mRight[parent] = left;

        // A's parent and left
        mParent[node] = left;
        mLeft[node] = mRight[left];
        if ( E_NULL != mLeft[node] )
            mParent[mLeft[node]] = node;

        // B's parent and left
        mRight[left] = node;
        mParent[left] = parent;

        // color part is special trick in RB-tree
        // change color
        // in this sit, C's color is red, after, change A's color red
        bool color = mRed[node];
        mRed[node] = mRed[left];
        mRed[left] = color;

        return left;
    }
    int RbTree::insert_val(int node, int value)
    {
        int nnode = E_NULL;
        // insert to null node
        if ( E_NULL == node )
        {
            nnode = new_node();
            if ( E_NULL != nnode )
            {
                mLeft[nnode] = E_NULL;
                mRight[nnode] = E_NULL;
                mRed[nnode] = true;
                mValue[nnode] = value;
            }
            return nnode;
        }

        // insert
        if ( value < mValue[node] )
        {
            nnode = insert_val(mLeft[node], value);
            mLeft[node] = nnode;
            mParent[nnode] = node;
        }
        else if ( value > mValue[node] )
        {
            nnode = insert_val(mRight[node], value);
            mRight[node] = nnode;
            mParent[nnode] = node;
        }
        else
        {
            return node;
        }

        // color and rotation part
        //  |
        // / \
        // check 3 links color
        const int left = mLeft[node];
        const int right = mRight[node];
        if ( !mRed[left] && mRed[right] )
        {
            // change to left-lean red node
            nnode = rotate_left(node);
        }
        else if ( mRed[left] && mRed[mLeft[left]] )
        {
            // split 4-node to two 2-nodes
            nnode = rotate_right(node);
            flip_colors(nnode);
        }
        else if ( mRed[left] && mRed[right] )
        {
            // split 4-node to two 2-nodes
            nnode = node;
            flip_colors(nnode);
        }
        else
        {
            // other case, no need to change or rotate
            return node;
        }

        return nnode;
    }
    void RbTree::flip_colors(int node)
    {
        // split one 4-node to 2-node/3-node
        mRed[mLeft[node]] = mRed[mRight[node]] = false;
        mRed[node] = true;
    }
    void RbTree::insertValue(int value)
    {
        mroot = insert_val(mroot, value);
        mRed[mroot] = false;
    }
    bool RbTree::contains(int value)
    {
        return find_node(mroot, value) != E_NULL;
    }
    int RbTree::find_node(int node, int value)
    {
        if ( E_NULL != node )
        {
            if ( value == mValue[node] )
                return node;
            if ( value < mValue[node] )
                return find_node(mLeft[node], value);
            if ( value > mValue[node] )
                return find_node(mRight[node], value);
        }
        return E_NULL;
    }
    void RbTree::delValue(int value)
    {
    }

} // end namespace Algorithms

int main()
{
    std::cout << "algorithms. " << std::endl;
//    Algorithms::InsertionSort sorttest(10);
//    Algorithms::SelectionSort sorttest(10);
//    Algorithms::ShellSort sorttest(10);
//    Algorithms::MergeSort sorttest(32);
//    Algorithms::QuickSort sorttest(1);
//    Algorithms::HeapSort sorttest(64);
//    Algorithms::PriorityQueue pq(32);
    Algorithms::RbTree rbtree(1024);
    const int TREESIZE = 20;
    int raw[TREESIZE];
    for (int i = 0; i < TREESIZE; i++)
        raw[i] = i;
    srand(time(NULL));
    std::random_shuffle(raw, raw + TREESIZE);
    for (int i = 0; i < TREESIZE; i++)
    {
        std::cout << raw[i] << " ";
        rbtree.insertValue(raw[i]);
    }
    std::cout << std::endl;

    rbtree.updateDepth();
    rbtree.dump();
//    for (int i = 0; i < 2 * TREESIZE; i++)
//    {
//        if ( !rbtree.contains(i) )
//            std::cout << "Ooops!" << i << std::endl;
//    }

//    for (int i = 10; i > 0; i--)
//    {
//        pq.put(i);
//        pq.dump();
//    }
//    while ( !pq.empty() )
//    {
//        std::cout << heap.getMin() << std::endl;
//        heap.delMin();
//        heap.dump();
//    }

//    std::cout << "array before sort" << std::endl;
//    sorttest.dump();
//    sorttest.sort();
//    std::cout << "array after sort" << std::endl;
//    sorttest.dump();
}
