#include<stdio.h>
#include<stdlib.h>
#include<time.h>
/* 
一、单向链表的增删改查
二、链表的排序（从大到小和从小到大）

 */

typedef struct linklist{
    int num;
    struct linklist *next;
} LinkList;
int element_num;//全局变量，表内元素个数
LinkList *InitList();//初始化头指针
void CreateList(LinkList *L,int n);//建立单向链表
void DisplayList(LinkList *L);//遍历链表
void DestroyList(LinkList *L);//释放整个链表
void InsertList(LinkList *L);//向position位置插入num数据
void DeleteList(LinkList *L);//删除
void FindElementInList(LinkList *L);//查找链表中的值
void ChangeElementInList(LinkList *L);//修改链表中某个位置的值
void choose(LinkList *L);//选择操作（插入，删除，查询，修改）
void ListSort(LinkList *L);//冒泡排序，由小到大和由大到小
int main()
{
    LinkList *list_one;
    int n;
    printf("please input the element quantity in the list:");
    scanf("%d",&n);
    list_one=InitList();
    CreateList(list_one,n);
    DisplayList(list_one);
    choose(list_one);
    DestroyList(list_one);
    // malloc(1);
    return 0;
}

LinkList *InitList()//初始化头指针
{
    LinkList *L;
    L=(LinkList *)malloc(sizeof(LinkList));
    L->next=NULL;
    return L;
}
void CreateList(LinkList *l,int n)//建立链表
{
    LinkList *p,*q;
    int i;
    p=l;
    srand((unsigned)time(NULL));
    for(i=0;i<n;i++)
    {
        q=(LinkList *)malloc(sizeof(LinkList));
        q->num=rand()%10;
        //scanf("%d",&(q->num));
        q->next=NULL;
        p->next=q;
        p=q;
        printf("%d,",q->num);
    }
    printf("input done\n");
}

void DisplayList(LinkList *L)//遍历列表
{
    LinkList *p;
    p=L->next;
    element_num=0;
    printf("element in the list:\n");
    while(1)
    {
        printf("%d\t",p->num);
        element_num++;
        if(p->next==NULL)
            break;
        p=p->next;
    }
    printf("Now there are %d elements in the list\n",element_num);
}

void DestroyList(LinkList *L)//释放整个链表
{
    LinkList *p;
    while(L!=NULL)
    {
        p=L;
        L=L->next;
        free(p);
    }
    if(L==NULL)
        printf("memory has been freed.");
}

void InsertList(LinkList *L)//插入
{
    LinkList *p,*q;
    int i,position,num;
    p=L;
    printf("please input the position and the number:");
    scanf("%d%d",&position,&num);
    for(i=0;i<position-1;i++)
    {
        p=p->next;
    }
    q=(LinkList *)malloc(sizeof(LinkList));
    q->num=num;
    q->next=p->next;
    p->next=q;
}

void DeleteList(LinkList *L)//删除
{
    LinkList *p,*q;
    int i,position;
    p=L;
    printf("please input the position:");
    scanf("%d",&position);
    for(i=0;i<position;i++)
    {
        q=p;
        p=p->next;
    }
    q->next=p->next;
    free(p);
}

void FindElementInList(LinkList *L)//查找链表中的值
{
    int num,position=1;
    LinkList *p;
    p=L->next;
    printf("please input the number which you want to find:");
    scanf("%d",&num);
    while(p!=NULL)
    {
        if(p->num==num)
        {
            printf("the number is in %d position\n");
        }
        else
        {
            p=p->next;
            position++;
        }
    }
}

void ChangeElementInList(LinkList *L)//修改链表中某个位置的值
{
    int changed,position;
    int i;
    LinkList *p;
    p=L;
    printf("please input the position where you want to change and the number:");
    scanf("%d%d",&changed,&position);
    for(i=0;i<position;i++)
    {
        p=p->next;
    }
    p->num=changed;
}

void choose(LinkList *L)//选择操作（插入，删除，查询，修改）
{
    printf("please choose what you want to do from the following options:\n");
    printf("1:Insert\n2:Delete\n3:select\n4:change\n5:sort\n0:quit\n");
    getchar();
    switch (getchar())
    {
    case '1':
        InsertList(L);
        DisplayList(L);
        choose(L);
        break;
    case '2':
        DeleteList(L);
        DisplayList(L);
        choose(L);
        break;
    case '3':
        FindElementInList(L);
        DisplayList(L);
        choose(L);
        break;
    case '4':
        ChangeElementInList(L);
        DisplayList(L);
        choose(L);
        break;
    case '5':
        ListSort(L);
        DisplayList(L);
        choose(L);
        break;
    default:
        break;
    }
}

void ListSort(LinkList *L)//冒泡排序（由大到小和由小到大）
{
    int temp,i,j;
    LinkList *p;
    p=L->next;
    printf("please input the way that you want to sort:\n1:from big to small\n2:from little to large\n");
    getchar();
    if(getchar()=='1')
    {
        for(i=0;i<element_num-1;i++)
        {
            for(j=0;j<element_num-1-i;j++)
            {
                printf("%dand%d\n",p->num,p->next->num);
                if(p->num<p->next->num)
                    {
                        temp=p->next->num;
                        p->next->num=p->num;
                        p->num=temp;    
                    }
                p=p->next;
            }
            p=L->next;
        }
    }
    else
    {
        for(i=0;i<element_num-1;i++)
        {
            for(j=0;j<element_num-1-i;j++)
            {
                if(p->num>p->next->num)
                    {
                        temp=p->next->num;
                        p->next->num=p->num;
                        p->num=temp;
                    }
                p=p->next;
            }
            p=L->next;
        }
    }
}