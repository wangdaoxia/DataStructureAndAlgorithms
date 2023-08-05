#include<stdio.h>
#include<stdlib.h>
#include<time.h>
/* 
（1）输入中缀表达式，输出前缀表达式和后缀表达式
（2）根据输入的前、中、后缀表达式求值(中序表达式有瑕疵，前序后序未编)
尝试用共用体代替两个数据域不同的结构体
 */
typedef struct stacknode{
    char data;
    struct stacknode *next;
}Stack;
typedef struct stacknode2{
    int num;
    struct stacknode2 *next;
}NumStack;

Stack *InitStack();//初始化栈顶指针
NumStack *InitStack2();//初始化算数栈顶指针
void CreateStack(Stack *S,int n);//建立一个栈
void DestroyStack(Stack *S);//释放内存
void DisplayStack(Stack *S);//遍历栈内数据
void Push(Stack *S,char data);//向栈中插入数据
void Push2(NumStack *S,int num);//向算数栈中插入数据
char Pop(Stack *S);//弹出栈顶元素
int Pop2(NumStack *S);//弹出算数栈栈顶元素
Stack *Reverse_Str(char *STR);//通过栈对中序表达式进行翻转
int Priority(char x);//判断运算符优先级
Stack *Middle_to_Pre(Stack *S);//将中序表达式转为前序表达式
Stack *Middle_to_Post(Stack *S);//将中序表达式转为后序表达式
Stack *Stack_Reverse(Stack *S);//栈的翻转
int Middle_Order_Result(char *s);//计算中序表达式的值
int Two_Operator_Priority(char a,char b);//运算符优先级，a在左，b在右，优先级高输出2，相同输出1，优先级小输出0
int Operation(int a,int b,char c);//执行运算，b是左侧数据，a是右侧数据

void main()
{
    Stack *Top,*t;
    char *str,s[10];
    int result;
    str=gets(s);
    puts(str);
    result=Middle_Order_Result(str);
    printf("result=%d",result);
    // printf("%s\n",str);
    // Top=Reverse_Str(str);
    // DisplayStack(Top);
    // Top=Middle_to_Post(Top);
    // DisplayStack(Top);
    // DestroyStack(Top);
    // srand((unsigned)time(NULL));
    //Top=InitStack();
    // CreateStack(Top,4);
    // DisplayStack(Top);
    // Push(Top,5);
    // DisplayStack(Top);
    // Pop(Top,&a);
    // DisplayStack(Top);
    // printf("the data poped is %d\n",a);
    // DestroyStack(Top);

}

Stack *InitStack()//初始化栈顶指针
{
    Stack *p;
    p=(Stack *)malloc(sizeof(Stack));
    p->next=NULL;
    return p;
}
NumStack *InitStack2()//初始化算数栈顶指针
{
    NumStack *p;
    p=(NumStack *)malloc(sizeof(NumStack));
    p->next=NULL;
    return p;
}

void CreateStack(Stack *S,int n)//建立一个栈
{
    int i;
    Stack *p;
    for(i=0;i<n;i++)
    {
        p=(Stack *)malloc(sizeof(Stack));
        p->data=i;
        p->next=S->next;
        S->next=p;
        printf("data:%c\t",p->data);
    }
}

void DestroyStack(Stack *S)//释放内存
{
    Stack *p;
    
    while(S!=NULL)
    {
        p=S;
        S=S->next;
        free(p);
    }
    if(S==NULL)
    {
        printf("The Stack is free.");
    }
}

void DisplayStack(Stack *S)//遍历栈内数据
{
    Stack *p;
    p=S->next;
    printf("the element in the stack:\n");
    while(1)
    {
        printf("%c\t",p->data);
        p=p->next;
        if(p==NULL)
            {
                printf("Stack bottom.\n");
                break;
            }
    }
}

