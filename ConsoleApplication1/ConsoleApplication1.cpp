#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
	char ch;
	bool is_end;
	vector<Node*> children;

	Node(char c) : ch(c), is_end(false) {}
	Node* find_child(char c) const {
		for (auto child : children) {
			if (child->ch == c) {
				return child;
			}
		}
		return nullptr;
	}
	void add_child(Node* child) {
		children.push_back(child);
	}
};

class Trie {
private:
	Node* root;

public:
	Trie() : root(new Node('\0')) {}

	void insert(const string& str) {
		Node* node = root;
		for (char c : str) {
			Node* child = node->find_child(c);
			if (child) {
				node = child;
			}
			else {
				child = new Node(c);
				node->add_child(child);
				node = child;
			}
		}
		node->is_end = true;
	}

	bool contains(const string& str) const {
		Node* node = root;
		for (char c : str) {
			node = node->find_child(c);
			if (!node) {
				return false;
			}
		}
		return node->is_end;
	}

	vector<string> autocomplete(const string& prefix) const {
		vector<string> res;
		Node* node = root;
		for (char c : prefix) {
			node = node->find_child(c);
			if (!node) {
				return res;
			}
		}
		autocomplete_helper(node, prefix, res);
		return res;
	}

private:
	void autocomplete_helper(const Node* node, const string& prefix, vector<string>& res) const {
		if (node->is_end) {
			res.push_back(prefix);
		}
		for (auto child : node->children) {
			autocomplete_helper(child, prefix + child->ch, res);
		}
	}
};

int main() {
	Trie trie;
	trie.insert("apple");
	trie.insert("banana");
	trie.insert("cherry");
	trie.insert("orange");
	trie.insert("pineapple");

	while (true) {
		cout << "Enter a prefix: ";
		string prefix;
		getline(cin, prefix);
		if (!prefix.empty()) {
			vector<string> completions = trie.autocomplete(prefix);
			if (completions.empty()) {
				cout << "No completions found.\n";
			}
			else {
				cout << "Completions: ";
				for (const string& s : completions) {
					cout << s << ' ';
				}
				cout << '\n';
			}
		}
	}

	return 0;
}