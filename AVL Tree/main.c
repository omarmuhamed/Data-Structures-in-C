#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
    int data;
    struct tree *right;
    struct tree *left;
} Tree;

Tree *create(int data) {
    Tree *node = (Tree *) malloc(sizeof(Tree));
    node->data = data;
    node->right = NULL;
    node->left = NULL;
    return node;
}

int height(Tree *tree) {
    if (tree == NULL) {
        return 0;
    } else {
        int right_height = height(tree->right);
        int left_height = height(tree->left);
        return (left_height > right_height) ? left_height + 1 : right_height + 1;
    }
}

void inorder_print(Tree *tree) {
    if (tree != NULL) {
        inorder_print(tree->left);
        printf("(D=%d | H=%d)  ", tree->data, height(tree));
        inorder_print(tree->right);
    }
}

void preorder_print(Tree *tree) {
    if (tree != NULL) {
        printf("(D=%d | H=%d)  ", tree->data, height(tree));
        preorder_print(tree->left);
        preorder_print(tree->right);
    }
}

void postorder_print(Tree *tree) {
    if (tree != NULL) {
        postorder_print(tree->left);
        postorder_print(tree->right);
        printf("(D=%d | H=%d)  ", tree->data, height(tree));
    }
}


void rightRotate(Tree **node) {
    Tree *temp1 = (*node)->left;
    Tree *temp2 = temp1->right;
    temp1->right = *node;
    (*node)->left = temp2;
    *node = temp1;
}

void leftRotate(Tree **node) {
    Tree *temp1 = (*node)->right;
    Tree *temp2 = temp1->left;
    temp1->left = *node;
    (*node)->right = temp2;
    *node = temp1;
}

Tree *delete(Tree **tree, int data) {

    if (tree != NULL) {
        if (data < (*tree)->data) {
            (*tree)->left = delete(&(*tree)->left, data);
        } else if (data > (*tree)->data) {
            (*tree)->right = delete(&(*tree)->right, data);
        } else {
            if ((*tree)->left == NULL) {
                Tree *temp = (*tree)->right;
                if (temp == NULL) {
                    temp = *tree;
                    *tree = NULL;
                } else {
                    **tree = *temp;
                }
                free(temp);
            } else if ((*tree)->right == NULL) {
                Tree *temp = (*tree)->left;
                if (temp == NULL) {
                    temp = *tree;
                    *tree = NULL;
                } else {
                    **tree = *temp;
                }
                free(temp);
            } else {
                Tree *temp = (*tree)->right;
                while (temp && temp->left) {
                    temp = temp->left;
                }
                (*tree)->data = temp->data;
                (*tree)->right = delete(&(*tree)->right, (*tree)->data);
            }
        }
    } else {
        return *tree;
    }
    if (*tree != NULL) {

        int balance_factor = height((*tree)->left) - height((*tree)->right);
        if (balance_factor > 1 && height((*tree)->left->left) - height((*tree)->left->right) >= 0) {
            rightRotate(tree);
        } else if (balance_factor > 1 && height((*tree)->left->left) - height((*tree)->left->right) < 0) {
            leftRotate(&(*tree)->left);
            rightRotate(tree);
        } else if (balance_factor < -1 && height((*tree)->right->left) - height((*tree)->right->right) <= 0) {
            leftRotate(tree);

        } else if (balance_factor < -1 && height((*tree)->right->left) - height((*tree)->right->right) > 0) {
            rightRotate(&(*tree)->right);
            leftRotate(tree);
        }
    } else {
        return *tree;
    }
    return *tree;
}

void insert(Tree **tree, int data) {
    if (*tree == NULL) {
        *tree = create(data);
        return;
    } else if ((*tree)->data > data) {
        insert(&(*tree)->left, data);
    } else {
        insert(&(*tree)->right, data);
    }
    int balance_factor;
    if (*tree != NULL) {
        balance_factor = height((*tree)->left) - height((*tree)->right);
    } else {
        balance_factor = 0;
    }
    if (balance_factor > 1 && data < (*tree)->left->data)
        rightRotate(tree);
    else if (balance_factor < -1 && data > (*tree)->right->data)
        leftRotate(tree);
    else if (balance_factor > 1 && data > (*tree)->left->data) {
        leftRotate(&(*tree)->left);
        rightRotate(tree);
    } else if (balance_factor < -1 && data < (*tree)->right->data) {
        rightRotate(&(*tree)->right);
        leftRotate(tree);
    }
}

int main() {
    Tree *tree = NULL;
    insert(&tree, 1);
    preorder_print(tree);
    printf("\n");
    insert(&tree, 34);
    preorder_print(tree);
    printf("\n");
    insert(&tree, 22);
    preorder_print(tree);
    printf("\n");
    insert(&tree, 20);
    preorder_print(tree);
    printf("\n");
    insert(&tree, 19);
    preorder_print(tree);
    printf("\n");
    insert(&tree, 4);
    preorder_print(tree);
    printf("\n");
    insert(&tree, 1);
    preorder_print(tree);
    printf("\n");
    preorder_print(tree);
    printf("\n");
    printf("Delete\n");
    delete(&tree, 22);
    preorder_print(tree);
    printf("\n");
    delete(&tree, 34);
    preorder_print(tree);
    printf("\n");
    delete(&tree, 20);
    preorder_print(tree);
    printf("\n");
}