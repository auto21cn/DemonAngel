//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /daemon/spell/first_aid.c
// by bor @DA
// 急救术(first_aid)
/*
cast first_aid
你低头喃喃唸道 : 慈爱之神黛妮雅啊 ... 请帮助您的信徒吧 !
> 你的身上泛起一环圣光, 然后渐渐淡去 ...

*/

#include <ansi.h>

inherit SKILL;

int cast_spell(object me, object target)
{
	if( !target ) target = me;
	if( (int)me->query_mp() < 20 ) return notify_fail("你的法力不够！\n");

	me->add("mp", -10);
	me->start_busy(1);
	message_vision(HIC+"$N低头喃喃唸道 : 慈爱之神黛妮雅啊 ... 请帮助您的信徒吧 !\n"NOR, me);
	call_out("first_aid", 0, me, target);
	return 1;
}

int first_aid(object me, object target)
{
	if( random( 40 ) > me->query_skill("cast",1) *2/3 + me->query_kar()*4 ) {
		message_vision("$N施法失败了。\n", me);
	} else {
		// 最后在判定一次对方是否在本格
		if(!target||environment(target)!=environment(me)) {
			write("你的目标已经跑掉了。\n");
			return 1;
		}
		if( target->query_hp()<=0 ) target->set("hp", 1);
		else target->receive_heal("hp", 5+random(2) );
		message_vision(HIY"$N的身上泛起一环圣光, 然后渐渐淡去 ...\n"NOR, target);
	}
	return 1;
}

int invoke(object me, object target, object wp)
{
	if( !target ) target = me;
	if( (int)me->query_mp() < 20 )  return notify_fail("你的法力不够！\n");
	if( !wp ) return notify_fail("你身上没有这种东西。\n");
	if( wp->query_temp("invoke_times") < 1 ) return notify_fail("这把武器的封印已耗尽了...\n");

	me->add("mp", -10);
	me->start_busy(1);
        message_vision(HIY"$N专心启动$n中封印的力量...\n\n"NOR, me, wp);
	wp->add_temp("invoke_times", -1);
	call_out("check_wand", 0, me, target, wp);
	return 1;
}

int check_wand(object me, object target, object wp)
{
	if( random(40) > (me->query_skill("invoke",1)*2/3 +me->query_kar()/4) ) {
		message_vision(HIG"$N启动封印失败, $n出现一道裂痕\n", me, wp);
		wp->add_temp("broken", 20);
		return 1;
	}
	if( wp->query_temp("broken") >= 100 ) {
		message_vision(HIG"$N手中的$n碎成一堆碎片...\n", me, wp);
		destruct(wp);
	} else {
		// 最后在判定一次对方是否在本格
		if(!target||environment(target)!=environment(me)) {
			write("你的目标已经跑掉了。\n");
			return 1;
		}
		if( target->query_hp()<=0 ) target->set("hp", 1);
		else target->receive_heal("hp", 5+random(2) );
		message_vision(HIY"$N的身上泛起一环圣光, 然后渐渐淡去 ...\n"NOR, target);
	}
	return 1;
}
