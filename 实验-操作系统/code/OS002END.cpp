//单道处理-->一个一个来
//FCFS、SJF、HRN
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include <conio.h>
#include <stdlib.h>
#define getpch(type) (type *)malloc(sizeof(type))
#define NULL 0
#define NUM 8
float T1 = 0, T2 = 0;
int times = 0;
int ntimes = 9999999;
int rptimes = 9999999;
FILE *fp = fopen("OS002data.txt", "r");
struct pcb
{
    char name[10];
    char state;      
    int rtime;       
    int ntime;       
    int stime;       
    int finishtime;  
    float cycletime; 
    float cltime;    
    float rp;        
    struct pcb *next;
} *ready = NULL, *p, *q, *r;
typedef struct pcb PCB;
void input()
{
    for (int i = 0; i < NUM; i++)
    {
        p = getpch(PCB);
        fscanf(fp, "%s%s%d%d\n", p->name, &p->state, &p->rtime, &p->ntime);
        p->stime = 0;
        p->finishtime = 0;
        p->cycletime = 0;
        p->cltime = 0;
        p->next = NULL;
        if (ready == NULL) ready = q = p;
        else
        {
            q->next = p;
            q = p;
        }
    }
    fclose(fp);
}
void disp(PCB *pr)
{
    printf("\n进程名\t开始时刻\t完成时刻\t周转时间\t带权周转时间\n");
    printf("%s\t", pr->name);
    printf("%d\t\t", pr->stime);
    printf("%d\t\t", pr->finishtime);
    printf("%f\t\t", pr->cycletime);
    printf("%f\t\t", pr->cltime);
    printf("\n");
}
void final()
{
    float s, t;
    t = T1 / NUM;
    s = T2 / NUM;
    getch();
    printf("\n\n全部完成!");
    printf("\n作业的平均周转时间是: %f", t);
    printf("\n作业的平均带权周转时间是%f: \n\n\n", s);
}
void calc(PCB *p)
{
    p->stime = times;
    p->state = 'R';
    p->finishtime = p->stime + p->ntime;
    p->cycletime = (float)(p->finishtime - p->rtime);
    p->cltime = (float)(p->cycletime / p->ntime);
    T1 += p->cycletime;
    T2 += p->cltime;
}
void ok(bool flag)
{
    if(flag)
    {
        ready = p->next;
        p->next = NULL;
    }
    else
    {
        q = ready;
        while (q->next != p)
            q = q->next;
        q->next = p->next;
    }
}
void running(PCB *p)
{
    ok(p == ready);
    calc(p);
    disp(p);
    times += p->ntime;
    p->state = 'F';
    printf("\n进程%s完成\t按任意键继续\n", p->name);
    free(p);
    getch();
}
float calcRp(PCB *p)
{
    float y;
    if (p->stime)
        y = (times - p->rtime + p->ntime) / p->ntime;
    return y;
}
void FCFS()
{
    int i, flag;
    input();
    for (i = 0; i < NUM; i++)
    {
        p = ready;
        flag = 1;
        do
        {
            if (p->state == 'W' && p->rtime <= times)
                flag = 0;
            if (flag)
                p = p->next;
        } while (p != NULL && flag);
        if (flag)
        {
            i--;
            printf("\n没有满足要求的进程,需等待");
            times++;
        }
        else
        {
            running(p);
        }
    }
}
void SJF()
{
    int i, flag;
    input();
    for (i = 0; i < NUM; i++)
    {
        p = ready;
        r = ready->next;
        flag = 1;
        do
        {
            while (r != NULL)
            {
                if (r->state == 'W' && r->rtime <= times && r->ntime <= ntimes)
                    ntimes = r->ntime;
                r = r->next;
            }
            if (p->state == 'W' && p->rtime <= times && p->ntime <= ntimes)
                flag = 0;
            if (flag)
                p = p->next;
        } while (p != NULL && flag);
        if (flag)
        {
            i--;
            printf("\n没有满足要求的进程,需等待");
            times++;
        }
        else
        {
            running(p);
            if (r != NULL)
                r = ready->next;
            ntimes = 9999999;
        }
    }
}
void HRN()
{
    int i, flag;
    input();
    for (i = 0; i < NUM; i++)
    {
        p = ready;
        r = ready->next;
        flag = 1;
        do
        {
            while (r != NULL)
            {
                r->rp = calcRp(r);
                if (r->state == 'W' && r->rtime <= times && r->rp <= rptimes)
                    rptimes = r->rp;
                r = r->next;
            }
            if (p->state == 'W' && p->rtime <= times && p->rp <= rptimes)
                flag = 0;
            if (flag)
                p = p->next;
        } while (p != NULL && flag);
        if (flag)
        {
            i--;
            printf("\n没有满足要求的进程,需等待");
            times++;
        }
        else
        {
            running(p);
            if (r != NULL)
                r = ready->next;
            rptimes = 9999999;
        }
    }
}
main()
{
    int x;
    printf("--------------------------------\n");
    printf("1:先来先服务（FCFS）\n");
    printf("2:最短作业优先（SJF）\n");
    printf("3:响应比高者优先（HRN）\n");
    printf("--------------------------------\n");
    printf("按数字键选择要执行的操作: ");
    scanf("%d", &x);
    printf("\n");
    switch (x)
    {
    case 1:
        FCFS();
        break;
    case 2:
        SJF();
        break;
    case 3:
        HRN();
        break;
    default:
        printf("输入的数字不正确\n");
        break;
    }
    return 0;
    printf("\n\n 进程已经完成.\n");
    getchar();
}