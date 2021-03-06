//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/usr/kingdoms.c
// by bor @DA

#pragma optimize
#pragma save_binary

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string *str, msg, king;
	int flag;

	seteuid(getuid());
	str = get_dir(KINGDOM_DIR);
	msg = "目前共有 "+sizeof(str)+" 个国家：\n";
	msg += "国家名称                     国王       人口  石阵 简介 连接出口位置\n";
	for(int i=0;i<sizeof(str);i++) {
		king = kingdom_data(str[i], "power", "query_all", "king")[0];
		if(kingdom_data(str[i], "open", "check")) flag += 1;

		msg += sprintf("%-29s%-13s%-5d%-8s%4s%17s\n"NOR,
			to_chinese_kingdom(str[i])+"("+capitalize(str[i])+")",
			king!=""?capitalize(king):"毁损",
			kingdom_data(str[i], "data", "query_par", "people"),
			(kingdom_data(str[i], "other", "query_par", "time_gate")?HIW"开启"NOR:""),
			(kingdom_data(str[i], "other", "query_par", "story")?"有":""),
			(kingdom_data(str[i], "open", "check")? HIW"开放"NOR:"")
		);
	}
	msg += "\n共有 "+flag+" 个国家具有完整的主权。\n";
	me->start_more(msg);
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式: kingdoms

查询所有国家资讯的指令。

HELP
	);
	return 1;
}