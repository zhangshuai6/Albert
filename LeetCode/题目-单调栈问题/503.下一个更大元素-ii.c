/*
 * @lc app=leetcode.cn id=503 lang=c
 *
 * [503] 下一个更大元素 II
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
int* nextGreaterElements(int* nums, int numsSize, int* returnSize){
    int i;
    int *retArray = NULL;
    Stack *stack = NULL;

    retArray = (int*)malloc((sizeof(int) * numsSize));
    if (retArray == NULL) {
        *returnSize = 0;
        return NULL;
    }

    memset(retArray, -1, (sizeof(int) * numsSize));

    stack = StackCreate();
    if (stack == NULL) {
        free(retArray);
        *returnSize = 0;
        return NULL;
    }

    for (i = 0; i < (2 * numsSize); i++) {
        while ((!StackEmpty(stack)) && (nums[StackTop(stack)] < nums[i % numsSize])) {
            retArray[StackTop(stack)] = nums[i % numsSize];
            StackPop(stack);
        }

        StackPush(stack, (i % numsSize));
    }

    StackDestroy(stack);

    *returnSize = numsSize;

    return retArray;
}


// @lc code=end

