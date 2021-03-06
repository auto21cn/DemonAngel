//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/npc/charge.c
// by bor @DA, 3/17 2003

// 目前提供给座骑用而已，如果有职业需要此指令，请另外写...
// 一时忘记，我当初写座骑是把他移到别格去, 那么此指令就不能用了

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object guard, ob;

	if( !me->query("list/pet/file") ) return 0;
	if( !me->query_temp("riding_pet") ) return 0;

	if( !objectp( guard = find_object(me->query("list/pet/file")) ) ) {
		call_other(me->query("list/pet/file"), "???");
		guard = find_object(me->query("list/pet/file"));
	}
	if( !arg || arg=="" ) return notify_fail("你没有选定攻击目标。\n");

	ob = present(arg, environment(me));
	if( !ob ) return notify_fail("这里没有这个人。\n");

	if( !me->is_fighting(ob) )
		return notify_fail("你目前没有和" + ob->name() + "战斗。\n");

	guard->charge_ob(ob);

	return 1;
}

int help(object me)
{
	write(@TEXT

指令格式 : charge <目标>

这是骑士的特殊指令，如果你有骑马的话，可以快速的冲向
敌人，使敌人 受到严重的撞击而受重伤。如果敌人是骑在马
上或是任何坐骑上，可能因受到冲击而坠落地上。

其他相关指令: kill, advance_class, warrior_adv


TEXT
	);
	return 1;
}
