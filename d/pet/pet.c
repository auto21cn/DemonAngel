//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /obj/pet/pet.c
// by bor @DA, 3/11 2003

inherit NPC;

#include <ansi.h>
#include <pet.h>

void create()
{
	set_name("恶龙", ({"bad dragon", "dragon", "bad"}));
	set("race", "野兽");
	set("level", 3);
	set("limbs", ({ "头部", "身体", "前爪", "后腿", "尾巴" }) );
	set("verbs", ({ "bite"}));
	set("unit", "只");
	set("value", (: query("level")*query("level")*3000 :));

//	set("owner", "bor");

	set_temp("pet/damage", 2);
	set_temp("pet/armor", 2);

	set_temp("pet/file", base_name(this_object()) );

	set_temp("pet/kee", query("level")*10+random(30) );	// 设定"气", 可以用来 charge 的, 预留一下
	set_temp("apply/kee", query_temp("pet/kee") );

	setup();
}

void init()
{
	add_action("do_mount", "mount");
	add_action("do_feed", "feed");
}

int is_pet() { return 1; }