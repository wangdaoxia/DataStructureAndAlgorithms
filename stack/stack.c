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

typedef union DataType
{
    int int_data;
    char char_data;
} DataType;

/**
 * @brief 栈节点
*/
typedef struct StackNode{
    DataType data;
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
void Push(Stack *_stack,DataType _data);//向栈中插入数据
DataType Pop(Stack *_stack);//弹出栈顶元素
char* InorderToPostorder(char* _expr_inorder);//中缀表达式转成后缀表达式
int IsNumber(char _data);//判断是否为数字
int IsOperator(char _data);//判断是否为运算符
int OperatorToIndex(char _operator);//将运算符与索引进行对应
int CompareOperatorPriority(char a,char b);//运算符优先级
int CaculatePostOrderExpression(char* _expression);//计算后缀表达式的值
DataType ArithmOperation(char op,DataType a,DataType b);//进行算术运算
int main(int argc,const char* argv[])
{
    char str[100];
    printf("please input the string\n");
    scanf("%s",str);
    printf("%s\n",str);
    char* result=InorderToPostorder(str);
    printf("The following is the Post Order expression:\n");
    printf("%s",result);
    printf("the result of the post order expression:\n");
    int res=CaculatePostOrderExpression(result);
    printf("%d",res);
    free(result);
    return 0;
}

Stack *InitStack()//初始化栈顶指针
{
    Stack* linked_stack=(Stack*)malloc(sizeof(Stack));
    // StackNode *p=(StackNode *)malloc(sizeof(StackNode));
    // p->next=NULL;
    // linked_stack->top=p;
    linked_stack->top=NULL;
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
            printf("%c ",temp->data.char_data);
        }    
    }
}

void Push(Stack *_stack,DataType _data)//向栈中插入数据
{
    StackNode *p=(StackNode *)malloc(sizeof(StackNode));
    p->data=_data;
    p->next=_stack->top;
    _stack->top=p;
}


DataType Pop(Stack *_stack)//弹出栈顶元素
{
    DataType data=_stack->top->data;
    char chardata=_stack->top->data.char_data;
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
    char* result=(char*)malloc(strlen(expr));
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
            DataType exprdata;
            exprdata.char_data=*expr;
            Push(stack,exprdata);
        }
        else if(*expr==')')
        {
            while(stack->top->data.char_data!='(')
            {
                DataType temp=Pop(stack);
                char chartemp=temp.char_data;
                *post_order_result=chartemp;
                post_order_result++;
            }
            Pop(stack);
        }
        else if(IsOperator(*expr))
        {
            if(stack->top==NULL||stack->top->data.char_data=='(')
            {
                DataType exprdata={*expr};
                Push(stack,exprdata);
            }
            else
           { 
            while(IsOperator(stack->top->data.char_data)&&CompareOperatorPriority(*expr,stack->top->data.char_data)!=1)
            {
                if(CompareOperatorPriority(*expr,stack->top->data.char_data)==0)
                {
                    DataType exprdata={*expr};
                    Push(stack,exprdata);
                    break;
                }
                else
                {
                    DataType temp=Pop(stack);
                    char chartemp=temp.char_data;
                    *post_order_result=chartemp;
                    post_order_result++;
                }
                
            }
            DataType exprdata={*expr};
            Push(stack,exprdata);
            }
        }
        else
        {
            printf("sorry, the expression is wrong!\n");
        }
        expr++;
        
    }
    while(stack->top!=NULL)
    {
        DataType data=Pop(stack);
        *post_order_result=data.char_data;
        post_order_result++;
    }
    DestroyStack(stack);
    *post_order_result='\0';
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

int CaculatePostOrderExpression(char* _expression)
{
    Stack* stack=InitStack();
    char* expr=_expression;
    while(*expr!='\0')
    {
        if(IsNumber(*expr))
        {
            DataType data={(int)(*expr-'0')};
            Push(stack,data);
        }
        else if(IsOperator(*expr))
        {
            DataType right=Pop(stack);
            DataType left=Pop(stack);
            DataType result;
            result=ArithmOperation(*expr,left,right);
            Push(stack,result);
        }
        expr++;
    }
    DataType result=Pop(stack);
    DestroyStack(stack);
    return result.int_data;
}

DataType ArithmOperation(char op,DataType a,DataType b)
{
    DataType result;
    switch (op)
    {
        case '+':
        {
            result.int_data=a.int_data+b.int_data;
            break;
        }
        case '-':
        {
            result.int_data=a.int_data-b.int_data;
            break;
        }
        case '*':
        {
            result.int_data=a.int_data*b.int_data; 
            break;
        }
        case '/':
        {
            result.int_data=a.int_data/b.int_data;
            break;
        } 
    }
    return result;
}