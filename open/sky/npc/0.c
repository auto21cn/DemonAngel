//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
//npc : /open/sky/npc/0.c
//create by pawlo     Mon Mar 10 20:59:54 2003

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("居民",({ "tavern", "taver", "tave", "tav", "ta", "t" }));
	set("long","他是一名一级的居民
");
	set("int",1);
	set("dex",1);
	set("con",1);
	set("level",1);
	set("type","tavern");
	set("owner","pawlo");
	set("kingdom","sky");
	set("gender","男性");
	set("unit","无");
	set("chasing",0);
	set("reward",0);
	set("no_corpse",0);
	set("wimpy",0);
	set("die_msg",0);

	setup();}
