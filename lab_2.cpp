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

bool insertUser(User*& head, const string& username, const string& password, const vector<string>& perms ={"view"}) {
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

bool authorize(User* head, const string& username , const string& action){
    //Runtime : O(n)//
    User* user = findUser(head , username); 
    if(user == nullptr){
        return false;
    }
    
    for(const string& perm : user->permissions){
        if(perm == action){
            return true;
        }
    }
        
        return false;
    
    
}

	int main()
	{
		User* head = nullptr;
		
		insertUser(head,"Jake","51015",{"view" , "admin" , "delete"});
		insertUser(head,"Sam","@2025",{"view" , "editor" , "create"});
		insertUser(head,"Kile","12345",{"view" , "viewer" , "edit"});
		insertUser(head,"Andvia","01ivi@",{"view"});
		insertUser(head,"Oliy","@nDy1",{"view" , "editor", "view"});
		
         cout << "Jake delete -> " << (authorize(head, "Jake", "delete")? "Allowed" : "Denied") << endl;  
         cout << "Sam create -> " << (authorize(head, "Sam", "create")? "Allowed" : "Denied") << endl;   
         cout << "Sam delete -> " << (authorize(head, "Sam", "delete")? "Allowed" : "Denied" )<< endl;    
         cout << "Olivia view -> " << (authorize(head, "Olivia", "view")? "Allowed" : "Denied" )<< endl; 
        cout << "Olivia edit -> " << (authorize(head, "Olivia", "edit")? "Allowed ": "Denied" )<< endl;  
        
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