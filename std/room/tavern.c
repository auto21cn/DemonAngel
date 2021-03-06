//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/room/tavern.c
// by bor @DA

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit ROOM;

void setup()
{
	seteuid(getuid());
	::setup();
}

void init()
{
	add_action("do_check_in","check_in");		// 补充体利用的
	add_action("do_list", "list");			// 检查这里的发展如何
}

int do_check_in(string arg)
{
	object me, rest_room;

	me = this_player();

	if( !me->can_afford(50) ) return notify_fail("你的钱不够。\n");

	me->add("gold", -50);

	message_vision(HIY"$N付了钱, 走进了他的房间。"+NOR+"\n", me);
	rest_room = new("/obj/rest.c");
	rest_room->set("exits/out", base_name(environment(me)) );
	me->move(rest_room);
	return 1;
}

int do_list()
{
	string msg;

	msg = "旅馆目前的发展为 :\n";

	msg += "\t"+develop_data(environment(this_player())->query("kingdom_id"), "query_par", "tavern", "dev")+"\n";

	write(msg);
	return 1;
}
