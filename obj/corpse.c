//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /obj/corpse.c

inherit ITEM;

void create()
{
	set_name("尸体", ({ "corpse" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
//		set("long", "发出一阵一阵恶臭的尸体。\n");
		set("unit", "具" );
	}
	setup();
}

int is_corpse() { return 1; }
string short() { return name()+"("+capitalize(query("id"))+")"; }

int receive_object(object oob, int from_inventory) { return 1; }
