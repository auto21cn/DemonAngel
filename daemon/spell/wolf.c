//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /daemon/spell/wolf.c
// by bor @DA
/*
□ 造狼术(wolf)
   召唤出一只虚幻的狼，在你的法术有效前，它会尽全力保护你。

> 你喃喃唸道 : 梅加梅尔 ～～ 凯特 ...
> 一颗光点由你的掌中飞出落在地上, 眨眼间变成一头恶狼 ...
魔狼开始跟踪你。
魔狼移动到你前面，替你承受攻击。

l wo
你看见一只有着棕色皮毛和尖锐犬齿的大狼, 牠是由魔法师用魔法
造出的幻狼, 只为保护牠的主人而战。
牠正处于最佳状况, 没有受伤。
> 你的魔狼突然闪了一闪, 消失了。
魔狼停止保护你。
魔狼停止跟踪你。

*/

#include <ansi.h>

inherit SKILL;

int cast_spell(object me, object target)
{
	if( (int)me->query_mp() < 20 ) return notify_fail("你的法力不够！\n");

	me->add("mp", -10);
	me->start_busy(1);
	message_vision(HIC+"$N喃喃唸道 : 梅加梅尔 ～～ 凯特 ...\n"NOR,me);
	target = new("/obj/npc/wolf");
	call_out("wolf", 0, me, target);
	return 1;
}

int wolf(object me, object target)
{
	if( random( 40 ) > me->query_skill("cast",1)*2/3 + me->query_kar()*4 ) {
		message_vision("$N施法失败了。\n", me);
		destruct(target);
	} else {
		call_out("remove_wolf", 200, me, target);
		message_vision(HIY"一颗光点由$N的掌中飞出落在地上, 眨眼间变成一头恶狼 ...\n"NOR, me);
		target->move(environment(me));
		target->set_leader(me);
		message_vision("$N决定开始跟随$n一起行动。\n", target, me);
		target->guard_ob(me);
	}
	return 1;
}

int remove_wolf(object me, object target)
{
	if(!target) return 1;
	if(me) message_vision(HIY"$N的魔狼突然闪了一闪, 消失了。\n"NOR, me);
	if(target) target->set_leader(0);
	me->remove_guard(target);
	destruct(target);
	return 1;
}

int invoke(object me, object target, object wp)
{
	if( (int)me->query_mp() < 20 ) return notify_fail("你的法力不够！\n");
	if( !wp ) return notify_fail("你身上没有这种东西。\n");
	if( wp->query_temp("invoke_times") < 1 ) return notify_fail("这把武器的封印已耗尽了...\n");

	me->add("mp", -10);
	me->start_busy(1);
        message_vision(HIY"$N专心启动$n中封印的力量...\n\n"NOR, me, wp);
	wp->add_temp("invoke_times", -1);
	target = new("/obj/npc/wolf");
	call_out("check_wand", 0, me, target, wp);
	return 1;
}

int check_wand(object me, object target, object wp)
{
	if( random(40) > (me->query_skill("invoke",1)*2/3 +me->query_kar()*4) ) {
		message_vision(HIG"$N启动封印失败, $n出现一道裂痕\n"NOR, me, wp);
		wp->add_temp("broken", 20);
		destruct(target);
		return 1;
	}
	if( wp->query_temp("broken") >= 100 ) {
		message_vision(HIG"$N手中的$n碎成一堆碎片...\n", me, wp);
		destruct(wp);
		destruct(target);
	} else {
		call_out("remove_wolf", 200, me, target);
		message_vision(HIY"一颗光点由$N的掌中飞出落在地上, 眨眼间变成一头恶狼 ...\n"NOR, me);
		target->move(environment(me));
		target->set_leader(me);
		message_vision("$N决定开始跟随$n一起行动。\n", target, me);
		target->guard_ob(me);
	}
	return 1;
}
