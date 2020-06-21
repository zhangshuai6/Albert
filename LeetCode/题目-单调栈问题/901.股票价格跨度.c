/*
 * @lc app=leetcode.cn id=901 lang=c
 *
 * [901] 股票价格跨度
 */

// @lc code=start

typedef struct Node_ {
    int price;
    int preContinueNum;
    struct Node_ *next;
} Node;

typedef struct {
    int num;
    Node *top;
} StockSpanner;


StockSpanner* stockSpannerCreate() {
    StockSpanner *stack = NULL;

    stack = (StockSpanner*)calloc(1, sizeof(StockSpanner));
    if (stack == NULL) {
        return NULL;
    }

    return stack;
}

void StackPush(StockSpanner *stack, int price, int preContinueNum)
{
    Node *node = NULL;

    if (stack == NULL) {
        return;
    }

    node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        return;
    }

    node->price = price;
    node->preContinueNum = preContinueNum;
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

void StackPop(StockSpanner *stack)
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

Node* StackTop(StockSpanner *stack)
{
    if ((stack == NULL) || (stack->num == 0)) {
        return 0;
    }

    return stack->top;
}

int StackEmpty(StockSpanner *stack)
{
    return (stack->num == 0) ? 1 : 0;
}

int stockSpannerNext(StockSpanner* obj, int price) {
    int i;
    int contDayNum = 1; 
    int preContDayNum = 0;
    Node *node = NULL;

    node = StackTop(obj);

    while ((!StackEmpty(obj)) && (node->price <= price)) {
        contDayNum += (node->preContinueNum + 1);
        preContDayNum += (node->preContinueNum + 1);
        StackPop(obj);
        node = StackTop(obj);
    }

    StackPush(obj, price, preContDayNum);

    return contDayNum;
}

void stockSpannerFree(StockSpanner* obj) {
    int num;

    if (obj == NULL) {
        return;
    }

    num = obj->num;
    while (num--) {
        StackPop(obj);
    }

    free(obj);

    return;    
}

/**
 * Your StockSpanner struct will be instantiated and called as such:
 * StockSpanner* obj = stockSpannerCreate();
 * int param_1 = stockSpannerNext(obj, price);
 
 * stockSpannerFree(obj);
*/
// @lc code=end

