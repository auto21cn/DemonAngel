//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// unarmed.c

#include <ansi.h>

inherit SKILL;

void skill_improved(object me)
{
	int s;

	s = me->query_skill("force", 1);
	if( s%10==9 && (int)me->query("str") < s/4) {
		tell_object(me, HIW "由于你勤练武艺，你的膂力提高了。\n" NOR);
		me->add("str", 2);
	}
}
