#include "maxHeap.hpp"

namespace maxHeap {
	maxHeap::maxHeap(int capa) :capacity(capa),count(0){
			data = new int[capa+1];
		}
	maxHeap::~maxHeap() { delete[] data; }
		
	int maxHeap::size() { return count; }

	void maxHeap::insert(int item) {
		data[++count] = item;
		maxHeapUp(count);
	}

	int maxHeap::max() {
		int v = data[1];

		swap(data[count--], data[1]);
		maxHeapDown(1);

		return v;
	}

	void maxHeap::testPrint() {

		// 我们的testPrint只能打印100个元素以内的堆的树状信息
		if (size() >= 100) {
			cout << "This print function can only work for less than 100 int";
			return;
		}

		// 我们的testPrint只能处理整数信息
		if (typeid(int) != typeid(int)) {
			cout << "This print function can only work for int item";
			return;
		}

		cout << "The max heap size is: " << size() << endl;
		cout << "Data in the max heap: ";
		for (int i = 1; i <= size(); i++) {
			// 我们的testPrint要求堆中的所有整数在[0, 100)的范围内
			assert(data[i] >= 0 && data[i] < 100);
			cout << data[i] << " ";
		}
		cout << endl;
		cout << endl;

		int n = size();
		int max_level = 0;
		int number_per_level = 1;
		while (n > 0) {
			max_level += 1;
			n -= number_per_level;
			number_per_level *= 2;
		}

		int max_level_number = int(pow(2, max_level - 1));
		int cur_tree_max_level_number = max_level_number;
		int index = 1;
		for (int level = 0; level < max_level; level++) {
			string line1 = string(max_level_number * 3 - 1, ' ');

			int cur_level_number = min(count - int(pow(2, level)) + 1, int(pow(2, level)));
			bool isLeft = true;
			for (int index_cur_level = 0; index_cur_level < cur_level_number; index++, index_cur_level++) {
				putNumberInLine(data[index], line1, index_cur_level, cur_tree_max_level_number * 3 - 1, isLeft);
				isLeft = !isLeft;
			}
			cout << line1 << endl;

			if (level == max_level - 1)
				break;

			string line2 = string(max_level_number * 3 - 1, ' ');
			for (int index_cur_level = 0; index_cur_level < cur_level_number; index_cur_level++)
				putBranchInLine(line2, index_cur_level, cur_tree_max_level_number * 3 - 1);
			cout << line2 << endl;

			cur_tree_max_level_number /= 2;
		}
	}

	void maxHeap::maxHeapUp(int index) {
		while (index > 1 && data[index /2] < data[index]) {
			swap(data[index], data[index / 2]);
			index /= 2;
		}
	}

	void maxHeap::maxHeapDown(int index) {
		while (2 * index <= count) {
			int sub_left = 2 * index;
			int max_side = sub_left;
			if (sub_left + 1 <= count && data[sub_left + 1] > data[sub_left])
				max_side = sub_left + 1;
			if (data[index] < data[max_side])
				swap(data[index], data[max_side]);
			index = max_side;
		}
	}

	void maxHeap::putNumberInLine(int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft) {

		int sub_tree_width = (cur_tree_width - 1) / 2;
		int offset = index_cur_level * (cur_tree_width + 1) + sub_tree_width;
		assert(offset + 1 < line.size());
		if (num >= 10) {
			line[offset + 0] = '0' + num / 10;
			line[offset + 1] = '0' + num % 10;
		}
		else {
			if (isLeft)
				line[offset + 0] = '0' + num;
			else
				line[offset + 1] = '0' + num;
		}
	}

	void maxHeap::putBranchInLine(string &line, int index_cur_level, int cur_tree_width) {

		int sub_tree_width = (cur_tree_width - 1) / 2;
		int sub_sub_tree_width = (sub_tree_width - 1) / 2;
		int offset_left = index_cur_level * (cur_tree_width + 1) + sub_sub_tree_width;
		assert(offset_left + 1 < line.size());
		int offset_right = index_cur_level * (cur_tree_width + 1) + sub_tree_width + 1 + sub_sub_tree_width;
		assert(offset_right < line.size());

		line[offset_left + 1] = '/';
		line[offset_right + 0] = '\\';
	}

	int maxHeapMain()
	{
		cout << "------------maxHeap-------------" << endl;
		int *arr = TestHelper::generateRandomArray(100, 0, 100);

		maxHeap heap(100);

		for (int i = 0; i < 100; i++)
			heap.insert(arr[i]);

		for (int i = 99; i >= 0; i--)
			arr[i] = heap.max();

		for (int i = 0; i < 100; i++)
			cout << i << " ";
		cout << endl;

		delete[] arr;
		return 0;
	}

}
