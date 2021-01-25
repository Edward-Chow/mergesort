#ifndef CSCI499_MERGE_SORT_H
#define CSCI499_MERGE_SORT_H
#include <vector>
#include <initializer_list>

template<class V>
class MergeSort {
	public:
		MergeSort(const std::initializer_list<V> &list);
		void Merge(int start, int mid, int end);
		void MergeSortFunc(int start, int end);
		void DisplayElements();
	private:
		int num_of_elements_;
		std::vector<V> elements_;
};
#endif // CSCI499_MERGE_SORT_H
