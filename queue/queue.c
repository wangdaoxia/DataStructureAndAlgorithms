#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
typedef int QueueType;
// 队列节点
typedef struct Queue
{
    QueueType data;             
    struct Queue* next;                 
} QueueNode;

typedef struct
{
    QueueNode* front;
    QueueNode* rear;
} LinkQueue;

// 初始化静态队列
LinkQueue* InitQueue();
// 销毁静态队列
void DestroyQueue(LinkQueue* _queue);
// 计算队列长度
int CaculateQueueLength(LinkQueue* _queue);
// 判断队列是否为空
bool QueueIsEmpty(LinkQueue* _queue);
// 入队操作
void EnQueue(LinkQueue* _queue);
// 出队操作
QueueNode* DeQueue(LinkQueue*_queue);


int main(int argc,const char* argv[])
{
    LinkQueue* queue=InitQueue();
    DestroyQueue(queue);
    return 0;
}

LinkQueue* InitQueue()
{
    QueueNode* headnode=(QueueNode*)malloc(sizeof(QueueNode));
    headnode->data=NULL;
    headnode->next=NULL;
    LinkQueue* head=(LinkQueue*)malloc(sizeof(LinkQueue));
    head->front=headnode;
    head->rear=headnode;
    return head;
}

void DestroyQueue(LinkQueue *_queue)
{
    
    if(_queue->front==_queue->rear)
        {
            free(_queue->front);
        }
}
