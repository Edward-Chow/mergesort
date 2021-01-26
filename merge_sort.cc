#include "merge_sort.h"

#include <iostream>
#include <initializer_list>
#include <string>

#include <benchmark/benchmark.h>
#include <gtest/gtest.h>
#include <glog/logging.h>
#include <gflags/gflags.h>

DEFINE_bool(print_log, true, "Allow to print log info to the console.");

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
void MergeSort<V>::DisplayElements() const {
    for (auto e : this->elements_) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

template<class V>
int MergeSort<V>::GetNumOfElements() const {
    return this->num_of_elements_;
}

template<class V>
std::vector<V> MergeSort<V>::GetElementsVec() const {
    return this->elements_;
}

void TestMergeSort() {
    MergeSort<int> testcase{1, 3, 2, 5, 4};
    testcase.MergeSortFunc(0, 4);
}

static void BM_TestMergeSort(benchmark::State &state) {
    for (auto _ : state) {
        TestMergeSort();
    }
}

BENCHMARK(BM_TestMergeSort);

TEST(MergeSortTest, CorrectResult) {
    MergeSort<int> testcase{1, 3, 2, 5, 4};
    testcase.MergeSortFunc(0, 4);
    std::vector<int> vec = testcase.GetElementsVec();
    std::vector<int> result = {1, 2, 3, 4, 5};
    ASSERT_EQ(vec.size(), result.size());
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(vec[i], result[i]);
    }
}

int main(int argc, char** argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    if (FLAGS_print_log) {
        LOG(INFO) << "CSCI499 Robust Software Design & Implementation";
    }
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
