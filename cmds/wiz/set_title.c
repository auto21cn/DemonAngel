//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/wiz/set_title.c
// by bor @DA, 2/23 2003

#include <ansi.h>
inherit F_CLEAN_UP;
 
int main(object me, string str)
{
	string id, title;
	object ob;

	if( !str ) return notify_fail("您要替谁取什么中文名字 ?\n"); 
	if( sscanf(str, "%s %s", id, title)!=2 ) return notify_fail("set_title <玩家> <头衔>\n");
	ob = present(id, environment(me));
	if(!ob) ob = me;
	if(!userp(ob)) return notify_fail("你只能替玩家新增头衔。\n");

	title = ansi_color(title);
	ob->set("title", title + NOR);
	write("Ok.\n"); 
	return 1; 
}
 
int help(object me)
{
	write(@HELP
指令格式: set_title <玩家> <头衔>
 
给予玩家一个超棒的头衔。

HELP
	);
}