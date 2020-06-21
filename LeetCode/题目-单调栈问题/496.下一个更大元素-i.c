/*
 * @lc app=leetcode.cn id=496 lang=c
 *
 * [496] 下一个更大元素 I
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
int* nextGreaterElement(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize){
    int i;
    int j;
    int *retArray = NULL;
    int *tempArray = NULL;
    Stack *stack = NULL;


    retArray = (int*)malloc(sizeof(int)*nums1Size);
    if (retArray == NULL) {
        *returnSize = 0;
        return NULL;
    }

    memset(retArray, -1, sizeof(int)*nums1Size);

    tempArray = (int*)malloc(sizeof(int)*nums2Size);
    if (tempArray == NULL) {
        *returnSize = 0;
        free(retArray);
        return NULL;
    }

    memset(tempArray, -1, sizeof(int)*nums2Size);

    stack = StackCreate();
    if (stack == NULL) {
        *returnSize = 0;
        free(retArray);
        free(tempArray);
        return NULL; 
    }

    for (i = 0; i < nums2Size; i++) {
        while ((!StackEmpty(stack)) && nums2[StackTop(stack)] < nums2[i]) {
            tempArray[StackTop(stack)] = nums2[i];
            StackPop(stack);
        }

        StackPush(stack, i);
    }

    for (i = 0; i < nums1Size; i++) {
        for (j = 0; j < nums2Size; j++) {
            if (nums1[i] == nums2[j]) {
                retArray[i] = tempArray[j];
                break;
            }
        }
    }

    free(tempArray);
    StackDestroy(stack);

    *returnSize = nums1Size;
    return retArray;
}


// @lc code=end

