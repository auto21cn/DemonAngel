//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// halt.c

#include "/doc/help.h"
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	if( !me->is_fighting() )
		return notify_fail("你现在并没有在战斗。\n");
	me->remove_all_killer();
	message_vision("$N用巫师的神力停止了这场打斗。\n", me);
	write("Ok.\n");
	return 1;
}

int help(object me)
{
   write(@HELP
指令格式: halt

可以停止所有与你(你)有关的战斗。
HELP
   );
   return 1;
}
