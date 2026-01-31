#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* build(int left, int right){
    if(left > right) return NULL;
    Node* node = (Node*)malloc(sizeof(Node));
    node -> value = (left+right)/2;
    node -> left = build(left, (left+right)/2 - 1);
    node -> right = build((left+right)/2 + 1, right);

    return node;
}

Node* build_structure(int n) {
    Node* answer = build(1, n);
    return answer;
}