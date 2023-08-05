#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
/* 
一、用三元组方式（行，列，值）的形式储存稀疏矩阵中的非零元素
二、结构体数组储存一个矩阵
三、实现目标：建立和输入稀疏矩阵，输出矩阵，两个稀疏矩阵相加，相乘，并存储到一个新的矩阵中，求转置矩阵
 */
typedef struct triple{
    int row;//行
    int col;//列
    int value;//值
}Triple;//三元组储存非零元素

typedef struct matrix{
    Triple data[MAXSIZE];//三元组表
    int row_num;//矩阵行数
    int col_num;//矩阵列数
    int data_num;//非零元素个数
}Matrix;//存储一个矩阵

Matrix *Matrix_Build();//建立一个稀疏矩阵
void DisplayMatrix(Matrix *m);//输出稀疏矩阵
Matrix *Two_Matrix_sum(Matrix *M1,Matrix *M2);//两个稀疏矩阵相加
Matrix *Two_Matrix_product(Matrix *M1,Matrix *M2);//两个稀疏矩阵乘积


void main()
{
    Matrix *M_one,*M_two,*sum;
    M_one=Matrix_Build();
    if(M_one->data_num==0)
    {
        printf("输入错误\n");
    }
    else
    {
        DisplayMatrix(M_one);
    }
    M_two=Matrix_Build();
    if(M_two->data_num==0)
    {
        printf("输入错误\n");
    }
    else
    {
        DisplayMatrix(M_two);
    }
    sum=Two_Matrix_sum(M_one,M_two);
    DisplayMatrix(sum);
}


Matrix *Matrix_Build()//建立一个稀疏矩阵
{
    int i;
    float judgement;//用来判断是否为稀疏矩阵
    Matrix *M;
    M=(Matrix *)malloc(sizeof(Matrix));
    printf("请输入稀疏矩阵的行数，列数，非零元素数:");
    scanf("%d%d%d",&M->row_num,&M->col_num,&M->data_num);
    judgement=(float)(M->data_num)/(M->row_num*M->col_num);
    if(judgement<=0.05)
    {
        printf("满足稀疏矩阵条件\n");
        printf("请输入稀疏矩阵的非零元素三元组:\n");
        for(i=0;i<M->data_num;i++)
        {
            scanf("%d%d%d",&M->data[i].row,&M->data[i].col,&M->data[i].value);
            if(M->data[i].col>M->col_num||M->data[i].row>M->col_num)
            {
                printf("输入错误，非零元素三元组行数/列数比稀疏矩阵大\n");
                break;
            }
        }

    }
    else
    {
        printf("不满足稀疏矩阵条件\n");
        M->data_num=0;
    }
    return M;
}

void DisplayMatrix(Matrix *m)//输出稀疏矩阵
{
    int i;
    printf("稀疏矩阵如下\n");
    for(i=0;i<m->data_num;i++)
    {
        printf("%4d%4d%4d\n",m->data[i].row,m->data[i].col,m->data[i].value);
    }
}

