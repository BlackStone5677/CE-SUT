#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* build(int left, int right){
    if(left > right) return NULL;
    Node* node = malloc(sizeof(Node));
    node -> value = (left+right)/2;
    node -> left = build(left, (left+right)/2 - 1);
    node -> right = build((left+right)/2 + 1, right);

    return node;
}

Node* build_structure(int n) {
    Node* answer = build(1, n);
    return answer;
}

void print_tree(Node* node, char* prefix, int isLeft) {
    if (node == NULL) return;

    printf("%s", prefix);

    printf("%s%d\n", isLeft ? "├─" : "└─", node->value);

    char newPrefix[256];
    snprintf(newPrefix, sizeof(newPrefix), "%s%s", prefix, isLeft ? "│ " : "  ");

    print_tree(node->left, newPrefix, 1);
    print_tree(node->right, newPrefix, 0);
}

int main(){
    int n;
    scanf("%d", &n);
    Node* root = build_structure(n);

    print_tree(root, "", 0);
}