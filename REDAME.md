#网络流之关键路径

最早开始时间利用顺序拓扑
最晚结束时间利用逆序拓扑

node[son].early_start = max(node[father].early_end,node[son].early_start)

node[father].last_end = min(node[son].last_start,node[father].last_end)

