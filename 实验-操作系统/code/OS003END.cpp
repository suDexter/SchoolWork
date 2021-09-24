#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define getpch(type) (type *)malloc(sizeof(type))
FILE *fp1 = fopen("OS003data01.txt","r");
FILE *fp2 = fopen("OS003data02.txt","r");
struct Tab
{
    int no;
    int size;
    int Add;
    char state;
} tab[5];
struct pcb
{
    char name[10];
    int size;
    struct pcb *link;
} *ready = NULL, *p;
typedef struct pcb PCB;
void Allocate(int No, int size)
{
    int i;
    int flag = 0;
    for (i = 0; i < 5; i++)
    {
        Tab p = tab[i];
        if (p.state == 'N' && p.size > size)
        {
            tab[i].state = 'Y';
            flag = 1;
            break;
        }
    }
    if(flag == 1) printf("作业No.%d(size = %d)分配成功！,在分区%d\n", No, size,i);
    else printf("作业No.%d(size = %d)分配失败\n", No, size);
}
void Create()
{
    int i;
    for (i = 0; i < 5; i++)
    {
        fscanf(fp1,"%d%d%d%s\n",&tab[i].no, &tab[i].size, 
        &tab[i].Add, &tab[i].state);
    }
    fclose(fp1);
}
void Print()
{
    int i;
    printf("分区号\t大小\t起址\t状态\n");
    for (i = 0; i < 5; i++)
    {
        printf("%d\t", tab[i].no);
        printf("%d\t", tab[i].size);
        printf("%d\t", tab[i].Add);
        printf("%c\t", tab[i].state);
        printf("\n");
    }
}
main(int argc, char *argv[])
{
    int i;
    Create();
    Print();
    printf("按任意键继续：\n");
    getchar();
    printf("分配作业：\n");
    for (i = 0; i < 10; i++)
    {
        int k;
        fscanf(fp2,"%d\n", &k);
        Allocate(i,k);
    }
    Print();
    getchar();
    printf("若有作业完成,回收该分区\n");
    printf("以2、3号分区为例\n");
    tab[2].state = 'N';
    tab[3].state = 'N';
    Print();
    getchar();
    printf("分配新的作业\n");
    Allocate(11, 1);
    Print();
    getchar();
    return 0;
}
