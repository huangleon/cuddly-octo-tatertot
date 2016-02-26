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
        if (lo < hi)
        {
            // partition
            int mid = partition(lo, hi);
            sort(lo, mid);
            sort(mid + 1, hi);
        }
    }
    int QuickSort::partition(int lo, int hi)
    {
    }
    void QuickSort::dump()
    {
        mData.dump();
    }
    // Implementation of Heap
    // Implementation of HeapSort
} // end namespace Algorithms

int main()
{
    std::cout << "algorithms. " << std::endl;
//    Algorithms::InsertionSort sorttest(10);
//    Algorithms::SelectionSort sorttest(10);
//    Algorithms::ShellSort sorttest(10);
    Algorithms::MergeSort sorttest(32);

    std::cout << "array before sort" << std::endl;
    sorttest.dump();
    sorttest.sort();
    std::cout << "array after sort" << std::endl;
    sorttest.dump();
}
