//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/room/wedding.c
// by smallpen

#pragma optimize
#pragma save_binary

inherit ROOM;
int do_me_check(object me,object ob1,object ob2);
int do_ob1_check(object me,object ob1,object ob2);
int do_ob2_check(object me,object ob1,object ob2);
int do_fail(object me,object ob1,object ob2);
void init()
{
        add_action("do_marry", "marry");
        add_action("do_answer","answer");
}

int do_marry(string arg)
{
        string man,woman,sex="你";
        object me = this_player(),ob1,ob2;
        string *parent,*child,*brother;
        int i;
        seteuid(getuid());
        
        if( me->is_busy()) return notify_fail("你现在正忙着。\n");
        if( !arg || sscanf(arg, "%s with %s", man,woman)!=2 ) return notify_fail("格式 : marry <男方> with <女方>。\n");
        if( !(ob1 = present(man, environment(me)) )) return notify_fail("男方好像不在现场唷？\n");
        if( !(ob2 = present(woman, environment(me)) )) return notify_fail("女方好像不在现场唷？\n");
        parent = ob1->query("parent");
        child = ob1->query("child");
        brother = ob1->query("brother");
        if( ob1->query("gender")!="男性" || ob2->query("gender")!="女性") return notify_fail("格式 : marry <男方> with <女方>。\n"); 
        for(i=0;i<sizeof(parent);i++) {
                if(ob2->query("id")==parent[i]) return notify_fail("他已经是你家族的人了。\n");
                }
        for(i=0;i<sizeof(child);i++) {
                if(ob2->query("id")==child[i]) return notify_fail("他已经是你家族的人了。\n");
                }
        for(i=0;i<sizeof(brother);i++) {
                if(ob2->query("id")==brother[i]) return notify_fail("他已经是你家族的人了。\n");
                }
        if( ob1->query("lover")) return notify_fail("男方已经结婚了！\n");
        if( ob2->query("lover")) return notify_fail("女方已经结婚了！\n");
        if( me->query("gender")=="男性") sex="你";
        write("你说道：依上天附予我的权力，在此地我将为"+ob1->query("name")+"与"+ob2->query("name")+"俩人证婚。\n\n");
        tell_room(environment(me),me->query("name")+"说道：依上天附予我的权力，在此地我将为"+ob1->query("name")+"与"+ob2->query("name")+"俩人证婚。\n\n",me);
        write(sex+"往前走了一步，开始证婚。\n\n");
                tell_room(environment(me),me->query("name")+"往前走了一步，开始证婚。\n\n",me);
                write(sex+"说道："+ob1->query("name")+"，你愿意用你一生的时间照顾"+ob2->query("name")+"，带她到处冒险，努力赚钱供她挥霍吗？\n\n");
        tell_room(environment(me),me->query("name")+"说道："+ob1->query("name")+"，你愿意用你一生的时间照顾"+ob2->query("name")+"，带她到处冒险，努力赚钱供她挥霍吗？\n\n",me);
        call_out("do_me_check", 1,me,ob1,ob2);
                return 1;
}

int do_answer(string arg)
{
        string ans;
        object me=this_player();

        seteuid(getuid());
        if(!me->query_temp("wedding")) return notify_fail("不是你要结婚吧！\n"); 
        if(me->query_temp("wedding") && !me->query_temp("answer")) return notify_fail("还没到你回答，不用急。\n");
        if(!arg ||sscanf(arg,"%s",ans)!=1) return notify_fail("请回答Yes or 我愿意！\n");
        if(!(ans =="yes" || ans=="我愿意")) return notify_fail("请回答Yes or 我愿意！\n");
        if(me->query("gender")=="男性") message_vision("$P微笑着说道：我愿意。\n\n",me);
        if(me->query("gender")=="女性") message_vision("$P低头羞答答地应道：我愿意...\n\n",me);
        me->delete_temp("answer");
        me->set_temp("swer","yes");
        return 1;
}

int do_me_check(object me,object ob1,object ob2)
{
        ob1->set_temp("wedding","ok");
        ob2->set_temp("wedding","ok");
        ob1->set_temp("answer","ok");
        call_out("do_ob1_check",10,me,ob1,ob2);

        return 1;
}

int do_ob1_check(object me,object ob1,object ob2)
{
        string sex="你";
        if(me->query("gender") =="女性") sex="你";
        if( ob1->query_temp("swer") ) {
                ob1->delete_temp("swer");
                ob1->delete_temp("wedding");
                ob2->set_temp("answer","ok");
                write(sex+"说道："+ob2->query("name")+"，你愿意一生跟着"+ob1->query("name")+"，陪他到处流浪，无论贫富悲喜都与他共度吗？\n\n");
                tell_room(environment(me),me->query("name")+"说道："+ob2->query("name")+"，你愿意一生跟着"+ob1->query("name")+"，陪他到处流浪，无论贫富悲喜都与他共度吗？\n\n",me);
                call_out("do_ob2_check",10,me,ob1,ob2);
                
        }
        else {
                call_out("do_fail",2,me,ob1,ob2);
                return 1;}
}
int do_ob2_check(object me,object ob1,object ob2)
{
        if( ob2->query_temp("swer") ) {
                ob2->delete_temp("swer");
                ob2->delete_temp("answer");
                ob2->delete_temp("wedding");
                ob1->set("lover",ob2->query("id"));
                ob2->set("lover",ob1->query("id"));
                write(me->query("name")+"大喊：我宣布"+ob1->query("name")+"与"+ob2->query("name")+"结为夫妻，愿大地之神玛拉祝福这对新人。\n");
                shout(me->query("name")+"大喊：我宣布"+ob1->query("name")+"与"+ob2->query("name")+"结为夫妻，愿大地之神玛拉祝福这对新人。\n");
                return 1;
                
        }
        else {
                call_out("do_fail",2,me,ob1,ob2);
                return 1;}
}
int do_fail(object me,object ob1,object ob2)
 {
        string sex="你";
        if(me->query("gender")=="女性") sex="你";
        ob1->delete_temp("wedding");
        ob2->delete_temp("wedding");
        ob1->delete_temp("answer");
        ob2->delete_temp("answer");
        ob1->delete_temp("swer");
        ob2->delete_temp("swer");
        write(sex+"说道：由于有一方有迟疑，所以我宣布这场婚礼无效！\n\n");
        tell_room(environment(me),me->query("name")+"说道：由于有一方有迟疑，所以我宣布这场婚礼无效！\n\n",me);
        return 1;
 }      
