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
    // Implementation of Heap
    Heap::Heap(int count)
        : COUNT(count)
          , mSize(0)
    {
        mData = new int[count];
    }
    Heap::~Heap()
    {
        delete[] mData;
    }
    void Heap::exch(int i, int j)
    {
        if ( i != j )
        {
            int val = mData[i];
            mData[i] = mData[j];
            mData[j] = val;
        }
    }
    void Heap::put(int val)
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
    void Heap::delMin()
    {
        if ( mSize > 0 )
        {
            exch(1, mSize);
            mSize --;
            heapify(1);
        }
    }
    void Heap::heapify(int i)
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
    void Heap::dump()
    {
        for (int i = 0; i < COUNT; i++)
            std::cout << mData[i] << " ";
        std::cout << std::endl;
    }
    // Implementation of HeapSort
} // end namespace Algorithms

int main()
{
    std::cout << "algorithms. " << std::endl;
//    Algorithms::InsertionSort sorttest(10);
//    Algorithms::SelectionSort sorttest(10);
//    Algorithms::ShellSort sorttest(10);
//    Algorithms::MergeSort sorttest(32);
    Algorithms::QuickSort sorttest(1);
    Algorithms::Heap heap(32);
    for (int i = 10; i > 0; i--)
    {
        heap.put(i);
        heap.dump();
    }
    while ( !heap.empty() )
    {
        std::cout << heap.getMin() << std::endl;
        heap.delMin();
        heap.dump();
    }

    std::cout << "array before sort" << std::endl;
    sorttest.dump();
    sorttest.sort();
    std::cout << "array after sort" << std::endl;
    sorttest.dump();
}
