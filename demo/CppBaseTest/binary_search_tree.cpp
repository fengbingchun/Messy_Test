#include "binary_search_tree.hpp"
#include <set>
#include <iostream>
#include <limits>
#include <tuple>
#include <string>
#include <sstream>
#include <string.h>
#include <algorithm>

namespace binary_search_tree_ {

int BinarySearchTree::Init(const std::vector<info>& infos)
{
	std::vector<int> ids;
	for (const auto& info : infos) {
		ids.emplace_back(info.id);
	}

	std::set<int> id_set(ids.cbegin(), ids.cend());
	if (id_set.size() != ids.size()) {
		fprintf(stderr, "id must be unique\n");
		return -1;
	}

	for (const auto& info : infos) {
		Insert(info);
	}

	return 0;
}

bool BinarySearchTree::Search(int id, info& data) const
{
	const node* root = tree;
	const node* tmp = Search(root, id);
	if (tmp) {
		data = tmp->data;
		return true;
	} else {
		return false;
	}
}

const node* BinarySearchTree::Search(const node* ptr, int id) const
{
	if (ptr) {
		if (ptr->data.id == id) {
			return ptr;
		} else if (ptr->data.id > id) {
			return Search(ptr->left, id);
		} else {
			return Search(ptr->right, id);
		}
	} else {
		return nullptr;
	}
}

int BinarySearchTree::Insert(const info& data)
{
	flag = true;

	if (tree) {
		Insert(tree, data);
	} else {
		tree = new node;
		tree->data = data;
		tree->left = nullptr;
		tree->right = nullptr;
	}

	return (int)flag;
}

void BinarySearchTree::Insert(node* ptr, const info& data)
{
	if (ptr->data.id == data.id) {
		flag = false;
		return;
	}

	if (ptr->data.id < data.id) {
		if (ptr->right) {
			Insert(ptr->right, data);
		} else {
			ptr->right = new node;
			ptr->right->data = data;
			ptr->right->left = nullptr;
			ptr->right->right = nullptr;
		}
	} else {
		if (ptr->left) {
			Insert(ptr->left, data);
		} else {
			ptr->left = new node;
			ptr->left->data = data;
			ptr->left->left = nullptr;
			ptr->left->right = nullptr;
		}
	}
}

bool BinarySearchTree::IsBinarySearchTree() const
{
	bool is_bst = true;
	const node* root = tree;
	IsBinarySearchTree(root, is_bst);

	return is_bst;
}

void BinarySearchTree::IsBinarySearchTree(const node* ptr, bool is_bst) const
{
	static int last_data = std::numeric_limits<int>::min();
	if (!ptr) return;

	IsBinarySearchTree(ptr->left, is_bst);

	if (last_data < ptr->data.id) last_data = ptr->data.id;
	else {
		is_bst = false;
		return;
	}

	IsBinarySearchTree(ptr->right, is_bst);
}

int BinarySearchTree::Traversal(int type) const
{
	if (!tree) {
		fprintf(stderr, "Error: it is an empty tree\n");
		return -1;
	}

	const node* root = tree;
	if (type == 0)
		PreorderTraversal(root);
	else if (type == 1)
		InorderTraversal(root);
	else if (type == 2)
		PostorderTraversal(root);
	else if (type == 3)
		LevelTraversal(root);
	else {
		fprintf(stderr, "Error: don't suppot traversal type, type only support: 0: pre-order, 1: in-order, 2: post-order\n");
		return -1;
	}

	return 0;
}

void BinarySearchTree::PreorderTraversal(const node* ptr) const
{
	if (ptr) {
		fprintf(stdout, "Info: id: %d, name: %s, age: %d, addr: %s\n",
			ptr->data.id, ptr->data.name.c_str(), ptr->data.age, ptr->data.addr.c_str());
		PreorderTraversal(ptr->left);
		PreorderTraversal(ptr->right);
	} 
}

void BinarySearchTree::InorderTraversal(const node* ptr) const
{
	if (ptr) {
		InorderTraversal(ptr->left);
		fprintf(stdout, "Info: id: %d, name: %s, age: %d, addr: %s\n",
			ptr->data.id, ptr->data.name.c_str(), ptr->data.age, ptr->data.addr.c_str());
		InorderTraversal(ptr->right);
	} 
}

void BinarySearchTree::PostorderTraversal(const node* ptr) const
{
	if (ptr) {
		PostorderTraversal(ptr->left);
		PostorderTraversal(ptr->right);
		fprintf(stdout, "Info: id: %d, name: %s, age: %d, addr: %s\n",
			ptr->data.id, ptr->data.name.c_str(), ptr->data.age, ptr->data.addr.c_str());
	} 
}

void BinarySearchTree::LevelTraversal(const node* ptr) const
{
	int h = GetMaxDepth();

	for (int i = 1; i <= h; ++i)
		LevelTraversal(ptr, i);	
}

void BinarySearchTree::LevelTraversal(const node* ptr, int level) const
{
	if (!ptr) return;

	if (level == 1)
		fprintf(stdout, "Info: id: %d, name: %s, age: %d, addr: %s\n",
			ptr->data.id, ptr->data.name.c_str(), ptr->data.age, ptr->data.addr.c_str());
	else if (level > 1) {
		LevelTraversal(ptr->left, level-1);
		LevelTraversal(ptr->right, level-1);
	}
}

void BinarySearchTree::DeleteTree(node* ptr)
{
	if (ptr) {	
		DeleteTree(ptr->left);
		DeleteTree(ptr->right);
		delete ptr;
	}
}

int BinarySearchTree::GetNodesCount() const
{	
	const node* root = tree;
	return GetNodesCount(root);
}

int BinarySearchTree::GetNodesCount(const node* ptr) const
{
	if (!ptr) return 0;
	else return GetNodesCount(ptr->left) + 1 + GetNodesCount(ptr->right);
}

int BinarySearchTree::GetMaxDepth() const
{
	const node* root = tree;
	return GetMaxDepth(root);
}

int BinarySearchTree::GetMaxDepth(const node* ptr) const
{
	if (!ptr) return 0;

	int left_depth = GetMaxDepth(ptr->left);
	int right_depth = GetMaxDepth(ptr->right);

	return std::max(left_depth, right_depth) + 1;
}

int BinarySearchTree::GetMinDepth() const
{
	const node* root = tree;
	return GetMinDepth(root);
}

int BinarySearchTree::GetMinDepth(const node* ptr) const
{
	if (!ptr) return 0;

	int left_depth = GetMaxDepth(ptr->left);
	int right_depth = GetMaxDepth(ptr->right);

	return std::min(left_depth, right_depth) + 1;
}

/*bool BinarySearchTree::IsBinaryBalanceTree() const
{
	const node* root = tree;
	return IsBinaryBalanceTree(root);
}

bool BinarySearchTree::IsBinaryBalanceTree(const node* ptr) const
{
	// TODO: code need to modify
	if (GetMaxDepth(ptr) - GetMinDepth(ptr) <= 1) return true;
	else return false;	
}*/

int BinarySearchTree::GetMinValue(info& data) const
{
	if (!tree) {
		fprintf(stderr, "Error： it is a empty tree\n");
		return -1;
	}

	const node* root = tree;
	while (root->left) root = root->left;
	data = root->data;

	return 0;
}

int BinarySearchTree::GetMaxValue(info& data) const
{
	if (!tree) {
		fprintf(stderr, "Error： it is a empty tree\n");
		return -1;
	}

	const node* root = tree;
	while (root->right) root = root->right;
	data = root->data;

	return 0;
}

int BinarySearchTree::Delete(int id)
{
	if (!tree) {
		fprintf(stderr, "Error: it is a empty tree\n");
		return -1;
	}

	const node* root = tree;
	const node* ret = Search(root, id);
	if (!ret) {
		fprintf(stdout, "Warning: this id don't exist in the tree: %d", id);
		return 0;
	}	

	tree = Delete(tree, id);	

	return 0;
}

node* BinarySearchTree::GetMinValue(node* ptr)
{
	node* tmp = ptr;
	while (tmp->left) tmp = tmp->left;

	return tmp;
}

node* BinarySearchTree::Delete(node* ptr, int id)
{
	if (!ptr) return ptr;

	if (id < ptr->data.id)
		ptr->left = Delete(ptr->left, id);
	else if (id > ptr->data.id) 
		ptr->right = Delete(ptr->right, id);
	else {
		if (!ptr->left) {
			node* tmp = ptr->right;
			delete ptr;
			return tmp;
		} else if (!ptr->right) {
			node* tmp = ptr->left;
			delete ptr;
			return tmp;
		}

		node* tmp = GetMinValue(ptr->right);
		ptr->data = tmp->data;
		ptr->right = Delete(ptr->right, tmp->data.id);
	}

	return ptr;	
}

int BinarySearchTree::SaveTree(const char* name) const
{
	std::ofstream file(name, std::ios::out);
	if (!file.is_open()) {
		fprintf(stderr, "Error: open file fail: %s\n", name);
		return -1;
	}

	const node* root = tree;
	int max_depth = GetMaxDepth(root);
	int max_nodes = (1 << max_depth) -1;
	root = tree;
	int nodes_count = GetNodesCount(root);
	//fprintf(stdout, "max_depth: %d, max nodes: %d\n", max_depth, max_nodes);
	file<<nodes_count<<","<<max_depth<<std::endl;
	std::vector<row> vec(max_nodes, std::make_tuple(-1, -1, " ", -1, " "));
	root = tree;
	NodeToRow(root, vec, 0);	

	for (const auto& v : vec) {
		file << std::get<0>(v)<<","<<std::get<1>(v)<<","<<std::get<2>(v)<<","<<std::get<3>(v)<<","<<std::get<4>(v)<<std::endl;
	}

	file.close();
	return 0;
}

void BinarySearchTree::NodeToRow(const node* ptr, std::vector<row>& rows, int pos) const
{
	if (!ptr) return;
 	
	rows[pos] = std::make_tuple(0, ptr->data.id, ptr->data.name, ptr->data.age, ptr->data.addr);

	if (ptr->left) NodeToRow(ptr->left, rows, 2 * pos + 1);
	if (ptr->right) NodeToRow(ptr->right, rows, 2 * pos + 2);
}

int BinarySearchTree::LoadTree(const char* name)
{
	std::ifstream file(name, std::ios::in);
	if (!file.is_open()) {
		fprintf(stderr, "Error: open file fail: %s\n", name);
		return -1;
	}

	std::string line, cell;
	std::getline(file, line);
	std::stringstream line_stream(line);
	std::vector<int> vec;
	while (std::getline(line_stream, cell, ',')) {
		vec.emplace_back(std::stoi(cell));
	}
	if (vec.size() != 2) {
		fprintf(stderr, "Error: parse txt file fail\n");
		return -1;
	}
	fprintf(stdout, "nodes count: %d, max depth: %d\n", vec[0], vec[1]);

	int max_nodes = (1 << vec[1]) - 1;
	std::vector<row> rows;

	while (std::getline(file, line)) {
		std::stringstream line_stream2(line);
		std::vector<std::string> strs;
		while (std::getline(line_stream2, cell, ',')) {
			strs.emplace_back(cell);
		}
		if (strs.size() != 5) {
			fprintf(stderr, "Error: parse line fail\n");
			return -1;
		}

		row tmp = std::make_tuple(std::stoi(strs[0]), std::stoi(strs[1]), strs[2], std::stoi(strs[3]), strs[4]);
		rows.emplace_back(tmp);
	}

	if (rows.size() != max_nodes || std::get<0>(rows[0]) == -1) {
		fprintf(stderr, "Error: parse txt file line fail\n");
		return -1;
	}

	node* root = new node;
	root->data = {std::get<1>(rows[0]), std::get<2>(rows[0]), std::get<3>(rows[0]), std::get<4>(rows[0])};
	root->left = nullptr;
	root->right = nullptr;
	tree = root;

	RowToNode(root, rows, max_nodes, 0);

	file.close();
	return 0;
}

void BinarySearchTree::RowToNode(node* ptr, const std::vector<row>& rows, int n, int pos)
{
	if (!ptr || n == 0) return;

	int new_pos = 2 * pos + 1;
	if (new_pos < n && std::get<0>(rows[new_pos]) != -1) {
		ptr->left = new node;
		ptr->left->data = {std::get<1>(rows[new_pos]), std::get<2>(rows[new_pos]), std::get<3>(rows[new_pos]), std::get<4>(rows[new_pos])};
		ptr->left->left = nullptr;
		ptr->left->right = nullptr;

		RowToNode(ptr->left, rows, n, new_pos);
	}

	new_pos = 2 * pos + 2;
	if (new_pos < n && std::get<0>(rows[new_pos]) != -1) {
		ptr->right = new node;
		ptr->right->data = {std::get<1>(rows[new_pos]), std::get<2>(rows[new_pos]), std::get<3>(rows[new_pos]), std::get<4>(rows[new_pos])};
		ptr->right->left = nullptr;
		ptr->right->right = nullptr;

		RowToNode(ptr->right, rows, n, new_pos);
	}	
}

////////////////////////////////////////////////
int test_binary_search_tree()
{
	fprintf(stdout, "create binary search tree:\n");
	std::vector<info> infos{{1004, "Tom", 8, "Beijing"}, {1005, "Jack", 9, "Tianjin"}, {1003, "Mark", 6, "Hebei"}, {1009, "Lisa", 11, "Beijiing"}, {1007, "Piter", 4, "Hebei"}, {1001, "Viner", 6, "Beijing"}};

	BinarySearchTree bstree;
	bstree.Init(infos);
	
	fprintf(stdout, "\ninsert operation:\n");
	std::vector<info> infos2{{1007, "xxx", 11, "yyy"}, {1008, "Lorena", 22, "Hebie"}, {1002, "Eillen", 14, "Shanxi"}};
	for (const auto& info : infos2) {
		int flag = bstree.Insert(info);
		if (flag) fprintf(stdout, "insert success\n");
		else fprintf(stdout, "Warning: id %d already exists, no need to insert\n", info.id);
	}

	fprintf(stdout, "\ntraversal operation:\n");
	fprintf(stdout, "pre-order traversal:\n");
	bstree.Traversal(0);
	fprintf(stdout, "in-order traversal:\n");
	bstree.Traversal(1);
	fprintf(stdout, "post-order traversal:\n");
	bstree.Traversal(2);
	fprintf(stdout, "level traversal:\n");
	bstree.Traversal(3);

	fprintf(stdout, "\nsearch operation:\n");
	std::vector<int> ids {1009, 2000};
	for (auto id : ids) {
		info ret;
		bool flag = bstree.Search(id, ret);
		if (flag)
			fprintf(stdout, "found: info: %d, %s, %d, %s\n", ret.id, ret.name.c_str(), ret.age, ret.addr.c_str());
		else
			fprintf(stdout, "no find: no id info: %d\n", id);
	}

	fprintf(stdout, "\nwhether or not is a binary search tree operation:\n");
	bool flag2 = bstree.IsBinarySearchTree();
	if (flag2) fprintf(stdout, "it is a binary search tree\n");
	else fprintf(stdout, "it is not a binary search tree\n");

	fprintf(stdout, "\ncalculate node count operation:\n");
	int count = bstree.GetNodesCount();
	fprintf(stdout, "tree node count: %d\n", count);
	
	fprintf(stdout, "\ncalculate tree depth operation:\n");
	int max_depth = bstree.GetMaxDepth();
	int min_depth = bstree.GetMinDepth();
	fprintf(stdout, "tree max depth: %d, min depth: %d\n", max_depth, min_depth);
	
	/*fprintf(stdout, "\nwhether or not is a binary balance tree operation:\n");
	flag2 = bstree.IsBinaryBalanceTree();
	if (flag2) fprintf(stdout, "it is a binary balance tree\n");
	else fprintf(stdout, "it is not a binary balance tree\n");*/
	
	fprintf(stdout, "\nget min and max value(id):\n");
	info value;
	bstree.GetMinValue(value);
	fprintf(stdout, "tree min value: id: %d\n", value.id);
	bstree.GetMaxValue(value);
	fprintf(stdout, "tree max value: id: %d\n", value.id);

	fprintf(stdout, "\ndelete node operation:\n");
	bstree.Delete(1005);
	bstree.Traversal(1);

	fprintf(stdout, "\nsave tree operation:\n");
#ifdef _MSC_VER
	char* name = "E:/GitCode/Messy_Test/testdata/binary_search_tree.model";
#else
	char* name = "testdata/binary_search_tree.model";
#endif
	bstree.SaveTree(name);

	fprintf(stdout, "\nload tree operation:\n");
	BinarySearchTree bstree2;
	bstree2.LoadTree(name);
	int count2 = bstree2.GetNodesCount();
	int max_depth2 = bstree2.GetMaxDepth();
	int min_depth2 = bstree2.GetMinDepth();
	fprintf(stdout, "tree node count: %d, tree max depth: %d, min depth: %d\n", count2, max_depth2, min_depth2);
	bstree2.Traversal(1);

	return 0;
}

} // namespace binary_search_tree_

