#include <string>
#include <iostream>
#include <cpr/cpr.h> 
#include <nlohmann/json.hpp> 
using namespace std; 
using json = nlohmann::json;

#include <algorithm>  
#include <cctype> 
#include <locale> 
            
//trim from start (in place)  
static inline void ltrim(std::string &s) { 
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { 
        return !std::isspace(ch); 
        }));             
}            
// trim from end (in place) 
static inline void rtrim(std::string &s) {  
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { 
        return !std::isspace(ch) && ch != '.'; 
        }).base(), s.end()); 
}        
// trim from both ends (in place) 
static inline void trim(std::string &s) { 
        rtrim(s); 
        ltrim(s); 
}
string askGPT(string q) { 
	string answer; 
	while(answer.size() == 0) { 
		cout << "q: " << q << endl; 
		const string body = "{\"model\": \"text-davinci-003\", \"prompt\": \"" + q + "\", \"temperature\": 0.5, \"max_tokens\": 500}"; 
		cpr::Response r = 
cpr::Post(cpr::Url{"https://api.openai.com/v1/completions"}, 
			cpr::Header{{"Authorization", "Bearer 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"},
			{"Content-type", "application/json"}}, 
			cpr::Body{body}); 
		auto d = json::parse(r.text); 
		answer = d["choices"][0]["text"]; 
		trim(answer); 
		cout << "response: " << answer << endl; 
		if(answer.size() == 0) { 
			cout << r.text << endl; 
		} 
	}
       return answer;	
}

struct node {
	string content;
	node* no;
	node* yes;
};

int main() {
	string animal, question, animal2, answer;
	//fin.open("transcript.txt");
	//fout.open("transcript.new.txt");

	/*cout << "Enter the name of an animal." << endl;
	animal= getInput();
	cout << "Enter a yes/no question describing this animal." << endl;
	question= getInput();*/


	node root;
	node leaf;
	node* current;
	animal= askGPT("Think of an animal.");
	question= askGPT("Think of a yes or no question that accurately describes a(n) " +animal+ ", but do not include the name of this animal in the question.");
	root.content= question;
	leaf.content=animal;

	root.yes=&leaf;
	root.no=NULL;
	leaf.yes=NULL;
	leaf.no=NULL;

	animal2= askGPT("Think of an animal that is not a(n) " + animal);
	current= &root;

	int i=0;
	while (true) {
		i++;
		node **parent_link=&(current->yes);
		
		answer= askGPT("Answer yes if the following statement says or accurately describes a(n) " + animal2+ ": " +current->content+ ". Otherwise, answer no.");
		//cout << current->content <<endl;
		
		if (answer=="Yes") {
			if (current->content==animal2) {
				//task: keep track of all animals that have been thought of so none repeated
				animal2=askGPT("Yay! Let's restart. Tell me an animal that is not a(n) " + animal2);	
				current=&root;
			} else if (current->yes !=nullptr) {
				current=current->yes;
			}
		}

		//if (current->content!=animal2) {
		if (answer=="No") {
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
					n->content=animal2;
					//animal2=askGPT("Good to know. Tell me an animal that is not a(n) " +animal2);
					//do same process as in task further above
				}
				if (current->yes==nullptr) { 
					question= askGPT("Think of a yes or no question that describes a(n) " + animal2 + " but does not describe a(n) "+ current->content+ ", and do not include the names of any animal in the question.");
					node *y=new node;//your animal(correct)
					current->yes=y;
					//y->content=animal;
					y->content=animal2;
					y->yes=NULL;
					y->no=NULL;
					current->content= question;
					*parent_link=y;
					current=&root;

				}
//		delete n;
			}
					animal2=askGPT("Good to know. Tell me an animal that is not a(n) " +animal2);
		}
	}
}	



