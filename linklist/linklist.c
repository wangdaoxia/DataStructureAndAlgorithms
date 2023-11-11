#include"linklist.h"
#include<assert.h>
int main(int argc,const char* argv[])
{
    LinkList *list_one;
    int n;
    printf("please input the element quantity in the list:");
    scanf("%d",&n);
    list_one=InitList();
    CreateList(list_one,n);
    TraverseList(list_one);
    LinkList* list_two=InitList();
    CreateList(list_two,n+2);
    TraverseList(list_two);
    LinkList* mergedlist=MergeTwoOrderedLinkList(list_one,list_two);
    TraverseList(mergedlist);
    DestroyList(list_two);
    // int length=GetLinkListLength(list_one);
    // printf("the length of list_one is %d.\n",length);
    // InsertList(list_one,3,11);
    // DeleteList(list_one,1);
    // TraverseList(list_one);
    // printf("%d\n",FindElementInList(list_one,10));
    // ChangeElementInList(list_one,3,100);
    // TraverseList(list_one);

    DestroyList(list_one);
    DestroyList(mergedlist);

    return 0;
}

LinkList *InitList()//初始化头指针
{
    LinkList *L;
    L=(LinkList *)malloc(sizeof(LinkList));
    L->next_=NULL;
    return L;
}

void CreateList(LinkList *L,int n)//建立链表
{
    LinkList *p,*q;
    p=L;
    // srand((unsigned)time(NULL));
    for(int i=0;i<n;i++)
    {
        InsertList(L,i,i);
    }
    printf("input done\n");
}

void TraverseList(LinkList *L)//遍历列表
{
    LinkList *p;
    p=L->next_;
    printf("Traverse begin:\nelements in the list:\n");
    while(1)
    {
        printf("%d\t",p->val_);
        if(p->next_==NULL)
            break;
        p=p->next_;
    }
    printf("\nTraverse done.\n");
}

void DestroyList(LinkList *L)//释放整个链表
{
    LinkList *p;
    while(L!=NULL)
    {
        p=L;
        L=L->next_;
        free(p);
    }
    if(L==NULL)
        printf("memory has been freed.");
}

void InsertList(LinkList *L,int pos,int val)
{
    LinkList *p,*q;
    p=L;
    assert(pos>=0);
    assert(pos<=GetLinkListLength(L));
    for(int i=0;i<pos;i++)
    {
        p=p->next_;
    }
    q=(LinkList *)malloc(sizeof(LinkList));
    q->val_=val;
    q->next_=p->next_;
    p->next_=q;
}

void DeleteList(LinkList *L,int pos)//删除
{
    assert(L!=NULL);
    LinkList *p,*q;
    p=L;
    assert(pos>=0);
    assert(pos<=GetLinkListLength(L));
    for(int i=0;i<pos;i++)
    {
        p=p->next_;
    }
    q=p->next_;
    p->next_=q->next_;
    free(q);
}

int FindElementInList(LinkList *L,int elem)//查找链表中的值
{
    assert(L!=NULL);
    int position=0;
    LinkList *p;
    p=L->next_;
    while(p!=NULL)
    {
        if(p->val_==elem)
        {
            printf("the number is in %d position\n",position);
            return position;
        }
        else
        {
            p=p->next_;
            position++;
        }
    }
    printf("sorry,the elem that you want to find is not in this list,please try another elem.\n");
    return -1;
}

void ChangeElementInList(LinkList *L,int pos,int val)//修改链表中某个位置的值
{
    assert(!ListIsEmpty(L));
    assert(pos>=0);
    assert(pos<=GetLinkListLength(L));
    LinkList *p;
    p=L->next_;
    for(int i=0;i<pos;i++)
    {
        p=p->next_;
    }
    p->val_=val;
}

// void choose(LinkList *L)//选择操作（插入，删除，查询，修改）
// {
//     printf("please choose what you want to do from the following options:\n");
//     printf("1:Insert\n2:Delete\n3:select\n4:change\n5:sort\n0:quit\n");
//     getchar();
//     switch (getchar())
//     {
//     case '1':
//         InsertList(L);
//         DisplayList(L);
//         choose(L);
//         break;
//     case '2':
//         DeleteList(L);
//         DisplayList(L);
//         choose(L);
//         break;
//     case '3':
//         FindElementInList(L);
//         DisplayList(L);
//         choose(L);
//         break;
//     case '4':
//         ChangeElementInList(L);
//         DisplayList(L);
//         choose(L);
//         break;
//     case '5':
//         ListSort(L);
//         DisplayList(L);
//         choose(L);
//         break;
//     default:
//         break;
//     }
// }

void ListSort(LinkList *L,SortMethod _method,OrderType _ordertype)//冒泡排序（由大到小和由小到大）
{
    assert(!ListIsEmpty(L));

    // int temp,i,j;
    // LinkList *p;
    // p=L->next_;
    // printf("please input the way that you want to sort:\n1:from big to small\n2:from little to large\n");
    // getchar();
    // if(getchar()=='1')
    // {
    //     for(i=0;i<element_num-1;i++)
    //     {
    //         for(j=0;j<element_num-1-i;j++)
    //         {
    //             printf("%dand%d\n",p->val_,p->next_->val_);
    //             if(p->val_<p->next_->val_)
    //                 {
    //                     temp=p->next_->val_;
    //                     p->next_->val_=p->val_;
    //                     p->val_=temp;    
    //                 }
    //             p=p->next_;
    //         }
    //         p=L->next_;
    //     }
    // }
    // else
    // {
    //     for(i=0;i<element_num-1;i++)
    //     {
    //         for(j=0;j<element_num-1-i;j++)
    //         {
    //             if(p->val_>p->next_->val_)
    //                 {
    //                     temp=p->next_->val_;
    //                     p->next_->val_=p->val_;
    //                     p->val_=temp;
    //                 }
    //             p=p->next_;
    //         }
    //         p=L->next_;
    //     }
    // }
}

int GetLinkListLength(LinkList* L)
{
    int length=0;
    LinkList *tmp=L->next_;
    while(tmp)
    {
        length++;
        tmp=tmp->next_;
    }
    return length;
}

bool ListExists(LinkList *L)
{
    if(L)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool ListIsEmpty(LinkList* L)
{
    assert(ListExists(L));
    if(L->next_==NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

LinkList* MergeTwoOrderedLinkList(LinkList* L1,LinkList *L2)
{
    if(ListIsEmpty(L1))
    {
        return L2;
    }
    else if(ListIsEmpty(L2))
    {
        return L1;
    }
    else
    {
        LinkList* res=InitList();
        LinkList* l1=L1->next_;
        LinkList* l2=L2->next_;
        int L1length=GetLinkListLength(L1);
        int L2length=GetLinkListLength(L2);
        int i1=0;
        int i2=0;
        while(i1<L1length&&i2<L2length)
        {
            if(l1->val_<l2->val_)
            {
                InsertList(res,i1+i2,l1->val_);
                l1=l1->next_;
                i1++;
            }
            else
            {
                InsertList(res,i1+i2,l2->val_);
                l2=l2->next_;
                i2++;
            }
        }
        if(i1==L1length)
        {
            while(i2<L2length)
            {
                InsertList(res,i1+i2,l2->val_);
                l2=l2->next_;
                i2++;
            }
        }
        else if(i2==L2length)
        {
            while(i1<L1length)
            {
                InsertList(res,i1+i2,l1->val_);
                i1++;
                l1=l1->next_;
            }
        }
        return res;
    }
}