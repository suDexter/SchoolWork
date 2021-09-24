//设计一个有5个进程共行的进程调度程序。
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include <conio.h>
#include <stdlib.h>
#define getpch(type) (type *)malloc(sizeof(type))
#define NULL 0
FILE *fp = fopen("OS001data.txt","r");
struct pcb
{ /* 定义进程控制块PCB */
    char name[10];
    char state;
    int super;
    int ntime;
    int rtime;
    struct pcb *link;
} *ready = NULL, *p;
typedef struct pcb PCB;
void sort() /* 建立对进程进行优先级排列函数*/
{
    PCB *first, *second;
    int insert = 0;
    if ((ready == NULL) || ((p->super) > (ready->super))) /*优先级最大者,插入队首*/
    {
        p->link = ready;
        ready = p;
    }
    else /* 进程比较优先级,插入适当的位置中*/
    {
        first = ready;
        second = first->link;
        while (second != NULL)
        {
            if ((p->super) > (second->super)) /*若插入进程比当前进程优先数大,*/
            {                                 /*插入到当前进程前面*/
                p->link = second;
                first->link = p;
                second = NULL;
                insert = 1;
            }
            else /* 插入进程优先数最低,则插入到队尾*/
            {
                first = first->link;
                second = second->link;
            }
        }
        if (insert == 0)
            first->link = p;
    }
}
void input() /* 建立进程控制块函数*/
{
    int i;
    for (i = 0; i < 5; i++)
    {
        p = getpch(PCB);
        fscanf(fp,"%s%d%d\n",p->name,&p->super,&p->ntime);
        p->rtime = 0;
        p->state = 'w';
        p->link = NULL;
        sort(); /* 调用sort函数*/
        printf("按任意键继续\n");
    }
}
int space()
{
    int l = 0;
    PCB *pr = ready;
    while (pr != NULL)
    {
        l++;
        pr = pr->link;
    }
    return (l);
}
void disp(PCB *pr) /*建立进程显示函数,用于显示当前进程*/
{
    printf("\n qname \t state \t super \t ndtime \t runtime \n");
    printf("|%s\t", pr->name);
    printf("|%c\t", pr->state);
    printf("|%d\t", pr->super);
    printf("|%d\t", pr->ntime);
    printf("|%d\t", pr->rtime);
    printf("\n");
}
void check() /* 建立进程查看函数 */
{
    PCB *pr;
    printf("\n **** 当前正在运行的进程是:%s", p->name); /*显示当前运行进程*/
    disp(p);
    pr = ready;
    printf("\n ****当前就绪队列状态为:\n"); /*显示就绪队列状态*/
    while (pr != NULL)
    {
        disp(pr);
        pr = pr->link;
    }
}
void destroy() /*建立进程撤消函数(进程运行结束,撤消进程)*/
{
    printf("\n 进程 [%s] 已完成.\n", p->name);
    free(p);
}
void running() /* 建立进程就绪函数(进程运行时间到,置就绪状态*/
{
    (p->rtime)++;
    if (p->rtime == p->ntime)
        destroy(); /* 调用destroy函数*/
    else
    {
        (p->super)--;
        p->state = 'w';
        sort(); /*调用sort函数*/
    }
}
int main() /*主函数*/
{
    int len, h = 0;
    input();
    len = space();
    while ((len != 0) && (ready != NULL))
    {
        getchar();
        h++;
        printf("\n The execute number:%d \n", h);
        p = ready;
        ready = p->link;
        p->link = NULL;
        p->state = 'R';
        check();
        running();
        printf("\n 按任一键继续......");
    }
    printf("\n\n 进程已经完成.\n");
    getchar();
    return 0;
}
