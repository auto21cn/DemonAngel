//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/room/post_office
// by bor @RG

#pragma optimize
#pragma save_binary

#include <ansi.h>
inherit ROOM;

void init()
{
	add_action("do_search","search");
}

int do_search(string arg)
{
	object obj, me;
	me = this_player();

	if( !arg || arg!="mailbox" ) {
		message_vision("$N在这里到处乱找，但是什么都找不到。\n", me);
		return 1;
	}
	if( me->query_temp("mail") ) {
		message_vision("$N在这里到处乱找，但是什么都找不到。\n", me);
		return 1;
	}
	message_vision("[1;30m$N从信箱堆中找出自己的信箱。\n[m", me);
	obj = new("obj/mailbox");
	obj->move(me);
	me->set_temp("mail", 1);
	return 1;
}

int valid_leave(object me)
{
	object obj;
	if( me->query_temp("mail") ) {
		obj = present("mailbox", me);
		me->delete_temp("mail");
		message_vision("$N把信箱丢回信箱堆中。\n", me);
		destruct(obj);
	}
	return 1;
}