/*
 * @lc app=leetcode.cn id=42 lang=c
 *
 * [42] 接雨水
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

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int trap(int* height, int heightSize){
    int retVal = 0;
    int i;
    int index;
    Stack *stack = NULL;

    stack = StackCreate();
    if (stack == NULL) {
        return 0;
    }

    for (i = 0; i < heightSize; i++) {
        while ((!StackEmpty(stack)) && (height[StackTop(stack)] <= height[i])) {
            index = StackTop(stack);
            StackPop(stack);

            if (StackEmpty(stack) == 1) {
                break;
            }

            retVal += (MIN(height[i], height[StackTop(stack)]) - height[index]) * (i - StackTop(stack) - 1);
        }

        StackPush(stack, i);
    }

    StackDestroy(stack);

    return retVal;
}


// @lc code=end

