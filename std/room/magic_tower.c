//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/room/magic_tower.c
// by bor @DA, 

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit ROOM;

private int spell_next_exp(int level);
private mapping got_list( object me );

mapping MAGE_1 = ([
	"magefire"	:	95,
	"magic_shield"	:	95,
	"wolf"		:	95,
	"coating"	:	95,
	"arc_fire"	:	95,
]);

mapping MAGE_2 = ([
	"fireball"	:	90,
	"magic_missile"	:	90,
	"stun"		:	85,
	"stone"		:	85,
	"storm"		:	85,
	"ogre_power"	:	85,
]);

mapping MAGE_3 = ([
	"mind_blast"	:	80,
]);

mapping CLERIC_1 = ([
	"firefly"	:	95,
	"strong"	:	95,
	"first_aid"	:	95,
	"fist"		:	95,
	"cure"		:	95,
	"heal"		:	95,
]);

mapping CLERIC_2 = ([
]);

mapping CLERIC_3 = ([]);

void init()
{
	add_action("do_list","list");
	add_action("do_study","study");
}

private int do_list(string arg)
{
	string msg="";
	object me = this_player();
	mapping spell=([]);

	spell = got_list(me);

	if( !mapp(spell) || zerop(spell) ) return notify_fail("你的职业没办法学习任何法术。\n");

	msg += "你目前可以学习到的法术有：";
	foreach(string list, int tmp in spell) {
		msg += sprintf("\n%-30s 目前进度 %2d%%, 下次尚需 %6d 点经验值才能升级",
			list, me->query_spell(list,1), spell_next_exp(me->query_spell(list,1)+1) );
	}
	me->start_more(msg+"\n");
	return 1;
}

private mapping got_list( object me )
{
	int learn;
	mapping base_spell=([]);

	switch( me->query("class") ) {
		case "魔法师" :
			learn = me->query_skill("magic", 1);
			if( learn <= 50 ) base_spell = MAGE_1;
			else if( learn >50 && learn <= 70 )
				base_spell = MAGE_1 + MAGE_2;
			else
				base_spell = MAGE_1 + MAGE_2 + MAGE_3;
			return base_spell;
			break;
		case "牧师" :
			learn = me->query_skill("magic", 1);
			if( learn <= 50 ) base_spell = CLERIC_1;
			else if( learn >50 && learn <= 70 )
				base_spell = CLERIC_1 + CLERIC_2;
			else
				base_spell = CLERIC_1 + CLERIC_2 + CLERIC_3;
			return base_spell;
			break;
		default:
			return 0;
	}
	return 0;
}

private int do_study(string arg)
{
	object me = this_player();
	mapping spell=([]);
	string *list=({}), learn_spell;
	int num, my_spell, exp;

	if( !arg || arg == "") return notify_fail("指令格式：study <法术名称>\n");
	arg = lower_case(arg);

	spell = got_list(me);
	if( !mapp(spell) || zerop(spell) ) return notify_fail("你的职业没办法学习任何法术。\n");
	list = keys(spell);
	if( zerop(list) ) return notify_fail("你的职业没办法学习任何法术。\n");

	if( sscanf(arg, "%d %s", num, learn_spell) != 2 ) {
		num = 1;
		learn_spell = arg;
	}
	if( num<1) num = 1;

	if( member_array(learn_spell, list) == -1 ) return notify_fail("目前不开放此法术。\n");

	for(int i=0; i<num; i++) {
		my_spell = me->query_spell(learn_spell, 1);
		if( my_spell >= spell[learn_spell] )
			return notify_fail("很抱歉，你的职业只能训练到目前这种地步。\n");
		if( my_spell>=65 && my_spell >= develop_data(environment(me)->query("kingdom_id"), "query_par", "magic_tower", "dev") )
			return notify_fail("本建筑物发展不足。\n");
		if( my_spell >= me->query_skill("magic",1)*3/2 )
			return notify_fail("你的相关魔法知识不足以理解更高深的法术了。\n");
		if( !me->check_exp(exp = spell_next_exp(my_spell+1)) ) return notify_fail("你的经验值不够。\n");
		me->set_spell(learn_spell, my_spell+1);
		me->pay_exp(exp);
		write("你的"+to_chinese(learn_spell)+"已经学会 "+me->query_spell(learn_spell, 1)+" %%了。\n");
	}
	me->save();
	return 1;
}

