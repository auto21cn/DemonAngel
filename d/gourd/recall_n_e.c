//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/city/recall_n_e

#include <room.h>

inherit WEDDING;

void create()
{
        set("short", "礼堂");
        set("long", @LONG
葫芦城中专门让两情相悦的情侣结为夫妻的地方

指令是: marry <男方> with <女方>
回答请用 answer yes

LONG
        );
        set("exits", ([
                "west" : __DIR__"recall_n_1",
        ]));
        setup();
        replace_program(WEDDING);
}



