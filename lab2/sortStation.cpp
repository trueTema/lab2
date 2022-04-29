#include "sortStation.h"



void sort(queue<my_pair>& src) {
	queue<string> cur(ListType);
	for (int i = 0; i < src.GetLength(); i++) {
		if (cur.GetLength() == 0 || !cur.find(src.front().type())) {
			cur.push(src.front().type());
		}
		src.push(src.front());
		src.pop();
	}
	stack<my_pair> st(ListType);
	while(cur.GetLength()) {
		string cur_type = cur.front();
		for (int j = 0; j < src.GetLength(); j++) {
			if (src.front().type() == cur_type) {
				st.push(src.front());
				src.pop();
				j--;
			}
			else {
				src.push(src.front());
				src.pop();
			}
		}
		cur.pop();
	}
	while (st.GetLength()) {
		src.push(st.top());
		st.pop();
	}
	while (src.GetLength()) {
		st.push(src.front());
		src.pop();
	}
	while (st.GetLength()) {
		src.push(st.top());
		st.pop();
	}
}

 void getSourceQueue(queue<my_pair>& res) {
	int n;
	cout << "¬ведите количество вагонов:" << endl;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string a;
		int b;
		cout << "¬ведите тип и номер " << i+1 <<"-го вагона:" << endl;
		cin >> a >> b;
		my_pair cur(a,b);
		res.push(cur);
	}
}

bool my_pair::operator==(my_pair a) {
	return this->type() == a.type()&& this ->num()== a.num();
}
bool my_pair::operator!=(my_pair a) {
	return !(this->type() == a.type() && this->num() == a.num());
}

std::ostream& operator << (std::ostream& os, my_pair& mp) {
	os << "<" << mp.type() << ", " << mp.num() << ">";
	return os;
}

my_pair::my_pair(string a, int b) {
	this->num_name = b;
	this->type_name = a;
}
string my_pair::type() {
	return this->type_name;
}
size_t my_pair::num() {
	return this->num_name;
}
my_pair::my_pair() {
	this->num_name = 0;
	this->type_name = "";
}