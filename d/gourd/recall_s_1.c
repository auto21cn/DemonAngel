//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/city/recall_s_1

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "南大街");
        set("long", @LONG
你来到了葫芦城的南大街。道路有着许多的行人在游览，这里已经是城
里的重点区域了，许许多多的重要设施都设于此，因此看来似乎平静无比，
往南边可以大致看到南门的样子啰，而往北边走就回中央广场了。
LONG
        );
        set("exits", ([
                "south" : __DIR__"recall_s_2",
                "north" : __DIR__"gourd_recall",
                "east"  : __DIR__"recall_s_e",
                "west"  : __DIR__"recall_s_w",
        ]));
        setup();
}
 



