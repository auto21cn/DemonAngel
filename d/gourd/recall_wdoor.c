//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/city/recall_wdoor
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "西城门");
        set("long", @LONG
这里是葫芦城的西城门。城门口可以看到穿着全套盔甲的士兵在巡视，
看来如果想要在这里闹事要三思而行，许多的人们来来往往十分忙碌，感觉
起来颇为繁荣，而城门看起来十分的高大雄伟，令人望而生畏。
LONG
        );
        set("exits", ([
                "east"  : __DIR__"recall_w_2",
        ]));
        setup();
}
 






