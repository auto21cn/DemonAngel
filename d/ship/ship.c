//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /d/ship/ship.c
// by bor @DA, 2/24 2003

#include <ansi.h>
inherit SHIP;

void create()
{
	set("short", "铁壳船(Iron Ship)" );
	set_name("铁壳船", ({ "Iron Ship", "iron", "ship" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @TEXT
你看到一个破旧的铁制的船只，不少人看着它都不禁摇头不敢
搭乘，宁可绕远路搭乘别的船只，也不愿意靠近，生怕所坐的船只
在半路上触礁而沉没。
TEXT
	);
		set("type", "ship");
		set("port1", "/d/gourd/ship_port.c");	// 系统港口
		set("port2", "/open/test/1.c");		// 国家港口
		set("max_load", 15);			// 预留一下
		set("value", 1);
		set("unit","艘");
		set("no_kill", 1);
		set("no_get", 1);
		set("kingdom_id", "test");		// 哪一国家的船只
	}
	setup();
}