private int spell_next_exp(int level)
{
	int exp;
	exp = level*level*15 + level* 3 + 30;
	return exp;
}

/*

mage_magic:

□ 巫师之火(magefire) 
造出一团魔法火焰, 漂浮在魔法师的前方, 以照亮四周。 

□ 弧光指(arc_fire) 
从指尖发出一道闪热电弧, 对敌人造成电击伤害。 

□ 魔法镀膜(coating) 
在武器上镀上一层魔法力场，以增加武器的伤害力。 

□ 飘浮(float) 
使施法者飘浮起来，可以飘过地洞和一些危险的陷阱。 

□ 魔法弹(magic_missle) 
集结一团魔法能量抛向敌人，对敌人造成魔法伤害。 

□ 亚伯拉之盾(magic_shield) 
凝聚周围的空气，形成一道隐形的盾牌。 

□ 造狼术(wolf) 
召唤出一只虚幻的狼，在你的法术有效前，它会尽全力
保护你。 

□ 火球术(fireball) 
唤出火焰精灵的力量，以炽热的火球攻击敌人。 

□ 鉴定术(identify) 
利用寂静的冥思以鉴定出物品的详细性质。 

□ 反魔法力场(anti_magic) 
布下一片可以吸收魔法的力场，可以吸收在力场中所有
人施出的法术。 

□ 电击术(stun) 
制造一个电场，电击所有在电场中的敌人，除了电击的
伤害以外，被电 的敌人还会麻痹一段时间。 

□ 化石术(stone) 
将敌人变成石头，僵化掉的敌人会有一段时间不能动，
不过，相对的， 他的皮也会变得比较硬。 

□ 毒击(poison) 
奸诈的魔法师最喜欢的法术。把邪恶精灵的力量送入敌人
体内，让他中 毒后，再躲在一旁欣赏敌人毒发挣扎的样子。 

□ 冰雪风暴(storm) 
召唤冰雪精灵的力量，制造出一场大型的冰雪风暴，让敌
人饱受刺骨寒 冰的侵袭。 

□ 巨魔之力(ogre_power) 
将自己变成像巨魔般狂暴，会使战斗力大幅提升。 

□ 火龙变幻(dragon) 
把自己转化成一只火龙，并且攻击敌人，在短暂的变身中
，或许有可能 造成敌人无法估计的伤害与恐惧。 

□ 隐身术(invisible) 
这是精灵特有的密法，可以把自己变成透明，以方便秘密
的行动，不过 这个法术有一个缺点，在移动的时候，隐身的力
场会波动，所以会暂时 失去效果。 

□ 召雷术(lightning) 
召唤最强的雷电，轰击所有在场的敌人。这是目前最强的
雷电系法术， 不过只能在户外使用。 

□ 核融合术(flare) 
用大量的魔力制造出小型的黑洞，利用黑洞中心核融合
发出的能量伤害 敌人。是目前所知威力最强的法术，只可惜
核融合难以控制，一但施法 失败，所有的能量会爆发在施法
者身上。 

□ 定位术(location) 
施法者运用大量魔力，在选定的地方留下自己的“念”，
只要念还没散 去，施法者便可以随时追寻着自己的意念，
返回自己选定的地方。 

□ 重力倍增(gravity) 
这是目前发现唯一一个完全无法闪避或减少伤害的法术。
施法者在敌人 四周建立结界，使得身陷其中的敌人感受到重力
增加好几倍，不仅使得 敌人体力不断消耗，同时也使敌人更容
易被击中。对于体积庞大的敌人， 如龙系生物，这个法术有超
乎想像的效果。

cleric_magic:

□ 萤光术(firefly)
向光之神祈祷, 使自己身上布满一层萤光, 以照明四周的
环境。在没有光源的 下水道, 一旦火把用完了, 萤光术就派的
上用场了。 

□ 造绳术(make_rope) 
在通过地洞等地方时, 如果没有带绳钩, 可以用这个法术
造出绳子。虽然是造 出来的绳子, 天下没有白吃的午餐, 你还
是要付钱的。 

□ 急救术(first_aid) 
向慈爱的月神黛妮雅祈祷, 使濒死的人恢复少许的 hp。 
由于只需要花费少许的 法力, 适合较低等级的牧师。 

□ 飞拳术(fist) 
请求战神助你一“拳”之力以打击敌人, 可以造成魔法
伤害。 

□ 飘浮(float) 
会使施法的对象飘浮起来, 以避开地面上的陷阱, 或飘过
地洞, 而不用绳钩。 

□ 祝福(bless) 
向大地之神祈祷, 请求大地之神增强施法对象的战力与
防护力。 

□ 治疗术(cure) 
比急救术高等一点的治疗用法术, 可以多恢复一些 hp 。 

□ 恢复术(heal) 
比治疗术更高级的治疗用法术, 可以恢复 20 点以上的 hp。 

□ 心灵之锤(spirit_hammer) 
请求战神的协助，用战神的雷锤打击敌人的心灵。 

□ 强壮(strong) 
增加受术者的力量以提升战斗力，同时也可以搬更重
的东西。 

□ 硬皮术(stone_skin) 
使受术者的皮肤硬化(石化), 以增加防御力。 

□ 疗毒术(cure_poison) 
把神圣的力量灌入施法对象的身上，以帮助他排除邪
恶力量的侵扰。 

□ 圣水术(holy_water) 
施法者凝聚神圣的力量化成圣水，由指尖对着敌人喷
洒。会对在场的所有敌人造成神圣力量的伤害。这是基本
的破魔法术，对于妖魔有加强的伤害效果。 

□ 冻结术(freeze) 
施法者请求大地之神将在场的所有敌人冻结。这个法
术伤害力不强，但是却会牵绊敌人，使他们的活动能力大
降，而更容易击中。 

□ 鉴定术(identify) 
利用寂静的冥思以鉴定出物品的详细性质。 

□ 强力恢复(restore) 
奉献大量的法力给月神，以交换祂的眷顾。这是强力的
恢复性法术，效率也很好。 

□ 恐惧术(fear) 
请求战神将战争的惨烈和恐惧吹入敌人的心中，使他们
怕得四肢发软、连武器都 握不牢。 

□ 幽灵之触(spectre_touch) 
施法者把自己转化成灵体，藉着碰触敌人的机会吸收他
的生命力，并将之转化成自己的生命力。这是一种极巧妙的
法术，如果遇到法力高的敌人，甚至有可能吸 到他的法力。 

□ 朦胧术(hazy) 
施法者使自己变成朦朦胧胧的一片，敌人便不容易击中
，这是相当有效的防御性 法术。 

□ 月光术(moon_light) 
这是一个在攻与守两方面都能兼顾的法术。施法者请求
月神戴妮雅的帮助，使柔和的月光洒在敌人与施法者身上，
月神的神力会吸取敌人的生命力转化为医疗魔法医治施法者。
这个法术的医疗效果并不比强力恢复差，唯一的缺点是只能在
月光照得到的地方使用。 

□ 破魔(demon_bane) 
这世高级的破魔法术，比圣水术更强大，不过只能针对
一个敌人。 

□ 死亡之指(death_touch) 
这是一个高难度但却有最高效率的法术，施法者请求死
神降临，带走敌人的灵魂。如果死神答应了你的要求，就算
是再强大的敌人也会立刻倒地死去。 

□ 复活术(regeneration) 
这是世界上最高难度但是也是最受崇拜的法术。施法者
奉献大量的法力给死神，藉以换取一个迷失的灵魂。如果死
神答应他的要求，那么已经死去的人就会得到 一副全新的身
体，就像不曾死过一样。 

□ 圣言术(holy_word) 
这是最强力的破邪法术，对妖魔的伤害力甚至胜过世上
一切已知的法术。施法者运用神圣的咒语打击一切邪恶的敌
人，如果施法者本身法力高强，甚至可以使敌人没命的逃窜
，直到死为止。

*/