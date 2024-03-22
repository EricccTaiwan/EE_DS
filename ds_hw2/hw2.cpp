#include <iostream>
#include <fstream>
#define STACK_SIZE 4
#define QUEUE_SIZE 8
#define MAX_STUDENTS 100
//�ֺεۤF

using namespace std;

// Implementation of Queue using Array
class Queue {
private:
    int front, rear, capacity;
    int* queue;

public:
    Queue(int size) {
        front = rear = 0;
        capacity = size;
        queue = new int[capacity];
    }

    void push(int item) {
        if (rear == capacity) {
            cout << "Queue is full!" << endl;
            return;
        }
        queue[rear++] = item;
    }

    int pop() {
        if (front == rear) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        return queue[front++];
    }

    bool isEmpty() {
        return front == rear;
    }
};

// Implementation of Stack using Array
class Stack {
private:
    int top, capacity;
    int* stack;

public:
    Stack(int size) {
        top = -1;
        capacity = size;
        stack = new int[capacity];
    }

    void push(int item) {
        if (top == capacity - 1) {
            cout << "Stack is full!" << endl;
            return;
        }
        stack[++top] = item;
    }

    int pop() {
        if (top == -1) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return stack[top--];
    }

    bool isEmpty() {
        return top == -1;
    }
};

