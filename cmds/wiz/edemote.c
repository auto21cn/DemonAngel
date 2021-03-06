//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/wiz/edemote.c
// modify by bor @ RG,

#pragma optimize
#pragma save_binary

/*
        新增一些额外的功能，或显示方式
        1. $T 第二参数的加入。
        2. emote 与中文意思的对照(chinese)
        3. 目前 es2 有的设定与部份解说：
                使用 emote 的玩家看到的：
                a. myself               不指定对象使用这个 emote 时，你自己看到的讯息
                b. myself_self          对自己使用这个 emote 时，自己看到的讯息
                c. myself_target        对别人使用这个 emote 时，自己看到的讯息
                d. myself_rest          当有指定对象且有第二参数时，自己所看到的讯息

                对方看到的讯息：
                e. target               对别人使用这个 emote 时，使用对象看到的讯息
                f. target_self          不指定特定对象且有第二参数时，使用对象所看到的讯息
                g. target_rest          当有指定对象且有第二参数时，使用对象所看到的讯息


                其他人看到的讯息：
                h. other                不指定对象使用这个 emote 时，其他人看到的讯息
                i. others_target        对别人使用这个 emote 时，除你自己和使用对象外，其他人看到的讯息
                j. others_self          对自己使用这个 emote 时，其他人看到的讯息
                k. others_rest          当没有指定对象且有第二参数时，其余的人看到的讯息

*/

inherit F_CLEAN_UP;

string tmp;     // 记录一下之前写的，有需要改再修正，否则用 tmp 取代

int main(object me, string arg)
{
        mapping emote;

        if( !arg ) return notify_fail("你要编辑什么 emote？\n");
        if( sscanf(arg, "-d %s", arg) ) {
                write("删除 emote：" + arg + "\n");
                EMOTE_D->delete_emote(arg);
                return 1;
        }

        // 显示某个 emote 的个别设定
        if( sscanf(arg, "-p %s", arg) ) {
                emote = EMOTE_D->query_emote(arg);
                printf("上次修改者：%-25s名称：%s,%s\n", emote["updated"], arg, emote["chinese"] );
                printf("───────────────────────────────────\n"
                "myself :\t%s\nmyself_self :\t%s\nmyself_target :\t%s\nmyself_rest :\t%s\n"
                "target :\t%s\ntarget_self :\t%s\ntarget_rest :\t%s\nothers :\t%s\n"
                "others_target :\t%s\nothers_self :\t%s\nothers_rest :\t%s\n",
                emote["myself"], emote["myself_self"], emote["myself_target"], emote["myself_rest"],
                emote["target"], emote["target_self"], emote["target_rest"],
                emote["others"], emote["others_target"], emote["others_self"], emote["others_rest"]
                );
                return 1;
        }

        emote = EMOTE_D->query_emote(arg);
        emote["updated"] = geteuid(me);

        write("编辑 emote：" + arg + "\n");

        write("讯息可以有好几行，用 . 表示结束，用 ~q 可以保留原先设定，而到下一个设定去。\n");
        write("讯息中可使用的参数有以下几种：\n");
        write("  $N  自己的名字。\n");
        write("  $n  使用对象的名字。\n");
        write("  $P  自己的人称代名词，如你、你、他、她、牠、它。\n");
        write("  $p  使用对象的人称代名词，如你、你、他、她、牠、它。\n");
        write("  $T  第二参数的使用。\n");
        write("───────────────────────────────────\n");
        log_file("emote", sprintf("[%s]%s edemote %s\n", ctime(time()), geteuid(me), arg ) );
        printf("项目【chinese】：请输入该 emote 的中文名称以四个中文字为限：\n\t【原先设定】：%s\n->", undefinedp(emote["chinese"])?"":emote["chinese"] );
        tmp = emote["chinese"];         // 先取得资料，以免被覆盖
        input_to("input_chinese", emote, arg);
        return 1;
}

