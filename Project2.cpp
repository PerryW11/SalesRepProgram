// Project2.cpp :
// Perry Winch, Joey Silvanus, Kervens Jasmin
//Completed on 12/05/2019

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdio>

using namespace std;

class Territory;
class SalesRep;
class Transaction;

vector<string> trxVec;
vector<string> terrVec;
vector<string> srVec;

vector<Territory> terrobj;
vector<SalesRep> saleobj;
vector<Transaction> trxobj;

class Territory
{
private:
	string id;
	string type;
	int value = 0;

public:
	Territory(string id, string type)
	{
		this->id = id;
		this->type = type;
	}

	string get_type()
	{
		return this->type;
	}

	string get_id()
	{
		return this->id;
	}

	int get_value()
	{
		return this->value;
	}

	friend ostream &operator<<(ostream &astream, const Territory &terr)
	{
		astream << endl
				<< "ID:" << terr.id << endl;
		if (terr.type == "PREMIUM" || terr.type == "PREMIUM ")
		{
			astream << "Premium" << endl;
		}
		else
		{
			astream << "Normal" << endl;
		}
		astream << "Value: " << terr.value << endl;
		return astream;
	}

	void calculateAmount(string type, int value1)
	{
		if (type == "1")
		{
			this->value += value1;
		}

		if (type == "2")
		{
			this->value += value1;
		}

		if (type == "3")
		{
			this->value -= value1;
		}

		if (type == "4")
		{
			this->value -= value1;
		}

		if (type == "5")
		{
			this->value -= value1;
		}

		if (type == "6")
		{
			this->value -= value1;
		}
	}
};

class SalesRep
{
private:
	string id;
	Territory *terrid;
	int amount;
	string oldscore;

public:
	SalesRep(string id, string terrid, string amount)
	{
		this->id = id;
		this->amount = stoi(amount);
		for (int x = 0; x < terrobj.size(); x++)
		{
			if (terrid == ((terrobj[x]).get_id()))
			{
				this->terrid = &terrobj[x];
			}
		}
		this->oldscore = amount;
	}

	string get_id()
	{
		return this->id;
	}

	Territory &get_territory()
	{
		return *this->terrid;
	}

	int get_amount()
	{
		return this->amount;
	}

	string get_oldscore()
	{
		return this->oldscore;
	}

	friend ostream &operator<<(ostream &astream, const SalesRep &srep)
	{
		astream << "ID:" << srep.id << endl;
		astream << "Assigned Territory:" << *(srep.terrid);
		astream << "Salesrep Score:    " << srep.amount << endl;
		return astream;
	}

	void calculateAmount(string type, double amount1)
	{
		if (type == "1")
		{
			if (this->get_territory().get_type() == "PREMIUM" || this->get_territory().get_type() == "PREMIUM ")
			{
				amount1 *= 1.5;
			}
			this->amount += (amount1 * 1.1);
		}

		if (type == "2")
		{
			if (this->get_territory().get_type() == "PREMIUM" || this->get_territory().get_type() == "PREMIUM ")
			{
				amount1 *= 1.5;
			}
			this->amount += (amount1 * 1.1);
		}

		if (type == "3")
		{
			this->amount -= amount1;
		}

		if (type == "4")
		{
			this->amount -= (amount1 * 1.25);
		}

		if (type == "5")
		{
		}

		if (type == "6")
		{
			this->amount -= (amount1 * 1.1);
		}

		if (type == "7")
		{
			if (this->get_territory().get_type() == "PREMIUM" || this->get_territory().get_type() == "PREMIUM ")
			{
				amount1 *= 1.5;
			}
			this->amount += (amount1 * 0.75);
		}
	}
};

class Transaction
{
private:
	string trxid;
	SalesRep *salerepid;
	string type;
	int amount;

public:
	Transaction(string trxid, string salerepid, string type, string amount)
	{
		this->trxid = trxid;
		this->type = type;
		this->amount = stoi(amount);
		for (int x = 0; x < saleobj.size(); x++)
		{
			if (saleobj[x].get_id() == salerepid)
			{
				this->salerepid = &saleobj[x];
			}
		}
	}

	string get_type()
	{
		return this->type;
	}

	SalesRep &get_salesrep()
	{
		return *this->salerepid;
	}

	int get_amount()
	{
		return this->amount;
	}

