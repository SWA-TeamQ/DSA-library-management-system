#pragma once

#include <vector>
#include <string>
#include "models/Book.hpp"

using namespace std;

#pragma once
#include <vector>

template <typename T, typename Compare>
void mergeSort(std::vector<T>& arr, Compare compare)
{
    if (arr.size() <= 1)
        return;

    int mid = arr.size() / 2;

    std::vector<T> left(arr.begin(), arr.begin() + mid);
    std::vector<T> right(arr.begin() + mid, arr.end());

    mergeSort(left, compare);
    mergeSort(right, compare);

    int i = 0, j = 0, k = 0;

    while (i < left.size() && j < right.size())
    {
        if (compare(left[i], right[j]))
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < left.size())
        arr[k++] = left[i++];

    while (j < right.size())
        arr[k++] = right[j++];
}
