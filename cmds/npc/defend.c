//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/npc/defend.c
// by bor @DA, 3/17 2003

inherit F_CLEAN_UP;
#include <ansi.h>

int main(object me, string arg)
{
	object ob;

	if( !arg ) return notify_fail("指令格式：defend <某人>。\n");

	if( !objectp(ob = present(arg, environment(me))) )
		return notify_fail("这里没有 " + arg + "。\n");

	if( !ob->is_character() ) return notify_fail("你没办法保护他。\n");

	if( ob == me ) return notify_fail("不用保护自己 !!\n");

	me->guard_ob(ob);
	message_vision(HIY"$N移动到$n前面, 替$n承受攻击。\n"NOR, me, ob);
	return 1;
}

int help (object me)
{
	write(@HELP

指令格式 : defend <对象>

这个指令可以让你保护你的同伴, 把所有对他的直接攻击都接
过来, 但是 对法术性的攻击却帮不上忙了. 你最多可以同时保
护四个人, 不过, 保护 的人越多就越容易分心。你可以保护非
玩家生物(mob) ，但是要等到你是 英雄以后。

相关讯息 : undefend, kill, party

 
HELP
	);
	return 1;
}
