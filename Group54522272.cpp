#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

struct NODE {
	int index;
	string data;
	NODE* next;
};
NODE* createNode(int index, string data) {
	NODE* p = new NODE;
	p->index = index;
	p->data = data;
	p->next = NULL;
	return p;
}
void insertNode(NODE* &dictionary, int index, string data) {
	NODE* p = createNode(index, data);
	if(dictionary == NULL)
		dictionary = p;
	else {
		NODE* t = dictionary;
		while(t->next != NULL)
			t = t->next;
		t->next = p;
	}
}
void printList (NODE* head) {
	if (head == NULL)
		cout << "Danh sach lien ket rong. \n";
	else
		for (NODE* p = head; p != NULL; p = p->next)
			cout << p->data << ": " << p->index << endl;
}
int search(NODE* dictionary, string data) {
	for(NODE* p = dictionary; p != NULL; p = p->next)
		if(data == p->data)
			return p->index;
	return -1;
}
string findI(NODE* dictionary, int index) {
	string a = "";
	for(NODE* p = dictionary; p != NULL; p = p->next)
		if(index == p->index)
			return p->data;
	return a;
}
vector<int> encoding(string input, NODE* &dictionary) {
	string prev = "", output = "";
	dictionary = NULL;
	int n = input.length(), i = 0, index = 256;
	vector<int> result;
	while(i <= n) {
		string temp = prev + input[i];
		if(temp.length() == 1)
			prev = temp;
		else if(search(dictionary, temp) == -1) {
			if(prev.length() == 1)
				result.push_back((int)prev[0]);
			else
				result.push_back(search(dictionary, prev));
			if(i != n)
				insertNode(dictionary, index++, temp);
			prev = input[i];
		} else
			prev = temp;
		i++;
	}

	return result; 
}
string convert(int a, NODE* dictionary) {
	string str = "";
	if(a < 256)
		str = (char)a;
	else
		str = findI(dictionary, a);
	return str;
}
bool checkInDictionary(string a, NODE* dictionary) {
	if(a.length() == 1)
		return true;
	else if(search(dictionary, a) != -1)
		return true;
	return false;
}
string decoding(vector<int> input, NODE* &dictionary) {
	dictionary = NULL;
	string prev = "", output = "", cur = "";
	int n = input.size(), index = 256, pW, cW, i = 1;
	cW = input[0];
	output += (char)cW;
	while(i < n) {
		pW = cW;
		cW = input[i];
		cur = convert(cW, dictionary);
		prev = convert(pW,dictionary);
		if(checkInDictionary(cur, dictionary)) {
			output += cur;
			insertNode(dictionary, index++, prev + cur[0]);
		} else {
			cur = prev[0];
			output += prev;
			output += cur;
			insertNode(dictionary, index++, prev + cur);
		}
		i++;
	}
	return output;
}

void read_encoding(string file_1, string file_2) {
	ifstream ifi;
	ifi.open(file_1.c_str());
	
	fstream ofi;
	ofi.open(file_2.c_str(), ios::out | ios::ate | ios::binary);
	
	if(!ifi.is_open()) {
		return;
	}
	string str;
	NODE* head = NULL;
	while(!ifi.eof()) {
		getline(ifi, str, '\n');
		
		vector<int> a = encoding(str, head);
		int n = a.size();

	
		ofi.write((char*)(&a), sizeof(int)*n);

	}
	
	ifi.close();
	ofi.close();
}

void read_encoding_p(string file_1, string file_2) {
	ifstream ifi;
	ifi.open(file_1.c_str());
	
	fstream ofi;
	ofi.open(file_2.c_str(), ios::out | ios::ate | ios::binary);
	
	if(!ifi.is_open()) {
		return;
	}
	string str;
	NODE* head = NULL;
	while(!ifi.eof()) {
		getline(ifi, str, '\n');
		vector<int> a = encoding(str, head);
		int n = a.size();

		ofi.write((char*)(&n), sizeof(int));
		ofi.write((char*)(&a), sizeof(int)*n);
		if (head == NULL)
			cout << "Danh sach lien ket rong. \n";
		else {
			for (NODE* p = head; p != NULL; p = p->next)
			cout << p->data << ": " << p->index << endl;
		}
	}
	
	ifi.close();
	ofi.close();
}

void read_decoding(string file_1, string file_2) {
	fstream f;
	f.open(file_1, ios::in | ios::binary | ios::ate);
	ofstream ofi;
	ofi.open(file_2.c_str());
	if(!f.is_open())
	{
		cout << "Khong the mo file";
		return;
	}
	vector<int> a;
	f.seekg(0, ios::end);
	int n = f.tellg()/sizeof(int);
	f.seekg(0, ios::beg);
		f.read((char *)(&a), sizeof(int)*n);
	f.close();
	NODE* head = NULL;
	string b = decoding(a, head);
	ofi << b;
	ofi.close();
}
void read_decoding_p(string file_1, string file_2) {
	fstream f;
	f.open(file_1, ios::in | ios::binary | ios::ate);
	ofstream ofi;
	ofi.open(file_2.c_str());
	if(!f.is_open())
	{
		cout << "Khong the mo file";
		return;
	}
	vector<int> a;
	f.seekg(0, ios::end);
	int n = f.tellg()/sizeof(int);
	f.seekg(0, ios::beg);
		f.read((char *)(&a), sizeof(int)*n);
	f.close();
	NODE* head = NULL;
	string b = decoding(a, head);
	ofi << b;
	if (head == NULL)
		cout << "Danh sach lien ket rong. \n";
	else {
		for (NODE* p = head; p != NULL; p = p->next)
		cout << p->data << ": " << p->index << endl;
	}
	ofi.close();
}
int main(int argc, char** argv) {
	NODE* p = NULL;

	if (argc != 5)
    	return -1;
    //C:\Users\HP\Desktop\vy\Untitled1.exe e C:\Users\HP\Desktop\vy\file.txt C:\Users\HP\Desktop\vy\vyvy.bin d
    string argv1 = string(argv[1]);
    string argv4 = string(argv[4]);
	if (argv1 == "-e")
    {
		if(argv4 == "-i") {
			read_encoding(argv[2],argv[3]);
		} else if(argv4 == "-d" || argv4 == "-ind") {
			read_encoding_p(argv[2],argv[3]);
		} else {
			cout << "Khong hop le !" << endl;
		}
	}
    
    else if (argv1 == "-d")
    {	
		if(argv4 == "-i") {
			read_decoding(argv[2],argv[3]);
		} else if(argv4 == "-d" || argv4 == "-ind") {
			read_decoding_p(argv[2],argv[3]);
		} else {
			cout << "Khong hop le !" << endl;
		}
	}
	else 	
		cout << "Khong hop le !";

	return 0;
}
