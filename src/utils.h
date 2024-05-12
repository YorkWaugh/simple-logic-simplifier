#define OK 1
#define ERROR 0

typedef int Status;
typedef struct LNode
{
    int *data;
    struct LNode *next;
} LNode, *LinkList;

// Inserting an array of length n into a link list.
Status ListInsert(LinkList L, int *e, int n)
{
    int i;
    LinkList p = L;
    while (p->next)
        p = p->next;
    if (!p)
        return ERROR;
    struct LNode *s = (LinkList)malloc(sizeof(LNode));
    s->data = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        s->data[i] = e[i];
    s->next = p->next;
    p->next = s;
    return OK;
}

// Delete the nth node in the link list.
Status LiskDelete(LinkList L, int i)
{
    LinkList p = L, q;
    int j = 0;
    while (p->next && j < i - 1)
    {
        p = p->next;
        ++j;
    }
    if (!p->next || j > i - 1)
        return ERROR;
    q = p->next;
    p->next = q->next;
    free(q->data);
    free(q);
    return OK;
}

Status DestoryList(LinkList L)
{
    LinkList p = L, q = p->next;
    while (q)
    {
        free(p);
        p = q, q = q->next;
    }
    free(p);
    return OK;
}

// Conversion from decimal to binary
int *ConvertBinNum(int num, int length)
{
    int *BinNum;
    BinNum = (int *)malloc(length * sizeof(length));
    int i = length - 1, x = num;
    do
    {
        BinNum[i] = x % 2;
        x /= 2;
    } while (i--);
    return BinNum;
}

// Prints a binary number of length n.
void PrintBinNum(int *BinNum, int Length)
{
    int i;
    for (i = 0; i < Length; i++)
        printf("%d", BinNum[i]);
    free(BinNum);
}

void PrintBinItems(int *BinNum, int Length)
{
    int i;
    for (i = 0; i < Length; i++)
    {
        if (BinNum[i] == 0)
            printf("%c'", 'A' + i);
        if (BinNum[i] == 1)
            printf("%c", 'A' + i);
    }
}

// Determine if they are logically adjacent. If they are, return the different position
int LogicAdj(int *Bin1, int *Bin2, int Length)
{
    int i, p = 0;
    for (i = 0; i < Length; i++)
        if (Bin1[i] != Bin2[i])
            p++;
    if (p == 1)
    {
        for (i = 0; i < Length; i++)
            if (Bin1[i] != Bin2[i])
                p = i + 1;
        return p;
    }
    return 0;
}

Status CountAdd(int *Table, int *BinNum, int n, int j)
{
    if (n != 1)
    {
        if (BinNum[0] != 2)
            CountAdd(Table, BinNum + 1, n - 1, j + BinNum[0] * (1 << (n - 1)));
        else
        {
            CountAdd(Table, BinNum + 1, n - 1, j + (1 << (n - 1)));
            CountAdd(Table, BinNum + 1, n - 1, j);
        }
    }
    else
    {
        if (BinNum[0] != 2)
            Table[j + BinNum[0]]++;
        else
        {
            Table[j]++;
            Table[j + 1]++;
        }
    }
    return OK;
}

Status CountSub(int *Table, int *BinNum, int n, int j)
{
    if (n != 1)
    {
        if (BinNum[0] != 2)
            CountSub(Table, BinNum + 1, n - 1, j + BinNum[0] * (1 << (n - 1)));
        else
        {
            CountSub(Table, BinNum + 1, n - 1, j + (1 << (n - 1)));
            CountSub(Table, BinNum + 1, n - 1, j);
        }
    }
    else
    {
        if (BinNum[0] != 2)
            Table[j + BinNum[0]]--;
        else
        {
            Table[j]--;
            Table[j + 1]--;
        }
    }
    return OK;
}

// Determine if the item needs to be deleted
int CountDeter(int *Table, int *BinNum, int n, int j)
{
    if (n != 1)
    {
        if (BinNum[0] != 2)
            return CountDeter(Table, BinNum + 1, n - 1, j + BinNum[0] * (1 << (n - 1)));
        else
            return CountDeter(Table, BinNum + 1, n - 1, j + (1 << (n - 1))) && CountDeter(Table, BinNum + 1, n - 1, j);
    }
    else
    {
        if (BinNum[0] != 2)
        {
            if (Table[j + BinNum[0]] <= 1)
                return 0;
            else
                return 1;
        }
        else
        {
            if (Table[j] <= 1 || Table[j + 1] <= 1)
                return 0;
            else
                return 1;
        }
    }
}
