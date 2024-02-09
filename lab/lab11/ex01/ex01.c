/* iaed-23 - ist1103449 - lab11/ex01 */
#include <stdio.h>
#include <stdlib.h>

typedef struct stru_node {
    struct stru_node *next;
    int val;
} node;

node* pop(node *head) {
    node *n = head;
    if (head != NULL) {
        head = head->next;
        free(n);
    }
    return head;
}

node* push(node *head, int val) {
    node *ne = malloc(sizeof(node));
    ne->val = val;
    ne->next = head;
    return ne;
}

void destroy(node *h) {
    node *n;
    while (h) {
        n = h;
        h = h->next;
        free(n);
    }
}

void print(node *h) {
    while (h) {
        printf("%d\n", h->val);
        h = h->next;
    }
}

int main() {
    node *head = NULL;
    int val;
    while (scanf("%d", &val && (val != 0))) {
        push(head, val);
    }
    print(head);
    destroy(head);
    return 0;
}
