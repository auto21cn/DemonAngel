//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /daemon/condition/magic_shield.c

#include <ansi.h>
#include <condition.h>

int update_condition(object me, int time)
{
	if(time <= 0) {
		me->add("apply/ac", -12);
		me->add("apply/db", -8);
		message("vision",HIY+gender_self(me->query("gender"))+"的魔法盾消失了。\n"NOR, me);
		message("vision",HIY+me->name(1)+"的魔法盾消失了。\n"NOR, environment(me), me);

		return 0;
	}
	else me->apply_condition("magic_shield", time - 1);
	return 1;
}
