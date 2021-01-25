#include "merge_sort.h"
#include <iostream>
#include <initializer_list>

template <class V>
MergeSort<V>::MergeSort(const std::initializer_list<V> &list) {
	for (auto element : list) {
    	this->elements_.push_back(element);
	}
    this->num_of_elements_ = this->elements_.size();
}

template<class V>
void MergeSort<V>::Merge(int start, int mid, int end) {
    std::vector<V> temp_vec(this->elements_);
    int i = start, j = mid + 1, k = start;
    while (i <= mid && j <= end) {
        if (temp_vec[i] < temp_vec[j])
            this->elements_[k++] = temp_vec[i++];
        else
            this->elements_[k++] = temp_vec[j++];
    }

    while (i <= mid) this->elements_[k++] = temp_vec[i++];
    while (j <= end) this->elements_[k++] = temp_vec[j++];
}

template<class V>
void MergeSort<V>::MergeSortFunc(int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;
        this->MergeSortFunc(start, mid);
        this->MergeSortFunc(mid + 1, end);
        this->Merge(start, mid, end);
    }
}

template<class V>
void MergeSort<V>::DisplayElements() {
    for (auto e : this->elements_) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

int main() {
    MergeSort<int> testcase{1, 3, 2, 5, 4};
    testcase.DisplayElements();
    testcase.MergeSortFunc(0, 4);
    testcase.DisplayElements();
    return 0;
}
