//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/npc/invoke.c
// by bor @DA, 5/24 2003

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit F_CLEAN_UP;
int check_wp_type(string type);

int main(object me, string arg)
{
	object wp_ob, tar;
	string wp, ppl, magic;

	seteuid(getuid());
	if( !me->query_skill("invoke", 1) ) return notify_fail("你不会这项技能．\n");
	if( me->is_busy() ) return notify_fail("你的动作还没有完成，不能启动封印。\n");
	if( !arg ) return notify_fail("语法 : invoke <法器> on <对象>\n");
	if( sscanf(arg, "%s on %s", wp, ppl) == 2 ) {
		tar = present( ppl, environment(me) );
		wp_ob = present( wp, me );
		if( !tar ) return notify_fail("附近没有这个人．\n");
	} else {
		tar = me;
		wp_ob = present( arg, me );
	}

	if( !wp_ob ) return notify_fail("你身上没有这把武器．\n");
	if( !wp_ob->query("equipped") ) return notify_fail("你并无装备这武器．\n");
	if( !check_wp_type(wp_ob->query("type")) ) return notify_fail("这把武器，不能经由invoke而解开封印．\n");
	if( !(magic = wp_ob->query("invoke_magic")) ) return notify_fail("这把武器没有任何封印．\n");
	if( wp_ob->query_temp("invoke_times") < 1 ) return notify_fail("这把武器的封印已耗尽了...\n");

	if( environment(me)->query_temp("no_cast") || environment(me)->query("no_cast") )
		return notify_fail("这里不能施法。\n");

	if( file_size(SPELL_D(magic)+".c")==-1 ) return notify_fail("没有这样的封印 !!\n");

	SPELL_D(magic)->invoke(me, tar, wp_ob);
	return 1;
}

int check_wp_type(string type)
{
	switch(type) {
		case "wand":
		case "staff":
			return 1;
			break;
		default:
			return 0;
	}
	return 0;
}

int help(object me)
{
	write(@HELP

指令格式 : invoke <法器名称> on <对象>

法器使用 -

    在这个世界上，法师们常在闲暇时将多余的法力封入特定的法器中，以备不时
之需。而 invoke 就是可以把这些封印的力量释放出来的技能和指令。解开封印的
力量须要耗费一定法力，一个完全不懂法器使用技巧的人还是有机会可以引出封印
的力量，但是不仅要多消耗很多法力，同时还有很大的机会造成法器的损坏，当法
器坏得不能在用后，封存在里面的力量就随之而去了。

相关讯息 : recharge, skills, spells

HELP
	);
	return 1;
}
