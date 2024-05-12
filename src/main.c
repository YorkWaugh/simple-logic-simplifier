#include <stdio.h>
#include <stdlib.h>

#include "ops.h"

int main()
{
    int n, i, t, flag;
    int *Table;
    LinkList *Expression;
    while (1)
    {
        printf("Inputs number of variables(0 to exit):");
        scanf("%d", &n);
        if (n == 0)
            break;
        printf("Mode(1 / 2): ");
        scanf("%d", &t);
        if (t == 1)
            CreateTable1(&Table, n);
        else
            CreateTable2(&Table, n);
        CreateExpression(Table, &Expression, n);
        for (i = 1; i <= n; i++)
            MergeItems(Table, Expression, i, n);
        for (i = 0; i <= n; i++)
            SimplifyItems(Table, Expression, i, n);
        flag = 0;
        for (i = 0; i <= n; i++)
            PrintItems(Expression, i, n, &flag);
        if (flag == 0)
            printf("0");
        putchar('\n');
        for (i = 0; i <= n; i++)
            DestoryList(Expression[i]);
        free(Table);
        free(Expression);
    }
    return 0;
}