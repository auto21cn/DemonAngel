//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /daemon/spell/stone.c
// by bor @DA

#include <ansi.h>

inherit SSERVER;

int cast_spell(object me, object target)
{
	if( me->is_busy() ) return notify_fail("你正忙着。\n");
	if( !target ) {
		if( !(target = offensive_target(me)) )
			return notify_fail("找不到任何目标!!\n");
	}
	if( target == me ) return notify_fail("你要有目标才能施法。\n");
	if((int)me->query_mp() < (80+me->query_base_mp()/8) ) return notify_fail("你的法力不够！\n");

	me->add("mp", -(40+me->query_base_mp()/8));
	me->start_busy(2);
	message_vision(HIC"$N喃喃念道 : 凯特 ～ 赛尔梅尔 ...\n"NOR, me);
	call_out("stone", 1, me, target);
	return 1;
}

int stone(object me, object target)
{
	if( random( 60 ) > me->query_skill("cast",1)*2/3 + me->query_kar()*4 ) {
		message_vision("$N施法失败了。\n", me);
	} else {
		target->start_busy(5);
		me->kill_ob(target);
		target->kill_ob(me);
		message_vision(HIY"$N手指往$n一指，把$n变成石头。\n"NOR, me, target);
	}
	return 1;
}

int invoke(object me, object target, object wp)
{
	if( !target ) {
		if( !(target = offensive_target(me)) )
			return notify_fail("找不到任何目标!!\n");
	}
	if( target == me ) return notify_fail("你要有目标才能施法。\n");
	if((int)me->query_mp() < (80+me->query_base_mp()/8) ) return notify_fail("你的法力不够！\n");
	if( !wp ) return notify_fail("你身上没有这种东西。\n");
	if( wp->query_temp("invoke_times") < 1 ) return notify_fail("这把武器的封印已耗尽了...\n");

	me->add("mp", -(40+me->query_base_mp()/10));
	me->start_busy(2);
        message_vision(HIY"$N专心启动$n中封印的力量...\n\n"NOR, me, wp);
	wp->add_temp("invoke_times", -1);
	call_out("check_wand", 1, me, target, wp);
	return 1;
}

int check_wand(object me, object target, object wp)
{
        if( !wp ) {
                write("你身上没有武器 !!\n");
                return 1;
        }
	if( random( 50 ) > me->query_skill("cast",1)*2/3 + me->query_kar()*4 ) {
		message_vision(HIG"$N启动封印失败, $n出现一道裂痕\n", me, wp);
		wp->add("broken", 20);
		return 1;
	}
        if( wp->query("broken") >= 100 ) {
		message_vision(HIG"$N手中的$n碎成一堆碎片...\n", me, wp);
		destruct(wp);
        } else {
		target->start_busy(5);
		me->kill_ob(target);
		target->kill_ob(me);
		message_vision(HIY"$N手指往$n一指，把$n变成石头。\n"NOR, me, target);
	}
	return 1;
}
