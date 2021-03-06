//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/adm/delete_kingdom.c
// by bor @RG

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string name, *channeld_ch;
	object *list;
	int i;

	if(!wizardp(me)) return notify_fail("你没有权力使用这个指令。\n");
	if( !arg || arg =="") return notify_fail("指令格式：delete_kingdom <国家名称>\n");
	seteuid(getuid());
	if( !check_kingdom(arg) ) return notify_fail("指令格式：delete_kingdom <国家名称>\n");

	name = full_kingdom(arg);

	list = users();
	i = sizeof(list);
	while( i-- ) {
		if( list[i]->query("kingdom/id")==arg ) {
			list[i]->delete("cwd");
			list[i]->delete("home");
			list[i]->delete("kingdom");
			list[i]->delete("title"); 
			channeld_ch = list[i]->query("channels");
			if( pointerp(channeld_ch) && member_array("kingdom", channeld_ch)!=-1 ) {
                                channeld_ch -= ({ "kingdom" });
				list[i]->set("channels", channeld_ch);
			}
			tell_object(list[i], sprintf("你成了没有国籍的冒险者了。\n"));
			list[i]->save();
		}
	}

	CHINESE_D->remove_kingdom_name( arg);

	if( !rename(KINGDOM_DIR+arg+"/", DATA_DIR+"nuke/kingdom/"+arg+"/") )
		write( name+ "资料已删除。\n");
	else write( name+ "资料移除失败。\n");

	log_file("kingdom_destory", sprintf("[%s] %s destroy kingdom - %s.\n",
		ctime(time())[0..15], geteuid(this_player(1)), arg));

	write("\n"+HIW+"一只怪兽突然出现在"+HIR+name+HIW+"大肆破坏...."+HIR+name+HIW+"就此灭亡。\n"NOR);
	shout("\n"+HIW+"一只怪兽突然出现在"+HIR+name+HIW+"大肆破坏...."+HIR+name+HIW+"就此灭亡。\n"NOR);
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式：delete_kingdom <国家名称>

这是管理者用来清除违规国家的终极利器。

HELP
	);
	return 1;
}
