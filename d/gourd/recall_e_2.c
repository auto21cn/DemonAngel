//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/city/recall_e_2
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "南大街");
        set("long", @LONG
你来到了葫芦城的东大街。感觉起来这里的气氛十分热闹，有着很多的
人们在这里闲晃交谈，很多的第一手资料和新闻都可以在这里听到，所以常
常有人在这里待着，往东边过去就是葫芦城的东门，而往西边走就回中央广
场了。
LONG
        );
        set("exits", ([
                "west" : __DIR__"recall_e_1",
                "east"  : __DIR__"recall_edoor",
        ]));
        setup();
}
 




