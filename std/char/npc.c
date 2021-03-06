//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/char/npc.c

#include <command.h>
#include <type.h>
#include <ansi.h>


inherit CHARACTER;
inherit F_CLEAN_UP;

static mixed next_chat;

object carry_object(string file)
{
	object ob;

	if( !objectp(ob = new(file)) ) return 0;
	ob->move(this_object());
	return ob;
}

object add_money(string type, int amount)
{
	object ob;

	ob = carry_object("/obj/money/" + type);
	if( !ob ) return 0;
	ob->set_amount(amount);
}

int accept_fight(object who)
{
	string att;

	att = query("attitude");

	if( is_fighting() )	switch(att) {
		case "heroism":
			command("say 哼！出招吧！\n");
			break;
		default:
			command("say 想倚多为胜，这不是欺人太甚吗！\n");
			return 0;
	}

	if( (int)query("gin") * 100 / (int)query("max_gin") >= 90
	&&	(int)query("kee") * 100 / (int)query("max_kee") >= 90
	&&	(int)query("sen") * 100 / (int)query("max_sen") >= 90 ) {
		switch(att) {
			case "friendly":
				command("say " + RANK_D->query_self(this_object())
					+ "怎么可能是" + RANK_D->query_respect(who)
					+ "的对手？\n");
				return 0;
			case "aggressive":
			case "killer":
				command("say 哼！出招吧！\n");
				break;
			default:
				if( !is_fighting() )
					command("say 既然" + RANK_D->query_respect(who)
						+ "赐教，" + RANK_D->query_self(this_object())
						+ "只好奉陪。\n");
		}
		return 1;
	} else
		return 0;
}

int accept_order(object who, string verb)
{
// by bor @DA, 3/17 2003
// who order this_object() 时, 先决条件 who 必须要能够先执行该指令

	string *list = ({"defend", "follow"});	// 你允许 npc 可以被 order 的指令

//	log_file("aa", sprintf("%s accept %s\n", who->query("id"), verb ) );
	if( member_array(verb, list ) == -1 ) return 0;

	if( stringp(who->find_command(verb)) ) return 1;
	return 0;
}

// This function is called by the reset() of the room that creates this
// npc. When this function is called, it means the room demand the npc
// to return its startroom.
int return_home(object home)
{
	// Are we at home already?
	if( !environment()
	||	environment()==home )
		return 1;

	// Are we able to leave?
	if( !living(this_object())
	||	is_fighting()
	||	!mapp(environment()->query("exits")) ) return 0;

	// Leave for home now.
	message("vision", this_object()->name() + "急急忙忙地离开了。\n",
		environment(), this_object());
	return move(home);
}

void do_chat(mixed c) { next_chat = c; }

mixed
eval_chat(mixed chat)
{
    chat = evaluate(chat);

    switch(typeof(chat))
    {
    case STRING:
	say(CYN + chat + NOR);
	return 0;
    case ARRAY:
	if( !sizeof(chat) ) return 0;
	chat[0] =  eval_chat(chat[0]);
	return chat - ({ 0 });
    case FUNCTION:
	return chat;
    default:
	return 0;
    }
}

// This is the chat function dispatcher. If you use function type chat
// message, you can either define your own functions or use the default
// ones.
int chat()
{
	string *msg;
	int chance, rnd;

    // Evaluate programmed chat first.
    if( next_chat ) {
	next_chat = eval_chat(next_chat);
	return 1;
    }

	if( !environment() ) return 0;

	if( !chance = (int)query(is_fighting()? "chat_chance_combat": "chat_chance") )
		return 0;

	if( arrayp(msg = query(is_fighting()? "chat_msg_combat": "chat_msg"))) {
		if( random(100) < chance ) {
			rnd = random(sizeof(msg));
			if( stringp(msg[rnd]) )
				say(msg[rnd]);
			else if( functionp(msg[rnd]) )
				return evaluate(msg[rnd]);
		}
		return 1;
	}
}

// Default chat function: Let the npc random move to another room.
int random_move()
{
	mapping exits;
	string *dirs;

	if( !mapp(exits = environment()->query("exits")) ) return 0;
	dirs = keys(exits);
	command("go " + dirs[random(sizeof(dirs))]);
}

// Default chat function: Let the npc cast his/her enabled spells
void cast_spell(string spell)
{
	string spell_skill;

	if( stringp(spell_skill = query_skill_mapped("spells")))
		SKILL_D(spell_skill)->cast_spell(this_object(), spell);
}

// Default chat function: Let the npc exert his/her enabled force
int exert_function(string func)
{
	string force_skill;

	if( stringp(force_skill = query_skill_mapped("force")))
		SKILL_D(force_skill)->exert_function(this_object(), func);
}

// Default chat function: Let the npc perform special action with 
// his/her enabled martial art
int perform_action(string action)
{
	object weapon;
	string martial_skill, act;

	if( sscanf(action, "%s.%s", martial_skill, act) != 2 )
		return 0;
	martial_skill = query_skill_mapped(martial_skill);
	if( stringp(martial_skill) )
		return SKILL_D(martial_skill)->perform_action(this_object(), act);		
}

