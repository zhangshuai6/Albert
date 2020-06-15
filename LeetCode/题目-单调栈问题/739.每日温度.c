/*
 * @lc app=leetcode.cn id=739 lang=c
 *
 * [739] 每日温度
 */

// @lc code=start

typedef struct Node_ {
    int val;
    struct Node_ *next;
} Node;

typedef struct Stack_ {
    int num;
    Node *top;
} Stack;

Stack* StackCreate()
{
    Stack *stack = NULL;

    stack = (Stack*)calloc(1, sizeof(Stack));
    if (stack == NULL) {
        return NULL;
    }

    return stack;
}

void StackPush(Stack *stack, int val)
{
    Node *node = NULL;

    if (stack == NULL) {
        return;
    }

    node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        return;
    }

    node->val = val;
    node->next = NULL;

    if (stack->num == 0) {
        stack->top = node;
    } else {
        node->next = stack->top;
        stack->top = node;
    }

    (stack->num)++;

    return;
}

void StackPop(Stack *stack)
{
    Node *node = NULL;

    if ((stack == NULL) || (stack->num == 0)) {
        return;
    }

    node = stack->top;
    stack->top = node->next;

    (stack->num)--;

    free(node);

    return;
}

int StackTop(Stack *stack)
{
    if ((stack == NULL) || (stack->num == 0)) {
        return 0;
    }

    return stack->top->val;
}

int StackEmpty(Stack *stack)
{
    return (stack->num == 0) ? 1 : 0;
}

void StackDestroy(Stack *stack)
{   
    int num;

    if (stack == NULL) {
        return;
    }

    num = stack->num;
    while (num--) {
        StackPop(stack);
    }

    free(stack);

    return;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* T, int TSize, int* returnSize){
    int *retArray = NULL;
    int i;
    Stack *stack = NULL;

    retArray = (int*)calloc(TSize, sizeof(int));
    if (retArray == NULL) {
        return NULL;
    }

    stack = StackCreate();
    if (stack == NULL) {
        return NULL;
    }

#if 0
/* 实现 1 反向 单调递减栈 */
    for (i = (TSize - 1); i >= 0; i--) {
        while ((!StackEmpty(stack)) && (T[StackTop(stack)] <= T[i])) {
            StackPop(stack);
        }

        retArray[i] = (StackEmpty(stack) == 1) ? 0 : (StackTop(stack) - i);
        StackPush(stack, i);
    }
#endif
/* 实现 2 正向 单调递减栈 */
    for (i = 0; i < TSize; i++) {
        while ((!StackEmpty(stack)) && (T[StackTop(stack)] < T[i])) {
            retArray[StackTop(stack)] = i - StackTop(stack);
            StackPop(stack);
        }

        StackPush(stack, i);
    }

    StackDestroy(stack);

    *returnSize = TSize;

    return retArray;
}


// @lc code=end

