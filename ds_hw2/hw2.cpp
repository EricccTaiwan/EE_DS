#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define STACK_SIZE 4
#define QUEUE_SIZE 8
#define MAX_WEIGHT 260

using namespace std;

class Queue 
{ // Queue class
private:
    int front, rear, capacity;
    int* queue;

public:
    Queue(int size) 
    {
        front = rear = 0;
        capacity = size;
        queue = new int[capacity];
    }

    bool isEmpty() 
    {
        return front == rear;
    }

    bool isFull(){
        return (rear+1) % capacity == front;
    }
    void push(int weight) {
        queue[rear] = weight;
        rear = (rear+1) % capacity;
    }

    int pop() {
        int weight = queue[front];
        front = (front + 1) % capacity;
        return weight;
    }
    int size() {
        return (rear - front + capacity) % capacity;
    }
    int next(){
        return queue[front];
    }


};

class Stack {  // Stack class 
private:
    int top, capacity;
    int* stack;

public:
    Stack(int size) {
        top = -1;
        capacity = size;
        stack = new int[capacity];
    }

    void push(int weight) {
        if (isFull()) {
            cout << "Stack is full!" << endl;
            return;
        }
        stack[++top] = weight;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return stack[top--];
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == capacity - 1;
    }

    int sum() {
        int total = 0;
        for (int i = 0; i <= top; ++i) {
            total += stack[i];
        }
        return total;
    }
};

int main(){
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");
    if (!inputFile.is_open()) {
        cout << "Failed to open input file." << endl;
        return 1;
    }

    int test_case; //測資數量
    inputFile >> test_case;

    for (int i = 0; i < test_case; ++i) 
    {
        int student_num; //學生數量
        inputFile >> student_num;
        
        Queue student_weight (student_num+1);
        Queue eebuilding (student_num+1);
        Queue train_station(QUEUE_SIZE+1);
        Stack bus(STACK_SIZE);
        //70,67,75,55,51,40,87,65,58,86,66,43,57,76,68,61,60,63,39,74
        for( int j = 0 ; j < student_num ; j++ )
        {
            int weight ;
            char comma ;
            inputFile >> weight;  //讀取學生體重
            student_weight.push(weight);
            if(j!=student_num-1){   //忽略逗號
                inputFile >> comma;
            }
        }

        while( !eebuilding.isFull() )
        {
            while(!train_station.isFull() && !student_weight.isEmpty())
            {
                int weight = student_weight.pop();
                train_station.push(weight);
            }

            while(!train_station.isEmpty() && !bus.isFull())
            {
                int weight = train_station.pop();
                bus.push(weight);
                int bus_sum_weight = bus.sum();
                int attempt = 0;
                int train_station_size = train_station.size();
                // 公車超重
                while (bus_sum_weight > MAX_WEIGHT && attempt < train_station_size) {
                    int bus_last_overweight = bus.pop();
                    int bus_next_weight = train_station.pop();
                    bus.push(bus_next_weight);
                    train_station.push(bus_last_overweight);
                    ++attempt;
                    bus_sum_weight = bus.sum(); //迴圈內宣告只在迴圈內有效 所以這裡不能是int bus(後略
                }
                if (bus_sum_weight > MAX_WEIGHT) { 
                    break;
                }                  
            }
            while (!bus.isEmpty()) 
            {
                int weight_from_bus = bus.pop();
                eebuilding.push(weight_from_bus);
            }

        }

        while( !eebuilding.isEmpty() ) 
        {
            int weight_eebuilding = eebuilding.pop();
            outputFile << weight_eebuilding;

            if (!eebuilding.isEmpty()) 
            {
                outputFile << ",";
            }
        }

        if (i != test_case - 1) 
        {
            outputFile << endl;
        }

    }


    inputFile.close();
    outputFile.close();
    
    return 0;
}