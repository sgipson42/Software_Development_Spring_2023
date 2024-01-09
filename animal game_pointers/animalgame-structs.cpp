#include <string>
#include <iostream>
using namespace std;


struct node {
        string content;
        node* no;
        node* yes;
};

int main() {
        string animal, question, answer;
        cout << "Enter the name of an animal." << endl;
        getline(cin, animal);
        cout << "Enter a yes/no question describing this animal." << endl;
        getline(cin, question);

        node root;
        node leaf;
        node* current;
        root.content= question;
        leaf.content=animal;

        root.yes=&leaf;
        root.no=NULL;
        leaf.yes=NULL;
        leaf.no=NULL;

        cout<< "Think of an animal." << endl;
        current= &root;

        int i=0;
        while (true) {
                i++;
                node **parent_link=&(current->yes);
                //*parent_link= current;

                cout << current->content <<endl;
                getline(cin, answer);

                if(answer== "yes") {
                        if (current->yes !=nullptr) {
                                current=current->yes;
                        }
                }

                if(answer== "no") {
                        if (current->no !=nullptr) {
                                current=current->no;
                        }
                        else if(current->no==nullptr) {
                                //if current->yes exists, a question was asked--dont want to replace yes branch, just create a new tree section for no
                                node *n=new node;
                                n->content=current->content;
                                current->no=n;
                                n->yes=NULL;
                                n->no=NULL;

                                if (current->no==root.no) {
                                        cout << "What is your animal?" << endl;
                                        getline(cin, animal);
                               }
                                if (current->yes==nullptr) {
                                        //means current was a guess
                                        cout << "What is your animal?" << endl;
                                        getline(cin, animal);
                                        cout << "Better question to ask?" << endl;
                                        getline(cin, question);
                                        node *y=new node;//your animal(correct)
                                        current->yes=y;
                                        y->content=animal;
                                        y->yes=NULL;
                                        y->no=NULL;
                                        current->content= question;
                                        *parent_link=y;
                                        current=&root;

                                }
//              delete n;
                        }
                }
        }
}
