#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define STACK_SIZE 4 // 公車最大數量
#define QUEUE_SIZE 8 // 公車站最大數量
#define N 20

void queue(int *wait_student);
bool queue_isempty(void);
bool queue_isfull(void);
void queue_push(int weight);
int queue_pop(void);
void stack(void);
bool stack_isempty(void);
bool stack_isfull(void);
void stack_push(int weight);
int stack_pop(void);

int order = 0; // 學生進去公車站的數量
int top = 0, front = 0, rear = 0, stack_list[STACK_SIZE], queue_list[QUEUE_SIZE];
int main(void)
{
    int EE_student_number = 0;
    int wait_student[N];
    int EE_student[N];
    printf("Please input 20 students' weight : \n");
    for (int x, i = 0; i < N; i++) // 讀取所有20位學生的體重
    {
        scanf("%d", &x);
        wait_student[i] = x;
    }
    while (EE_student_number != 20) // 將學生載往電機系館的過程
    {
        queue(wait_student); // 將公車站排滿八人
        stack();             // 公車坐滿人數限制

        printf("The bus arrives at EE buildings\n");
        while (!stack_isempty()) // 公車上的人一一下車
        {
            EE_student[EE_student_number] = stack_pop();
            printf("%d ", EE_student[EE_student_number++]);
        }
        printf("get off the bus\n");
        printf("Back to train station~~\n");
        printf("\n");
    }
    printf("The order of students enter EE building is :\n");
    printf("{");
    for (int i = 0; i < N; i++) // 最後將系館的20人順序印出來
    {
        printf("%d ", EE_student[i]);
    }
    printf("\b}");
    printf("\n");
}
void queue(int *wait_student) // 目標為將公車站人填滿
{
    while (1)
    {
        if (queue_isfull() || order == 20) // 當公車的人滿了或者已經20人進公車站時，就結束
        {
            printf("Waiting in line : "); // 將公車站裡的人input
            for (int i = front + 1; i < rear + 1; i++)
            {
                printf("%d ", queue_list[i % QUEUE_SIZE]);
            }
            printf("\n");
            break;
        }
        else
        {
            queue_push(*(wait_student + order++)); // 將學生體重輸入進去，學生順序加一
        }
    }
}
bool queue_isempty(void) // 檢測queue是不是為空
{
    return front == rear;
}
bool queue_isfull(void) // 檢測queue是不是為滿
{
    return (rear - front) == QUEUE_SIZE;
}
void queue_push(int weight)
{
    queue_list[++rear % QUEUE_SIZE] = weight;
}
int queue_pop(void)
{
    return queue_list[++front % QUEUE_SIZE];
}
void stack(void)
{
    int weight = 0;
    int times = rear - front;   // 紀錄公車站總共有幾人
    for (int i = 0; i < 4; i++) // 第一步驟：四人先上公車
    {
        weight += queue_list[(front + 1) % QUEUE_SIZE]; // 檢測總重
        printf("%d ", queue_list[(front + 1) % QUEUE_SIZE]);
        stack_push(queue_list[(front + 1) % QUEUE_SIZE]); // 人上公車
        queue_pop();                                      // 人下公車站
        times--;                                          // 紀錄還有幾個人可以做更換
        if (times <= 0)
            break;
    }
    printf("get on the bus\n");
    while (weight > 260) // 第二步驟：如果超重就要換人，直到公車站的人都換過
    {
        queue_push(stack_pop()); // 公車下車的人進公車站
        printf("OVERWEIGHT!! %d gets off the bus\n", queue_list[rear % QUEUE_SIZE]);
        weight -= queue_list[rear % QUEUE_SIZE];
        if (times <= 0)
            break;
        else
        {
            stack_push(queue_pop()); // 公車站的人進公車
            printf("%d gets on the bus\n", stack_list[top - 1]);
            weight += stack_list[top - 1];
            times--;
        }
    }
    for (int i = 0; i < top; i++) // 第三步驟：公車出發
    {
        printf("%d ", stack_list[i]);
    }
    printf("are on the bus and aren't overweighting\n");
    printf("THe bus departs from train station\n");
}
bool stack_isempty(void) // 檢測stack是不是為空
{
    return top == 0;
}
bool stack_isfull(void) // 檢測stack是不是為滿
{
    return top == STACK_SIZE;
}
void stack_push(int weight)
{
    stack_list[top++] = weight;
}
int stack_pop(void)
{
    return stack_list[--top];
}