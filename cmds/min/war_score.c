//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/war_score.c
// by bor @DA, 3/6 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

string age_string(int time);

int main(object me, string arg)
{
	string id, msg="", *war_list;
	mapping war;

	if(!(id= me->query("kingdom/id"))) return notify_fail("你没有国籍不能使用。\n");
	if(!kingdom_data(id, "war", "check")) return notify_fail("贵国目前没有任何一场战争。\n");

	war_list = kingdom_data(id, "war", "query_all");
	for(int i=0; i<sizeof(war_list); i++) {
		if( !mapp( war = kingdom_data(id, "war", "query", war_list[i] ) )) continue;
		msg += full_kingdom(id)+"对"+full_kingdom(war_list[i])+"的战争还剩下 "+age_string(find_object("/cmds/min/declare.c")->query_war_end())+"\n";
		msg += "到目前为止战争结果如下：\n\n";
		msg += "金币数 ：掠夺 " + war["gold"]      + " 枚 / 被掠夺 "+war["gold_"]   +" 枚\n";
		msg += "杀怪数 ：杀敌 " + war["npc"]       + " 只 / 被杀 " + war["npc_"]    +" 只\n";
		msg += "杀敌数 ：杀敌 " + war["enemy"]     + " 人 / 被杀 " + war["enemy_"]  +" 人\n";
		msg += "房间数 ：占领 " + war["room"]      + " 间 / 被占 " + war["room_"]   +" 间\n";
		msg += "建筑物 ：摧毁 " + war["building"]  + " 座 / 被毁 "+ war["building_"]+" 座\n\n";
	}

	me->start_more(msg);
	return 1;
}

string age_string(int time)
{
	int day, hour, minute, sec;

	sec = time % 60;
	time /=60;
	minute = time % 60;
	time /= 60;
	hour = time % 24;
	time /= 24;
	day = time;
	return (day?day+" 天 ":"")+(hour?hour+" 小时 ":"")+minute+" 分 " + sec + " 秒";
}

int help(object me)
{
	write(@HELP

指令格式 : war_score

这是国王与大臣用的指令, 查看战争的进行时间和胜负状况。

HELP
	);
	return 1;
}
