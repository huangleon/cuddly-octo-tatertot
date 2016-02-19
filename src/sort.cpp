#include "sort.h"
#include <iostream>

namespace Algorithms {

    InsertionSort::InsertionSort(int count)
        : COUNT(count)
    {
        srand(
        mNumbers = new int[COUNT];
        for (int i = 0; i < COUNT; i++)
            mNumbers[i] = rand();
    }
    InsertionSort::~InsertionSort()
    {
        delete[] mNumbers;
    }

    void InsertionSort::sort()
    {
        for (int i = 0; i < COUNT - 1; i++)
        {
            for (int j = i + 1; j > 0; j--)
            {
                // compare j with j - 1
                if (mNumbers[j] < mNumbers[j - 1])
                    exch(j, j - 1);
                else
                    break;
            }
        }
    }
    void InsertionSort::dump()
    {
        for (int i = 0; i < COUNT; i++)
            std::cout << mNumbers[i] << " ";
        std::cout << std::endl;
    }
    void InsertionSort::exch(int i, int j)
    {
        int val = mNumbers[i];
        mNumbers[i] = mNumbers[j];
        mNumbers[j] = val;
    }
} // end namespace Algorithms

int main()
{
    std::cout << "algorithms. " << std::endl;
}
