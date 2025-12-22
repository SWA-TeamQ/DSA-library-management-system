#pragma once
#include <functional>
#include "dsa/Array.hpp"

using namespace std;

template <typename T, typename Func>
void mergeSort(Array<T> &arr, Func func, bool reverse = false)
{
    if (arr.size() <= 1)
        return;

    int mid = arr.size() / 2;

    Array<T> left;
    for(int i = 0; i < mid; i++){
        left.append(arr[i]);
    }

    Array<T> right;
    for(int i = mid; i < arr.size(); i++){
        right.append(arr[i]);
    }

    mergeSort(left, func, reverse);
    mergeSort(right, func, reverse);

    int i = 0, j = 0, k = 0;

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
