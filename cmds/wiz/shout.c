//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/npc/shout.c

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	if( !wizardp(me) ) return notify_fail("目前暂不开放玩家 shout。\n");

	if (!arg) return notify_fail("指令格式：shout <讯息>\n");
	shout(HIY"“"HIR"重要广播"NOR+HIY"”" + me->name(1) + WHT"(" + capitalize(me->query("id")) + ")："HIM + arg + "\n"NOR);
	write(HIY"“"HIR"重要广播"NOR+HIY"”" + me->name(1) + WHT"(" + capitalize(me->query("id")) + ")："HIM + arg + "\n"NOR);
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式：shout <讯息>

这个指令让你将 <讯息> 传送出去，所有正在游戏中的人都会听见你的话。

HELP
	);
	return 1;
}

