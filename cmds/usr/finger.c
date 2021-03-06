//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/usr/finger.c

//SKYMONARCH By 2003/3/8

#include <ansi.h>

int main(object me, string arg)
{
        int i, num;
        string str, *finger, msg;
        object ob;

//        seteuid(ROOT_UID);
        finger = me->query("finger");
        if( !arg ) {
                msg = "";
                str = me->name() + "的好友目前在线上的有：\n";
                if( sizeof(finger) ) {
                        for(i=0;i<sizeof(finger);i++) {
                                if( ob = find_player(finger[i]) ) {
                                        msg += sprintf(HIY"[%2d]"NOR" %s\n", i + 1, ob->short() );
                                        num++;
                                }
                        }
                        if( !num ) str += "你目前没有任何好友上线。\n";
                        else str += msg;
                } else str += "你还没有设定好友名单。\n"; 
                me->start_more(str);
        } else if( sscanf(arg,"-d %s", arg) ) {
                if( pointerp(finger) ) {
                        if( member_array(arg, finger) == -1 )
                                return notify_fail( capitalize(arg) + " 不在你的好友名单中。\n");
                        else me->set("finger", finger - ({ arg }) );
                } else return notify_fail("你还没有设定好友名单。\n");
                write("你把 " + capitalize(arg) + " 从你的好友名单中去除。\n");
        } else if( sscanf(arg, "-a %s", arg) ) {
                if( file_size(DATA_DIR + "login/" + arg[0..0] + "/" + arg + __SAVE_EXTENSION__) < 0 )
                        return notify_fail("没有这位使用者。\n");
                if( arg == me->query("id") )
                        return notify_fail("你不能把自己加入好友名单。\n");
                if( !pointerp(finger) ) me->set("finger", ({ arg }) );
                else {
                        if( member_array(arg, finger) != -1 )
                                return notify_fail( capitalize(arg) + " 已经在你的好友名单中。\n");
                        else me->set("finger", finger + ({ arg }) );
                }
               write("你把 " + capitalize(arg) + " 列入你的好友名单中。\n");
        } else if( arg == "-l" ) {
                str = "目前" + me->name() + "的好友名单有：\n";
                        str += HIC"★★★★★★★★★★★★★★★★★★★★★★★★★\n"NOR;
                if( sizeof(finger) ) {
                        for(i=0;i<sizeof(finger);i++) {
                                if( !objectp(ob = FINGER_D->acquire_login_ob(finger[i])) ) {
                                        me->set("finger", finger - ({ finger[i] }) );
                                        write("你的好友 " + capitalize(finger[i]) + " 从这个世界上消失了。\n");
                                }
                                str += sprintf(HIY"[%2d]"NOR" %s\n", i + 1,
                                        ob->query("name") + "(" + capitalize(finger[i]) + ")");
                        }
                        str += YEL"------------------------------------------\n"NOR;
                        str += "目前共有 " + sizeof(finger) + " 位好友。\n";
                } else str += "你还没有设定好友名单。\n";
                        str += YEL"==========================================\n"NOR;
                me->start_more(str);
        } else if( arg == "-all" ) {
                if( !wizardp(me) ) return notify_fail("你不能使用这个参数。\n");
          	else me->start_more(FINGER_D->finger_all());
        } else {
                write( FINGER_D->finger_user(arg) );
	}
        return 1;
}

int help(object me)
{
        write(@HELP
----------------------------------------
指令格式：finger [-l|-a|-d] <玩家>
----------------------------------------
说明：
 finger         列出目前有上线的好友
 finger -a      增加新的 id 进名单内
 finger -d      将某个人的 id 从名单中去除
 finger -l      列出所有的好友名单
 finger <玩家>  查询玩家资料
----------------------------------------
HELP);
        return 1;
}
