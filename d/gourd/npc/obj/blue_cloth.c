//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /d/gourd/npc/obj/blue_cloth.c

#include <armor.h>
#include <ansi.h>
inherit CLOAK;

void create()
{
	set_name("蓝布长衫", ({ "blue cloth", "cloth" }) );
	set_weight(200);

	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "件");
		set("value", 600);
		set("long", "一件粗布缝制的布衣，看起来像是乡下姑娘的衣服。\n");
		set("wear_as", "cloth");
//		set("apply_armor/cloth", ([
//			"armor": 2,
//		]));
		setup();
	}
	setup();
}
