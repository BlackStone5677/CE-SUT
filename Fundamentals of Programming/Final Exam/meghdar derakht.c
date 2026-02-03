#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int val;
    struct Node *left;
    struct Node *right;
} Node;
int idx = 0;

Node* buildTree(char *preorder[], int n) {
    if (idx >= n) return NULL;

    if (strcmp(preorder[idx], "x") == 0) {
        idx++;
        return NULL;
    }

    Node *node = (Node*)malloc(sizeof(Node));
    node->val = atoi(preorder[idx++]);
    node->left = buildTree(preorder, n);
    node->right = buildTree(preorder, n);
    return node;
}

int computeValue(Node *node) {
    if (!node) return 0;

    if (!node->left && !node->right) {
        return node->val;
    }

    int leftVal = computeValue(node->left);
    int rightVal = computeValue(node->right);

    if (node->left && node->right) {
        node->val = node->val * (leftVal + rightVal);
    } else if (node->left || node->right) {
        int childVal = node->left ? leftVal : rightVal;
        node->val = node->val + 2 * childVal;
    }
    free(node->left);
    free(node->right);
    node->left = node->right = NULL;

    return node->val;
}


int main() {
    char line[5000];
    if (!fgets(line, sizeof(line), stdin)) {
        return 1;
    }

    char *preorder[1000];
    int count = 0;
    char *token = strtok(line, " \n");
    while (token != NULL) {
        preorder[count++] = token;
        token = strtok(NULL, " \n");
    }

    Node *root = buildTree(preorder, count);
    int result = computeValue(root);
    printf("%d\n", result);

    free(root);

    return 0;
}