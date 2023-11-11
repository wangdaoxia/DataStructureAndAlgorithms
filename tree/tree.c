#include"tree.h"
#include<stdlib.h>
#include<assert.h>
int main(int argc,const char* argv[])
{
    int num_of_nodes=0;
    printf("please input the number of nodes:");
    scanf("%d",&num_of_nodes);
    TreeNode* root=InitTree();
    int *treearray=(int*)malloc(sizeof(int)*num_of_nodes);
    for(int i=0;i<num_of_nodes;i++)
    {
        treearray[i]=rand()%20;
        printf("%d,",treearray[i]);
    }
    printf("\n");
    CreateTree(root,treearray,num_of_nodes);
    printf("前序遍历:\n");
    PreOrderTraverse(root);
    printf("中序遍历:\n");
    InOrderTraverse(root);
    printf("后序遍历:\n");
    PostOrderTraverse(root);
    printf("层序遍历:\n");
    LevelOrderTraverse(root);
    int depth=DepthOfTree(root);
    printf("depth:%d\n",depth);
    DestroyTree(root);
    return 0;
}

TreeNode* InitTree()
{
    TreeNode* root=(TreeNode*)malloc(sizeof(TreeNode));
    root->left_=NULL;
    root->right_=NULL;
    return root;
}

void CreateTree(TreeNode* root,int* nums,int numsize)
{
    assert(numsize>0);
    root->val_=nums[0];
    for(int i=1;i<numsize;i++)
    {
        InsertNode(root,nums[i]);
    }
}

void DestroyTree(TreeNode* root)
{
    if(root==NULL)
    {
        return;
    }
    else
    {
        TreeNode* left=root->left_;
        TreeNode* right=root->right_;
        // printf("root:%d\n",root->val_);
        free(root);
        root=NULL;
        DestroyTree(left);
        DestroyTree(right);
    }
}

bool TreeIsEmpty(TreeNode* root)
{
    if(root==NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int DepthOfTree(TreeNode* root)
{
    if(root==NULL)
    {
        return 0;
    }
    else
    {
        int leftdepth=DepthOfTree(root->left_);
        int rightdepth=DepthOfTree(root->right_);
        return leftdepth>rightdepth?leftdepth:rightdepth+1;
    }
}

void PreOrderTraverse(TreeNode* root)
{
    if(root==NULL)
    {
        return;
    }
    else
    {
        printf("pre-order traverse:%d\n",root->val_);
        PreOrderTraverse(root->left_);
        PreOrderTraverse(root->right_);
        return;
    }
}

void InOrderTraverse(TreeNode* root)
{
    if(root==NULL)
    {
        return;
    }
    else
    {
        InOrderTraverse(root->left_);
        printf("In-order traverse:%d\n",root->val_);
        InOrderTraverse(root->right_);
        return;
    }
}

void PostOrderTraverse(TreeNode* root)
{
    if(root==NULL)
    {
        return;
    }
    else
    {
        PostOrderTraverse(root->left_);
        PostOrderTraverse(root->right_);
        printf("post-order traverse:%d\n",root->val_);
        return;
    }
}

void InsertNode(TreeNode* root,int val)
{
    
    if(val<root->val_)
    {
        if(root->left_==NULL)
        {
            TreeNode* tmp=InitTree();
            tmp->val_=val;
            root->left_=tmp;
        }
        else
        {
            InsertNode(root->left_,val);
        }
    }
    else
    {
        if(root->right_==NULL)
        {
            TreeNode* tmp=InitTree();
            tmp->val_=val;
            root->right_=tmp;
        }
        else
        {
            InsertNode(root->right_,val);
        }
    }
    
}

void LevelOrderTraverse(TreeNode* root)
{
    int in=0;
    int out=0;
    TreeNode* tmp[100];
    tmp[in++]=root;
    while(in>out)
    {
        if(tmp[out])
        {
            printf("%d,",tmp[out]->val_);
            tmp[in++]=tmp[out]->left_;
            tmp[in++]=tmp[out]->right_;
        }
        out++;
    }
}