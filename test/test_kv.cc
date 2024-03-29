#include <iostream>
#include <kcpolydb.h>
#include <string>

using namespace std;
using namespace kyotocabinet;

int main(int argc, char ** )
{
	PolyDB db;
	if (!db.open("casket.kch", PolyDB::OWRITER | PolyDB::OCREATE))
	{
		cerr<< "open error: "<< db.error().name() <<endl;
	}
	 // store records
	if (!db.set("foo", "hop") ||
	    !db.set("bar", "step") ||
	    !db.set("baz", "jump")) {
	  cerr << "set error: " << db.error().name() << endl;
	}
	// retrieve a record
	string value;
	if (db.get("foo", &value)) {
		cout << value << endl;
	} else {
		cerr << "get error: " << db.error().name() << endl;
	}

	// traverse records
	DB::Cursor* cur = db.cursor();
	cur->jump();
	string ckey, cvalue;
	while (cur->get(&ckey, &cvalue, true)) {
		cout << ckey << ":" << cvalue << endl;
	}
	delete cur;

	// close the database
	if (!db.close()) {
	  cerr << "close error: " << db.error().name() << endl;
	}

	return 0;
}