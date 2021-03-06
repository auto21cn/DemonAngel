//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /adm/simul_efun/object.c

varargs int getoid(object ob)
{
	int id;

	if (!ob) ob = previous_object();
	sscanf(file_name(ob), "%*s#%d", id);
	return id;
}

// Get the owner of a file.  Used by log_error() in master.c.
string file_owner(string file)
{
    string name, rest, dir;

    if (file[0] != '/') {
        file = "/" + file;
    }
    if (sscanf(file, "/u/%s/%s/%s", dir, name, rest) == 3) {
        return name;
    }
    return 0;
}

// domain_file should return the domain associated with a given file.
string domain_file(string file)
{
	string domain;

	if( sscanf(file, "/d/%s/%*s", domain) )
		return domain;

	return ROOT_UID;
}

// creator_file should return the name of the creator of a specific file.
string creator_file(string file)
{
	string *path, euid;

	path = explode(file, "/") - ({ 0 });
	switch(path[0]) {
		case "adm":
		case "cmds":
			return ROOT_UID;
		case "u":
			if( this_player(1) ) euid = getuid(this_player(1));
			if( !euid ) euid = geteuid(previous_object(1));
			if( euid && euid != ROOT_UID ) return euid;
			return "NONAME";
		case "d":
		case "open":
			return DOMAIN_UID;
		default:
			return MUDLIB_UID;
	}
}

// author_file should return the name of the author of a specific file.
string author_file(string file)
{
	string name;

	if( sscanf(file, "/u/%*s/%s/%*s", name) )
		return name;
	return ROOT_UID;
}

void destruct(object ob)		// es2 1.2b
{
	string err;

	if (ob) {
		if( previous_object() )
			err = catch(ob->remove( geteuid(previous_object()) ));
		else
			err = catch(ob->remove(0));
		if( err ) {
			if( userp(ob) && geteuid(previous_object())!=ROOT_UID ) return;
			log_file("destruct", sprintf("[%s]%O[%O]\n%s\n", ctime(time()), ob, geteuid(previous_object()), err));
		}
		efun::destruct(ob);
	}
}
int zerop(mixed arg)
{
	if(sizeof(arg) == 0) return 1;
	return 0;
}

object load_player(string id)			// by bor @DA, 3/9 2003
{
	object ob;

	if(strsrch(id, ".") != -1) return 0;
	if(find_player(id)) return 0;
	ob = new(LOADUSER_OB);		// 请各位去追踪整个 restore 的过程, 各位就知道为什么又要多弄个 LOADUSER_OB了
	ob->set("id", id);		// LOADUSER_OB 参考自 LOGIN_OB 的写法的
	if(!ob->restore()) return 0;	// 原先的 USER_OB 没办法藉由 set("id", xx) 的方式去 restore() 出 object 除非修改
	return ob;			// USER_OB 的 query_save_file(), 因此既然它没上线, 弄一个 LOADUSER_OB出来也无不可
}

int exec( object to, object from )
{
	if(file_name(previous_object() ) != "/adm/daemons/logind" && file_name(previous_object() ) !="/cmds/wiz/update" )
		error("EXEC error somebody use ...");
	efun::exec(to, from);
}
