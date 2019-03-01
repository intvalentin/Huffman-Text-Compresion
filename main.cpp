#include <iostream>
#include <queue>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;


class Huffman {

public:

	void text(string txt);
	void BuildTree();
	int freq();
	void Afisare();
	void CompresieAfisare();


private:

	struct Tree {
		char simbol;
		float freq=0.00;
		float Total=0.00;
		int nr=0;
		Tree *left = NULL;
		Tree *right = NULL;
	 };
	list<struct Tree> myList;
	list<struct Tree> mList;
	list<int>Compresie;

	typedef Tree *pointer;
	pointer Root,Temp;
    int a=0,b=0,c=a,d=b;
	void AfisarePrivate(pointer aux,int p,int k);
};


int main() {
	Huffman huff;
	ifstream str;
	string a;
	str.open("str.txt");
	if (!str.is_open()) {
		exit(EXIT_FAILURE);
	}

	getline(str, a);
	//cout << endl << a << endl;


	huff.text(a);
	huff.freq();
	huff.BuildTree();
	huff.Afisare();

	getchar();

}

void Huffman::text(string txt) {
	int a = txt.length(), i,j,aux=0;
	Tree temp,auxa;
	list<struct Tree>::iterator it,ij;


	for (i = 0;i < a;i++) {
		temp.simbol = txt[i];
		temp.nr = 0;

		for (j = 0;j < a;j++) {
			if (temp.simbol == txt[j]) {
				temp.nr+=1;
			}

		}
		for (it = myList.begin(); it != myList.end(); ++it) {
			if (temp.simbol == it->simbol) {
				aux += 1;
			}
		}
		if (aux ==0) {

			myList.push_back(temp);
		}
		aux = 0;

	}

	cout << "mylist contains:";
	for (it = myList.begin();it != myList.end();++it) {
		cout << it->simbol << " " << it->nr << endl;
	}
	cout << "--------------" << endl;
	aux = 0;

	for (it = myList.begin(); it != myList.end(); ++it) {

		for (ij = it; ij != myList.end(); ++ij) {

			if (it->nr > ij->nr) {
				auxa.simbol = it->simbol;
				auxa.nr = it->nr;
				it->simbol = ij->simbol;
				it->nr = ij->nr;
				ij->simbol = auxa.simbol;
				ij->nr = auxa.nr;
			}

		}


	}
	/*
	for (it = mList.begin();it != mList.end();++it) {
		cout << it->simbol << " " << it->nr << endl;
	}
	*/
	cout << "--------------" << endl;
	for (it = myList.begin();it != myList.end();++it) {
		it->left = NULL; it->right = NULL;
		cout << it->simbol << " " << it->nr << endl;
	}


}

void Huffman::BuildTree() {
	cout << endl<<"--------Build Tree--------";
	list<struct Tree>::iterator it;
	queue<struct Tree> Jumate;
	Tree a;
	float verificare=0;
	int backup=0;
	Temp = new Tree;	Root = Temp;

	for (it = myList.begin();it != myList.end();++it) {
		verificare = verificare + it->freq;
		Jumate.push(*it);
		backup += 1;
		if (verificare > 50)
			break;
	}
	a = Jumate.front();
	//cout << endl << a.simbol;
	pointer aux,auxb;
	while (!Jumate.empty()) {

		if (!Jumate.empty()) {
			Temp->left = &Jumate.front();
			cout << endl << Temp->left->simbol;
			Jumate.pop();
			Temp->Total += Temp->left->freq;
			//cout << endl << Temp->Total;
		}

		if (!Jumate.empty()) {
			Temp->right = &Jumate.front();
			Jumate.pop();
			Temp->Total += Temp->left->freq;
			//cout << endl << Temp->Total;
		}
	//	cout << endl << Temp->Total;

		if (Root != Temp) {
			aux = new Tree;
			aux->left = Root;
			aux->right = Temp;
			Root = aux;
			Root->Total = Root->left->Total + Root->right->Total;
		}

		if(!Jumate.empty())
			Temp = new Tree;

	}
	//cout <<endl<<"Root Total="<< Root->Total<<endl<<"Left Tree Total="<<Root->left->Total<<endl<<"Right Tree Total="<<Root->right->Total;
	it = myList.begin();
	while (backup > 0) {
		++it;
		--backup;
	}
	while (it != myList.end()) {
		Jumate.push(*it);
		++it;
	}

	Temp = new Tree; auxb = Temp;
	while (!Jumate.empty()) {
		if (!Jumate.empty()) {
			Temp->left = &Jumate.front();
			Jumate.pop();
			Temp->Total += Temp->left->freq;
			//cout << endl << Temp->Total;
		}

		if (!Jumate.empty()) {
			Temp->right = &Jumate.front();
			Jumate.pop();
			Temp->Total += Temp->left->freq;
			//cout << endl << Temp->Total;
		}
		if (auxb != Temp) {
			aux = new Tree;
			aux->left = Root;
			aux->right = Temp;
			auxb = aux;
			auxb->Total = auxb->left->Total + auxb->right->Total;
		}

		if (!Jumate.empty())
			Temp = new Tree;
	}

	//Final Root
	aux = new Tree;
	aux->left = Root;
	aux->right = auxb;
	Root = aux;
	Root->Total = Root->left->Total + Root->right->Total;
	cout << endl << "-----Root final(should be around 100%[might be little error])-----" << endl << "Total=" << Root->Total <<endl<< "Left tree=" << Root->left->Total << endl << "Right tree=" << Root->right->Total<<endl;


}

int Huffman::freq() {
	int total=0;
	float calc, a, b;
	list<struct Tree>::iterator it;

	for (it = myList.begin();it != myList.end();++it)
		total = total + it->nr;

	for (it = myList.begin();it != myList.end();++it) {
		a = it->nr;b = total; calc = (a / b) * 100;
		it->freq = calc;
		cout << endl << calc;
	}

	return total;
}

void Huffman::Afisare() {
	AfisarePrivate(Root,a,b);
}

void Huffman::AfisarePrivate(pointer x,int p,int k){


	//cout << endl << x->simbol;
	if (x != NULL) {

		if (x->left != 0) {
                ++a;
            Compresie.push_back(0);

			AfisarePrivate(x->left,a,b);
            if(x->left!=0){
                    --a;
			CompresieAfisare();
            }
		}
		//cout << aux->numar << " ";
		if(x->freq!=0){
		cout << endl << x->simbol<<" <-> ";


	    }
		if (x->right != 0) {
                ++b;
                //cout<<endl<<"K="<<k;
                while(p>0){
                    Compresie.push_back(0);
                    --p;
                }
                while(k>0){

                    Compresie.push_back(1);
                    --k;
                }

            Compresie.push_back(1);
			AfisarePrivate(x->right,a,b);
			if(x->left!=0){
                --b;
			CompresieAfisare();
			}
		}
	}
	else {
		cout << "[Arborele este gol]";
	}

}

void Huffman::CompresieAfisare(){
    ofstream compresie;
    compresie.open("compresie.txt",ios::app);
    list<int>::iterator it;

    for(it=Compresie.begin();it!=Compresie.end();++it){
        compresie<<*it;
        cout<<*it;
    }

    Compresie.clear();
}
