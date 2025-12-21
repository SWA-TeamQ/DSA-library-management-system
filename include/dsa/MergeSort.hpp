#pragma once
#include <vector>
#include <functional>

template <typename T, typename Func>
void mergeSort(std::vector<T> &arr, Func func, bool reverse = false)
{
    if (arr.size() <= 1)
        return;

    size_t mid = arr.size() / 2;

    std::vector<T> left(arr.begin(), arr.begin() + mid);
    std::vector<T> right(arr.begin() + mid, arr.end());

    mergeSort(left, func, reverse);
    mergeSort(right, func, reverse);

    size_t i = 0, j = 0, k = 0;

    while (i < left.size() && j < right.size())
    {
        if(!reverse){
            if(func(left[i]) <= func(right[j]))
                arr[k++] = left[i++];
            else
                arr[k++] = right[j++];
        }
        else{
            if(func(left[i]) >= func(right[j]))
                arr[k++] = left[i++];
            else
                arr[k++] = right[j++];
        }
    }

    while (i < left.size())
        arr[k++] = left[i++];

    while (j < right.size())
        arr[k++] = right[j++];
}
