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

typedef struct Queue_ {
    int num;
    Node *rear;
    Node *front;
} Queue;

Queue* QueueCreate()
{
    Queue *queue = NULL;

    queue = (Queue*)calloc(1, sizeof(Queue));
    if (queue == NULL) {
        return NULL;
    }

    return queue;
}

void EnQueue(Queue *queue, int val)
{
    Node *node = NULL;

    if (queue == NULL) {
        return;
    }

    node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        return;
    }

    node->val = val;
    node->next = NULL;
    node->prev = NULL;

    if (queue->num == 0) {
        queue->rear = node;
        queue->front = node;
    } else {
        node->next = queue->rear;
        queue->rear->prev = node;
        queue->rear = node;
    }

    (queue->num)++;

    return;
}

void DeQueueRear(Queue *queue)
{
    Node *node = NULL;

    if (queue == NULL) {
        return;
    }

    if (queue->num == 0) {
        return;
    }

    node = queue->rear;
    queue->rear = node->next;

    if (queue->num != 1) {
        queue->rear->prev = NULL;
    } else {
        queue->front = NULL;
    }

    (queue->num)--;

    free(node);

    return;
}

void DeQueueFront(Queue *queue)
{
    Node *node = NULL;

    if (queue == NULL) {
        return;
    }

    if (queue->num == 0) {
        return;
    }

    node = queue->front;

    if (queue->num != 1) {
        queue->front->prev->next = NULL;
        queue->front = queue->front->prev;
    } else {
        queue->front = NULL;
        queue->rear = NULL;
    }

    (queue->num)--;

    free(node);

    return;
}

int QueueGetRear(Queue *queue)
{
    if (queue == NULL) {
        return 0;
    }

    if (queue->num == 0) {
        return 0;
    }

    return queue->rear->val;
}

int QueueGetFront(Queue *queue)
{
    if (queue == NULL) {
        return 0;
    }

    if (queue->num == 0) {
        return 0;
    }

    return queue->front->val;
}

int QueueEmpty(Queue *queue)
{
    return (queue->num == 0) ? 1 : 0;
}

void QueueDestroy(Queue *queue)
{   
    int num;

    if (queue == NULL) {
        return;
    }

    num = queue->num;
    while (num--) {
        DeQueueRear(queue);
    }

    free(queue);

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
    Queue *queue = NULL;

    retSize = numsSize - k + 1;

    retArray = (int*)malloc(sizeof(int) * retSize);
    CHECK_NULL_RETURN_NULL(retArray);

    queue = QueueCreate();
    if (queue == NULL) {
        return NULL;
    }

    for (i = 0; i < numsSize; i++) {
        while ((!QueueEmpty(queue)) && (nums[QueueGetRear(queue)]) < nums[i]) {
            DeQueueRear(queue);
        }

        EnQueue(queue, i);
        if ((i + 1) >= k) {
            retArray[j++] = nums[QueueGetFront(queue)];
        }

        if ((i - QueueGetFront(queue) + 1) >= k) {
            DeQueueFront(queue);
        }
    }

    QueueDestroy(queue);

    *returnSize = retSize;
    return retArray;
}
// @lc code=end

