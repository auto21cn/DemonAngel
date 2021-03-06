//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/set_long.c
// by bor @RG

#pragma optimize
#pragma save_binary

#include <ansi.h>

int main(object me, string arg)
{
	object env;
	seteuid(getuid(me));
	if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
	if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");
	if( !env = environment(me)) return notify_fail("找不到环境。\n");
	if( env->query("no_change") ) return notify_fail("这里不能变更房间的资料。\n");
	if( !me->query("kingdom/id")) return 0;
	if( env->query("kingdom_id")!=me->query("kingdom/id") ) return notify_fail("这里不是我国的领地了\n");

	me->edit( (: call_other, __FILE__, "do_change", me :) );
	return 1;
}

void do_change(object me, string str)
{
	string *str_arg;

	str = ansi_color( str );

	if( strlen(str) > 8000 ) {
		write("你的参数太长了。\n");
		return;
	}
	str_arg = explode(str, "\n");

	if( sizeof(str_arg) > 10 ) {
		write("请控制在十行以内。\n");
		return;
	}
	str = kill_all_bug(str);
	environment(me)->set("long", str);
	write("ok!\n");

	do_saveroom(environment(me));
	return ;
}

int help()
{
	write(@HELP

指令格式：set_long

这是贵族用来修饰房间叙述的指令。

HELP
        );
        return 1;
}
