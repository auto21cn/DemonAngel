//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/ally.c
// by smallpen

#pragma optimize
#pragma save_binary
#include <ansi.h>
string show_ally(object me,string id);
int do_time(object me);
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object *ob,*ob1;
        string cancel,country;
        int flag,i,j;
        seteuid(getuid());
        if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
        if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");
        if( !arg ) {
                show_ally(me,me->query("kingdom/id"));
                return 1;       
        }
        
        if( sscanf(arg, "%s with %s", cancel, country)!=2 ) {
                if( sscanf(arg, "with %s",country)!=1) {
                        return notify_fail("指令格式 : ally <cancel> with 某国。 \n");}
                else {  
                        if(!check_kingdom(country))  return notify_fail("没有这个国家\n");
                        flag=1;}
                }
        else {
                if(cancel!="cancel")    return notify_fail("指令格式 : ally <cancel> with 某国。 \n");
                if(!check_kingdom(country))  return notify_fail("没有这个国家\n");
                flag=0;
        }
//结盟          
                
        if( flag==1) {
                if(country==me->query("kingdom/id")) return notify_fail("你不能跟自己结盟。\n");
                if(kingdom_data(me->query("kingdom/id"), "ally","check",country)) return notify_fail("此国已经跟贵国同盟了。\n");
                ob = users();
                for(i=0;i<sizeof(ob); i++) {
                        if(country==ob[i]->query("kingdom/id")) {
                                if(ob[i]->query("kingdom/minister") || ob[i]->query("kingdom/king")) {
                                        ob1 = users();
                                        for(j=0;j<sizeof(ob1);j++) {
                                                if(ob1[i]->query_temp("ally") == me->query("kingdom/id")) {
                                                        if(!kingdom_data(me->query("kingdom/id"), "ally", "add",country)) return notify_fail("国家资料有误，没办法将对方写入资料内。\n");
                                                        if(!kingdom_data(country,"ally","add",me->query("kingdom/id"))) return notify_fail("国家资料有误，没办法将对方写入资料内。\n");
                                                        write(HIY""+to_chinese_kingdom(me->query("kingdom/id")) + "正式宣告从现在起与"+to_chinese_kingdom(country)  + "达成同盟协议。\n"+NOR);
                                                        shout(HIY""+to_chinese_kingdom(me->query("kingdom/id")) + "正式宣告从现在起与"+to_chinese_kingdom(country)  + "达成同盟协议。\n"+NOR);
                                                        ob1[i]->delete_temp("ally");
                                                        ob1[i]->save();
                                                        return 1;
                                                                                                }
                                                                }       
                                        write(HIY""+"你提出与"+to_chinese_kingdom(ob[i]->query("kingdom/id"))+"的同盟提议。\n"+NOR);
                                        tell_object(ob[i], full_kingdom(me->query("kingdom/id"))+"的"+ me->query("name") + "要求和贵国建立同盟关系。\n");
                                        //ob[i]->command(kingdom 正式要求与我国建立同盟关系。) ;
                                        me->set_temp("ally",ob[i]->query("kingdom/id"));
                                        call_out("do_time_check",10,me);
                                        return 1;
                                                                                }
                                
                                                        }
                                        }
                return notify_fail("对方没有贵族在线上。\n");
                }
        

//解除同盟      
if(flag==0) {
        if(country==me->query("kingdom/id")) return notify_fail("你不能跟自己解除结盟。\n");
                if(!kingdom_data(me->query("kingdom/id"), "ally","check",country)) return notify_fail("此国尚未和贵国同盟。\n");
                if(!kingdom_data(me->query("kingdom/id"), "ally", "sub",country)) return notify_fail("国家资料有误，没办法将对方写入资料内。\n");
                if(!kingdom_data(country,"ally","sub",me->query("kingdom/id"))) return notify_fail("国家资料有误，没办法将对方写入资料内。\n");
                        write(HIY""+to_chinese_kingdom(me->query("kingdom/id")) + "正式宣告从现在起解除与"+to_chinese_kingdom(country)  + "的同盟协议。\n"+NOR);
                        shout(HIY""+to_chinese_kingdom(me->query("kingdom/id")) + "正式宣告从现在起解除与"+to_chinese_kingdom(country)  + "的同盟协议。\n"+NOR);
                        return 1;
                        
}
}
string show_ally(object me,string id)
{
        string *list,str="";
        int i;
        str += sprintf("目前%s的同盟国有：\n\n",to_chinese_kingdom(id) );
                if(!list = kingdom_data(id,"ally","query_all"))
                        str += "贵国尚无同盟国。\n\n";
                else {
                        for(i=0; i<sizeof(list);i++) {
                                str += sprintf("%s\n",full_kingdom(list[i]));
                        }
                        str += sprintf("\n共 %d 国。\n\n",sizeof(list));
                }
                return me->start_more(str);
                
}       

int do_time_check(object me)
{
        if(!me->query_temp("ally")) remove_call_out(do_time(me));
        else call_out("do_time", 6, me);
        return 1;
}

int do_time(object me)
{
        if( me->query_temp("ally") ) {
                me->delete_temp("ally");
                write("看样子对方好像不想与贵国结盟。\n");
        }
        return 1;
}
int help(object me)
{
        write(@HELP
指令格式 : ally with <国家>             :  送出结盟协议
           ally cancel with <国家>      :  终止结盟关系
           ally                         :  察看目前同盟的国家。
                                                                                
这个指令可以和其他国家结盟。结盟通常是表示互相友好之意, 也同时定下
了互不侵犯的协定, 所以在对同盟国宣战之前, 一定要先解除同盟关系。两
国结盟了以后, 双方的人民就可以互相通过关卡而互访, 除此之外, 并没有
其他权力义务关系。
                                                                                
结盟时, 需要两国大臣的同意, 而终止结盟时只要片面宣布就算生效了。

相关讯息 : declare

HELP
        );
        return 1;
}       
