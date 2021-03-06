//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/saveroom.c
// by bor @DA,

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me)
{
	object env;

	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
	if( me->is_fight() ) return notify_fail("你现在战斗中。\n");
	if(!env = environment(me)) return 0;

if( !wizardp(me) ) {
	if( env->query("kingdom_id")!=me->query("kingdom/id") ) return notify_fail("这已经不是我国的领土!!\n");
}
	if( env->query("no_save") || env->query("no_change") )
		return notify_fail("这里有特殊的设定，不能存档。有事请恰管理者来察看。\n");
	do_saveroom(env);
	refresh_room(env);
	write("房间储存完毕。\n");
	return 1;
}

int help(object me) {

	write(@HELP

指令格式 : saveroom

这是贵族用来储存房间性质的指令，当你修改房间叙述、性质时，你可以
藉由此指令达到储存房间的目的。

相关讯息 : delete_room, makeroom

HELP
	);
	return 1;
}
