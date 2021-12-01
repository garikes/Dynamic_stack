#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct stackNode
{
    char* data;
    struct stackNode* link;
};
struct stackNode* top;
struct circular_node {
    char data[9];
    struct circular_node* next;
};
struct circular_node* circ_head = NULL;
void stackPush(char* rech)
{
    struct stackNode* temp;
    temp = new stackNode();
    if (!temp)
    {
        exit(1);
    }
    temp->data = (char*)malloc(sizeof(char) * strlen(rech));
    strcpy(temp->data, rech);
    temp->link = top;
    top = temp;
}
int stackIsEmpty()
{
    return top == NULL;
}
void stackPop()
{
    struct stackNode* temp;
    if (top == NULL)
    {
        exit(1);
    }
    else
    {
        temp = top;
        top = top->link;
        temp->link = NULL;
        free(temp);
    }
}
void stackDisplay()
{
    struct stackNode* temp;
    if (top == NULL)
    {
        exit(1);
    }
    else
    {
        temp = top;
        while (temp != NULL)
        {
            printf("%s -> ", temp->data);
            temp = temp->link;
        }
    }
}
void pushCirc(char* v) {
    if (circ_head == NULL) {
        circ_head = (struct circular_node*)malloc(sizeof(struct circular_node));;
        circ_head->next = NULL;
        strcpy(circ_head->data, v);
    }
    else {
        circular_node* temp = (struct circular_node*)malloc(sizeof(struct circular_node));
        strcpy(temp->data, v);
        temp->next = circ_head;
        circ_head = temp;
    }
}
void printCirc() {
    circular_node* temp = circ_head;
    printf("\n[ ");
    while (temp != NULL) {
        printf("(%s) ", temp->data);
        temp = temp->next;
    }
    printf(" ]");
}
int checkValue(char* v) {
    int N = strlen(v);
    if (N > 9) {
        return 0;
    }
    for (int i = 0; i < N; i++) {
        if (v[i] >= '0' && v[i] <= '9') {
            continue;
        }
        else if (v[i] >= 'A' && v[i] <= 'F') {
            continue;
        }
        else if (v[i] >= 'a' && v[i] <= 'f') {
            continue;
        }
        else {
            return 0;
        }
    }
    return 1;
}
void file_input(char path[]) {
    FILE* fp;
    char buffer[50];
    fp = fopen(path, "r");
    if (fp == NULL) {
        puts("Неможливо відкрити файл");
        return;
    }
    while (!feof(fp)) {
        fgets(buffer, 50, fp);
        buffer[strcspn(buffer, "\n")] = 0;
        stackPush(buffer);
    }
    fclose(fp);
    return;
}
void pushHexValue(char* v) {
    if (checkValue(v)) {
        pushCirc(v);
    }
}
void robota() {
    struct stackNode* ptr = top;
    while (ptr != NULL) {
        pushHexValue(ptr->data);
        ptr = ptr->link;
    }
}
int main() {
    system("chcp 1251");
    char path[] = "input.txt";
    puts("Виберіть тип вводу: 1 - клавіатура, 2 - файл");
    int input;
    char buffer[50];
    scanf("%d", &input);
    getchar();
    switch (input) {
        case(1):
            printf("Виберіть кількість речень: ");
            scanf("%d", &input);
            getchar();
            for (int i = 0; i < input; i++) {
                fgets(buffer, 50, stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                stackPush(buffer);
            }
            break;
        case(2):
            file_input(path);
    }
    puts("Послідовність символьних рядків:");
    stackDisplay();
    robota();
    puts("Послідовність hex чисел:");
    printCirc();
}