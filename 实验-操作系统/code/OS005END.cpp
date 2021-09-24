#include <stdio.h>
int Available [100] = {1,3,2};
int Max       [100][100]={{2,3,2},{4,2,3},{3,4,2}};
int Allocation[100][100]={{1,0,1},{1,1,1},{1,1,0}};
int Need      [100][100];
int Request   [100][100];
int Finish    [100];
int p         [100];
int m = 3, n = 3;
int isSafe()
{
	int i, j;
	int a = 0;
	int Work[100]; //可利用资源数组
	for (i = 0; i < n; i++)
		Work[i] = Available[i];
	for (i = 0; i < m; i++)
		Finish[i] = 0;//初始化进程满足条件状态
	for (i = 0; i < m; i++) {
		if (Finish[i] == 1)
			continue;
		else
		{
			for (j = 0; j < n; j++)
			{
				if (Need[i][j] > Work[j])//判断若每个种类需要资源大于可利用资源则结束
					break;
			}
			if (j == n)//判断每个种类需要资源都小于可利用资源
			{
				Finish[i] = 1;
				for (int k = 0; k < n; k++)
					Work[k] += Allocation[i][k];//可利用资源回收进程的释放资源
				p[a++] = i;//存储对应进程号作为后续输出安全序列号
				i = -1;//该次循环结束则i++后重新从头遍历查找Finish=0的分配资源，直至所有进程Finish=1
			}
			else continue;
		}

	}
	if (a == m) {
		printf("系统是安全的\n");
		printf("系统安全序列是:\n");
		for (i = 0; i < a; i++) {
			printf("%d", p[i]);
			if (i != a - 1)
				printf("-->");

		}
		printf("\n");
		return 1;
	}
	else {
		printf("系统是不安全的，不存在安全序列！");
		return 0;
	}

}
// 申请资源输入函数
void apply() {
	int i, j, k = 0;
	while (1) {
		printf("输入要申请的资源的进程号：（第一个进程号为0，第二个进程号为1，依此类推）\n");
		scanf("%d", &k);
		printf("输入进程所请求的各个资源的数量\n");//在已占用资源的基础上申请资源
		for (i = 0; i < n; i++)
			scanf("%d", &Request[k][i]);
		while (1) {
			for (i = 0; i < n; i++) {
				if (Request[k][i] > Need[k][i])
				{
					printf("所请求资源数超过进程的需求量！\n");
					printf("请重新输入进程所需要请求的各资源的数量：\n");
					for (i = 0; i < n; i++)
						scanf("%d", &Request[k][i]);
					break;
				}
			}
			for (i = 0; i < n; i++) {
				if (Request[k][i] > Available[i])
				{
					printf("所请求资源数超过系统所有的资源数！\n");
					printf("请重新输入进程所需要请求的各资源的数量：\n");
					for (i = 0; i < n; i++)
						scanf("%d", &Request[k][i]);
					break;
				}
			}
			break;
		}
		for (i = 0; i < n; i++)
		{
			Available[i] -= Request[k][i];
			Allocation[k][i] += Request[k][i];
			Need[k][i] -= Request[k][i];
		}
		printf("此时进程已占用资源矩阵:\n");
		for (i = 0; i < m; i++) {
			for (j = 0; j < n; j++) {
				printf("%d ", Allocation[i][j]);
			}
			printf("\n");
		}
		printf("此时进程还需资源矩阵:\n");
		for (i = 0; i < m; i++) {
			for (j = 0; j < n; j++) {
				printf("%d ", Need[i][j]);
			}
			printf("\n");
		}
		printf("此时系统可利用资源：\n");
		for (i = 0; i < n; i++)
			printf("%d ", Available[i]);
		printf("\n");
		if (isSafe())
			printf("同意分配请求\n");
		else
		{
			printf("不同意分配请求\n");
			for (i = 0; i < n; i++)
			{
				Available[i] += Request[k][i];
				Allocation[k][i] -= Request[k][i];
				Need[k][i] += Request[k][i];
			}
		}
		for (i = 0; i < m; i++)
			Finish[i] = 0;
		char Flag;
		printf("是否再次请求分配？是请按Y，否请按N\n");
		while (1)
		{
			getchar();
			scanf("%c", &Flag);
			if (Flag == 'Y' || Flag == 'N') {
				break;

			}
			else
			{
				printf("请按要求重新输入:\n");
				continue;
			}
		}
		if (Flag == 'Y')
			continue;
		else break;
	}
}

int main()
{
	int i, j;
	char flag;
	printf("进程数%d\n",m);
	printf("资源种类数%d\n",n);
	printf("每个进程最大各类资源需求(Max)\n");
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ", Max[i][j]);
		}
		printf("\n");
	}
	printf("每个进程已经占用的各类资源(Allocation)\n");
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%d ", Allocation[i][j]);
			Need[i][j] = Max[i][j] - Allocation[i][j];
		}
		printf("\n");
	}
	printf("每个进程还需资源(Need)\n");
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ", Need[i][j]);
		}
		printf("\n");
	}
	printf("可利用的各类资源(Available)\n");
	for (i = 0; i < n; i++)
		printf("%d ", Available[i]);
	if (isSafe()) {
		printf("是否需要指定进程申请资源分配？是请按Y，否请按N\n");
		while (1)
		{
			
			scanf("%c", &flag);
			if (flag == 'Y' || flag == 'N') {
				break;
			}
			else {
				printf("请按要求重新输入:\n");
				continue;
			}
		}
		if (flag == 'Y') {
			apply();
		}
	}
	else {
		getchar();
		return 0;
	}
	getchar();
	return 0;
}