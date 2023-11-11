#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
/* 
一、单向链表的增删改查
二、链表的排序（从大到小和从小到大）

 */

typedef struct linklist{
    int val_;
    struct linklist *next_;
} LinkList;
typedef enum OrderType {
    L2B,B2L
} OrderType;
typedef enum SortMethod {
    BUBBLE,QUICK,HILL
} SortMethod;
// int element_num;//全局变量，表内元素个数
/**
 * @brief 初始化链表
 * 
 * @return LinkList* 
 */
LinkList *InitList();
/**
 * @brief 创建随机链表
 * 
 * @param L 链表头
 * @param n 链表长度
 */
void CreateList(LinkList *L,int n);
/**
 * @brief 遍历链表
 * 
 * @param L 
 */
void TraverseList(LinkList *L);
/**
 * @brief 释放链表
 * 
 * @param L 
 */
void DestroyList(LinkList *L);
/**
 * @brief 向pos位置插入num数据
 * 
 * @param L 
 * @param pos 插入位置,以0开始
 * @param val 插入的数据
 */
void InsertList(LinkList *L, int pos,int val);
/**
 * @brief 删除pos位置的数据
 * 
 * @param L 
 * @param pos 删除的位置
 */
void DeleteList(LinkList *L,int pos);//删除
/**
 * @brief 查找链表中的值
 * 
 * @param L 
 * @param elem 查找的值
 * @return 在链表中第一次出现的位置
 */
int FindElementInList(LinkList *L,int elem);
/**
 * @brief 修改链表中指定位置的值
 * 
 * @param L 
 * @param pos 修改元素的位置
 * @param val 修改后的值
 */
void ChangeElementInList(LinkList *L, int pos, int val);
// void choose(LinkList *L);//选择操作（插入，删除，查询，修改）
/**
 * @brief 对链表进行排序
 * 
 * @param L 
 * @param method 排序的方式
 */
void ListSort(LinkList *L, SortMethod _method, OrderType _ordertype);
/**
 * @brief 合并两个有序链表
 * 
 * @param L1 
 * @param L2 
 */
LinkList* MergeTwoOrderedLinkList(LinkList* L1,LinkList *L2);
/**
 * @brief 合并两个乱序链表
 * 
 * @param L1 
 * @param L2 
 */
void MergeTwoRandomLinkList(LinkList* L1,LinkList *L2);
/**
 * @brief 获取单向链表的长度
 * 
 * @param L 
 */
int GetLinkListLength(LinkList* L);
/**
 * @brief 检验链表是否存在
 * 
 * @param L 
 * @return true 
 * @return false 
 */
bool ListExists(LinkList *L);
/**
 * @brief 检验链表是否为空
 * 
 * @param L 
 * @return true 
 * @return false 
 */
bool ListIsEmpty(LinkList *L);