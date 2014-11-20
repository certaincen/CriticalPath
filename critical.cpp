//
//  main.cpp
//  cplustest
//
//  Created by curtain on 14/11/20.
//  Copyright (c) 2014年 HIT. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <queue>
#define N 1005
#define MAXNUM  5000
#define UNDONE -1
#define MINNUM -1

using namespace std;

typedef struct node
{
    int flag;
    int early_start;
    int early_end;
    int value;
    int last_start;
    int last_end;
    int pre_num[N];
    int after_num[N];
    int len_pre;
    int len_after;
    int in_degree;
    int out_degree;
}task_node;
task_node net_work[N];
queue<task_node> q;
void topological_order()
{
    while(!q.empty())
    {
        q.pop();
    }
    task_node start_node = net_work[0];
    q.push(start_node);
    while (!q.empty())
    {
        task_node cur_node = q.front();
        q.pop();
        int i;
        for(i=0;i<cur_node.len_after;i++)
        {
            int index = cur_node.after_num[i];
            net_work[index].in_degree--;
            if (net_work[index].early_start < cur_node.early_end)
            {
                net_work[index].early_start = cur_node.early_end;
                net_work[index].early_end = net_work[index].early_start + net_work[index].value;
            }
            if (net_work[index].in_degree == 0 && net_work[index].flag != 1)
            {
                q.push(net_work[index]);
            }
        }
    }
    return;
}
void inverse_topological_order(int end_index)
{
    task_node end_node = net_work[end_index];
    while(!q.empty())
    {
        q.pop();
    }
    q.push(end_node);
    while(!q.empty())
    {
        task_node cur_node = q.front();
        q.pop();
        int i;
        for (i=0;i<cur_node.len_pre;i++)
        {
            int index = cur_node.pre_num[i];
            net_work[index].out_degree--;
            if (net_work[index].last_end > cur_node.last_start)
            {
                net_work[index].last_end = cur_node.last_start;
                net_work[index].last_start = net_work[index].last_end - net_work[index].value;
            }
            if (net_work[index].out_degree == 0 && net_work[index].flag != 1)
            {
                q.push(net_work[index]);
            }
        }
        
    }
    return;
}
bool find_critical_path(int index)
{
    int i;
    if (index != 0 && net_work[index].flag == 1)
        return true;
    task_node cur_node = net_work[index];
    if (cur_node.early_start != cur_node.last_start)
        return false;
    for (i=0;i<cur_node.len_after;i++)
    {
        if (find_critical_path(cur_node.after_num[i]))
        {
            printf("->(%d,%d)",cur_node.value,index);
            return true;
        }
    }
    return false;
}
void init(int n)
{
    int i;
    for (i=0;i<=n+1;i++)
    {
        net_work[i].flag = 0;
        net_work[i].early_start = MINNUM;
        net_work[i].early_end = UNDONE;
        net_work[i].value = 0;
        net_work[i].last_start = UNDONE;
        net_work[i].last_end = MAXNUM;
        memset(net_work[i].pre_num,0,sizeof(net_work[i].pre_num));
        memset(net_work[i].after_num,0,sizeof(net_work[i].after_num));
        net_work[i].len_pre = 0;
        net_work[i].len_after = 0;
        net_work[i].in_degree = 0;
        net_work[i].out_degree = 0;
    }
    return;
}
void add_node(int fa, int son)
{
    net_work[fa].after_num[net_work[fa].len_after++] = son;
    net_work[fa].out_degree++;
    net_work[son].pre_num[net_work[son].len_pre++] = fa;
    net_work[son].in_degree++;
    
}
void show_item(int n)
{
    int i;
    for(i=0;i<=n+1;i++)
    {
        printf("%d-%d-%d-%d-%d\n",i,net_work[i].early_start,net_work[i].early_end,net_work[i].last_start,net_work[i].last_end);
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    int i;
    init(n);
    net_work[0].flag = 1;
    net_work[n+1].flag = 1;
    net_work[0].early_start = 0;
    net_work[0].early_end = 0;
    for (i=1;i<=n;i++)
    {
        scanf("%d",&net_work[i].value);	
    }
    int m;
    scanf("%d",&m);
    for (i=0;i<m;i++)
    {
        int fa,son;
        scanf("%d%d",&fa,&son);
        add_node(fa,son);
    }
    topological_order();
    net_work[n+1].last_start = net_work[n+1].early_start;
    net_work[n+1].last_end = net_work[n+1].early_end;
    inverse_topological_order(n+1);
    find_critical_path(0);
    printf("---------------\n");
    show_item(n);
    printf("\nEND\n");
    
    return 0;
}
