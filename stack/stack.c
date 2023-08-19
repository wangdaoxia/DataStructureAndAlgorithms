#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/* 
（1）中缀表达式转为后缀表达式
（2）中缀表达式转为前缀表达式
（3）后缀表达式求值
（4）前缀表达式求值
（5）中缀表达式求值
 */

/**
 * @brief 栈节点
*/
typedef struct StackNode{
    char data;
    struct StackNode *next;
}StackNode;

typedef struct Stack
{
    StackNode* top;
} Stack;
// 运算符
const char OPERATOR[7]="+-*/()";
// 运算符优先级
const int PRIOIRITY[6][6] = {
/*        +   -   *   /   (   )  */
/* + */ { 0,  0, -1, -1, -1,  1 },
/* - */ { 0,  0, -1, -1, -1,  1 },
/* * */ { 1,  1,  0,  0, -1,  1 },
/* / */ { 1,  1,  0,  0, -1,  1 },
/* ( */ {-1, -1, -1, -1, -1,  0 },
/* ) */ { 1,  1,  1,  1,  0,  1 }
};

Stack *InitStack();//初始化栈顶指针
void DestroyStack(Stack *_stack);//释放内存
void DisplayStack(Stack *_stack);//遍历栈内数据
void Push(Stack *_stack,char _data);//向栈中插入数据
char Pop(Stack *_stack);//弹出栈顶元素
char* InorderToPostorder(char* _expr_inorder);//中序表达式转成后序表达式
int IsNumber(char _data);//判断是否为数字
int IsOperator(char _data);//判断是否为运算符
int OperatorToIndex(char _operator);//将运算符与索引进行对应
// int Priority(char x);//判断运算符优先级
// StackNode *Middle_to_Pre(StackNode *S);//将中序表达式转为前序表达式
// StackNode *Middle_to_Post(StackNode *S);//将中序表达式转为后序表达式
// StackNode *Stack_Reverse(StackNode *S);//栈的翻转
// int Middle_Order_Result(char *s);//计算中序表达式的值
int CompareOperatorPriority(char a,char b);//运算符优先级，a在左，b在右，优先级高输出2，相同输出1，优先级小输出0
// int Operation(int a,int b,char c);//执行运算，b是左侧数据，a是右侧数据

int main(int argc,const char* argv[])
{
    char str[100];
    printf("please input the string\n");
    scanf("%s",str);
    printf("%s\n",str);
    char* result=InorderToPostorder(str);
    printf("The following is the Post Order expression:\n");
    printf("%s",result);
    free(result);
    return 0;
}

Stack *InitStack()//初始化栈顶指针
{
    Stack* linked_stack=(Stack*)malloc(sizeof(Stack));
    StackNode *p=(StackNode *)malloc(sizeof(StackNode));
    p->next=NULL;
    linked_stack->top=p;
    return linked_stack;
}

void DestroyStack(Stack *_stack)//释放内存
{
    while(_stack->top!=NULL)
    {
        Pop(_stack);
    }
    free(_stack);   
}

void DisplayStack(Stack *_stack)//遍历栈内数据
{
    if(_stack->top==NULL)
    {
        printf("sorry, the stack is empty!\n");
    }
    else
    {
        StackNode *temp=_stack->top;
        printf("The data in the stack is as follows:\n");
        while (temp!=NULL)
        {
            printf("%c ",temp->data);
        }    
    }
}

void Push(Stack *_stack,char _data)//向栈中插入数据
{
    StackNode *p=(StackNode *)malloc(sizeof(StackNode));
    p->data=_data;
    p->next=_stack->top;
    _stack->top=p;
}


char Pop(Stack *_stack)//弹出栈顶元素
{
    char data=_stack->top->data;
    StackNode* temp=_stack->top;
    _stack->top=_stack->top->next;
    free(temp);
    return data;
}

char* InorderToPostorder(char* _expr_inorder)
{
    //初始化运算符栈
    Stack *stack=InitStack();
    char* expr=_expr_inorder;
    char* result=(char*)malloc(strlen(expr)+1);
    char* post_order_result=result;
    while(*expr!='#')
    {
        if(IsNumber(*expr))
        {
            *post_order_result=*expr;
            post_order_result++;
        }
        else if(*expr=='(')
        {
            Push(stack,*expr);
        }
        else if(*expr==')')
        {
            while(stack->top->data!='(')
            {
                char temp=Pop(stack);
                *post_order_result=temp;
                post_order_result++;
            }
            Pop(stack);
        }
        else if(IsOperator(*expr))
        {
            if(stack->top->data=='(')
            {
                Push(stack,*expr);
            }
            else
           { 
            while(IsOperator(stack->top->data)&&CompareOperatorPriority(*expr,stack->top->data)!=1)
            {
                char temp=Pop(stack);
                *post_order_result=temp;
                post_order_result++;
            }
            // if(CompareOperatorPriority(*expr,stack->top->data)!=0)
            Push(stack,*expr);
            }
        }
        else
        {
            printf("sorry, the expression is wrong!\n");
        }
        expr++;
        
    }
    while(stack->top->next!=NULL)
    {
        *post_order_result=Pop(stack);
        post_order_result++;
    }
    DestroyStack(stack);
    return result;
}