Matrix *Two_Matrix_sum(Matrix *M1,Matrix *M2)//两个稀疏矩阵相加
{
    int i,j;
    Matrix *twoMsum;
    Triple *p;
    twoMsum=(Matrix *)malloc(sizeof(Matrix));
    p=twoMsum->data;
    twoMsum->data_num=0;
    i=j=0;
    printf("赋值成功\n");
    if(M1->row_num==M2->row_num&&M1->col_num==M2->col_num)
    {
        twoMsum->col_num=M1->col_num;
        twoMsum->row_num=M1->row_num;
        while(i<M1->data_num&&j<M2->data_num)
        {
            printf("i=%d,j=%d\n",i,j);
            if(M1->data[i].row>M2->data[j].row)
            {
                twoMsum->data_num++;
                p->row=M2->data[j].row;
                p->col=M2->data[j].col;
                p->value=M2->data[j].value;
                p++;
                j++;
            }
            else if(M1->data[i].row==M2->data[j].row)
            {
                if(M1->data[i].col>M2->data[j].col)
                {
                    twoMsum->data_num++;
                    p->row=M2->data[j].row;
                    p->col=M2->data[j].col;
                    p->value=M2->data[j].value;
                    p++;
                    j++;
                }
                else if(M1->data[i].col==M2->data[j].col)
                {
                    twoMsum->data_num++;
                    p->row=M2->data[j].row;
                    p->col=M2->data[j].col;
                    p->value=M2->data[j].value+M1->data[i].value;
                    p++;
                    i++;
                    j++;
                }
                else
                {
                    twoMsum->data_num++;
                    p->row=M1->data[i].row;
                    p->col=M1->data[i].col;
                    p->value=M1->data[i].value;
                    p++;
                    i++;
                }
            }
            else
            {
                twoMsum->data_num++;
                p->row=M1->data[i].row;
                p->col=M1->data[i].col;
                p->value=M1->data[i].value;
                p++;
                i++;
            }         
        }
//        printf("i=%d,j=%d\n",i,j);
    if(i!=M1->data_num)
    {
        for(;i<M1->data_num;i++)
        {
            twoMsum->data_num++;
            p->row=M1->data[i].row;
            p->col=M1->data[i].col;
            p->value=M1->data[i].value;
            p++;
        }
    }
    if(j!=M2->data_num)
    {
        for(;j<M2->data_num;j++)
        {
            twoMsum->data_num++;
            p->row=M2->data[j].row;
            p->col=M2->data[j].col;
            p->value=M2->data[j].value;
            p++;
        }
    }
        return twoMsum;
        /* for(i=0;i<M1->data_num;i++)
        {
            for(j=0;j<M2->data_num;j++)
            {
                if(M1->data[i].row==M2->data[j].row&&M1->data[i].col==M2->data[i].col)
                {                   
                    twoMsum->data_num++;
                    p->col=M1->data[i].col;
                    p->row=M1->data[i].row;
                    p->value=M1->data[i].value+M2->data[j].value;
                    p++;
                    break;   
                }
                else
                {
                    p->row=M1->data[i].row;
                    p->col=M1->data[i].col;
                    p->value=M1->data[i].value;
                    p++;
                }
            }
        } */
    }
    else
    {
        printf("相加错误，两个矩阵不是同型矩阵\n");
    }
}

Matrix *Two_Matrix_product(Matrix *M1,Matrix *M2)//两个稀疏矩阵乘积 
/* 
1.两矩阵三元组都以行数从小到大排序
2.插入积矩阵的三元组的行和列必是每个M1矩阵三元组的行和M2矩阵的列
3.积矩阵三元组x行y列的元素值为M1实际原矩阵中所有x行元素与M2实际原矩阵中所有y列元素乘积和
4.
 */
{
    Matrix *product;
    Triple *p;
    int i,j,value_sum;
    product=(Matrix *)malloc(sizeof(Matrix));
    p=product->data;
    if(M1->col_num==M2->row_num)
    {
        product->row_num=M1->row_num;
        product->col_num=M2->col_num;
        for(i=0;i<M1->data_num;i++)
        {
            for(j=0;j<M2->data_num;j++)
            {
                if(M1->col_num>M2->row_num)
                {
                    continue;
                }
                else if(M1->col_num==M2->row_num)
                {
                    
                }
                else
                {

                }
            }
        }
    }
    else
    {
        printf("两个矩阵无法相乘\n");
    }
}

Matrix *SortMatrixByRowOrCol(Matrix *M,int i)//i为0时从小到大按行列排序，否则按列行排序
{
    Triple *p,*q,temp;
    int m,n;
    p=M->data;
    q=p+1;
    if(i==0)
    {
        /* while(1)
        {
            if(q->row<p->row)
            {
                temp=*p;
                *p=*q;
                *q=temp;
            }
            else if(q->row==p->row)
            {
                if(q->col<p->col)
                {
                    temp=*p;
                    *p=*q;
                    *q=temp;
                }
            }
            q++;
            p++;
        } */
    }
}
