#include "utils.h"

// Create truth table Mode 1
Status CreateTable1(int **Table, int n)
{
    int p = pow(2, n);
    *Table = (int *)malloc(p * sizeof(int));
    int i;
    printf("Input value(True:1,False:0,Irrelevant:2): \n");
    for (i = 0; i < p; i++)
    {
        PrintBinNum(ConvertBinNum(i, n), n);
        printf(": ");
        scanf("%d", *Table + i);
    }
    return OK;
}

// Create truth table Mode 2
Status CreateTable2(int **Table, int n)
{
    int p = pow(2, n);
    *Table = (int *)malloc(p * sizeof(int));
    int t;
    for (t = 0; t < p; t++)
        (*Table)[t] = 0;
    printf("Input truth-taking items (decimal numbers, -1 to end): \n");
    while (scanf("%d", &t), t != -1)
        (*Table)[t] = 1;
    printf("Input Irrelevant items (decimal numbers, -1 to end): \n");
    while (scanf("%d", &t), t != -1)
        (*Table)[t] = 2;
    return OK;
}

// Creating Logical Expressions.
Status CreateExpression(int *Table, LinkList **Expression, int n)
{
    *Expression = (LinkList *)malloc((n + 1) * sizeof(LinkList));
    (*Expression)[0] = (LinkList)malloc(sizeof(LNode));
    (*Expression)[0]->next = NULL;
    int i, *BinNum;
    for (i = 0; i < pow(2, n); i++)
    {
        if (Table[i] > 0)
        {
            BinNum = ConvertBinNum(i, n);
            ListInsert((*Expression)[0], BinNum, n);
            free(BinNum);
        }
    }
    return OK;
}

Status MergeItems(int *Table, LinkList *Expression, int m, int n)
{
    Expression[m] = (LinkList)malloc(sizeof(LNode));
    Expression[m]->next = NULL;
    LinkList i, j;
    int s, t, *p;
    for (i = Expression[m - 1]->next; i; i = i->next)
        for (j = i->next; j; j = j->next)
        {
            t = LogicAdj(i->data, j->data, n);
            if (t)
            {
                p = (int *)malloc(n * sizeof(int));
                for (s = 0; s < n; s++)
                    p[s] = i->data[s];
                p[t - 1] = 2;
                ListInsert(Expression[m], p, n);
                CountAdd(Table, p, n, 0);
                free(p);
            }
        }
    return OK;
}

Status SimplifyItems(int *Table, LinkList *Expression, int m, int n)
{
    LinkList i = Expression[m]->next;
    int p = 1;
    while (i)
    {
        if (CountDeter(Table, i->data, n, 0))
        {
            CountSub(Table, i->data, n, 0);
            i = i->next;
            LiskDelete(Expression[m], p);
        }
        else
        {
            p++;
            i = i->next;
        }
    }
    return OK;
}

// flag is used to determine if the first
Status PrintItems(LinkList *Expression, int m, int n, int *flag)
{
    LinkList p;
    p = Expression[m]->next;
    if (m == n)
    {
        if (p)
        {
            printf("1");
            *flag = 1;
        }
        return OK;
    }
    while (p)
    {
        if (*flag)
            printf("+");
        *flag = 1;
        PrintBinItems(p->data, n);
        p = p->next;
    }
    return OK;
}
