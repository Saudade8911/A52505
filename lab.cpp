#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
using namespace std;

struct Customer {
    char id[10];
    char name[50];
    char serviceType[20];
    int arrivalTime;
    int processingTime;   
    int waitingWeight;    
};

struct Node {
    Customer data;
    Node* next;
};

struct Queue {
    Node* front;
    Node* rear;
    int size;
};

struct Action {
    char type[10];        // ADD, DELETE, UPDATE
    Customer oldData;
    Customer newData;
};

struct StackNode {
    Action data;
    StackNode* next;
};

struct Stack {
    StackNode* top;
};


Customer inputCustomer() {
    Customer c;

    cout << "Nhap ma khach hang: ";
    cin >> c.id;

    cin.ignore();

    cout << "Nhap ho ten: ";
    cin.getline(c.name, 50);

    cout << "Nhap loai dich vu: ";
    cin.getline(c.serviceType, 20);

    cout << "Nhap thoi gian den (phut): ";
    cin >> c.arrivalTime;

    cout << "Nhap thoi gian xu ly (pj): ";
    cin >> c.processingTime;

    cout << "Nhap trong so cho (wj): ";
    cin >> c.waitingWeight;

    return c;
}

void printCustomer(Customer c) {
    cout << "ID: " << c.id << endl;
    cout << "Ho ten: " << c.name << endl;
    cout << "Dich vu: " << c.serviceType << endl;
    cout << "Thoi gian den: " << c.arrivalTime << endl;
    cout << "Thoi gian xu ly: " << c.processingTime << endl;
    cout << "Trong so cho: " << c.waitingWeight << endl;
}

Node* createNode(Customer c) {
    Node* p = new Node;

    p->data = c;
    p->next = NULL;

    return p;
}

void initList(Node*& head) {
    head = NULL;
}

bool isEmptyList(Node* head) {
    return head == NULL;
}

void addCustomer(Node*& head, Customer c) {
    Node* p = createNode(c);

    if (head == NULL) {
        head = p;
        return;
    }

    Node* temp = head;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = p;
}