	friend ostream &operator<<(ostream &astream, const Transaction &trx)
	{
		astream << "ID:" << trx.trxid << endl;
		astream << "Assigned Sales rep:" << endl
				<< *trx.salerepid << endl;
		astream << "Transaction Type:" << trx.type << endl;
		astream << "Transaction Amount:" << trx.amount << endl;
		return astream;
	}

	void do_math()
	{
		this->get_salesrep().get_territory().calculateAmount(this->get_type(), this->get_amount());

		this->get_salesrep().calculateAmount(this->get_type(), this->get_amount());
	}
};

class Parsing
{
private:
	string theFile;

public:
	void parseThis(string file)
	{
		ifstream infile(file);
		if (file == "transaction.txt")
		{
			ifstream trxFile("transaction.txt");
			string line;

			while (getline(trxFile, line))
			{
				trxVec.emplace_back(line);
			}
		}

		if (file == "salerep.txt")
		{
			ifstream srFile("salerep.txt");
			string line3;

			while (getline(srFile, line3))
			{
				srVec.emplace_back(line3);
			}
		}

		if (file == "territory.txt")
		{
			ifstream trrFile("territory.txt");
			string line2;

			while (getline(trrFile, line2))
			{
				terrVec.emplace_back(line2);
			}
		}
	}

	void makeObjects(vector<string> trxVec, vector<string> terrVec, vector<string> srVec)
	{
		for (int x = 0; x < terrVec.size(); x++)
		{
			vector<string> pieces;
			stringstream ss(terrVec[x]);
			string piece;
			while (getline(ss, piece, ','))
			{
				pieces.push_back(piece);
			}
			Territory terr(pieces[0], pieces[1]);
			terrobj.emplace_back(terr);
		}

		for (int x = 0; x < srVec.size(); x++)
		{
			vector<string> pieces;
			stringstream ss(srVec[x]);
			string piece;
			while (getline(ss, piece, ','))
			{
				pieces.push_back(piece);
			}
			SalesRep sr(pieces[0], pieces[1], pieces[2]);
			saleobj.emplace_back(sr);
		}

		for (int x = 0; x < trxVec.size(); x++)
		{
			vector<string> pieces;
			stringstream ss(trxVec[x]);
			string piece;
			while (getline(ss, piece, ','))
			{
				pieces.push_back(piece);
			}
			Transaction trx(pieces[0], pieces[1], pieces[2], pieces[3]);
			trxobj.emplace_back(trx);
		}
	}
};

void create_file()
{
	ofstream outputfile;
	outputfile.open("territory_output.txt");
	sort(terrobj.begin(), terrobj.end(), [](Territory lhs, Territory rhs) {
		return lhs.get_value() > rhs.get_value();
	});
	for (int x = 0; x < terrobj.size(); x++)
	{
		outputfile << terrobj[x].get_id() << ", " << std::setfill('0') << std::setw(7) << terrobj[x].get_value() << endl;
	}
	outputfile.close();
}

void update_file()
{
	fstream update;
	update.open("salerep.txt", ios::in | ios::out);
	update.seekg(0, update.end);
	int size = update.tellg();
	update.seekg(0, update.beg);
	char *buffer = new char[size];
	update.read(buffer, size);
	string wfile(buffer);
	string compare;
	for (int x = 0; x < saleobj.size(); x++)
	{
		compare = saleobj[x].get_oldscore();
		int position = wfile.find(compare);
		if (position != string::npos)
		{
			update.seekp(position);
			stringstream nfile;
			nfile << std::setw(7) << std::setfill('0') << saleobj[x].get_amount();
			string output = nfile.str();
			const char *input = output.c_str();
			update.write(input, 7);
		}
	}
	update.close();
}

int main()
{
	Parsing parse;
	parse.parseThis("territory.txt");
	parse.parseThis("salerep.txt");
	parse.parseThis("transaction.txt");
	parse.makeObjects(trxVec, terrVec, srVec);

	for (int x = 0; x < trxobj.size(); x++)
	{
		trxobj[x].do_math();
	}

	create_file();
	update_file();

	sort(saleobj.begin(), saleobj.end(), [](SalesRep lhs, SalesRep rhs) {
		return lhs.get_amount() > rhs.get_amount();
	});

	for (int x = 0; x < saleobj.size(); x++)
	{
		cout << saleobj[x].get_id() << ", " << saleobj[x].get_amount() << endl;
	}
}