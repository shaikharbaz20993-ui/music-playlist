#include<iostream>
using namespace std;
class Song{
public:
    string name;
    Song* next;
    Song* prev;

    Song(string name){
        this->name = name;
        next = prev = NULL;
    }
};
class List{
    Song* head;
    Song* tail;
    Song* curr;

public:
    List(){
        head = tail = curr = NULL;
    }

    ~List(){
        while(head != NULL){
            Song* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addsong(string n){
        Song* newSong = new Song(n);
        if(head == NULL){
            head = tail = curr = newSong;
        } else{
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
    }

    void deleteSong(int pos){
        // empty list
        if(head == NULL){
            cout<<"Song list is empty"<<endl;
            return;
        }

        // invalid position
        Song* temp = head;
        int count = 0;

        while(temp != NULL){
            count++;
            temp = temp->next;
        }

        if(pos<1 || pos>count){
            cout<<"Invalid";
            return;
        }

        // only one song
        if(head == tail){
            Song* temp = head;
            head = tail = curr = NULL;
            delete temp;
            return;
        }

        // delete head;
        if(pos == 1){
            Song* temp = head;
            head = head->next;
            head->prev = NULL;

            if(temp == curr){
                curr = curr->next;
            }
            delete temp;
            return;
        }

        // delete tail
        if(count == pos){
            Song* temp = tail;
            tail = tail->prev;
            tail->next = NULL;

            if(temp == curr){
                curr = curr->prev;
            }
            delete temp;
            return;
        }

        // delete middle
        temp = head;
        for(int i=1; i<pos; i++){
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

        if(temp == curr){
            curr = curr->prev;
        }
        delete temp;
    }

    void search(string s){
        
        Song* temp = head;
        while(temp != NULL){
            if(temp->name == s){
                curr = temp;
                cout<<"\nNow playing : "<<curr->name<<endl<<endl;
                return;
            }
            temp = temp->next;
        }
        cout<<"\nNot found\n\n";
    }
    
    void displayPlaylist(){

        if(curr != NULL){
            cout<<"\n Now playing : "<<curr->name<<endl<<endl;
        } else{
            cout<<"\nNo song"<<endl;
        }

        int i = 1;
        Song* temp = head;
        while(temp != NULL){
            cout<<i<<" : "<<temp->name<<endl;
            temp = temp->next;
            i++;
        }
        cout<<endl;

    }

    void nextSong(){
        if(curr != NULL && curr->next != NULL){
            curr = curr->next;
            cout<<"\nNow playing : "<<curr->name<<endl<<endl;

        }
        else{
            cout<<"No next song available."<<endl<<endl;
        }
    }

    void previousSong(){
        if(curr != NULL && curr->prev != NULL){
            curr = curr->prev;
            cout<<"\nNow playing : "<<curr->name<<endl<<endl;
        } else{
            cout<<"No previous song available."<<endl;
        }

    }

};
int main(){
    List s1;
    cout<<"\n\n================***Music Playlist***===============\n\n\n";

    while(true){

        int n;
        cout<<"1 : Add song"<<endl;
        cout<<"2 : Search song"<<endl;
        cout<<"3 : Delete song"<<endl;
        cout<<"4 : All songs"<<endl;
        cout<<"5 : next song"<<endl;
        cout<<"6 : previous song"<<endl;
        cout<<"7 : Exit"<<endl;
        cout<<"\nEnter The number : ";
        cin>>n;

        if(n == 1){
            string s;
            cout<<"Enter the name of Song : ";
            getline(cin>>ws,s);
            s1.addsong(s);
            s1.displayPlaylist();
        }

        else if(n == 2){
            string s;
            cout<<"Song name : ";
            getline(cin>>ws,s);
            s1.search(s);
        }

        else if(n == 3){
            int n;
            cout<<"\n Which song you want to delete : \n";
            s1.displayPlaylist();
            cout<<"Enter the number : ";
            cin>>n;
            s1.deleteSong(n);
        }

        else if(n == 4){
            s1.displayPlaylist();
        }

        else if(n == 5){
            s1.nextSong();
        }

        else if(n == 6){
            s1.previousSong();
        }

        else if(n == 7){
            return 0;
        }
        else{
            cout<<"\nWrong input\n\n";
        }
    }
}