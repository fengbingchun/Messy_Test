#include "sort.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

const std::vector<int> array_src{ 12, -32, 138, -54, 34, 87, 200, -1, -901, 88 };

static void print_result(const std::vector<int>& vec)
{
	for (int i = 0; i < vec.size(); i++)
		fprintf(stderr, "%d  ", vec[i]);
	fprintf(stderr, "\n");
}

int test_sort_bubble() // √∞≈›≈≈–Ú
{
	// reference: http://mathbits.com/MathBits/CompSci/Arrays/Bubble.htm
	std::vector<int> vec(array_src.begin(), array_src.end());
	int tmp = 0;

	for (int i = 1; i < vec.size(); i++) {
		for (int j = 0; j < vec.size() - 1; j++) {
			if (vec[j + 1] < vec[j]) {
				tmp = vec[j];
				vec[j] = vec[j + 1];
				vec[j + 1] = tmp;
			}
		}
	}

	fprintf(stderr, "bubble sort result: \n");
	print_result(vec);

	return 0;
}

int test_sort_insertion() // ≤Â»Î≈≈–Ú
{
	// reference: http://cforbeginners.com/insertionsort.html
	std::vector<int> vec(array_src.begin(), array_src.end());
	int tmp = 0, j = 0;

	for (int i = 1; i < vec.size(); i++){
		j = i;

		while (j > 0 && vec[j] < vec[j - 1]){
			tmp = vec[j];
			vec[j] = vec[j - 1];
			vec[j - 1] = tmp;
			j--;
		}
	}

	fprintf(stderr, "insertion sort result: \n");
	print_result(vec);

	return 0;
}

int test_sort_selection() // —°‘Ò≈≈–Ú
{
	// reference: http://mathbits.com/MathBits/CompSci/Arrays/Selection.htm
	std::vector<int> vec(array_src.begin(), array_src.end());
	int tmp = 0;

	for (int i = vec.size() - 1; i > 0; i--) {
		int first = 0;
		for (int j = 1; j <= i; j++) {
			if (vec[j] > vec[first])
				first = j;
		}

		tmp = vec[first];
		vec[first] = vec[i];
		vec[i] = tmp;
	}

	fprintf(stderr, "selection sort result: \n");
	print_result(vec);

	return 0;
}

int test_sort_shell() // œ£∂˚≈≈–Ú
{
	// reference: http://www.cplusplus.com/forum/general/123961/
	std::vector<int> vec(array_src.begin(), array_src.end());
	int tmp = 0, gap = 0;

	for (int gap = vec.size() / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < vec.size(); i++) {
			for (int j = i - gap; j >= 0 && vec[j] > vec[j + gap]; j -= gap) {
				tmp = vec[j];
				vec[j] = vec[j + gap];
				vec[j + gap] = tmp;
			}
		}
	}

	fprintf(stderr, "shell sort result: \n");
	print_result(vec);

	return 0;
}

// left is the index of the leftmost element of the subarray
// right is one past the index of the rightmost element
static void merge(std::vector<int>& vecSrc, int left, int right, std::vector<int>& vecDst)
{
	// base case: one element
	if (right == left + 1) {
		return;
	} else {
		int i = 0;
		int length = right - left;
		int midpoint_distance = length / 2;
		/* l and r are to the positions in the left and right subarrays */
		int l = left, r = left + midpoint_distance;

		/* sort each subarray */
		merge(vecSrc, left, left + midpoint_distance, vecDst);
		merge(vecSrc, left + midpoint_distance, right, vecDst);

		/* merge the arrays together using scratch for temporary storage */
		for (i = 0; i < length; i++) {
			/* Check to see if any elements remain in the left array; if so,
			* we check if there are any elements left in the right array; if
			* so, we compare them.  Otherwise, we know that the merge must
			* use take the element from the left array */
			if (l < left + midpoint_distance && (r == right || std::min(vecSrc[l], vecSrc[r]) == vecSrc[l])) {
				vecDst[i] = vecSrc[l];
				l++;
			} else {
				vecDst[i] = vecSrc[r];
				r++;
			}
		}
		/* Copy the sorted subarray back to the input */
		for (i = left; i < right; i++) {
			vecSrc[i] = vecDst[i - left];
		}
	}
}

int test_sort_merge() // πÈ≤¢≈≈–Ú
{
	// reference: http://www.cprogramming.com/tutorial/computersciencetheory/merge.html
	std::vector<int> vecSrc(array_src.begin(), array_src.end());
	std::vector<int> vecDst(array_src.size());

	merge(vecSrc, 0, vecSrc.size(), vecDst);

	fprintf(stderr, "merge sort result: \n");
	print_result(vecDst);

	return 0;
}

static void quick(std::vector<int>& vec, int left, int right)
{
	int i = left, j = right;
	int tmp;
	int pivot = vec[(left + right) / 2];

	// partition
	while (i <= j) {
		while (vec[i] < pivot)
			i++;
		while (vec[j] > pivot)
			j--;
		if (i <= j) {
			tmp = vec[i];
			vec[i] = vec[j];
			vec[j] = tmp;
			i++;
			j--;
		}
	};

	// recursion
	if (left < j)
		quick(vec, left, j);
	if (i < right)
		quick(vec, i, right);
}

int test_sort_quick() // øÏÀŸ≈≈–Ú
{
	// reference: http://www.algolist.net/Algorithms/Sorting/Quicksort
	std::vector<int> vec(array_src.begin(), array_src.end());

	quick(vec, 0, vec.size() - 1);

	fprintf(stderr, "quick sort result: \n");
	print_result(vec);

	return 0;
}

static void max_heapify(std::vector<int>& vec, int i, int n)
{
	int temp = vec[i];
	int j = 2 * i;

	while (j <= n) {
		if (j < n && vec[j + 1] > vec[j])
			j = j + 1;

		if (temp > vec[j]) {
			break;
		} else if (temp <= vec[j]) {
			vec[j / 2] = vec[j];
			j = 2 * j;
		}
	}

	vec[j / 2] = temp;
}

static void heapsort(std::vector<int>& vec, int n)
{
	for (int i = n; i >= 2; i--) {
		int temp = vec[i];
		vec[i] = vec[1];
		vec[1] = temp;

		max_heapify(vec, 1, i - 1);
	}
}

static void build_maxheap(std::vector<int>& vec, int n)
{
	for (int i = n / 2; i >= 1; i--)
		max_heapify(vec, i, n);
}

int test_sort_heap() // ∂—≈≈–Ú
{
	// reference: http://proprogramming.org/heap-sort-in-c/
	std::vector<int> vec(array_src.begin(), array_src.end());
	vec.insert(vec.begin(), -1);

	build_maxheap(vec, vec.size()-1);
	heapsort(vec, vec.size()-1);

	std::vector<int> vecDst(vec.begin() + 1, vec.end());
	fprintf(stderr, "heap sort result: \n");
	print_result(vecDst);

	return 0;
}

static bool cmp(int i, int j)
{
	return (i<j);
}

int test_sort_STL() // std::sort
{
	// reference: http://www.cplusplus.com/reference/algorithm/sort/
	std::vector<int> vec(array_src.begin(), array_src.end());

	std::sort(vec.begin(), vec.end(), cmp);

	fprintf(stderr, "STL sort result: \n");
	print_result(vec);

	std::vector<int> vec1(array_src.begin(), array_src.end());

	std::stable_sort(vec1.begin(), vec1.end(), cmp);

	fprintf(stderr, "STL stable sort result: \n");
	print_result(vec1);

	return 0;
}

