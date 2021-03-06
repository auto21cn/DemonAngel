//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/room/barracks.c
// by bor @DA, 5/23 2003

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit ROOM;

void destruct_me( string file );

object env = this_object();

void setup()
{
	seteuid(getuid());
	::setup();
}

void init()
{
	if( wizardp(this_player()) || env->query("kingdom_id") == this_player()->query("kingdom/id") ) {
		if( wizardp(this_player()) || this_player()->query("kingdom/minister")
		|| this_player()->query("kingdom/king")) {
			add_action("do_list", "list");
			add_action("do_garrison", "garrison");
			add_action("do_take", "take");
			add_action("do_dismiss", "dismiss");
		}
	}
}

int do_list(string arg)
{
	object me, ob;
	string *list=({}), msg;
	int tmp=-1;

	me = this_player();

	if( !env->query("data") || !arrayp(env->query("data")) )
		return notify_fail("目前军营空荡荡，并无任何军人驻守于此。\n");

	if( zerop(list = env->query("data")) )
		return notify_fail("目前军营空荡荡，并无任何军人驻守于此。\n");

	msg = "目前的驻军有 :\n";
	for(int i=0; i< sizeof(list); i++) {
		if( file_size(list[i]+".c") ==-1 ) continue;
		tmp = -1;
		if( ob = find_object(list[i]) ) { tmp = 1; }
		else ob = new(list[i]);
		msg += sprintf(" %2d : %s 第 %2d 级驻军 - %s\n", i,
			tmp==1? "[离营]":"[在营]", ob->query("level"), ob->short());
		if( tmp==-1 ) destruct_me(list[i]);
		reset_eval_cost();
	}
	me->start_more(msg);
	return 1;
}

int do_garrison(string arg)
{
	object me, ob;
	mapping room;
	string *list=({});
	int flag = -1;

	me = this_player();

	if( !arg ) return notify_fail("你要招唤哪一位军人回营？\n");
	if( !(ob = present(arg, env))) return notify_fail("没有这个生物 !!\n");
	if( ob->query("level") > 45 ) return notify_fail("军营的生物等级最大只能到 45。\n");
	if( ob->query("type") != "barracks" ) return notify_fail("军营内只能人类军人才能驻守。\n");
	if(  env->query("data") && arrayp(list = env->query("data")) && sizeof(list) >= 30 )
		return notify_fail("这里的军营太拥挤了，不能再驻守人员。\n");

	if( member_array(base_name(ob), list) != -1 ) {
		write(ob->name_id()+"回营驻守了。\n");
		destruct_me(base_name(ob));
		return 1;
	}

	if( !env->query("objects") || zerop(env->query("objects")) )
		return notify_fail("这里不是他的家，不能随便驻守于此 !!\n");

	room = env->query("objects");
	if( sizeof(keys(room))>0 )
	foreach( string npc, int tmp in room ) {
		if( file_size(npc+".c")==-1 ) continue;
		if( base_name(ob)!=npc ) continue;
		if( member_array(npc, list) == -1 ) {
			flag = 1;
			list += ({ npc });
			map_delete(room, npc);
			write(ob->name_id()+"搬到这里来驻守了。\n");
			destruct_me(npc);
		}
	}

	if( flag ==1 ) {
		env->set("data", list);
		if( sizeof(room)>0 ) env->set("objects", room);
		else env->delete("objects");
		do_saveroom(env);
		refresh_room(env);
	} else
		write(ob->name_id()+"的资料有问题, 无法搬到这里驻守!!\n");
	return 1;
}


int do_take(string arg)
{
	int num;
	object me, ob;
	string *list=({});

	me = this_player();

	if( !arg ) return notify_fail("你要招唤那一支军队 ?\n");
	num = atoi(arg);
	if( num == -1 ) return notify_fail("你要招唤那一支军队 ?\n");

	if( !env->query("data") || !arrayp(env->query("data")) )
		return notify_fail("这里没有这支部队。\n");
	if( zerop(list = env->query("data")) ) return notify_fail("这里没有这支部队。\n");
	if( num > (sizeof(list)-1) || num < 0 ) return notify_fail("这里没有这支部队。\n");
	if( find_object(list[num]) ) return notify_fail("这支驻军已经被带出营区了。\n");

	ob = new(list[num]);
	ob->move(env);
	ob->set_temp("barracks", 1);		// 记录他是从军营叫出来的 [不能修改, 不能被 garrison]
	write("你命令"+ob->name(1)+"从营区出来。\n");
	return 1;
}

int do_dismiss(string arg)
{
	int num;
	object me, ob;
	mapping room;
	string *list;

	me = this_player();

	if( !arg ) return notify_fail("你要命令谁解除离营？\n");
	num = atoi(arg);
	if( num == -1 ) return notify_fail("你要命令谁解除离营？\n");
	if( !(list = env->query("data")) || !arrayp(list) )
		return notify_fail("这里并无驻守人员。\n");
	if( num > (sizeof(list)-1) || num < 0 ) return notify_fail("没有这个编号的生物 !!\n");

	if( !env->query("objects") ) env->set("objects", ([]));
	room = env->query("objects");
	if( sizeof(keys(room)) >= 3 ) return notify_fail("这里的生物太拥挤了 !!\n");

	room[list[num]] = 1;
	env->set("objects", room);

	if( !(ob = find_object(list[num])) )
		ob = new(list[num]);

	list -= ({ list[num] });
	if(sizeof(list)>0) env->set("data", list);
	else env->delete("data");

	if( ob->query_temp("barracks") ) ob->delete_temp("barracks");

	do_saveroom(env);
	ob->move(env);
	write("你解除"+ob->name(1)+"在此驻守的命令。\n");

	refresh_room(env);
	return 1;
}

void destruct_me( string file )
{
	object *all;
	all = children(file);
	if( sizeof(all) )
	for(int i=0; i<sizeof(all); i++)
		destruct(all[i]);
	return ;
}
