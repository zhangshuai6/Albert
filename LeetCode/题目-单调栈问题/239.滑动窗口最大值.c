/*
 * @lc app=leetcode.cn id=239 lang=c
 *
 * [239] 滑动窗口最大值
 */

// @lc code=start

#define CHECK_NULL_RETURN_VOID(p) \
    {                             \
        if (NULL == (p)) {        \
            return;               \
        }                         \
    }

#define CHECK_NULL_RETURN_NULL(p) \
    {                             \
        if (NULL == (p)) {        \
            return NULL;          \
        }                         \
    }

#define CHECK_NULL_RETURN_ZERO(p) \
    {                             \
        if (NULL == (p)) {        \
            return 0;             \
        }                         \
    }

typedef struct Node_ {
    int val;
    struct Node_ *next;
    struct Node_ *prev;
} Node;

typedef struct Stack_ {
    int num;
    Node *top;
    Node *bottom;
} Stack;

Stack* StackCreate()
{
    Stack *stack = NULL;

    stack = (Stack*)calloc(1, sizeof(Stack));
    CHECK_NULL_RETURN_NULL(stack);

    return stack;
}

void StackPush(Stack *stack, int val)
{
    Node *node = NULL;

    CHECK_NULL_RETURN_VOID(stack);

    node = (Node*)malloc(sizeof(Node));
    CHECK_NULL_RETURN_VOID(node);

    node->val = val;
    node->next = NULL;
    node->prev = NULL;

    if (stack->num == 0) {
        stack->top = node;
        stack->bottom = node;
    } else {
        node->next = stack->top;
        stack->top->prev = node;
        stack->top = node;
    }

    (stack->num)++;

    return;
}

void StackPop(Stack *stack)
{
    Node *node = NULL;

    CHECK_NULL_RETURN_VOID(stack);
    if (stack->num == 0) {
        return;
    }

    node = stack->top;
    stack->top = node->next;

    if (stack->num != 1) {
        stack->top->prev = NULL;
    } else {
        stack->bottom = NULL;
    }

    (stack->num)--;

    free(node);

    return;
}

void StackPopBottom(Stack *stack)
{
    Node *node = NULL;

    CHECK_NULL_RETURN_VOID(stack);
    if (stack->num == 0) {
        return;
    }

    node = stack->bottom;

    if (stack->num != 1) {
        stack->bottom->prev->next = NULL;
        stack->bottom = stack->bottom->prev;
    } else {
        stack->bottom = NULL;
        stack->top = NULL;
    }

    (stack->num)--;

    free(node);

    return;
}

int StackTop(Stack *stack)
{
    CHECK_NULL_RETURN_ZERO(stack)

    if (stack->num == 0) {
        return 0;
    }

    return stack->top->val;
}

int StackBottom(Stack *stack)
{
    CHECK_NULL_RETURN_ZERO(stack)

    if (stack->num == 0) {
        return 0;
    }

    return stack->bottom->val;
}

int StackEmpty(Stack *stack)
{
    return (stack->num == 0) ? 1 : 0;
}

void StackDestroy(Stack *stack)
{   
    int num;

    CHECK_NULL_RETURN_VOID(stack);

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
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize){
    int retSize;
    int i;
    int j = 0;
    int *retArray = NULL;
    Stack *stack = NULL;

    retSize = numsSize - k + 1;

    retArray = (int*)malloc(sizeof(int) * retSize);
    CHECK_NULL_RETURN_NULL(retArray);

    stack = StackCreate();
    if (stack == NULL) {
        free(stack);
        return NULL;
    }

    for (i = 0; i < numsSize; i++) {
        while ((!StackEmpty(stack)) && (nums[StackTop(stack)]) < nums[i]) {
            StackPop(stack);
        }

        StackPush(stack, i);
        if ((i + 1) >= k) {
            retArray[j++] = nums[StackBottom(stack)];
        }

        if ((i - StackBottom(stack) + 1) >= k) {
            StackPopBottom(stack);
        }
    }

    StackDestroy(stack);

    *returnSize = retSize;
    return retArray;
}
// @lc code=end