private int
input_chinese(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {
                if(msg=="~q") emote["chinese"] = tmp;
                if( strlen(msg)>8 ) {
                        write("emote 的中文名称以四个中文字为限：\n");
                        input_to("input_chinese", emote, pattern);
                        return 1;
                }
                printf("项目【myself】：不指定对象使用这个 emote 时，你自己看到的讯息：\n\t【原先设定】：%s\n->", undefinedp(emote["myself"])?"":emote["myself"] );
                tmp = emote["myself"];
                input_to("get_msg_myself", emote, pattern);
                return 1;
        }
//      if( !undefinedp(emote["chinese"]) )
//              emote["chinese"] += msg + "\n";
//      else emote["chinese"] = msg;
        emote["chinese"] = msg +"\n";
        write("->");
        input_to("input_chinese", emote, pattern);
        return 1;
}

private int
get_msg_myself(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {
                if(msg=="~q") emote["myself"] = tmp;
                printf("项目【others】：不指定对象使用这个 emote 时，其他人看到的讯息：\n\t【原先设定】：%s\n->", undefinedp(emote["others"])?"":emote["others"] );
                tmp = emote["others"];
                input_to("get_msg_others", emote, pattern);
                return 1;
        }

        emote["myself"] = msg +"\n";
        write("->");
        input_to("get_msg_myself", emote, pattern);
        return 1;
}

private int
get_msg_others(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {
                if(msg=="~q") emote["others"] = tmp;
                printf("项目【myself_self】：对自己使用这个 emote 时，自己看到的讯息：\n\t【原先设定】：%s\n->", undefinedp(emote["myself_self"])?"":emote["myself_self"] );
                tmp = emote["myself_self"];
                input_to("get_msg_myself_self", emote, pattern);
                return 1;
        }
        emote["others"] = msg +"\n";
        write("->");
        input_to("get_msg_others", emote, pattern);
        return 1;
}

private int

get_msg_myself_self(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {
                if(msg=="~q") emote["myself_self"] = tmp;
                printf("项目【others_self】：对自己使用这个 emote 时，其他人看到的讯息：\n\t【原先设定】：%s\n->", undefinedp(emote["others_self"])?"":emote["others_self"] );
                tmp = emote["others_self"];
                input_to("get_msg_others_self", emote, pattern);
                return 1;
        }
        emote["myself_self"] = msg +"\n";
        write("->");
        input_to("get_msg_myself_self", emote, pattern);
        return 1;
}

private int
get_msg_others_self(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {
                if(msg=="~q") emote["others_self"] = tmp;
                printf("项目【myself_target】：对别人使用这个 emote 时，自己看到的讯息：\n\t【原先设定】：%s\n->", undefinedp(emote["myself_target"])?"":emote["myself_target"] );
                tmp = emote["myself_target"];
                input_to("get_msg_myself_target", emote, pattern);

                return 1;
        }
        emote["others_self"] = msg +"\n";
        write("->");
        input_to("get_msg_others_self", emote, pattern);
        return 1;
}

private int
get_msg_myself_target(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {
                if(msg=="~q") emote["myself_target"] = tmp;
                printf("项目【target】：对别人使用这个 emote 时，使用对象看到的讯息：\n\t【原先设定】：%s\n->", undefinedp(emote["target"])?"":emote["target"] );
                tmp = emote["target"];
                input_to("get_msg_target", emote, pattern);
                return 1;
        }
        emote["myself_target"] = msg +"\n";
        write("->");
        input_to("get_msg_myself_target", emote, pattern);
        return 1;
}

private int
get_msg_target(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {
                if(msg=="~q") emote["target"] = tmp;
                printf("项目【others_target】：对别人使用这个 emote 时，除你自己和使用对象外，其他人看到的讯息：\n\t【原先设定】：%s\n->", undefinedp(emote["others_target"])?"":emote["others_target"] );
                tmp = emote["others_target"];
                input_to("get_msg_others_target", emote, pattern);
                return 1;
        }
        emote["target"] = msg +"\n";
        write("->");
        input_to("get_msg_target", emote, pattern);
        return 1;
}

private int
get_msg_others_target(string msg, mapping emote, string pattern)
{
	if(msg=="." || msg=="~q") {
		if(msg=="~q") emote["others_target"] = tmp;
		else if( emote["others_target"] ) emote["others_target"] += "\n";
		printf("项目【myself_rest】：当有指定对象且有第二参数时，自己所看到的讯息：\n\t【原先设定】：%s\n->", undefinedp(emote["myself_rest"])?"":emote["myself_rest"] );
		tmp = emote["myself_rest"];
		input_to("get_msg_myself_rest", emote, pattern);
		return 1;
	}
	if( !undefinedp(emote["others_target"]) )
		emote["others_target"] += msg + "\n";
	else emote["others_target"] = msg;
	write("->");
	input_to("get_msg_others_target", emote, pattern);
	return 1;
}

