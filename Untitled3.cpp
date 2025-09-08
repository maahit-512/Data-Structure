#include <iostream>
#include <string>
using namespace std;
struct Order {
    int orderID;
    string items[3];
    string customerName;
};
class CircularQueue {
    Order* queue;
    int front;
    int rear;
    int size;
    int capacity;
public:
    CircularQueue(int cap) {
        capacity = cap;
        queue = new Order[capacity];
        front = -1;
        rear = -1;
        size = 0;
    }
    ~CircularQueue() {
        delete[] queue;
    }
    bool isFull() {
        return size == capacity;
    }
    bool isEmpty() {
        return size == 0;
    }
    bool enqueue(const Order& order) {
        if (isFull()) return false;
        rear = (rear + 1) % capacity;
        queue[rear] = order;
        if (front == -1) front = 0;
        size++;
        return true;
    }
    bool dequeue(Order& order) {
        if (isEmpty()) return false;
        order = queue[front];
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % capacity;
        }
        size--;
        return true;
    }
    void display() {
        if (isEmpty()) {
            cout << "No orders in queue\n";
            return;
        }
        int count = size;
        int i = front;
        while (count--) {
            cout << "Order ID: " << queue[i].orderID << ", Customer: " << queue[i].customerName << ", Items: ";
            for (int j = 0; j < 3; j++) cout << queue[i].items[j] << " ";
            cout << "\n";
            i = (i + 1) % capacity;
        }
    }
};
Order getOrderFromUser() {
    Order order;
    cout << "Enter Order ID: ";
    cin >> order.orderID;
    cin.ignore();
    cout << "Enter Customer Name: ";
    getline(cin, order.customerName);
    for (int i = 0; i < 3; i++) {
        cout << "Enter item " << i + 1 << ": ";
        getline(cin, order.items[i]);
    }
    return order;
}
int main() {
    CircularQueue orders(10);
    int choice;
    Order processedOrder;
    do {
        cout << "\n1. Add Order\n2. Process Order\n3. Display Orders\n4. Exit\nChoose: ";
        cin >> choice;
        cin.ignore();
        if (choice == 1) {
            Order o = getOrderFromUser();
            if (!orders.enqueue(o)) {
                cout << "Queue Full! Cannot add order.\n";
            }
        } else if (choice == 2) {
            if (orders.dequeue(processedOrder)) {
                cout << "Processed Order ID: " << processedOrder.orderID << " for " << processedOrder.customerName << "\n";
            } else {
                cout << "No orders to process.\n";
            }
        } else if (choice == 3) {
            orders.display();
        }
    } while (choice != 4);
    return 0;
}
