#include <iostream>
#include <string>
using namespace std;

class node {
        string content;
        node *yes;
        node *no;

        public:
        node(string content) {//constructor
                this->content=content;
                yes= nullptr;
                no= nullptr;
                //want this because in next constructor immediately set yes=yes, make sure you have no bad pointers
        }
        node(string content, node *yes, node *no) {//do we need this?
                this->content= content;
                this->yes= yes;
                this->no= no;
        } // if you use this, then add this:
        node() {//default constructor? do we need this?
                content= "NO DATA!";
                yes=nullptr;
                no=nullptr;
        }


        /*~node() {//cant use delete if you didnt use new--itll crash
                 //so if a node where created like node n; node q; n.yes=&q; itll delete this and crash
                if (yes!=nullptr) {
                        delete yes;
                }
                if (no!=nullptr) {
                        delete no;
                }
        }*/
        node *getYes() {//getter-- *getYes is return type, () no input parameters
                return yes;
        }
        void setYes(node *dest) {//setter
                                 //makes a yes node
                yes= dest;
        }
        node *getNo() {//"follow the address of no to get to its value"
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
        node *root;//why does root need to be a pointer?
        node *current; //needs to live as long as object lives so put it here
        node *update;
        public:
        //animal should be 'yes' answer to the questipn
        animaltree(string first_question, string first_animal) {//set up the initial tree structure and content
                root=new node(first_question);//uses the first node constructor with string input
                node *animal= new node(first_animal);//uses first node cosntructor
                //root->yes=animal; this doesnt work becuase yes in private, from a different class
                root->setYes(animal);//animal is a node pointer
                                     //because it is the yes direction, needs to be a pointer to be accessed in the tree structure
                                     //anytime you want to set data for a node, you do this with pointers because its how the data is connected
                                     //anytime you want to access a function for pointers, you do this with the arrow
                                     //the function isn't called on the pointer like it is on an object, first the ibject had to be pointed to and then the function is called on that
                current=root;
        }
        //destructor
        ~animaltree() {//destructors have no parameters
                //delete each node that was put on the heap
                //if you delete too many, you will crash the program
                //make sure that the number of deletes is the number of new nodes
                //have to walk down tree and delete from bottom up kind of, cant delete root first because then you cant get to anything else
                //cant make destructor animaltree recursive, cant call itsels, so need a separate function too 
                deleteTree(root);
        }

        void deleteTree(node *n) {//pointer saying where you are supposed to be deleting from, starting at root
                //trees are a recursive structure--nodes have nodes have nodes
                if (n==nullptr) { //no tree
                        return;
                }
                if (n->getNo() != nullptr) {
                        deleteTree(n->getNo());
                }
                if (n->getYes() != nullptr) {
                        deleteTree(n->getYes());
                }
                delete n;//deletes the first and final node
        }
        void createLeaves(string new_question, string correct_animal) {
                //make class data immutable, never change the data itself just add to it
                node *y=new node(correct_animal);
                node *n=new node(current->getContent());
                //node *update=new node(new_question, y, n);
                //current=update;
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
                //if (current->getYes()==nullptr && current->getNo()==nullptr) {
                if (!current->getYes() && !current->getNo()) {//if neither of these are valid pointers
                        return true;
                } else {
                        return false;
                }

        }
        bool hasYes() {
                //if (current->getYes()!=nullptr) {
                if (current->getYes()) {
                        return true;
                } else {
                        return false;
                }
        }
        bool hasNo() {
                //if (current->getNo()!=nullptr) {
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
        animaltree tree(q1, a1);//tree is the object?
        //task 1:create a function in animaltree that returns the current question/animal
        //cout << tree.getContent() << endl;
        //task 2: create a function in animaltree that goes down yes/no path so you can then use the function in task 1 to retrun the next message 
        //tree.followYes();
        //cout << tree.getContent() << endl;

        cout << "Think of a new animal." << endl;

        while(1) {
                //if at leaf, ask if this is your animal
                //if yes, restart game
                //if no, ask for the correct animal, new question, and make the new nodes

                //if not at a leaf, print the question and get response
                //if yes, follow yes, if it exists
                //if yes doesnt exist ask animal and create it, then restart
                //if no, follow no, if it exists
                //if not, create the node and restart
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
                        } else if (tree.hasYes()) { //no doesn't exist, but yes does (like on root)
                                cout << "What is your animal?" << endl;
                                getline(cin, a1);
                                tree.createFirstNo(a1);
                                //method to create no node--separate yes and no node creation?
                                tree.reset();
                        } else if (!tree.hasYes()) {//means guess was an animal
                                                    //!tree.hasNo() already shown true
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