private int
get_msg_myself_rest(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {
                if(msg=="~q") emote["myself_rest"] = tmp;
                printf("项目【target_self】：不指定特定对象且有第二参数时，使用对象所看到的讯息：\n\t【原先设定】：%s\n->", undefinedp(emote["target_self"])?"":emote["target_self"] );
                tmp = emote["target_self"];
                input_to("get_msg_target_self", emote, pattern);
                return 1;
        }
        emote["myself_rest"] = msg +"\n";
        write("->");
        input_to("get_msg_myself_rest", emote, pattern);
        return 1;
}

private int
get_msg_target_self(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {
                if(msg=="~q") emote["target_self"] = tmp;
                printf("项目【target_rest】：当有指定对象且有第二参数时，被指定对象所看到的讯息：\n\t【原先设定】：%s\n->", undefinedp(emote["target_rest"])?"":emote["target_rest"] );
                tmp = emote["target_rest"];
                input_to("get_msg_target_rest", emote, pattern);
                return 1;
        }
        emote["target_self"] = msg +"\n";
        write("->");
        input_to("get_msg_target_self", emote, pattern);
        return 1;
}

private int
get_msg_target_rest(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {

                if(msg=="~q") emote["target_rest"] = tmp;
                printf("项目【others_rest】：当没有指定对象且有第二参数时，所有的人看到的讯息：\n\t【原先设定】：%s\n->", undefinedp(emote["others_rest"])?"":emote["others_rest"] );
                tmp = emote["others_rest"];
                input_to("get_msg_others_rest", emote, pattern);
                return 1;
        }
        emote["target_rest"] = msg +"\n";
        write("->");
        input_to("get_msg_target_rest", emote, pattern);
        return 1;
}

private int
get_msg_others_rest(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {
                if(msg=="~q") emote["others_rest"] = tmp;
                EMOTE_D->set_emote(pattern, emote);
                write("Emote "+pattern+" 编辑结束。\n");
                return 1;
        }
        emote["others_rest"] = msg +"\n";
        write("->");
        input_to("get_msg_others_rest", emote, pattern);
        return 1;
}

int help(object me)
{
        write(@HELP

指令格式：edemote [-d|-p] <emote>
 
这个指令可以修改, 删除 emote 或列出其内容. 加上 -d 参数会删除
指定的 emote, -p 参数则会列出指定 emote 的内容. 列出的顺序与编
辑 emote 时相同.
 
输入 emote 讯息时有三个项目: 没有目标, 指定目标或是对自己. 若
不想有某项讯息, 则直接在空白行输入 '.' 跳过.
 
一个 emote 讯息可以有很多行, 在空白行输入 '.' 结束输入该项 emote.
 
编辑 emote 时可以用以下的符号来表示:
 
$N : 自己的名字.
$n : 目标的名字.
$P : 自己的人称代名词.
$p : 目标的人称代名词.
$T : 第二参数。


各英文代码的解说：

                使用 emote 的玩家看到的：
                a. myself               不指定对象使用这个 emote 时，你自己看到的讯息
                b. myself_self          对自己使用这个 emote 时，自己看到的讯息
                c. myself_target        对别人使用这个 emote 时，自己看到的讯息
                d. myself_rest          当有指定对象且有第二参数时，自己所看到的讯息

                对方看到的讯息：
                e. target               对别人使用这个 emote 时，使用对象看到的讯息
                f. target_self          不指定特定对象且有第二参数时，使用对象所看到的讯息
                g. target_rest          当有指定对象且有第二参数时，使用对象所看到的讯息

                其他人看到的讯息：
                h. other                不指定对象使用这个 emote 时，其他人看到的讯息
                i. others_target        对别人使用这个 emote 时，除你自己和使用对象外，其他人看到的讯息
                j. others_self          对自己使用这个 emote 时，其他人看到的讯息
                k. others_rest          当没有指定对象且有第二参数时，其余的人看到的讯息


HELP
        );
        return 1;
}
