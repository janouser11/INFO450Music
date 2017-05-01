#include <iostream>
#include <fstream>

using namespace std;

class node {
    node *next;
    char songTitle[25];
    char artist[25];
public:
    node(char a[25], char t[25]);
    friend class linkedList;
};
node::node(char a[25], char t[25]) {
    strcpy(artist, a);
    strcpy(songTitle, t);
    next = NULL;
}
class linkedList {
    char filename[50];
    node *tail;
    node *head;
public:
    linkedList();
    void setFilename(char f[]);
    void readList();
    void addNodeToEnd(node *nptr);
    void showList();;
    void play();
    void skip();
    int deleteSong();
};
linkedList::linkedList() {
    tail = NULL;
    head = NULL;
}
int linkedList::deleteSong() {
    char response[25];
    node *ptr = head;
    cout << "Input the song you wish to delete (Be case sensitive)" << endl;
    cin.clear();
    cin.ignore();
    gets(response);

    if (ptr == NULL)
        return -1;
    if (strcmp(response, ptr->songTitle) == 0) {
        if (head == tail) {
            head = NULL;
            tail = NULL;
        } else
            head = head->next;
        delete ptr;
        return 0;
    }

    while (ptr != NULL) {
        if (ptr->next && (strcmp((ptr->next)->songTitle, response) == 0)) {
            if (tail == ptr->next)
                tail = ptr;
            node *tbd = ptr->next;
            ptr->next = (ptr->next)->next;
            delete tbd;
            return 0;
        }
        ptr = ptr->next;
    }
    return -1;
}
void linkedList::play() {
    char response[20];
    node *ptr;
    ptr = head;
    cout << "Input the song you wish to play (Be case sensitive)\n";
    cin.clear();
    cin.ignore();
    gets(response);
    while (ptr != NULL) {
        if (strcmp(response, ptr->songTitle) == 0) {
            cout << "Now playing " << ptr->songTitle << " by " << ptr->artist << endl;
        }
        ptr = ptr->next;
    }
}
void linkedList::skip() {
    char response[25];
    node *ptr;
    ptr = head;
    cout << "Input the song you wish to skip (Be case sensitive)\n";
    cin.clear();
    cin.ignore();
    gets(response);
    while (ptr != NULL) {
        if (strcmp(response, ptr->songTitle) == 0) {
            cout << "Skipped song " << ptr->songTitle << " by " << ptr->artist << endl;
            ptr = ptr->next;
            if (ptr->songTitle )
                cout << "Now playing " << ptr->songTitle << " by " << ptr->artist << endl;
        }
        ptr = ptr->next;
    }

}
void linkedList::readList() {
    ifstream infile(filename);
    if (!infile) {
        return;
    }

    while (!infile.eof()) {
        node *ptr;
        char artist[20];
        char title[20];

        infile.getline(artist,20, ',');
        if (strlen(artist)) {
            infile.getline(title,20);
            ptr = new node(artist, title);
            addNodeToEnd(ptr);
        }
    }
    infile.close();
}
void linkedList::showList() {
    node *ptr;
    ptr = head;
    cout << "Song Playlist\n";
    cout << "___________________\n";
    if (ptr == NULL) {
        cout << "There appears to be nothing in this file " << endl;
        return;
    } while (ptr != NULL) {
        cout << "Artist: " << ptr->artist << "\t Title: " << ptr->songTitle << endl;
        ptr = ptr->next;
    }
}
void linkedList::addNodeToEnd(node *ptr) {
    if (head == NULL) {
        head = ptr;
        tail = ptr;
    } else {
        tail->next = ptr;
        tail = ptr;
    }
}
void linkedList::setFilename(char f[]) {
    strcpy(filename, f);
}

int main() {
    bool answer = true;
    char userInput;
    char filename[50];
    cout << "Welcome to my music shuffle\n";
    cout << "****************************\n";
    cout << "Please enter file path of playlist: " << endl;
    gets(filename);
    linkedList *myLinkedList = new linkedList();
    myLinkedList->setFilename(filename);
    myLinkedList->readList();

    do {
        myLinkedList->showList();
        cout << " " << endl;
        cout << "__________________________" << endl;
        cout << "What would you like to do?" << endl;
        cout << "[P]lay \t\t [S]kip \t\t [D]elete \t\t [Q]uit\n" << endl;
        cin >> userInput;

        //Conditional for case sensitivity
        if ((userInput == 'P') || (userInput == 'p')) {
            myLinkedList->play();
            answer = true;
        } else if ((userInput == 'S') || (userInput == 's')) {
            myLinkedList->skip();
            answer = true;
        } else if ((userInput == 'D') || (userInput == 'd')) {
            if (myLinkedList->deleteSong())
                myLinkedList->showList();
            answer = true;
        } else if ((userInput == 'Q') || (userInput == 'q')) {
            cout << "Exiting now!!" << endl;
            answer = false;
        } else {
            cout << "Error, invalid input!!" << endl;
            answer = true;
        }
    } while (answer);
}