//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /feature/irc.c
// by bor @ RG, 1/22, 2002
// 记得在 globals.h 内定义 #define F_IRC "/feature/irc"
// 在 /std/char.c 内补上继承 inherit F_IRC; 
// ver: 1.0

#include <ansi.h>
#include <dbase.h>
#include <origin.h>
#include <command.h>

static object *irc_team;
static string irc_color;

int add_irc_team_member(object ob)
{
	object member;

	if( arrayp(irc_team) ) {
		if( member_array(ob, irc_team)==-1 ) irc_team += ({ ob });
	} else {
		irc_team = ({ this_object(), ob });
	}

	foreach(member in irc_team) member->set_irc_team(irc_team);
	return 1;
}

int is_irc_team_leader()
{
	return arrayp(irc_team) && irc_team[0]==this_object();
}

// 检查该玩家是否是自己 irc 内一员
int is_irc_team_form(object ob)
{
	return member_array(ob, irc_team)!=-1;
}

int set_irc_team(mixed t)
{
	irc_team = t;
}

int set_irc_form()
{
	irc_team = ({ this_object() });
	irc_color = CHINESE_D->ansi_color(HIC);
}

string query_irc_color()
{
	if( irc_color ) {
		return irc_color;
	} else return HIC;
}

string set_irc_color( string arg )
{
	irc_color = CHINESE_D->ansi_color(arg);
}

varargs int dismiss_irc_team(object ob)
{
	int i;
	object member;

	if( !arrayp(irc_team) ) return 0;
    
	if( irc_team[0]==this_object() ) {
		if( objectp(ob) ) {	// 电台主人禁止某位玩加收听
			irc_team -= ({ ob });
			foreach(member in irc_team) member->set_irc_team(irc_team);
			ob->set_irc_team(0);
		} else {
			// 电台结束
			foreach(member in irc_team) {
				member->set_irc_team(0);
			}
			irc_team = 0;
		}
	} else {
		// 玩家离开某电台
		irc_team -= ({ this_object() });
		foreach(member in irc_team) member->set_irc_team(irc_team);
		irc_team = 0;
	}
	return 1;
}

object *query_irc_team()
{
	return irc_team;
}

