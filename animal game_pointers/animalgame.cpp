#include <iostream>
#include <string>
using namespace std;

class node {
	string content;
	node *yes;
	node *no;

	public:
	node(string content) {
		this ->content=content; 
		yes= nullptr;
		no= nullptr;
	}

	node *getYes() {
		return yes;
	}

	void setYes(node *dest) {
		yes= dest;
	}

	node *getNo() {
		return no;
	}

	void setNo(node *dest) {
		no= dest;
	}

	void setContent(string content) {
		this->content=content;
	}

	string getContent() {
		return content;
	}
};

class animaltree {
	node *root;
	node *current; 

	public: 
	animaltree(string first_question, string first_animal) {
		root=new node(first_question);
		node *animal= new node(first_animal);
		root->setYes(animal);
		current=root;
	}

	~animaltree() {
		deleteTree(root);
	}

	void deleteTree(node *n) {
		if (n==nullptr) { 
			return;
		}
		if (n->getNo() != nullptr) {
			deleteTree(n->getNo());
		}
		if (n->getYes() != nullptr) {
			deleteTree(n->getYes());
		}
		delete n;
	}

	void createLeaves(string new_question, string correct_animal) {
		node *y=new node(correct_animal);
		node *n=new node(current->getContent());
		current->setContent(new_question);
		current->setYes(y);
		current->setNo(n);
	}

	void createFirstNo(string animal) {
		node *n=new node(animal);
		current->setNo(n);
	}

	void reset() {
		cout << "Think of a new animal." << endl;
		current=root;
	}

	string getContent() { 
		return current->getContent();
	}

	void followYes() {
		current= current->getYes();
	}

	void followNo() {
		current= current->getNo();
	}

	bool isAnimal() {
		if (!current->getYes() && !current->getNo()) {
			return true;
		} else {
			return false;
		}
		
	}

	bool hasYes() {
		if (current->getYes()) {
			return true;
		} else {
			return false;
		}
	}

	bool hasNo() {
		if (current->getNo()) {
			return true;
		} else {
			return false;
		}
	}
};

int main() {
	string q1, a1;
	cout << "Tell me an animal." << endl;
	getline(cin, a1);
	cout << "Tell me a question which has answer 'yes' for this animal." << endl;
	getline(cin, q1);
	animaltree tree(q1, a1);

	cout << "Think of a new animal." << endl;

	while(1) {
		cout << tree.getContent() << endl;
		string ans;
		getline(cin, ans);

		if(ans=="exit") {
			break;
		}
		if(ans=="y") { 
			if (!tree.isAnimal()) {
				tree.followYes();
			} else {
			tree.reset();
			}
		}
		if(ans=="n") {
			if (tree.hasNo()) {
				tree.followNo();
			} else if (tree.hasYes()) { 
				cout << "What is your animal?" << endl;
			        getline(cin, a1);
				tree.createFirstNo(a1);
				tree.reset();
			} else if (!tree.hasYes()) {
				cout << "What is your animal?" << endl;
				getline(cin, a1);
				cout << "Better question to ask?" << endl;
				getline(cin, q1);
				tree.createLeaves(q1, a1);
				tree.reset();
			}

		}
	}
}
