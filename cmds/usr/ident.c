//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/usr/ident.c
// by bor @RG, 5/19 2003

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string type, str="";

	seteuid(getuid(me));
	if(!arg) return notify_fail("使用格式 : ident <物品>\n");
	if( !(ob = present(arg, me)) ) return notify_fail("你身上没有这一件东西。\n");

	message_vision(HIC"$N低头对着"NOR"$n冥想 !\n\n", me, ob);
	me->start_busy(2);

	switch( ob->query("type") ) {
		case "ring":		type = "戒指";		break;
		case "shield":		type = "盾牌";		break;
		case "body":		type = "护甲";		break;
		case "gloves":		type = "手套";		break;
		case "necklace":	type = "项炼";		break;
		case "boots":		type = "鞋子";		break;
		case "armor":		type = "臂环";		break;
		case "cloak":		type = "披风";		break;
		case "head":		type = "头盔";		break;
		case "leggings":	type = "胫甲";		break;

		case "blade":		type = "刀类武器";	break;
		case "fork":		type = "叉类武器";	break;
		case "staff":		type = "杖类武器";	break;
		case "throwing":	type = "投掷类武器";	break;
		case "wand":		type = "魔杖类武器";	break;
		case "spear":		type = "矛戟类武器";	break;
		case "whip":		type = "鞭类武器";	break;
		case "axe":		type = "斧类武器";	break;
		case "hammer":		type = "锤类武器";	break;
		case "dagger":		type = "匕首类武器";	break;
		case "sword":		type = "剑类武器";	break;
	}

	if( ob->query("armor_type") ) {
		str += sprintf("名称 : %s(%s)  重量 : %d\t价值 : %d %s\n\n", ob->query("name"), capitalize(ob->query("id")), ob->query_weight(), ob->query("value"), "枚金币" );
		str += sprintf("型式 : 防具    防具种类 : %s\t防具等级 : %d    伤害吸收力 : %d\n\n", type, ob->query("armor_prop/ac"), ob->query("armor_prop/db") );
		str += sprintf("使用等级 : %d    制造地 : %s\n", ob->query("level"), ob->query("kingdom")?ob->query("kingdom"):"???" );
		str += "\n附加值 : ";
		if(ob->query("add_attr"))
		foreach( string add, int tmp in ob->query("add_attr") ) {
			str += sprintf("%s : %d, ", add, tmp );
		}
	} else if( ob->query("skill_type") ) {
		str += sprintf("名称 : %s(%s)  重量 : %d    价值 : %d %s\n\n", ob->query("name"), capitalize(ob->query("id")), ob->query_weight(), ob->query("value"), "枚金币" );
		str += sprintf("型式 : %s  等级 : %d\t需要技能 : %d    最大伤害力 : %d\n\n", type, ob->query("level"), ob->query("skill"), ob->query("weapon_prop/Mh") );
		str += sprintf("制造地 : %s\n", ob->query("kingdom")?ob->query("kingdom"):"???" );

		if( ob->query("invoke_magic") ) {
			str += sprintf("\n封印魔法 : %s       剩余次数 : %d    受损度 : %d%%\n", ob->query("invoke_magic"), ob->query_temp("invoke_times"), ob->query_temp("broken") );
		}
		str += "\n附加值 : ";
		if(ob->query("add_attr"))
		foreach( string add, int tmp in ob->query("add_attr") ) {
			str += sprintf("%s : %d, ", add, tmp );
		}
	} else return notify_fail("这不是装备或武器。\n");

	write(str+"\n");
	return 1;
}  

int help(object me)
{
	write ("使用格式：ident <物品>\n");
	return 1;
}    

/*
你低头对着初心者の护戒冥想 !
名称 : 初心者の护戒(Newbie's war ring)  重量 : 2        价值 70 枚金币
型式 : 防具     防具种类 : 戒指 防具等级 : 0    伤害吸收力 : 2
使用等级 : 5    制造地 : neve_island

名称 : 言灵法杖(Holy soul staff)        重量 : 359      价值 2410 枚金币
型式 : 杖类武器 等级 : 80       需要技能 : 160  最大伤害力 : 80
制造地 : shogunate
封印魔法 : 心灵之锤(Spirit_hammer)       剩余次数 : 10   受损度 : 80%
附加值 :   智慧 : 5

名称 : 月之杖(Staff of moon)    重量 : 128      价值 550 枚金币

型式 : 杖类武器 等级 : 18       需要技能 : 36   最大伤害力 : 18

制造地 : ??

封印魔法 : 治疗术(Cure)  剩余次数 : 5    受损度 : 0%

> 
名称 : 邪龙杖(Dragon wand)      重量 : 56       价值 710 枚金币

型式 : 魔杖类武器       等级 : 25       需要技能 : 50   最大伤害力 : 20

制造地 : ??

封印魔法 : 喷火龙(Dragon_breath)         剩余次数 : 10   受损度 : 60%


*/