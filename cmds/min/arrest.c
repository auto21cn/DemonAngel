//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/arrest.c
// by sbada @RG

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

#include <ansi.h>

#define ARR_COST	5000

int main(object me, string arg)
{
	string *list, msg ="", tar;
	object ob;

	seteuid(getuid(me));
	if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
	if( me->is_fight() ) return notify_fail("你现在在战斗中。\n");
	if( !arg ) {
		if( !arrayp(list = kingdom_data(me->query("kingdom/id"), "arrest", "query_all")) ) return notify_fail("\n贵国目前并没有通缉人。\n");
		msg += "贵国现在正通缉着 :\n";
		for( int i=0; i<sizeof(list); i++ ) {
			msg += sprintf("\t%-16s  通缉时间 %s\n", list[i],
				kingdom_data(me->query("kingdom/id"), "arrest", "query_par", list[i])
			);
		}
		msg += "\n";
		me->start_more(msg);
		return 1;
	}

	// 取消通缉
	if(sscanf( arg, "%s cancel", tar ) == 1) {
		if( !(ob = find_player(tar)) ) ob = load_player(tar);
		if( !ob ) return notify_fail("这个人已经不存在。\n");
		if( !kingdom_data(me->query("kingdom/id"), "arrest", "sub", tar) ) return notify_fail("\n贵国目前并没有通缉人。\n");
		if( arrayp(list = ob->query("arrest")) ) {
			if( member_array(me->query("kingdom/id"), list)!=-1 )
				ob->set("arrest", list - ({me->query("kingdom/id")}) );
			if( zerop(ob->query("arrest"))) ob->delete("arrest");
			ob->save();
		}
		write(HIY"我 -- " + to_chinese_kingdom(me->query("kingdom/id")) + (me->query("kingdom/king")?"国王":"大臣")+ NOR + me->short() + "为" + ob->short(1) + "发布特赦令．．．\n"
		"即日起宽恕他所犯的一切罪行，并取消对他的通缉令。\n" );
		shout(HIY"我 -- " + to_chinese_kingdom(me->query("kingdom/id")) + (me->query("kingdom/king")?"国王":"大臣")+ NOR + me->short() + "为" + ob->short(1) + "发布特赦令．．．\n"
		"即日起宽恕他所犯的一切罪行，并取消对他的通缉令。\n" );
		if(!find_player(tar)) destruct(ob);
		return 1;
	}
	// 通缉
	if( !ob = find_player(arg) ) return notify_fail("没有这个人或是他不在线上 !\n");
	if( !userp(ob) ) return notify_fail("他不是一位玩家。\n");
	if( me == ob ) return notify_fail("你不能通缉自己。\n");
	if( ob->query("kingdom/king") && ob->query("kingdom/id")==me->query("kingdom/id") ) return notify_fail("国王不能被通缉。\n");
	if( !me->can_afford(ARR_COST*ob->query("level")) ) return notify_fail("你身上没有足够的钱发通缉。\n");
	if( kingdom_data(me->query("kingdom/id"), "data", "query_par", "gold") < ARR_COST * ob->query("level") * 2 ) return notify_fail("国库中没有足够的钱。\n");
	if( kingdom_data(me->query("kingdom/id"), "arrest", "check", arg) ) return notify_fail("这个人已被贵国通缉了。\n");
	if( sizeof(kingdom_data(me->query("kingdom/id"), "arrest", "query_all"))>=3 ) return notify_fail("最多只能同时通缉三人。\n");
	if(!kingdom_data(me->query("kingdom/id"), "arrest", "add", arg)) return notify_fail("贵国资料错误，无法写入。\n");

	if( arrayp(list = ob->query("arrest")) ) {
		if( member_array(me->query("kingdom/id"), list)==-1 )
			ob->set("arrest", list + ({me->query("kingdom/id")}) );
	} else ob->set("arrest", ({me->query("kingdom/id")}) );
	ob->save();
	me->pay_money(ARR_COST * ob->query("level") );
	me->save();
	kingdom_data(me->query("kingdom/id"), "data", "gold", "sub", ARR_COST * ob->query("level")* 2 );

	write(HIY + "我 - "+to_chinese_kingdom(me->query("kingdom/id")) + "的" + (me->query("kingdom/king")?"国王":"大臣") +" -- " + me->short() + "发布了" + ob->short() + "的通缉令．．．\n"NOR
	"即日起全面追缉" + ob->short() + "死活不论。\n" );
	shout(HIY + "我 - "+to_chinese_kingdom(me->query("kingdom/id")) + "的" + (me->query("kingdom/king")?"国王":"大臣") +" -- " + me->short() + "发布了" + ob->short() + "的通缉令．．．\n"NOR
	"即日起全面追缉" + ob->short() + "死活不论。\n" );
        return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : arrest <某人> <cancel>

这是贵族行使权力一个种方法，不过最好不要滥用通缉的权力，
否则可能会招来

相关讯息 : die, 

HELP
	);
	return 1;
}