void Push(Stack *S,char data)//向栈中插入数据
{
    Stack *p;
    p=(Stack *)malloc(sizeof(Stack));
    p->data=data;
    p->next=S->next;
    S->next=p;
}
void Push2(NumStack *S,int num)//向算数栈中插入数据
{
    NumStack *p;
    p=(NumStack *)malloc(sizeof(NumStack));
    p->num=num;
    p->next=S->next;
    S->next=p;
}

char Pop(Stack *S)//弹出栈顶元素
{
    Stack *p;
    char temp;
    p=S->next;   
    S->next=p->next;
    temp=p->data;
    free(p);
    return temp;
}
int Pop2(NumStack *S)//弹出算数栈栈顶元素
{
    NumStack *p;
    int temp;
    p=S->next;   
    S->next=p->next;
    temp=p->num;
    free(p);
    return temp;
}

Stack *Reverse_Str(char *STR)//通过栈对中序表达式进行翻转
{
    char *p;
    Stack *q;
    p=STR;
    q=InitStack();
    while(*p!='\0')
    {
        Push(q,*(p++));
    }
    return q;
}

Stack *Middle_to_Pre(Stack *S)//将中序表达式转为前序表达式
{
    char temp;
    Stack *pre,*operator,*p;
    pre=InitStack();
    operator=InitStack();
    p=S;
    while(p->next!=NULL)
    {
        temp=Pop(p);
        if(temp>='0'&&temp<='9')
        {
            Push(pre,temp);
        }
        else if(temp==')')
        {
            Push(operator,temp);
            printf("ope=%c\t",operator->next->data);
        }
        else if(temp!=')'&&temp!='(')
        {
            while(1)
            {
                if(operator->next==NULL)
                {
                    Push(operator,temp);
                    printf("ope=%c\t",operator->next->data);
                    break;
                } 
                else if(operator->next->data==')')
                {
                    Push(operator,temp);
                    printf("op=%c\t",operator->next->data);
                    break;
                }
                else if(Priority(temp)>=Priority(operator->next->data))
                {
                    Push(operator,temp);
                    break;   
                }
                else
                {
                    Push(pre,Pop(operator));                   
                    //operator=operator->next;
                }
            }
        }
        else if(temp=='(')
            {
                while(1)
                {
                    Push(pre,Pop(operator));
                    //operator=operator->next;
                    if(operator->next->data==')')
                    {
                        Pop(operator);
                        break;
                    }
                }
            }
    }
    while(operator->next!=NULL)
    {
        Push(pre,Pop(operator));
    }
    return pre;
}

int Priority(char x)//判断优先级
{
    int y;
    switch (x)
    {
    case '(':
        y=3;
        break;
    case ')':
        y=3;
        break;
    case '*':
        y=2;
        break;
    case '/':
        y=2;
        break;
    case '+':
        y=1;
        break;
    case '-':
        y=1;
        break;
    default:
        break;
    }
    return y;
}

Stack *Stack_Reverse(Stack *S)//栈的翻转
{
    Stack *temp;
    temp=InitStack();
    while(S->next!=NULL)
    Push(temp,Pop(S));
    return temp;
}
Stack *Middle_to_Post(Stack *S)//将中序表达式转为后序表达式
{
    char temp;
    Stack *pre,*operator,*p;
    pre=InitStack();
    operator=InitStack();
    p=Stack_Reverse(S);
    while(p->next!=NULL)
    {
        temp=Pop(p);
        if(temp>='0'&&temp<='9')
        {
            Push(pre,temp);
        }
        else if(temp=='(')
        {
            Push(operator,temp);
            printf("ope=%c\t",operator->next->data);
        }
        else if(temp!=')'&&temp!='(')
        {
            while(1)
            {
                if(operator->next==NULL)
                {
                    Push(operator,temp);
                    printf("ope=%c\t",operator->next->data);
                    break;
                } 
                else if(operator->next->data=='(')
                {
                    Push(operator,temp);
                    printf("op=%c\t",operator->next->data);
                    break;
                }
                else if(Priority(temp)>=Priority(operator->next->data))
                {
                    Push(operator,temp);
                    break;   
                }
                else
                {
                    Push(pre,Pop(operator));                   
                    //operator=operator->next;
                }
            }
        }
        else if(temp==')')
            {
                while(1)
                {
                    Push(pre,Pop(operator));
                    //operator=operator->next;
                    if(operator->next->data=='(')
                    {
                        Pop(operator);
                        break;
                    }
                }
            }
    }
    while(operator->next!=NULL)
    {
        Push(pre,Pop(operator));
    }
    return Stack_Reverse(pre);
}


