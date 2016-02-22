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
    void Sort::exch(int i, int j)
    {
        if ( i != j )
        {
            int val = mNumbers[i];
            mNumbers[i] = mNumbers[j];
            mNumbers[j] = val;
        }
    }

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
    }
    void ShellSort::dump()
    {
        mData.dump();
    }

} // end namespace Algorithms

int main()
{
    std::cout << "algorithms. " << std::endl;
    Algorithms::InsertionSort sorttest(10);
//    Algorithms::SelectionSort sorttest(10);

    std::cout << "array before sort" << std::endl;
    sorttest.dump();
    sorttest.sort();
    std::cout << "array after sort" << std::endl;
    sorttest.dump();
}
