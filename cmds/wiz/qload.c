//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// qload.c

inherit F_CLEAN_UP;

int main()
{
    write(query_load_average() + "\n");
    return 1;
}

int help(object me)
{
write(@HELP
指令格式 : qload 

这个指令显示出目前 CPU 的负担, cmds/s 是每秒编译几个 cmds
comp lines/s 是每秒几行。
HELP
    );
    return 1;
}