int Middle_Order_Result(char *s)//计算中序表达式的值
{
    int result;
    char *p;
    p=s;
    NumStack *Arith_num;
    Stack *operator;
    Arith_num=InitStack2();
    operator=InitStack();
    Push(operator,'#');
    while(1)
    {
        if(*p>='1'&&*p<='9')
        {
            Push2(Arith_num,*p-'0');
            printf("Arith_num top is %d\n",Arith_num->next->num);
            p++;
        }
        else if(*p=='#')
        {
            if(operator->next->data=='#')
            {
                break;
            }
            else
            {
                while(operator->next->data!='#')
                {
                    if(Two_Operator_Priority(operator->next->data,*p)==2)
                    {
                        result=Operation(Pop2(Arith_num),Pop2(Arith_num),Pop(operator));
                        Push2(Arith_num,result);
                    }
                    else if(Two_Operator_Priority(operator->next->data,*p)==1)
                    {
                        //printf("priority 1\n");
                        printf("Poped operator=%c\n",Pop(operator));
                    }
                    else
                    {
                        //printf("Priority 0\n");
                        Push(operator,*p);
                        //printf("operator=%c\t",operator->next->data);
                    }
                }
            }
        }
        else
        {
            if(Two_Operator_Priority(operator->next->data,*p)==2)
            {
                printf("priority 2\n");
                result=Operation(Pop2(Arith_num),Pop2(Arith_num),Pop(operator));
                Push2(Arith_num,result);
            }
            else if(Two_Operator_Priority(operator->next->data,*p)==1)
            {
                printf("priority 1\n");
                printf("Poped operator=%c\n",Pop(operator));
            }
            else
            {
                printf("Priority 0\n");
                Push(operator,*p);
                //printf("operator=%c\t",operator->next->data);
            }
            p++;
        }
        //printf("Arith_num=%d\toperator=%c\t*p=%c\n",Arith_num->next->num,operator->next->data,*p);
    }
    return Arith_num->next->num;
}

int Operation(int a,int b,char c)//执行运算，b是左侧数据，a是右侧数据
{
    switch (c)
    {
    case '+':
        return a+b;
        break;
    case '-':
        return a-b;
        break;
    case '*':
        return a*b;
        break;
    case '/':
        return a/b;
        break;
    default:
        break;
    }
}


int Two_Operator_Priority(char a,char b)//运算符优先级，a在左，b在右，优先级高输出2，相同输出1，优先级小输出0
{
    int c=0;
    switch(a)
    {
        case ')':
            switch (b)
            {
            case '(':
                a=1;
                break;
            default:
                break;
            }
            break;
        case '(':
            switch (b)
            {
            case ')':
                a=1;
                break;
            case '#':
                a=-1;
                break;
            default:
                break;
            }
            break;
        case '*':
            switch (b)
            {
            case '(':
                break;           
            default:
                a=2;
                break;
            }
            break;
        case '/':
            switch (b)
            {
            case '(':
                break;
            default:
                a=2;
                break;
            }
            break;
        case '+':
            switch (b)
            {
            case '*':
                break;
            case '/':
                break;
            case '(':
                break;
            default:
                a=2;
                break;
            }
            break;
        case '-':
            switch (b)
            {
            case '*':
                break;
            case '/':
                break;
            case '(':
                break;
            default:
                a=2;
                break;
            }
            break;
    }
    return a;
}