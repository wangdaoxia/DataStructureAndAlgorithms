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
void EnQueue(LinkQueue* _queue,QueueType _elem);
// 出队操作
QueueType DeQueue(LinkQueue*_queue);
// 打印队列数据
void PrintQueue(LinkQueue* _queue);

int main(int argc,const char* argv[])
{
    LinkQueue* queue=InitQueue();
    int queuelength=0;
    printf("please input the quantity of a queue:");
    scanf("%d",&queuelength);
    for(int i=0;i<queuelength;i++)
    {
        EnQueue(queue,i);
    }
    PrintQueue(queue);
    int length=CaculateQueueLength(queue);
    printf("\n%d",length);
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
    while(!QueueIsEmpty(_queue))
    {
        DeQueue(_queue);
    }
    free(_queue->front);
    free(_queue);
}

void EnQueue(LinkQueue* _queue,QueueType _elem)
{
    QueueNode* temp=(QueueNode*)malloc(sizeof(QueueNode));
    if(!temp)
    {
        exit(1);
    }
    temp->data=_elem;
    temp->next=NULL;
    _queue->rear->next=temp;
    _queue->rear=temp;
}

QueueType DeQueue(LinkQueue*_queue)
{
    if(QueueIsEmpty(_queue))
    {
        exit(1);
        
    }
    else
    {
        QueueNode* p=_queue->front->next;
        QueueType tempdata=p->data;
        _queue->front->next=p->next;
        if(_queue->rear==p)
        {
            _queue->rear=_queue->front;
        }
        free(p);
        return tempdata;
    }
}

bool QueueIsEmpty(LinkQueue* _queue)
{
    if(_queue->front==_queue->rear)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int CaculateQueueLength(LinkQueue* _queue)
{
    QueueNode* temp=_queue->front;
    int count=0;
    while(temp!=_queue->rear)
    {
        count++;
        temp=temp->next;
    }
    return count;
}

void PrintQueue(LinkQueue* _queue)
{
    if(QueueIsEmpty(_queue))
    {
        printf("sorry, the queue is empty!");
    }
    else
    {
        QueueNode* temp=_queue->front->next;
        while(temp!=_queue->rear->next)
        {
            printf("%d\t",temp->data);
            temp=temp->next;
        }
    }
}