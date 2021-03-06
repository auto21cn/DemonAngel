//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /d/obj/gift/red_bag.c
// by bor @DA, 3/5 2003

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIR"红包袋"NOR, ({"red bag","red","bag"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long","你可以试着打开(open bag)它或者存放(put xxx)金币到红包内。\n");
		set("value", 50);
		set("unit", "封");
		set("new", 1);
	}
	setup();
}

void init()
{
	if(userp(this_player())) {
		add_action("do_open","open");
		add_action("do_put","put");
	}
}

int do_open(string str)
{
	object me = this_player();

	if( !query("gold") ) return notify_fail("这是一个空的红包袋。\n");

	message_vision("$N将红包拆开来, 结果里面放满 "+query("gold")+" 枚金币。\n", me, this_object() );

	me->got_money(query("gold"));
	destruct(this_object());
	return 1;
}

int do_put(string str)
{
	int num;
	object me = this_player();

	num = atoi(str);
	if(num==-1) return notify_fail("目前只能存放金币。\n");
	if( !this_object()->query("new") ) return notify_fail("里面已经放置金币了。\n");
	if(num<100) return notify_fail("至少要存个一百枚金币才够看吧。\n");
	if(num>200000) return notify_fail("大红包最多只能包个二十万，否则红包纸会撑破。\n");
	if(!me->can_afford(num)) return notify_fail("你身上没有么多钱可以放进红包袋内。\n");

	this_object()->set("gold", num);
	this_object()->delete("new");

	me->pay_money(num);

	message_vision("$N将红包拆开来, 随手将 "+num+" 枚金币封进红包内。\n", me, this_object() );

	return 1;
}