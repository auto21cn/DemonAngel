//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/room/actionroom.c
// by bor @RG, 3/5, 2001

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit ROOM;

void move_room(object me, string pre_msg, string post_msg, string file);
int check_ob(object me, mapping action);

object env;

void setup()
{
	seteuid(getuid());
	env = this_object();
	::setup();
}

void init()
{
	mapping act_move;
	string *a_move;

	if( mapp(act_move = env->query("action_move")) && sizeof(act_move)>0 ) {
		a_move = keys(act_move);
		if( sizeof(a_move)>0 ) add_action("action_move", a_move);
	}
}

int action_move(string arg)
{
	mapping action;
	object me = this_player();
	string verb;

	if(!verb = query_verb()) return 0;
	if(!mapp(action = env->query("action_move/"+verb))) return 0;
	// 如果移动的目标不正确
	if(!arg||arg!=action["toward"]) return 0;
	if(action["check_ob"]&&check_ob(me, action)==-1) return 0;
	if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");
	if(undefinedp(action["msg"])) tell_object(me, "你突然觉得一阵晕眩。\n");
	else tell_object(me, action["msg"]+"\n");
	move_room(me, action["pre_msg"], action["post_msg"], action["file"]);
	return 1;
}

// 移动到该房间
void move_room(object me, string pre_msg, string post_msg, string file)
{
	if(!me) return ;
	if(undefinedp(pre_msg)) message_vision("$N的身影突然闪了一闪, 消失了。\n", me);
	else message_vision(pre_msg+"\n", me);
	me->start_busy(2);
	call_out("move_to", 2, me, post_msg, file);
	return ;
}

void move_to(object me, string post_msg, string file)
{
	if(!me) return ;
	me->move(file);
	if(undefinedp(post_msg)) message_vision("$N的身影突然出现了。\n", me);
	else message_vision(post_msg+"\n", me);
	return ;
}

int check_ob(object me, mapping action) // 检查你身上是否有任务品才能作动作词
{
	object ob;
	int flag = -1;

	// flag == -1 ：如果你身上没有该 ob 的话，回应 -1
	foreach(ob in all_inventory(me)) {
		if(base_name(ob)+".c"!=action["check_ob"]) continue;
		flag = 1;
		break;
	}
	return flag;
}
