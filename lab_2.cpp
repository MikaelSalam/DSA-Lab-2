#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct User {

	string username;
	string password;
	vector<string> permissions;
	User* next;

	User (const string& u, const string& p, const vector<string>& perms = {"view"}) {
		username = u;
		password = p;
		permissions = perms;
		next = nullptr;
	}
};

bool insertUser(User*& head, const string& username, const string& password, const vector<string>& perms = {"view"}) {
    //Worst Case Runtime: O(n)//
    
    //Runtime: O(n)//
	User* current = head;
	while(current != nullptr) {
		if(current->username == username) {
			return false;
		}
		current = current -> next;
	}


	User* newUser = new User(username, password, perms);
	if(head == nullptr) {
		head = newUser;
		return true;
	}
    //Runtime : O(n)//
	User* end = head;
	while(end->next != nullptr) {
		end = end->next;
	}
	end->next = newUser;
	return true;
    
}



User* findUser(User* head, const string& username) {
    //Worst Case Runtime : O(n)//
	User* current = head;
	while(current != nullptr) {
		if(current->username == username) {
			return current;
		}
		current = current->next;
	}
	return nullptr;
}


bool authenticate(User* head, const string& username, const string& password) {
    //Worst Case Runtime : O(n)//
	User* current = head;
	while(current != nullptr) {
		if(current->username == username && current->password == password) {
			return true;
		}
		current = current->next;
	}
	return false;

}

bool removeFront(User*& head) {
    //Runtime: O(1)//
	User* current = head;
	if(current == nullptr) {
		return false;
	}

	User* temp = head;
	head = head->next;
	delete temp;
	return true;
}


bool removeByUsername(User*& head, const string& username) {
    //Worst Case Runtime : O(n)//
	if(head == nullptr){
	    return false;
	}
	
	if(head->username == username){
	    User*temp = head;
	    head = head->next;
	    delete temp;
	    return true;
	}
	
	User* current = head;
	while(current->next != nullptr){
	    if(current->next->username == username){
	        User* temp = current->next;
	        current->next = current->next->next;
	        delete temp;
	        return true;
	    }
	    current= current->next;
	}
	
	return false;
}


void clearList(User*& head) {
   //Runtime : O(n)//
    User* current = head;
        while(current!= nullptr){
            User* temp = current->next;
            delete current;
            current = temp;
        }
    head = nullptr;
}

bool authorize(User* head , const string& username , const string& action = "viewer"){
    //Runtime : O(n) //
    User* user = findUser (head , username);
    if(user == nullptr){
		return false;
	}
    
	if(user->role == "admin"){
		return true;
	}
	else if(user->role == "editor"){
		return (action == "view"|| action == "edit"|| action == "create");
	}
	else if(user->role == "viewer"){
		return (action == "view");
	}
	return false;
}


int main() {

    User* head = nullptr;
		
	insertUser(head,"Jake","51015","admin");
	insertUser(head,"Sam","@2025","editor");
	insertUser(head,"Kile","12345","viewer");
	insertUser(head,"Andy","@nDy1","editor");
	insertUser(head,"Olivia","01ivi@","viewer");
    
    cout << "Jake (admin, delete): " << authorize(head, "Jake", "delete") << endl;
    cout << "Sam (editor, edit): " << authorize(head, "Sam", "edit") << endl;
    cout << "Kile (viewer, edit): " << authorize(head, "Kile", "edit") << endl;
    cout << "Andy (editor, view): " << authorize(head, "Andy", "view") << endl;
    cout << "Olivia (viewer, view): " << authorize(head, "Olivia", "view") << endl;
     

    cout<<"Finding User.\n";
		User* user = findUser(head,"Sam");
		if(user != nullptr){
		    cout<<"User Found:  "<< user -> username<<endl;
		}else{
		    cout<<"User Not Found"<<endl;
		}
		cout<<endl;
		
		cout<<"Athentication.\n";
		cout<<"Authenticate Jake/51015 "<< (authenticate(head, "Jake" , "51015")? "Success" : "Fail")<<endl;
		cout<<"Authenticate Will/Wi11y "<<(authenticate(head, "Will" , "Wi11y")? "Success": "Fail")<<endl;
        cout<<endl;
        
        cout<<"Removing Front.\n";
        removeFront(head);
        
        cout<<"Removing By User Name. \n";
        removeByUsername(head ,"Andy");
        
        cout<<"Clearing the List.\n";
        clearList(head);
        
		return 0;
	}