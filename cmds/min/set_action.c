//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/set_action.c
// by bor @RG

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit F_CLEAN_UP;
int show_action(object me);
int check_verb(object env, string type, string verb);
int move_set(object env, string type, string verb, string par, string set);

string *action_type = ({"move"});
string *move_type = ({"check_ob", "toward", "pre_msg", "msg", "post_msg"});

int main(object me, string arg)
{
	object env;
	string type, verb, par, set;

	seteuid(getuid());
	if(!env = environment(me)) return 0;

	if( !env->query("kingdom_id")
	|| env->query("kingdom_id")!=me->query("kingdom/id")
	) return 0;

	if(!arg) {
		show_action(me);
		return 1;
	}

	if(sscanf(arg,"%s %s %s %s", type, verb, par, set)!=4 )
		return notify_fail("指令格式：set_action <动作类型> <动作词> <参数> <参数的新值>\n");

	switch(type) {
		case "move":
			if(!check_verb(env, type, verb)) return notify_fail("这里并没有这个动作词!!\n");
			if( member_array(par, move_type) == -1 ) return notify_fail("没有这样的参数型态。\n");
			move_set(env, type, verb, par, set);
		break;
		default:
			return notify_fail("目前不开放 "+type+" 型态的动作类型。\n");
	}
	return 1;
}

int show_action(object me)
{
	object env;
	string str, _action, __action, tmp;

	env = environment(me);
	if(env->query("type")!="actionroom") {
		write("这个房间没有动作词。\n");
		return 1;
	}
	str = "这个房间中的动作词有：\n\n";
	if(env->query("action_move")&&sizeof(keys(env->query("action_move")))>0) {
		str += sprintf("action_move 的动作词包含：\n");
		foreach(_action, tmp in env->query("action_move")) {
			str += sprintf(_action+"\n");
			foreach(__action, tmp in env->query("action_move/"+_action)) {
				if(__action=="file") continue;
				if(__action=="dir" ) str += sprintf("\t实际方向   : "+tmp+"\n");
				else if(__action=="check_ob") str += sprintf("\t"+__action+"   : 有\n");
				else str += sprintf("\t"+__action+"   : "+tmp+"\n");
			}
			str += "\n";
		}
	}
	me->start_more(str);
	return 1;
}

// 先检查环境是否有该动作词
int check_verb(object env, string type, string verb)
{
	if(!env->query("action_"+type)&&!env->query("action_"+type+"/verb") ) return 0;
	return 1;
}

int move_set(object env, string type, string verb, string par, string set)
{
	object me = this_player(), ob;
	if(par!="check_ob") env->set("action_"+type+"/"+verb+"/"+par, set);
	else {
		ob = present(set, me);
		if(!ob) return notify_fail("你身上没有这个东西。\n");
		// 不判定是否为自己国家的物品
		env->set("action_"+type+"/"+verb+"/"+par, base_name(ob)+".c" );
	}
	tell_object(me, "你将 "+par+ " 设定为 "+set+"\n");
	do_saveroom(env);
	refresh_room(env);
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : 对房间 set_action <动作类型> <动作词> <参数> <参数的新值>

动作型态，目前分为 move。

例如：你想要下一个指令叫做 jump tree ，可以从一个房间移动到另一个房间，达到跳树的
	效果。你可以下达 add_action move jump north。

	解说：
		1. move 是我们选定的动作型态，因为目前只开放 move，所以啰 @@
		2. jump 就是你选的动作词。
		3. 参数为 north，为什么不直写成 tree ??我们实际上的参数应该是 tree
		   是没错的，不过实际上，我们必须指定“方向”才知道，我们跳往何处。
		   如果你要美化参数成 tree，这就要靠 set_action 来达成了。
		4. 美化：set_action move jump toward tree，这时会将 north 改为
		   tree，以后就可以直接 jump tree 来达到自己想要的指令了。

相关讯息 : add_action

HELP
	);
	return 1;
}
