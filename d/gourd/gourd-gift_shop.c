//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /d/gourd/gourd-gift_shop.c

#include <ansi.h>
#include <room.h>

inherit GIFT_SHOP;

void create()
{
	set("short", "【礼品店】");
	set("long", @TEXT
这里一走近来就看到不少的礼品呈现于此, 年关将近, 人来人往的
争相购买, 住在葫芦镇内的当地人都知道这是一家非常出名的老店, 除
了料好口碑不错外, 老板娘是一位活拨外向极具亲和力, 就连出门在外
的冒险者差不多都感受其活力。如果你想要选购(buy)礼品, 请慢慢观
赏(list)一番。
TEXT
	);
	set("outdoors", 1);
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/d/gourd/3.c",
]));
	setup();
}
