//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// home.c

#include "/doc/help.h"

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string msg, to;

	if( !arg ) {
		if( file_size(to = user_path(geteuid(me)) + "workroom.c") <= 0 )
			return notify_fail("你没有自己的工作室。\n");
//		to = user_path(geteuid(me)) + "workroom";
	} else if( arg == "wiz") {
		to = "/d/wiz/hall1";
	} else return notify_fail("你要回哪？\n");

	if( stringp(msg = me->query("env/msg_home")) ) message_vision(msg + "\n", me);

	me->move(to);
	return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : home

利用此一指令可直接回到自己的工作室。
如果你有 'msg_home' 这个设定, 则在场的人都会看到那个讯息.
home wiz 可以回到公开的  wiz board。请不要 summon 非 wiz进去。
HELP
    );
    return 1;
}
