//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/delete_mob.c
// by bor @DA, 5/23 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

#include <ansi.h>

int main(object me,string arg)
{
	object env, ob;
	mapping room;
	int flag = -1;

	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
	if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");
	if( !arg ) return notify_fail("指令格式：delete_mob <NPC>\n");
	if( !env = environment(me)) return notify_fail("找不到环境。\n");
 
	if( !me->query("kingdom/id") || !env->query("kingdom_id")
	|| env->query("kingdom_id") != me->query("kingdom/id")
	) return notify_fail("这里不是贵国的土地。\n");

	if( !objectp(ob = present(arg, env)) ) return notify_fail("没有这个生物!\n");
	if( ob->query_temp("barracks") ) return notify_fail("请先解除他离营的状态, 才能消灭此生物!!\n");
       
	if( env->query("objects") && mapp(room = env->query("objects"))  ) {
		foreach(string npc, int tmp in room) {
			if( file_size(npc+".c")==-1 ) continue;
			if( npc != base_name(ob) ) continue;
			flag = 1;
			break;
		}
	}
	message_vision("$N双手一挥, 把$n送入虚空中。\n", me, ob);
	if( flag == 1) {
		map_delete(room, base_name(ob));
		env->set("objects", room);
		rm( full_name(ob) );
		do_saveroom(env);
		refresh_room(env);
	} else {	// 如果 NPC 的 home 不在本格房间, 那么我们用 NPC 身上的"home" 去追他原先的 env
		object new_env;
		if( !(new_env = find_object( ob->query("home") )) ) {
			call_other(ob->query("home"), "create_room");
			new_env = find_object( ob->query("home") );
		}
		if( new_env->query("objects") && mapp(room = new_env->query("objects"))  ) {
			foreach(string npc, int tmp in room) {
				if( file_size(npc+".c")==-1 ) continue;
				if( npc != base_name(ob) ) continue;
				flag = 1;
				break;
			}
		}
		if( flag == 1) {
			map_delete(room, base_name(ob));
			new_env->set("objects", room);
			rm( full_name(ob) );
			do_saveroom(new_env);
			refresh_room(new_env);
		}
	}
	if( flag==1) {
		kingdom_data(me->query("kingdom/id"), "data", "sub", "npc", 1);
		kingdom_data(me->query("kingdom/id"), "data", "add", "npc_num", 1);
	}
	destruct(ob);
        return 1;       
}

int help(object me)
{
        write(@HELP
指令格式：delete_mob <who>
这是贵族用来将生物删除的指令

HELP
        );
        return 1;
}
