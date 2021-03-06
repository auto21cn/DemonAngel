//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/usr/spells.c
// by bor @DA

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	mapping spell;
	string *sk_name, msg;

	seteuid(getuid());
	if( !arg ) ob = me;
	else {
		if( wizardp(me) ) {	// 如果你是巫师，则可以察看玩家的技能
			arg = lower_case(arg);
			if( !ob = present(arg, environment(me)) )
				ob = find_player(arg);
			if( !ob ) ob = load_player(arg);
			if( !ob ) return notify_fail("没有这位玩家资料。\n");
		} else ob = me;
	}

	if( zerop(spell = ob->query_spells()) )
		return notify_fail( (ob==me?"你":ob->name_id())+"目前并没有学会任何法术。\n");

	sk_name  = keys(spell);

	if( ob == me ) msg = "你目前所学过的法术：\n\n";
	else msg = ob->name_id()+"目前所学过的法术：\n\n";

	for(int i=0 ;i < sizeof(sk_name);i++) {
		msg += sprintf("%-43s%3d\n",to_chinese(sk_name[i])+"("+sk_name[i]+")",
			spell[sk_name[i]] );
	}

	if( !find_player(ob->query("id")) ) destruct(ob);
	reset_eval_cost();
	me->start_more(msg);
	return 1;
}

int help(object me)
{
	write(@HELP
技能查询

指令格式 : spells

这个指令可以让你(你)查询所学过的法术。

相关讯息 : study, list, cost, skills

HELP
	);
	return 1;
}

/*
你目前所学过的法术有：

祝福 (bless)                                90/ 90
镇定术 (calm)                               80/ 80
治疗术 (cure)                               90/ 90
疗毒术 (cure_poison)                        90/ 90
死亡之指 (death_touch)                      90/ 90
破魔 (demon_bane)                           90/ 90
侦测隐形 (detect_invi)                      90/ 90
天使尘 (divine_dust)                        80/ 80
双倍医疗 (double_heal)                      80/ 80
巨大术 (enlarge)                            80/ 80
恐惧术 (fear)                               90/ 90
萤光术 (firefly)                            90/ 90
急救术 (first_aid)                          90/ 90
飞拳术 (fist)                               90/ 90
飘浮 (float)                                90/ 90
冻结术 (freeze)                             90/ 90
迅捷术 (haste)                              80/ 80
朦胧术 (hazy)                               90/ 90
恢复术 (heal)                               90/ 90
神圣爆破 (holy_blast)                       80/ 80
神圣之力 (holy_power)                       80/ 80
神圣精神 (holy_spirit)                      80/ 80
圣水术 (holy_water)                         90/ 90
圣言术 (holy_word)                          90/ 90
鉴定术 (identify)                           90/ 90
造绳术 (make_rope)                          90/ 90
月光术 (moon_light)                         90/ 90
纯洁之盾 (pure_shield)                      80/ 80
复活术 (regeneration)                       90/ 90
强力恢复 (restore)                          90/ 90
圣光术 (sanctuary)                          80/ 80
沈静术 (silence)                            80/ 80
幽灵之触 (spectre_touch)                    90/ 90
加速度 (speedup)                            80/ 80
心灵之锤 (spirit_hammer)                    90/ 90
硬皮术 (stone_skin)                         90/ 90
强壮 (strong)                               90/ 90

你目前所学过的法术：

月夜皓光(moon_light)                         7
自然之乐(nature_music)                       7

*/