Node* searchCustomer(Node* head, const char id[]) {
    Node* temp = head;

    while (temp != NULL) {
        if (strcmp(temp->data.id, id) == 0) {
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}

void displayList(Node* head) {
    if (head == NULL) {
        cout << "Danh sach rong!" << endl;
        return;
    }

    Node* temp = head;

    while (temp != NULL) {
        cout << "ID: " << temp->data.id << endl;
        cout << "Ho ten: " << temp->data.name << endl;
        cout << "Dich vu: " << temp->data.serviceType << endl;
        cout << "Thoi gian den: " << temp->data.arrivalTime << endl;
        cout << "Thoi gian xu ly: " << temp->data.processingTime << endl;
        cout << "Trong so cho: " << temp->data.waitingWeight << endl;
        temp = temp->next;
    }
}

bool removeCustomer(Node*& head, const char id[], Customer& deletedCustomer) {
    if (head == NULL) {
        return false;
    }

    if (strcmp(head->data.id, id) == 0) {
        deletedCustomer = head->data;

        Node* temp = head;
        head = head->next;

        delete temp;

        return true;
    }

    Node* prev = head;
    Node* current = head->next;

    while (current != NULL) {
        if (strcmp(current->data.id, id) == 0) {
            deletedCustomer = current->data;

            prev->next = current->next;

            delete current;

            return true;
        }

        prev = current;
        current = current->next;
    }

    return false;
}

bool updateCustomer(Node* head, const char id[], Customer& oldData) {
    Node* p = searchCustomer(head, id);

    if (p == NULL) {
        return false;
    }

    oldData = p->data;

    cout << "\nNhap thong tin moi:\n";

    cin.ignore();

    cout << "Nhap ho ten: ";
    cin.getline(p->data.name, 50);

    cout << "Nhap loai dich vu: ";
    cin.getline(p->data.serviceType, 20);

    cout << "Nhap thoi gian den: ";
    cin >> p->data.arrivalTime;

    cout << "Nhap thoi gian xu ly pj: ";
    cin >> p->data.processingTime;

    cout << "Nhap trong so wj: ";
    cin >> p->data.waitingWeight;

    return true;
}

void initQueue(Queue& q) {
    q.front = NULL;
    q.rear = NULL;
    q.size = 0;
}

bool isEmptyQueue(Queue q) {
    return q.front == NULL;
}

void enqueue(Queue& q, Customer c) {
    Node* p = createNode(c);

    if (isEmptyQueue(q)) {
        q.front = q.rear = p;
    }
    else {
        q.rear->next = p;
        q.rear = p;
    }

    q.size++;
}

bool dequeue(Queue& q, Customer& c) {
    if (isEmptyQueue(q)) {
        return false;
    }

    Node* temp = q.front;

    c = temp->data;

    q.front = q.front->next;

    if (q.front == NULL) {
        q.rear = NULL;
    }

    q.size--;

    delete temp;

    return true;
}

void displayQueue(Queue q) {
    if (isEmptyQueue(q)) {
        cout << "Queue dang rong!\n";
        return;
    }

    Node* temp = q.front;

    cout << "\nQueue: ";

    while (temp != NULL) {
        cout << temp->data.id;

        if (temp->next != NULL) {
            cout << " -> ";
        }

        temp = temp->next;
    }

    cout << endl;
}

void initStack(Stack& s) {
    s.top = NULL;
}

bool isEmptyStack(Stack s) {
    return s.top == NULL;
}

void push(Stack& s, Action a) {
    StackNode* p = new StackNode;

    p->data = a;
    p->next = s.top;

    s.top = p;
}

bool pop(Stack& s, Action& a) {
    if (isEmptyStack(s)) {
        return false;
    }

    StackNode* temp = s.top;

    a = temp->data;

    s.top = s.top->next;

    delete temp;

    return true;
}

Action createAction(const char type[],Customer oldData,Customer newData) {
    Action a;

    strcpy(a.type, type);

    a.oldData = oldData;
    a.newData = newData;

    return a;
}

void undo(
    Stack& history,
    Node*& list,
    Queue& q
) {
    if (isEmptyStack(history)) {
        cout << "Khong co thao tac de hoan tac!\n";
        return;
    }

    Action a;

    pop(history, a);

    if (strcmp(a.type, "ADD") == 0) {

        Customer temp;

        removeCustomer(list, a.newData.id, temp);

        cout << "Da Undo thao tac ADD.\n";
    }

    else if (strcmp(a.type, "DELETE") == 0) {

        addCustomer(list, a.oldData);

        cout << "Da Undo thao tac DELETE.\n";
    }

    else if (strcmp(a.type, "UPDATE") == 0) {

        Node* p = searchCustomer(list, a.oldData.id);

        if (p != NULL) {
            p->data = a.oldData;
        }

        cout << "Da Undo thao tac UPDATE.\n";
    }

    initQueue(q);

    Node* temp = list;

    while (temp != NULL) {
        enqueue(q, temp->data);
        temp = temp->next;
    }
}

void searchAndUpdate(
    Node*& list,
    Queue& q,
    Stack& history
) {
    char id[10];

    cout << "Nhap ID can tim: ";
    cin >> id;

    Node* p = searchCustomer(list, id);

    if (p == NULL) {
        cout << "Khong tim thay khach hang!\n";
        return;
    }

    cout << "\nThong tin khach hang hien tai:\n";
    printCustomer(p->data);

    Customer oldData;

    if (updateCustomer(list, id, oldData)) {

        Node* updated = searchCustomer(list, id);

        Action a = createAction(
            "UPDATE",
            oldData,
            updated->data
        );

        push(history, a);

        // Cap nhat lai Queue
        initQueue(q);

        Node* temp = list;

        while (temp != NULL) {
            enqueue(q, temp->data);
            temp = temp->next;
        }

        cout << "Cap nhat thanh cong!\n";
    }
}

void serveNextCustomer(
    Queue& q,
    int& servedCount,
    int& totalWaitingCost,
    int& totalWaitingTime
) {
    Customer c;

    if (!dequeue(q, c)) {
        cout << "Queue rong! Khong co khach de phuc vu.\n";
        return;
    }

    static int currentTime = 0;

    if (currentTime < c.arrivalTime) {
        currentTime = c.arrivalTime;
    }

    int waitingTime = currentTime - c.arrivalTime;

    int waitingCost = c.waitingWeight * waitingTime;

    currentTime += c.processingTime;

    servedCount++;

    totalWaitingTime += waitingTime;

    totalWaitingCost += waitingCost;

    cout << "\n===== PHUC VU KHACH =====\n";

    cout << "ID: " << c.id << endl;
    cout << "Ten: " << c.name << endl;
    cout << "Dich vu: " << c.serviceType << endl;
    cout << "Thoi gian cho: " << waitingTime << " phut\n";
    cout << "Chi phi cho: " << waitingCost << endl;

    cout << "Da phuc vu thanh cong!\n";
}

void printReport(
    Node* list,
    Queue q,
    int servedCount,
    int totalWaitingTime,
    int totalWaitingCost
) {
    cout << "\n";
    cout << "              BAO CAO CUOI NGAY\n";
    cout << "So khach da phuc vu: "
         << servedCount << endl;

    cout << "Tong thoi gian cho: "
         << totalWaitingTime << " phut\n";

    cout << "Tong chi phi cho: "
         << totalWaitingCost << endl;

    cout << "\nDanh sach khach con cho:\n";

    displayQueue(q);

    cout << "\nDanh sach tat ca khach:\n";

    displayList(list);
}



void sortByRatio(Customer a[], int n) {

    for (int i = 0; i < n - 1; i++) {

        for (int j = i + 1; j < n; j++) {

            double ratio1 =
                (double)a[i].waitingWeight /
                a[i].processingTime;

            double ratio2 =
                (double)a[j].waitingWeight /
                a[j].processingTime;

            if (ratio1 < ratio2) {
                Customer temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

int getCustomers(Node* list, Customer a[]) {

    int n = 0;

    Node* temp = list;

    while (temp != NULL) {

        a[n] = temp->data;

        n++;

        temp = temp->next;
    }

    return n;
}

void compareScheduling(Node* list) {

    Customer a[100];

    int n = getCustomers(list, a);

    if (n == 0) {
        cout << "Khong co ticket de sap lich!\n";
        return;
    }


    int timeFIFO = 0;
    int costFIFO = 0;

    for (int i = 0; i < n; i++) {

        timeFIFO += a[i].processingTime;

        costFIFO +=
            a[i].waitingWeight * timeFIFO;
    }

    sortByRatio(a, n);

    int timeSort = 0;
    int costSort = 0;

    cout << "\n===== THU TU SAU KHI SAP XEP wj/pj =====\n";

    cout << left
         << setw(8) << "ID"
         << setw(10) << "pj"
         << setw(10) << "wj"
         << setw(10) << "wj/pj"
         << endl;

    cout << "----------------------------------------\n";

    for (int i = 0; i < n; i++) {

        double ratio =
            (double)a[i].waitingWeight /
            a[i].processingTime;

        cout << left
             << setw(8) << a[i].id
             << setw(10) << a[i].processingTime
             << setw(10) << a[i].waitingWeight
             << setw(10) << fixed << setprecision(2)
             << ratio
             << endl;

        timeSort += a[i].processingTime;

        costSort +=
            a[i].waitingWeight * timeSort;
    }

    cout << "\n===== SO SANH =====\n";

    cout << "Chi phi FIFO: "
         << costFIFO << endl;

    cout << "Chi phi sau khi sap xep: "
         << costSort << endl;

    if (costSort < costFIFO) {
        cout << "Phuong an sap xep co chi phi cho thap hon.\n";
    }
    else if (costSort > costFIFO) {
        cout << "FIFO co chi phi cho thap hon trong du lieu nay.\n";
    }
    else {
        cout << "Hai phuong an co cung chi phi.\n";
    }
}

// =====================================================
//                   ADD CUSTOMER
// =====================================================

void addCustomerMenu(
    Node*& list,
    Queue& q,
    Stack& history
) {
    Customer c = inputCustomer();

    // Kiem tra ID trung
    if (searchCustomer(list, c.id) != NULL) {
        cout << "ID da ton tai!\n";
        return;
    }

    addCustomer(list, c);

    enqueue(q, c);

    Action a = createAction(
        "ADD",
        Customer{},
        c
    );

    push(history, a);

    cout << "Them khach hang thanh cong!\n";

    displayQueue(q);
}



void deleteCustomerMenu(
    Node*& list,
    Queue& q,
    Stack& history
) {
    char id[10];

    cout << "Nhap ID can xoa: ";
    cin >> id;

    Customer deleted;

    if (!removeCustomer(list, id, deleted)) {

        cout << "Khong tim thay khach hang!\n";

        return;
    }

    Action a = createAction(
        "DELETE",
        deleted,
        Customer{}
    );

    push(history, a);

    /*
        Tao lai Queue tu danh sach.
    */

    initQueue(q);

    Node* temp = list;

    while (temp != NULL) {

        enqueue(q, temp->data);

        temp = temp->next;
    }

    cout << "Xoa thanh cong!\n";
}

void menu() {

    cout << "\n";
    cout << "          SMART SERVICE DESK\n";
    cout << "1. Them khach vao hang doi\n";
    cout << "2. Phuc vu khach tiep theo\n";
    cout << "3. Tim kiem / cap nhat khach hang\n";
    cout << "4. Undo thao tac gan nhat\n";
    cout << "5. In bao cao cuoi ngay\n";
    cout << "6. Hien thi danh sach khach hang\n";
    cout << "7. Hien thi hang doi\n";
    cout << "8. Xoa khach hang\n";
    cout << "9. Sap xep ticket theo wj/pj\n";
    cout << "0. Thoat\n";

    cout << "=============================================\n";

    cout << "Nhap lua chon: ";
}

// =====================================================
//                         MAIN
// =====================================================

int main() {

    Node* list;

    Queue q;

    Stack history;

    initList(list);
    initQueue(q);
    initStack(history);

    int servedCount = 0;
    int totalWaitingTime = 0;
    int totalWaitingCost = 0;

    int choice;

    do {

        menu();

        cin >> choice;

        switch (choice) {

        case 1:
            addCustomerMenu(
                list,
                q,
                history
            );
            break;

        case 2:
            serveNextCustomer(
                q,
                servedCount,
                totalWaitingCost,
                totalWaitingTime
            );

            displayQueue(q);
            break;

        case 3:
            searchAndUpdate(
                list,
                q,
                history
            );
            break;

        case 4:
            undo(
                history,
                list,
                q
            );
            break;

        case 5:
            printReport(
                list,
                q,
                servedCount,
                totalWaitingTime,
                totalWaitingCost
            );
            break;

        case 6:
            displayList(list);
            break;

        case 7:
            displayQueue(q);
            break;

        case 8:
            deleteCustomerMenu(
                list,
                q,
                history
            );
            break;

        case 9:
            compareScheduling(list);
            break;
        case 0:
            cout << "Ket thuc chuong trinh.\n";
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);

    return 0;
}