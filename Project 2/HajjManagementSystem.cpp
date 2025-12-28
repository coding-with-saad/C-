#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <ctime>
#include <windows.h>

using namespace std;

const int MAX_ACCOMMODATIONS = 100;
const int MAX_RITUALS = 7;

struct Pilgrim {
    int id;
    char name[50];
    int age;
    char country[30];
    char gender;
    bool isElderly;
    bool isDisabled;
    int accommodationID;
    int groupNumber;

    Pilgrim() : id(0), age(0), gender('M'), isElderly(false),
                isDisabled(false), accommodationID(-1), groupNumber(-1) {
        strcpy(name, "");
        strcpy(country, "");
    }
};

class PilgrimNode {
public:
    Pilgrim data;
    PilgrimNode* next;

    PilgrimNode(Pilgrim p) : data(p), next(nullptr) {}
};

class PilgrimLinkedList {
private:
    PilgrimNode* head;
    int pilgrimCount;
    int nextID;

public:
    PilgrimLinkedList() : head(nullptr), pilgrimCount(0), nextID(1001) {}

    int addPilgrim(Pilgrim& pilgrim) {
        pilgrim.id = nextID++;
        PilgrimNode* newNode = new PilgrimNode(pilgrim);

        if (head == nullptr) {
            head = newNode;
        } else {
            PilgrimNode* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }

        pilgrimCount++;
        return pilgrim.id;
    }

    void displayAll() {
        if (head == nullptr) {
            cout << "\n\t\tNo pilgrims registered yet.\n";
            return;
        }

        cout << "\n\t\t========== REGISTERED PILGRIMS ==========\n\n";
        cout << "\t" << left << setw(8) << "ID" << setw(25) << "Name"
             << setw(6) << "Age" << setw(8) << "Gender" << setw(20) << "Country"
             << setw(10) << "Priority" << endl;
        cout << "\t" << string(80, '-') << endl;

        PilgrimNode* temp = head;
        while (temp != nullptr) {
            cout << "\t" << left << setw(8) << temp->data.id
                 << setw(25) << temp->data.name
                 << setw(6) << temp->data.age
                 << setw(8) << (temp->data.gender == 'M' ? "Male" : "Female")
                 << setw(20) << temp->data.country;

            if (temp->data.isDisabled) cout << "Disabled";
            else if (temp->data.isElderly) cout << "Elderly";
            else cout << "Normal";

            cout << endl;
            temp = temp->next;
        }
        cout << "\n\t\tTotal Pilgrims: " << pilgrimCount << endl;
    }

    Pilgrim* searchByID(int id) {
        PilgrimNode* temp = head;
        while (temp != nullptr) {
            if (temp->data.id == id) {
                return &(temp->data);
            }
            temp = temp->next;
        }
        return nullptr;
    }

    PilgrimNode* getHead() { return head; }
    int getCount() { return pilgrimCount; }

    Pilgrim* getAllPilgrimsArray() {
        if (pilgrimCount == 0) return nullptr;

        Pilgrim* arr = new Pilgrim[pilgrimCount];
        PilgrimNode* temp = head;
        int i = 0;

        while (temp != nullptr) {
            arr[i++] = temp->data;
            temp = temp->next;
        }

        return arr;
    }

    ~PilgrimLinkedList() {
        PilgrimNode* current = head;
        while (current != nullptr) {
            PilgrimNode* next = current->next;
            delete current;
            current = next;
        }
    }
};

class QueueNode {
public:
    int pilgrimID;
    QueueNode* next;

    QueueNode(int id) : pilgrimID(id), next(nullptr) {}
};

class TransportationQueue {
private:
    QueueNode* front;
    QueueNode* rear;
    int queueSize;
    int busCapacity;

public:
    TransportationQueue(int capacity = 50) : front(nullptr), rear(nullptr),
                                              queueSize(0), busCapacity(capacity) {}

    void enqueue(int pilgrimID) {
        QueueNode* newNode = new QueueNode(pilgrimID);

        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }

