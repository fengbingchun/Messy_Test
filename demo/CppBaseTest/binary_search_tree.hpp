#ifndef FBC_CPPBASE_TEST_BINARY_SEARCH_TREE_HPP_
#define FBC_CPPBASE_TEST_BINARY_SEARCH_TREE_HPP_

// Blog: https://blog.csdn.net/fengbingchun/article/details/83239268

#include <vector>
#include <fstream>
#include <string>

namespace binary_search_tree_ {

typedef struct info {
	int id; // suppose id is unique
	std::string name;
	int age;
	std::string addr;
} info;

typedef struct node {
	info data;
	node* left = nullptr;
	node* right = nullptr;
} node;

class BinarySearchTree {
public:
	BinarySearchTree() = default;
	~BinarySearchTree() { DeleteTree(tree); }

	typedef std::tuple<int, int, std::string, int, std::string> row; // flag(-1: no node, 0: have a node), id, name, age, addr

	int Init(const std::vector<info>& infos); // create binary search tree
	bool Search(int id, info& data) const;
	int Insert(const info& data);
	int Delete(int id); // delete a node
	int Traversal(int type) const; // 0: pre-order, 1: in-order, 2: post-order, 3: level
	int GetMaxDepth() const; // get tree max depth
	int GetMinDepth() const; // get tree min depth
	int GetNodesCount() const; // get tree node count
	bool IsBinarySearchTree() const; // whether or not is a binary search tree
	//bool IsBinaryBalanceTree() const; // whether ot not is a binary balance tree
	int GetMinValue(info& data) const;
	int GetMaxValue(info& data) const;
	int SaveTree(const char* name) const; // tree write in txt file
	int LoadTree(const char* name);

protected:
	void PreorderTraversal(const node* ptr) const;
	void InorderTraversal(const node* ptr) const;
	void PostorderTraversal(const node* ptr) const;
	void LevelTraversal(const node* ptr) const;
	void LevelTraversal(const node* ptr, int level) const;
	void DeleteTree(node* ptr);
	void Insert(node* ptr, const info& data);
	const node* Search(const node* ptr, int id) const;
	void IsBinarySearchTree(const node* ptr, bool is_bst) const;
	int GetNodesCount(const node* ptr) const;
	int GetMaxDepth(const node* ptr) const;
	int GetMinDepth(const node* ptr) const;
	//bool IsBinaryBalanceTree(const node* ptr) const;
	node* Delete(node* ptr, int id); // return new root
	node* GetMinValue(node* ptr);
	void NodeToRow(const node* ptr, std::vector<row>& rows, int pos) const;
	void RowToNode(node* ptr, const std::vector<row>& rows, int n, int pos);

private:
	node* tree = nullptr;
	bool flag;
};

int test_binary_search_tree();

} // namespace binary_search_tree_

#endif // FBC_CPPBASE_TEST_BINARY_SEARCH_TREE_HPP_

