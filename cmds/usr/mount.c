//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/usr/mount.c

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;
#include <ansi.h>

int do_ride(object me, object ob);

int main(object me,string arg)
{
	return do_ride(me, ob);
}

int do_ride(object me, object ob)
{
	message_vision("$N往"+ob->query("name")+"的身上一跳，顺利的骑上"+ob->query("name")+"。\n", me);
        return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : mount <目标>

这个指令让你骑上种你想骑的生物 -- 当然要他愿意让你骑。

相关讯息 : dismount, charge


HELP
	);
	return 1;
}