        queueSize++;
    }

    int dequeue() {
        if (front == nullptr) {
            return -1;
        }

        QueueNode* temp = front;
        int pilgrimID = front->pilgrimID;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
        queueSize--;
        return pilgrimID;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    int getSize() {
        return queueSize;
    }

    void displayQueue(PilgrimLinkedList& pilgrims) {
        if (front == nullptr) {
            cout << "\n\t\tTransportation queue is empty.\n";
            return;
        }

        cout << "\n\t\t========== TRANSPORTATION QUEUE ==========\n";
        cout << "\t\tQueue Size: " << queueSize << " | Bus Capacity: " << busCapacity << endl;
        cout << "\t\tBuses Needed: " << (queueSize + busCapacity - 1) / busCapacity << endl;
        cout << "\n\t\tPilgrims in Queue:\n";

        QueueNode* temp = front;
        int position = 1;

        while (temp != nullptr) {
            Pilgrim* p = pilgrims.searchByID(temp->pilgrimID);
            if (p) {
                cout << "\t\t" << position++ << ". ID: " << p->id
                     << " - " << p->name << endl;
            }
            temp = temp->next;
        }
    }

    int boardBus(PilgrimLinkedList& pilgrims) {
        if (isEmpty()) {
            return 0;
        }

        int boarded = 0;
        cout << "\n\t\t========== BOARDING BUS ==========\n";
        cout << "\t\tBoarding " << min(busCapacity, queueSize) << " pilgrims...\n\n";

        while (!isEmpty() && boarded < busCapacity) {
            int pilgrimID = dequeue();
            Pilgrim* p = pilgrims.searchByID(pilgrimID);
            if (p) {
                cout << "\t\t" << (boarded + 1) << ". " << p->name
                     << " (ID: " << p->id << ") boarded.\n";
            }
            boarded++;
        }

        cout << "\n\t\tTotal boarded: " << boarded << endl;
        cout << "\t\tRemaining in queue: " << queueSize << endl;

        return boarded;
    }

    ~TransportationQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

class PriorityQueueNode {
public:
    int pilgrimID;
    int priority;
    PriorityQueueNode* next;

    PriorityQueueNode(int id, int p) : pilgrimID(id), priority(p), next(nullptr) {}
};

class PriorityQueue {
private:
    PriorityQueueNode* front;
    int queueSize;

public:
    PriorityQueue() : front(nullptr), queueSize(0) {}

    void enqueue(int pilgrimID, int priority) {
        PriorityQueueNode* newNode = new PriorityQueueNode(pilgrimID, priority);

        if (front == nullptr || priority < front->priority) {
            newNode->next = front;
            front = newNode;
        } else {
            PriorityQueueNode* temp = front;
            while (temp->next != nullptr && temp->next->priority <= priority) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }

        queueSize++;
    }

    int dequeue() {
        if (front == nullptr) {
            return -1;
        }

        PriorityQueueNode* temp = front;
        int pilgrimID = front->pilgrimID;
        front = front->next;

        delete temp;
        queueSize--;
        return pilgrimID;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    int getSize() {
        return queueSize;
    }

    void displayQueue(PilgrimLinkedList& pilgrims) {
        if (front == nullptr) {
            cout << "\n\t\tPriority queue is empty.\n";
            return;
        }

        cout << "\n\t\t========== PRIORITY TRANSPORTATION QUEUE ==========\n";
        cout << "\t\tQueue Size: " << queueSize << endl;
        cout << "\n\t\tPriority Pilgrims:\n";

        PriorityQueueNode* temp = front;
        int position = 1;

        while (temp != nullptr) {
            Pilgrim* p = pilgrims.searchByID(temp->pilgrimID);
            if (p) {
                cout << "\t\t" << position++ << ". [Priority " << temp->priority
                     << "] ID: " << p->id << " - " << p->name;
                if (p->isDisabled) cout << " (Disabled)";
                else if (p->isElderly) cout << " (Elderly)";
                cout << endl;
            }
            temp = temp->next;
        }
    }

    ~PriorityQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

class Accommodation {
public:
    int id;
    char location[50];
    int capacity;
    int occupied;

    Accommodation() : id(0), capacity(0), occupied(0) {
        strcpy(location, "");
    }

    Accommodation(int i, const char* loc, int cap) : id(i), capacity(cap), occupied(0) {
        strcpy(location, loc);
    }

    bool assignPilgrim() {
        if (occupied < capacity) {
            occupied++;
            return true;
        }
        return false;
    }

    void display() {
        cout << "\t\tID: " << id << " | " << location
             << " | Capacity: " << capacity
             << " | Occupied: " << occupied
             << " | Available: " << (capacity - occupied) << endl;
    }
};

class AccommodationManager {
private:
    Accommodation accommodations[MAX_ACCOMMODATIONS];
    int accommodationCount;

public:
    AccommodationManager() : accommodationCount(0) {
        initializeAccommodations();
    }

    void initializeAccommodations() {
        addAccommodation("Makkah - Hotel Al-Safa", 150);
        addAccommodation("Makkah - Hotel Dar Al-Tawhid", 200);
        addAccommodation("Mina - Tent Camp A", 300);
        addAccommodation("Mina - Tent Camp B", 300);
        addAccommodation("Arafat - Tent Camp", 500);
        addAccommodation("Muzdalifah - Open Area", 400);
    }

    void addAccommodation(const char* location, int capacity) {
        if (accommodationCount < MAX_ACCOMMODATIONS) {
            accommodations[accommodationCount] =
                Accommodation(accommodationCount + 1, location, capacity);
            accommodationCount++;
        }
    }

    int assignAccommodation(Pilgrim& pilgrim) {
        for (int i = 0; i < accommodationCount; i++) {
            if (accommodations[i].assignPilgrim()) {
                pilgrim.accommodationID = accommodations[i].id;
                return accommodations[i].id;
            }
        }
        return -1;
    }

    void displayAll() {
        cout << "\n\t\t========== ACCOMMODATION STATUS ==========\n\n";
        for (int i = 0; i < accommodationCount; i++) {
            accommodations[i].display();
        }
        cout << "\n\t\tTotal Accommodations: " << accommodationCount << endl;
    }

    Accommodation* getAccommodation(int id) {
        for (int i = 0; i < accommodationCount; i++) {
            if (accommodations[i].id == id) {
                return &accommodations[i];
            }
        }
        return nullptr;
    }
};

class RitualStackNode {
public:
    char ritualName[50];
    char timestamp[30];
    RitualStackNode* next;

    RitualStackNode(const char* name) {
        strcpy(ritualName, name);
        time_t now = time(0);
        strcpy(timestamp, ctime(&now));
        next = nullptr;
    }
};

class RitualStack {
private:
    RitualStackNode* top;
    int ritualCount;

public:
    RitualStack() : top(nullptr), ritualCount(0) {}

    void push(const char* ritualName) {
        RitualStackNode* newNode = new RitualStackNode(ritualName);
        newNode->next = top;
        top = newNode;
        ritualCount++;
    }

    void displayRituals() {
        if (top == nullptr) {
            cout << "\n\t\tNo rituals completed yet.\n";
            return;
        }

        cout << "\n\t\t========== COMPLETED RITUALS (Most Recent First) ==========\n\n";
        RitualStackNode* temp = top;
        int count = 1;

        while (temp != nullptr) {
            cout << "\t\t" << count++ << ". " << temp->ritualName << endl;
            cout << "\t\t   Completed at: " << temp->timestamp;
            temp = temp->next;
        }

        cout << "\n\t\tTotal Rituals Completed: " << ritualCount << endl;
    }

    int getCount() {
        return ritualCount;
    }

    ~RitualStack() {
        while (top != nullptr) {
            RitualStackNode* temp = top;
            top = top->next;
            delete temp;
        }
    }
};

class BSTNode {
public:
    Pilgrim data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Pilgrim p) : data(p), left(nullptr), right(nullptr) {}
};

class PilgrimBST {
private:
    BSTNode* root;

    BSTNode* insertRec(BSTNode* node, Pilgrim pilgrim) {
        if (node == nullptr) {
            return new BSTNode(pilgrim);
        }

        if (pilgrim.id < node->data.id) {
            node->left = insertRec(node->left, pilgrim);
        } else if (pilgrim.id > node->data.id) {
            node->right = insertRec(node->right, pilgrim);
        }

        return node;
    }

    BSTNode* searchRec(BSTNode* node, int id) {
        if (node == nullptr || node->data.id == id) {
            return node;
        }

        if (id < node->data.id) {
            return searchRec(node->left, id);
        }

        return searchRec(node->right, id);
    }

    void inorderRec(BSTNode* node) {
        if (node != nullptr) {
            inorderRec(node->left);
            cout << "\t\tID: " << node->data.id << " - " << node->data.name
                 << " (Age: " << node->data.age << ")" << endl;
            inorderRec(node->right);
        }
    }

    void deleteTree(BSTNode* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    PilgrimBST() : root(nullptr) {}

    void insert(Pilgrim pilgrim) {
        root = insertRec(root, pilgrim);
    }

    Pilgrim* search(int id) {
        BSTNode* result = searchRec(root, id);
        if (result != nullptr) {
            return &(result->data);
        }
        return nullptr;
    }

    void displayInOrder() {
        cout << "\n\t\t========== PILGRIMS (SORTED BY ID) ==========\n\n";
        inorderRec(root);
    }

    ~PilgrimBST() {
        deleteTree(root);
    }
};

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void displayHeader() {
    system("cls");
    setColor(11);
    cout << "\n\n";
    cout << "\t\t========================================================\n";
    cout << "\t\t||                                                    ||\n";
    cout << "\t\t||        SMART HAJJ MANAGEMENT SYSTEM                ||\n";
    cout << "\t\t||        Data Structures Project                     ||\n";
    cout << "\t\t||                                                    ||\n";
    cout << "\t\t========================================================\n\n";
    setColor(7);
}

void displayMainMenu() {
    setColor(14);
    cout << "\n\t\t========== MAIN MENU ==========\n\n";
    setColor(7);
    cout << "\t\t1.  Pilgrim Registration\n";
    cout << "\t\t2.  View All Pilgrims\n";
    cout << "\t\t3.  Search Pilgrim\n";
    cout << "\t\t4.  Transportation Management\n";
    cout << "\t\t5.  Priority Queue (Elderly/Disabled)\n";
    cout << "\t\t6.  Accommodation Management\n";
    cout << "\t\t7.  Ritual Tracking\n";
    cout << "\t\t8.  Sort Pilgrims\n";
    cout << "\t\t9.  Generate Reports\n";
    cout << "\t\t10. Exit\n";
    setColor(14);
    cout << "\n\t\t==============================\n";
    setColor(7);
    cout << "\t\tEnter your choice: ";
}

void bubbleSortByAge(Pilgrim* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].age > arr[j + 1].age) {
                Pilgrim temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSortByID(Pilgrim* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].id < arr[minIdx].id) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Pilgrim temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}

int linearSearch(Pilgrim* arr, int n, const char* name) {
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void displayPilgrimDetails(Pilgrim* p) {
    if (p == nullptr) {
        cout << "\n\t\tPilgrim not found!\n";
        return;
    }

    setColor(10);
    cout << "\n\t\t========== PILGRIM DETAILS ==========\n";
    setColor(7);
    cout << "\n\t\tID: " << p->id << endl;
    cout << "\t\tName: " << p->name << endl;
    cout << "\t\tAge: " << p->age << endl;
    cout << "\t\tGender: " << (p->gender == 'M' ? "Male" : "Female") << endl;
    cout << "\t\tCountry: " << p->country << endl;
    cout << "\t\tElderly: " << (p->isElderly ? "Yes" : "No") << endl;
    cout << "\t\tDisabled: " << (p->isDisabled ? "Yes" : "No") << endl;
    cout << "\t\tGroup Number: " << (p->groupNumber == -1 ? "Not Assigned" : to_string(p->groupNumber)) << endl;
    cout << "\t\tAccommodation ID: " << (p->accommodationID == -1 ? "Not Assigned" : to_string(p->accommodationID)) << endl;
    setColor(10);
    cout << "\t\t====================================\n";
    setColor(7);
}

int main() {
    PilgrimLinkedList pilgrims;
    TransportationQueue transportQueue(50);
    PriorityQueue priorityQueue;
    AccommodationManager accommodationMgr;
    RitualStack ritualStack;
    PilgrimBST pilgrimBST;

    int choice;

    while (true) {
        displayHeader();
        displayMainMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                displayHeader();
                setColor(11);
                cout << "\n\t\t========== PILGRIM REGISTRATION ==========\n\n";
                setColor(7);

                Pilgrim newPilgrim;

                cout << "\t\tEnter Name: ";
                cin.ignore();
                cin.getline(newPilgrim.name, 50);

                cout << "\t\tEnter Age: ";
                cin >> newPilgrim.age;

                cout << "\t\tEnter Gender (M/F): ";
                cin >> newPilgrim.gender;

                cout << "\t\tEnter Country: ";
                cin.ignore();
                cin.getline(newPilgrim.country, 30);

                cout << "\t\tIs Elderly (65+)? (1-Yes/0-No): ";
                int elderly;
                cin >> elderly;
                newPilgrim.isElderly = (elderly == 1) || (newPilgrim.age >= 65);

                cout << "\t\tIs Disabled? (1-Yes/0-No): ";
                int disabled;
                cin >> disabled;
                newPilgrim.isDisabled = (disabled == 1);

                cout << "\t\tEnter Group Number: ";
                cin >> newPilgrim.groupNumber;

                int pilgrimID = pilgrims.addPilgrim(newPilgrim);
                pilgrimBST.insert(newPilgrim);

                int accomID = accommodationMgr.assignAccommodation(newPilgrim);

                setColor(10);
                cout << "\n\t\t✓ Pilgrim registered successfully!\n";
                cout << "\t\t  Assigned ID: " << pilgrimID << endl;
                if (accomID != -1) {
                    cout << "\t\t  Accommodation ID: " << accomID << endl;
                } else {
                    cout << "\t\t  No accommodation available!\n";
                }
                setColor(7);

                cout << "\n\t\tPress any key to continue...";
                cin.ignore();
                cin.get();
                break;
            }

            case 2: {
                displayHeader();
                pilgrims.displayAll();
                cout << "\n\t\tPress any key to continue...";
                cin.ignore();
                cin.get();
                break;
            }

            case 3: {
                displayHeader();
                setColor(11);
                cout << "\n\t\t========== SEARCH PILGRIM ==========\n\n";
                setColor(7);
                cout << "\t\t1. Search by ID (Binary Search Tree)\n";
                cout << "\t\t2. Search by Name (Linear Search)\n";
                cout << "\t\tEnter choice: ";
                int searchChoice;
                cin >> searchChoice;

                if (searchChoice == 1) {
                    cout << "\n\t\tEnter Pilgrim ID: ";
                    int searchID;
                    cin >> searchID;

                    Pilgrim* found = pilgrimBST.search(searchID);
                    displayPilgrimDetails(found);
                } else if (searchChoice == 2) {
                    cout << "\n\t\tEnter Pilgrim Name: ";
                    char searchName[50];
                    cin.ignore();
                    cin.getline(searchName, 50);

                    Pilgrim* arr = pilgrims.getAllPilgrimsArray();
                    int count = pilgrims.getCount();

                    if (arr != nullptr) {
                        int idx = linearSearch(arr, count, searchName);
                        if (idx != -1) {
                            displayPilgrimDetails(&arr[idx]);
                        } else {
                            cout << "\n\t\tPilgrim not found!\n";
                        }
                        delete[] arr;
                    }
                }

                cout << "\n\t\tPress any key to continue...";
                cin.ignore();
                cin.get();
                break;
            }

            case 4: {
                displayHeader();
                setColor(11);
                cout << "\n\t\t========== TRANSPORTATION MANAGEMENT ==========\n\n";
                setColor(7);
                cout << "\t\t1. Add Pilgrim to Queue\n";
                cout << "\t\t2. View Transportation Queue\n";
                cout << "\t\t3. Board Bus\n";
                cout << "\t\t4. Back to Main Menu\n";
                cout << "\n\t\tEnter choice: ";
                int transChoice;
                cin >> transChoice;

                if (transChoice == 1) {
                    cout << "\n\t\tEnter Pilgrim ID to add to queue: ";
                    int pilgrimID;
                    cin >> pilgrimID;

                    Pilgrim* p = pilgrims.searchByID(pilgrimID);
                    if (p != nullptr) {
                        transportQueue.enqueue(pilgrimID);
                        setColor(10);
                        cout << "\n\t\t✓ Pilgrim " << p->name << " added to transportation queue!\n";
                        setColor(7);
                    } else {
                        setColor(12);
                        cout << "\n\t\t✗ Pilgrim not found!\n";
                        setColor(7);
                    }
                } else if (transChoice == 2) {
                    transportQueue.displayQueue(pilgrims);
                } else if (transChoice == 3) {
                    transportQueue.boardBus(pilgrims);
                }

                cout << "\n\t\tPress any key to continue...";
                cin.ignore();
                cin.get();
                break;
            }

            case 5: {
                displayHeader();
                setColor(11);
                cout << "\n\t\t========== PRIORITY QUEUE ==========\n\n";
                setColor(7);
                cout << "\t\t1. Add Elderly/Disabled to Priority Queue\n";
                cout << "\t\t2. View Priority Queue\n";
                cout << "\t\t3. Process Priority Pilgrim\n";
                cout << "\t\t4. Back to Main Menu\n";
                cout << "\n\t\tEnter choice: ";
                int prioChoice;
                cin >> prioChoice;

                if (prioChoice == 1) {
                    cout << "\n\t\tEnter Pilgrim ID: ";
                    int pilgrimID;
                    cin >> pilgrimID;

                    Pilgrim* p = pilgrims.searchByID(pilgrimID);
                    if (p != nullptr) {
                        int priority = 3;
                        if (p->isDisabled) priority = 1;
                        else if (p->isElderly) priority = 2;

                        priorityQueue.enqueue(pilgrimID, priority);
                        setColor(10);
                        cout << "\n\t\t✓ Pilgrim " << p->name << " added with priority " << priority << "!\n";
                        setColor(7);
                    } else {
                        setColor(12);
                        cout << "\n\t\t✗ Pilgrim not found!\n";
                        setColor(7);
                    }
                } else if (prioChoice == 2) {
                    priorityQueue.displayQueue(pilgrims);
                } else if (prioChoice == 3) {
                    int pilgrimID = priorityQueue.dequeue();
                    if (pilgrimID != -1) {
                        Pilgrim* p = pilgrims.searchByID(pilgrimID);
                        if (p) {
                            setColor(10);
                            cout << "\n\t\t✓ Processing priority pilgrim: " << p->name << " (ID: " << p->id << ")\n";
                            setColor(7);
                        }
                    } else {
                        cout << "\n\t\tPriority queue is empty!\n";
                    }
                }

                cout << "\n\t\tPress any key to continue...";
                cin.ignore();
                cin.get();
                break;
            }

            case 6: {
                displayHeader();
                accommodationMgr.displayAll();
                cout << "\n\t\tPress any key to continue...";
                cin.ignore();
                cin.get();
                break;
            }

            case 7: {
                displayHeader();
                setColor(11);
                cout << "\n\t\t========== RITUAL TRACKING ==========\n\n";
                setColor(7);
                cout << "\t\t1. Mark Ritual as Completed\n";
                cout << "\t\t2. View Completed Rituals\n";
                cout << "\t\t3. Back to Main Menu\n";
                cout << "\n\t\tEnter choice: ";
                int ritualChoice;
                cin >> ritualChoice;

                if (ritualChoice == 1) {
                    cout << "\n\t\t========== HAJJ RITUALS ==========\n";
                    cout << "\t\t1. Ihram (State of Consecration)\n";
                    cout << "\t\t2. Tawaf (Circumambulation of Kaaba)\n";
                    cout << "\t\t3. Sa'i (Walking between Safa and Marwa)\n";
                    cout << "\t\t4. Standing at Arafat\n";
                    cout << "\t\t5. Muzdalifah (Night Stay)\n";
                    cout << "\t\t6. Rami (Stoning the Devil)\n";
                    cout << "\t\t7. Sacrifice (Qurbani)\n";
                    cout << "\n\t\tSelect ritual to mark as completed: ";
                    int ritualNum;
                    cin >> ritualNum;

                    const char* rituals[] = {
                        "Ihram (State of Consecration)",
                        "Tawaf (Circumambulation of Kaaba)",
                        "Sa'i (Walking between Safa and Marwa)",
                        "Standing at Arafat",
                        "Muzdalifah (Night Stay)",
                        "Rami (Stoning the Devil)",
                        "Sacrifice (Qurbani)"
                    };

                    if (ritualNum >= 1 && ritualNum <= 7) {
                        ritualStack.push(rituals[ritualNum - 1]);
                        setColor(10);
                        cout << "\n\t\t✓ Ritual marked as completed!\n";
                        setColor(7);
                    } else {
                        setColor(12);
                        cout << "\n\t\t✗ Invalid ritual selection!\n";
                        setColor(7);
                    }
                } else if (ritualChoice == 2) {
                    ritualStack.displayRituals();
                }

                cout << "\n\t\tPress any key to continue...";
                cin.ignore();
                cin.get();
                break;
            }

            case 8: {
                displayHeader();
                setColor(11);
                cout << "\n\t\t========== SORT PILGRIMS ==========\n\n";
                setColor(7);
                cout << "\t\t1. Sort by ID (Selection Sort)\n";
                cout << "\t\t2. Sort by Age (Bubble Sort)\n";
                cout << "\t\t3. Display Sorted by ID (BST In-Order)\n";
                cout << "\n\t\tEnter choice: ";
                int sortChoice;
                cin >> sortChoice;

                Pilgrim* arr = pilgrims.getAllPilgrimsArray();
                int count = pilgrims.getCount();

                if (arr != nullptr && count > 0) {
                    if (sortChoice == 1) {
                        selectionSortByID(arr, count);
                        cout << "\n\t\t========== PILGRIMS SORTED BY ID ==========\n\n";
                    } else if (sortChoice == 2) {
                        bubbleSortByAge(arr, count);
                        cout << "\n\t\t========== PILGRIMS SORTED BY AGE ==========\n\n";
                    } else if (sortChoice == 3) {
                        pilgrimBST.displayInOrder();
                        delete[] arr;
                        cout << "\n\t\tPress any key to continue...";
                        cin.ignore();
                        cin.get();
                        break;
                    }

                    cout << "\t" << left << setw(8) << "ID" << setw(25) << "Name"
                         << setw(6) << "Age" << setw(20) << "Country" << endl;
                    cout << "\t" << string(60, '-') << endl;

                    for (int i = 0; i < count; i++) {
                        cout << "\t" << left << setw(8) << arr[i].id
                             << setw(25) << arr[i].name
                             << setw(6) << arr[i].age
                             << setw(20) << arr[i].country << endl;
                    }

                    delete[] arr;
                } else {
                    cout << "\n\t\tNo pilgrims to sort!\n";
                }

                cout << "\n\t\tPress any key to continue...";
                cin.ignore();
                cin.get();
                break;
            }

            case 9: {
                displayHeader();
                setColor(11);
                cout << "\n\t\t========== SYSTEM REPORTS ==========\n\n";
                setColor(7);

                int totalPilgrims = pilgrims.getCount();
                int queueSize = transportQueue.getSize();
                int prioritySize = priorityQueue.getSize();
                int ritualsCompleted = ritualStack.getCount();

                cout << "\t\t📊 Total Pilgrims Registered: " << totalPilgrims << endl;
                cout << "\t\t🚌 Pilgrims in Transportation Queue: " << queueSize << endl;
                cout << "\t\t⚠️  Pilgrims in Priority Queue: " << prioritySize << endl;
                cout << "\t\t🕋 Rituals Completed: " << ritualsCompleted << " / 7" << endl;

                int progress = (ritualsCompleted * 100) / 7;
                cout << "\n\t\t🔄 Hajj Progress: " << progress << "%" << endl;

                cout << "\n\t\t========================================\n";

                cout << "\n\t\tPress any key to continue...";
                cin.ignore();
                cin.get();
                break;
            }

            case 10: {
                displayHeader();
                setColor(10);
                cout << "\n\n\t\t========================================\n";
                cout << "\t\t   Thank you for using the system!\n";
                cout << "\t\t   May Allah accept everyone's Hajj.\n";
                cout << "\t\t========================================\n\n";
                setColor(7);
                return 0;
            }

            default: {
                setColor(12);
                cout << "\n\t\t✗ Invalid choice! Please try again.\n";
                setColor(7);
                cout << "\n\t\tPress any key to continue...";
                cin.ignore();
                cin.get();
                break;
            }
        }
    }

    return 0;
}
