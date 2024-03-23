#include <iostream>
#include <fstream>

#define STACK_SIZE 4
#define QUEUE_SIZE 8
#define MAX_WEIGHT 260

using namespace std;
class Stack {  // Stack class 
private:
    int top, capacity;
    int* stack;
public:
    Stack(int size) 
    {
        top = -1;
        capacity = size;
        stack = new int[capacity];
    }
    void push(int weight) 
    {
        stack[++top] = weight;
    }
    int pop() 
    {
        return stack[top--];
    }
    bool isEmpty() 
    {
        return top == -1;
    }
    bool isFull() 
    {
        return top == capacity - 1;
    }
    int sum() 
    {
        int total = 0;
        for (int i = 0; i <= top; ++i) {
            total += stack[i];
        }
        return total;
    }
};
class Queue { // Queue class
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
    void push(int weight) 
    {
        queue[rear] = weight;
        rear = (rear+1) % capacity;
    }
    int pop() 
    {
        int weight = queue[front];
        front = (front + 1) % capacity;
        return weight;
    }
    int size() 
    {
        return (rear - front + capacity) % capacity;
    }

};

void student_to_station(Queue& train_station, Queue& student_weight);
void station_to_bus(Queue& train_station, Stack& bus);
void bus_to_eebuilding(Stack& bus, Queue& eebuilding);
void eebuilding_print(Queue& eebuilding, ofstream& outputFile);

int main(){
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    Queue train_station  (QUEUE_SIZE+1); //固定大小
    Stack bus            (STACK_SIZE);   //固定大小
    
    int test_case; //測資數量
    inputFile >> test_case;
    for (int i = 0; i < test_case; ++i) 
    {
        int student_num; //學生數量
        inputFile >> student_num;
        Queue student_weight (student_num+1); //根據測資
        Queue eebuilding     (student_num+1); //根據測資

        if(student_num < 8 || student_num>100) 
        {   
            outputFile << "student number should be between 8 and 100 !"<<endl;  //題目人數限制
            for( int j = 0 ; j < student_num ; j++ )
            {
                int weight ;
                inputFile >> weight;         
                student_weight.push(weight);
                if (j!=student_num-1)
                {        
                    inputFile.ignore(1, ',');
                }
            }
            inputFile.clear();
            continue;
        }

        bool valid_weight = true;
        for( int j = 0 ; j < student_num ; j++ )
        {
            int weight ;
            inputFile >> weight;         
            if (weight<0 || weight > 260)
            {  
                valid_weight = false;   //題目體重限制
            }
            student_weight.push(weight);
            if (j!=student_num-1)
            {      
                inputFile.ignore(1, ',');
            }
        }

        if(!valid_weight)
        {
            outputFile << "student weight should be between 0 and 260 !"<<endl;
            inputFile.clear();
            continue;
        }

        while( !eebuilding.isFull() )
        {
            student_to_station(train_station ,student_weight); //學生進火車站
            station_to_bus    (train_station ,bus           ); //火車站學生，進公車
            bus_to_eebuilding (bus           ,eebuilding    ); //公車，到達eebuilding
        }

        eebuilding_print(eebuilding,outputFile); //印出eebuilding的學生體重

        if (i != test_case - 1) 
        {
            outputFile << endl;
        }
    }
    inputFile.close();
    outputFile.close();
    return 0;
}

void student_to_station(Queue& train_station, Queue& student_weight)
{
    while( !train_station.isFull() && !student_weight.isEmpty() ) //車站未滿，測資仍有人
    {
        int weight = student_weight.pop();
        train_station.push(weight);
    }
}

void station_to_bus(Queue& train_station, Stack& bus)
{
    while( !train_station.isEmpty() && !bus.isFull() )  //火車站有學生，公車未滿
    {
        int weight = train_station.pop();
        bus.push(weight);
        int bus_sum_weight = bus.sum();
        int attempt = 0;
        int train_station_size = train_station.size();
        while (bus_sum_weight > MAX_WEIGHT && attempt < train_station_size)  //公車超重，且為嘗試次數小於火車站人數
        {
            int bus_last_overweight = bus.pop();
            train_station.push(bus_last_overweight);
            int bus_next_weight = train_station.pop();
            bus.push(bus_next_weight);
            ++attempt;
            bus_sum_weight = bus.sum();
        }
        if (bus_sum_weight > MAX_WEIGHT)  //公車超重，且為車站內的人都嘗試過
        { 
            break;
        }                  
    }
}

void bus_to_eebuilding(Stack& bus, Queue& eebuilding)
{
    while( !bus.isEmpty() )  //直到公車沒人
    {
        int weight = bus.pop();
        eebuilding.push(weight);
    }
}

void eebuilding_print(Queue& eebuilding, ofstream& outputFile)
{
    while( !eebuilding.isEmpty() ) //直到eebuilding沒人
    {
        int weight_eebuilding = eebuilding.pop();
        outputFile << weight_eebuilding;
        if (!eebuilding.isEmpty()) 
        {
            outputFile << ",";
        }
    }
}