#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    int height;
    struct node *left;
    struct node *right;
};

int height(struct node *root) {
    if (root == NULL)
        return -1;

    return root->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct node *createNode(int data) {
    struct node *newnode;

    newnode = (struct node *)malloc(sizeof(struct node));

    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->height = 0;

    return newnode;
}

int balanceFactor(struct node *root) {
    if (root == NULL)
        return 0;

    return height(root->left) - height(root->right);
}

/* Right rotation - LL case */

struct node *rightRotate(struct node *root) {
    struct node *temp;
    struct node *t;

    temp = root->left;
    t = temp->right;

    temp->right = root;
    root->left = t;

    root->height = 1 + max(height(root->left),
                            height(root->right));

    temp->height = 1 + max(height(temp->left),
                            height(temp->right));

    return temp;
}

/* Left rotation - RR case */

struct node *leftRotate(struct node *root) {
    struct node *temp;
    struct node *t;

    temp = root->right;
    t = temp->left;

    temp->left = root;
    root->right = t;

    root->height = 1 + max(height(root->left),
                            height(root->right));

    temp->height = 1 + max(height(temp->left),
                            height(temp->right));

    return temp;
}

struct node *insert(struct node *root, int data) {

    /* Normal BST insertion */

    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);

    else if (data > root->data)
        root->right = insert(root->right, data);

    else
        return root;

    /* Correct height */

    root->height = 1 + max(height(root->left),
                            height(root->right));

    int balance = balanceFactor(root);

    /* LL case */

    if (balance > 1 && data < root->left->data)
        return rightRotate(root);

    /* RR case */

    if (balance < -1 && data > root->right->data)
        return leftRotate(root);

    /* LR case */

    if (balance > 1 && data > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    /* RL case */

    if (balance < -1 && data < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorder(struct node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(struct node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int main() {

    struct node *root = NULL;
    int n, data, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");

    for (i = 0; i < n; i++) {
        scanf("%d", &data);
        root = insert(root, data);
    }

    printf("\nInorder: ");
    inorder(root);

    printf("\nPreorder: ");
    preorder(root);

    printf("\nPostorder: ");
    postorder(root);

    return 0;
}