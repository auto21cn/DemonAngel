//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
#include <armor.h>
#include <ansi.h>
inherit RING;
void create() {
	set_name("戒指", ({"ring"}) );
	set_weight(10); 
	set("new", 1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
一件天空打造出来的戒指。
LONG);
		set("armor_prop/ac",3);
		set("armor_prop/db",3);
		set("type","ring");
		set("level",30);
		set("owner","pawlo");
		set("kingdom","sky");
		set("unit","件");
	}
	setup();
}