int IsNumber(char _data)
{
    if(_data>='0'&&_data<='9')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int IsOperator(char _data)
{
    char operator[7]="+-*/()";
    for(int i=0;i<7;i++)
    {
        if(_data==operator[i])
        {
            return 1;
        }
    }
    return 0;
}
// int Priority(char x)//判断优先级
// {
//     int y;
//     switch (x)
//     {
//     case '(':
//         y=3;
//         break;
//     case ')':
//         y=3;
//         break;
//     case '*':
//         y=2;
//         break;
//     case '/':
//         y=2;
//         break;
//     case '+':
//         y=1;
//         break;
//     case '-':
//         y=1;
//         break;
//     default:
//         break;
//     }
//     return y;
// }

// StackNode *Stack_Reverse(StackNode *S)//栈的翻转
// {
//     StackNode *temp;
//     temp=InitStack();
//     while(S->next!=NULL)
//     Push(temp,Pop(S));
//     return temp;
// }
// StackNode *Middle_to_Post(StackNode *S)//将中序表达式转为后序表达式
// {
//     char temp;
//     StackNode *pre,*operator,*p;
//     pre=InitStack();
//     operator=InitStack();
//     p=Stack_Reverse(S);
//     while(p->next!=NULL)
//     {
//         temp=Pop(p);
//         if(temp>='0'&&temp<='9')
//         {
//             Push(pre,temp);
//         }
//         else if(temp=='(')
//         {
//             Push(operator,temp);
//             printf("ope=%c\t",operator->next->data);
//         }
//         else if(temp!=')'&&temp!='(')
//         {
//             while(1)
//             {
//                 if(operator->next==NULL)
//                 {
//                     Push(operator,temp);
//                     printf("ope=%c\t",operator->next->data);
//                     break;
//                 } 
//                 else if(operator->next->data=='(')
//                 {
//                     Push(operator,temp);
//                     printf("op=%c\t",operator->next->data);
//                     break;
//                 }
//                 else if(Priority(temp)>=Priority(operator->next->data))
//                 {
//                     Push(operator,temp);
//                     break;   
//                 }
//                 else
//                 {
//                     Push(pre,Pop(operator));                   
//                     //operator=operator->next;
//                 }
//             }
//         }
//         else if(temp==')')
//             {
//                 while(1)
//                 {
//                     Push(pre,Pop(operator));
//                     //operator=operator->next;
//                     if(operator->next->data=='(')
//                     {
//                         Pop(operator);
//                         break;
//                     }
//                 }
//             }
//     }
//     while(operator->next!=NULL)
//     {
//         Push(pre,Pop(operator));
//     }
//     return Stack_Reverse(pre);
// }


// int Middle_Order_Result(char *s)//计算中序表达式的值
// {
//     int result;
//     char *p;
//     p=s;
//     NumStack *Arith_num;
//     StackNode *operator;
//     Arith_num=InitStack2();
//     operator=InitStack();
//     Push(operator,'#');
//     while(1)
//     {
//         if(*p>='1'&&*p<='9')
//         {
//             Push2(Arith_num,*p-'0');
//             printf("Arith_num top is %d\n",Arith_num->next->num);
//             p++;
//         }
//         else if(*p=='#')
//         {
//             if(operator->next->data=='#')
//             {
//                 break;
//             }
//             else
//             {
//                 while(operator->next->data!='#')
//                 {
//                     if(Two_Operator_Priority(operator->next->data,*p)==2)
//                     {
//                         result=Operation(Pop2(Arith_num),Pop2(Arith_num),Pop(operator));
//                         Push2(Arith_num,result);
//                     }
//                     else if(Two_Operator_Priority(operator->next->data,*p)==1)
//                     {
//                         //printf("priority 1\n");
//                         printf("Poped operator=%c\n",Pop(operator));
//                     }
//                     else
//                     {
//                         //printf("Priority 0\n");
//                         Push(operator,*p);
//                         //printf("operator=%c\t",operator->next->data);
//                     }
//                 }
//             }
//         }
//         else
//         {
//             if(Two_Operator_Priority(operator->next->data,*p)==2)
//             {
//                 printf("priority 2\n");
//                 result=Operation(Pop2(Arith_num),Pop2(Arith_num),Pop(operator));
//                 Push2(Arith_num,result);
//             }
//             else if(Two_Operator_Priority(operator->next->data,*p)==1)
//             {
//                 printf("priority 1\n");
//                 printf("Poped operator=%c\n",Pop(operator));
//             }
//             else
//             {
//                 printf("Priority 0\n");
//                 Push(operator,*p);
//                 //printf("operator=%c\t",operator->next->data);
//             }
//             p++;
//         }
//         //printf("Arith_num=%d\toperator=%c\t*p=%c\n",Arith_num->next->num,operator->next->data,*p);
//     }
//     return Arith_num->next->num;
// }

// int Operation(int a,int b,char c)//执行运算，b是左侧数据，a是右侧数据
// {
//     switch (c)
//     {
//     case '+':
//         return a+b;
//         break;
//     case '-':
//         return a-b;
//         break;
//     case '*':
//         return a*b;
//         break;
//     case '/':
//         return a/b;
//         break;
//     default:
//         break;
//     }
// }


int CompareOperatorPriority(char a,char b)//运算符优先级，a在左，b在右
{
    int left_index=OperatorToIndex(a);
    int right_index=OperatorToIndex(b);
    return PRIOIRITY[left_index][right_index];
}

int OperatorToIndex(char _operator)
{
    switch (_operator)
    {
    case '+':
        return 0;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 3;
    case '(':
        return 4;
    case ')':
        return 5;
    default:
        return -1;
    }
}