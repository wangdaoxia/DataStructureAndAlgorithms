/**
 * @brief 二叉树相关的函数声明 
 * @author wanghao 
 * @date 2023/11/06
 * **/
#include<stdio.h>
#include<stdbool.h>
/**
 * @brief  二叉树结点的定义
**/
typedef struct treenode
{
    int val_;
    struct treenode* left_;
    struct treenode* right_;
} TreeNode;

/**
 * @brief 初始化二叉树
 * 
 * @return ** TreeNode* 
 */
TreeNode* InitTree();
/**
 * @brief 销毁二叉树
 * 
 * @param root 指向二叉树
 * @return ** void 
 */
void DestroyTree(TreeNode* root);
/**
 * @brief 创建一颗二叉树
 * 
 * @param root 
 * @return ** void 
 */
void CreateTree(TreeNode* root,int* nums,int numsize);
/**
 * @brief 清空二叉树
 * 
 * @param root 
 * @return ** void 
 */
void ClearTree(TreeNode* root);
/**
 * @brief 检验树是否为空
 * 
 * @param root 
 * @return true 
 * @return false 
 */
bool TreeIsEmpty(TreeNode* root);
/**
 * @brief 获取树的深度
 * 
 * @param root 
 * @return int 
 */
int DepthOfTree(TreeNode* root);
/**
 * @brief 树的前序遍历
 * 
 * @param root 
 */
void PreOrderTraverse(TreeNode* root);
/**
 * @brief 树的中序遍历
 * 
 * @param root 
 */
void InOrderTraverse(TreeNode* root);
/**
 * @brief 树的后序遍历
 * 
 * @param root 
 */
void PostOrderTraverse(TreeNode* root);
/**
 * @brief 向树中插入节点
 * 
 * @param root 
 */
void InsertNode(TreeNode* root,int val);
/**
 * @brief 树的层序遍历
 * 
 * @param root 
 */
void LevelOrderTraverse(TreeNode* root);



