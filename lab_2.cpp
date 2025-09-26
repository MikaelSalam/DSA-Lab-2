#include <iostream>
#include <string>
using namespace std;

struct User {

	string username;
	string password;
	string role;
	User* next;

	User (cosnt string& u, const string& p, const string& r = "Viewer") {
		username = u;
		password = p;
		role = r;
		next = nullptr;
	}
};

bool insertUser(User*& head, const string& username, const string& password, const string& role = "Viewer") {
    //Worst Case Runtime: O(n)//
    
    //Runtime: O(n)//
	User* current = head;
	while(current != nullptr) {
		if(current->username == username) {
			return false;
		}
		current = current -> next;
	}


	User* newUser = new User(username, password, role);
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

int main() {

    User* head = nullptr;
		
	insertUser(head,"Jake","51015");
	insertUser(head,"Sam","@2025");
	insertUser(head,"Kile","12345");
	insertUser(head,"Andy","@nDy1");
	insertUser(head,"Olivia","01ivi@");

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