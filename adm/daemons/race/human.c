//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /adm/daemons/race/human.c

// A normal human is at least 40 kg weight
#define BASE_WEIGHT 4500

inherit F_DBASE;

mapping *combat_action = ({
	([	"action":		"$N挥拳攻击$n的$l",
		"damage_type":	"瘀伤",
	]),
	([	"action":		"$N往$n的$l一抓",
		"damage_type":	"抓伤",
	]),
	([	"action":		"$N往$n的$l狠狠地踢了一脚",
		"damage_type":	"瘀伤",
	]),
	([	"action":		"$N提起拳头往$n的$l捶去",
		"damage_type":	"瘀伤",
	]),
	([	"action":		"$N对准$n的$l用力挥出一拳",
		"damage_type":	"瘀伤",
	]),
});

void create()
{
	seteuid(getuid());
	set("unit", "位");
	set("gender", "男性");
	set("can_speak", 1);
	set("attitude", "peaceful");
	set("limbs", ({
		"头部",	"颈部",	"胸口",	"后心",	"左肩",	"右肩",	"左臂",
		"右臂",	"左手",	"右手",	"腰间",	"小腹",	"左腿",	"右腿",
		"左脚",	"右脚"
	}) );
}

void setup_human(object ob)
{
	mapping my;
	string *attr_list = ({"int","dex","con","str","kar","sta"});
	int wg;

	my = ob->query_entire_dbase();

	ob->set("default_actions", (: call_other, __FILE__, "query_action" :));

	if( undefinedp(my["age"]) ) my["age"] = random(13) + 3;

	if( undefinedp(my["level"]) ) my["level"] = 1;
	
/*	for(int i=0; i<sizeof(attr_list); i++) {
		my["max_"+attr_list[i]] = my["level"] + 1;
	}

	my["max_hp"] = my["max_con"]* 5 + ob->query("apply/con") * 3;
	my["max_mp"] = my["max_int"]* 7 + ob->query("apply/int") * 5;

	if( undefinedp(my["hp"]) ) my["hp"] = my["max_hp"];
	if( undefinedp(my["mp"]) ) my["mp"] = my["max_mp"];
*/

//	分母的 hp		属性			法术			装备
	my["base_hp"] = 34 + ob->query("con")*5 + ob->query("apply/con")*3 + ob->query_temp("apply/con")*2;
	my["base_mp"] = 20 + ob->query("int")*5 + ob->query("apply/int")*3 + ob->query_temp("apply/int")*2;

	if( undefinedp(my["hp"]) ) my["hp"] = my["base_hp"];
	if( undefinedp(my["mp"]) ) my["mp"] = my["base_mp"];

	for(int i=0; i<sizeof(attr_list); i++) {
		if( undefinedp(my[attr_list[i]]) ) my[attr_list[i]] = 1;
	}

	ob->set_default_object(__FILE__);

	wg = BASE_WEIGHT + my["level"] * 2/3 + my["str"] * 480;
	if( wg < 100 ) wg = my["level"] * my["level"] * 10 + 500;

	if( !ob->query_weight() ) ob->set_weight( BASE_WEIGHT );
	ob->set_max_encumbrance( wg );
}

mapping query_action()
{
	return combat_action[random(sizeof(combat_action))];
}
