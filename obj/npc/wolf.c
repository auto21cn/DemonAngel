//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /obj/npc/wolf.c

inherit NPC;

void create()
{
	set_name("魔狼", ({ "magic wolf", "magic", "wolf"}) );
	set("race", "野兽");
	set("long", @TEXT
你看见一只有着棕色皮毛和尖锐犬齿的大狼, 牠是由魔法师用魔法
造出的幻狼, 只为保护牠的主人而战。
TEXT
	);
	set("level", 5+random(2));

	add_temp("apply/damage", query("level"));

	setup();
}

void die()
{
	object ob;
	if( objectp( ob = query_temp("owner")) ) {
		this_object()->remove_guard(ob);
		this_object()->set_leader(0);
	}
	::die();
}
