//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/npc/recharge.c
// by bor @DA, 5/25 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;
#include <ansi.h>

int main(object me, string arg)
{
	object ob;
	int cost;

	seteuid(getuid());
	if( !me->query_skill("recharge") ) return notify_fail("你不懂封印的技能。\n");
	if( me->is_busy() ) return notify_fail("你上一个动作还没完成。\n");
	if( !arg ) return notify_fail("你要把魔法封印到哪？\n");
	ob = present(arg, me);
	if( !ob ) return notify_fail("你身上没有这样东西。\n");
	if( ob->query_temp("invoke_times")>=10 )
		return notify_fail(ob->name()+"已经蓄满法力, 不能再加强了。\n");

	if( me->query_mp()< 100 ) return notify_fail("你的法力不足以加强封印的力量。\n");

	cost = 45+random(4);
	if( me->query_mp()<cost ) return notify_fail("你的法力不足以加强封印的力量。\n");

	me->add("mp", -cost);
	message_vision(HIY"$N的法力徐徐的慢慢灌入" + ob->name() + "之中。\n"NOR, me);
	me->start_busy(2);
	call_out("recharge", 0, me, ob);
	return 1;
}

int recharge(object me, object ob)
{
	if( ob->query("skill")/23+random(30) > me->query_skill("recharge", 1)*2/3 + me->query_kar()/2 ) {
		ob->add_temp("broken", 20);
		me->add("broken", 20);
		if( ob->query_temp("broken") >= 100 ) {
			message_vision(HIG"$N手中的$n碎成一堆碎片...\n"NOR, me, ob);
			me->delete("broken");
			destruct(ob);
			return 1;
		}
		tell_object(me, ""+ob->name()+"“啪”地一声, 出现了一道裂痕, 法术封印失败了。\n");
		return 1;
	}
	if( ob->query_temp("invoke_times")>=10 ) {
		write(ob->name()+"已经蓄满法力, 不能再加强了。\n");
		return 1;
	}
	ob->add_temp("invoke_times", 1);
	me->add("invoke_times", 1);
	message_vision("$N发出嗡嗡的共鸣音, 然后缓缓地把你的法力吸收进去。\n"NOR, ob);
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : recharge             为手上的法器补充法力。
	   recharge <法器名称>  为法器补充法力。
	   recharge <法术名称>  魔剑士专用，把魔法封入普通的武器中。

法器充电 -

    一个施法者可以利用适当的法器，将自己多余的法力封入其中，使法力转换
成某种特定的法术形态存在于法器中。对法器充电的技能相当重要，如果没有技
能，不仅会浪费法力，同时也会损坏法器本身。

    由于魔剑士对于剑类武器的特殊钻研，使得他们能够随意的把自己知道的法
术与自己的剑结合，进而将任一柄强度足以承受魔法力量的剑暂时变成可怕的魔
法剑，这样的结合型态比一般状况稳定，在法力充入与提出的时刻，就算是失败
也不会使武器损坏，最多也只是储存的法力消失而已。

相关讯息 : invoke, spells


HELP
	);
	return 1;
}
