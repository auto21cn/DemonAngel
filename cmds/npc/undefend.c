//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/npc/undefend.c
// by bor @DA,

inherit F_CLEAN_UP;

#include <ansi.h>

int main(object me, string arg)
{
	object ob;

	seteuid(getuid());
	if(!arg) return notify_fail("指令格式 : undefend <对象>\n");
	ob = present(arg, environment(me));
	if( !ob ) return notify_fail("这里没有这个人。\n");
	if( member_array(ob, me->query_guarding()) == -1 )
		return notify_fail("你现在并没有保护任何人。\n");

	me->sub_guard(ob);
	message_vision(HIY"$N停止保护$n。\n"NOR, me, ob);
	return 1;
}

int help (object me)
{
	write(@HELP

指令格式 : undefend <对象>

如果你已经不想保护某人了, 你可以用这个指令停止保护他.

相关讯息 : defend, party, kill. 

 
HELP
	);
	return 1;
}
