#include <iostream>
#include <list>
#include <math.h>
#include <stdlib.h>

using namespace std;

list<pair<double,int> > trie_p(list<pair<double,int> > p_in){
	pair<double,int> currentp = p_in.front();
	list<pair<double,int> > ptries = list<pair<double,int> >(1,currentp);
	list<pair<double,int> >::iterator it;
	while(p_in.size()>1){
		p_in.pop_front();
		currentp = p_in.front();
		for(it=ptries.begin();it!=ptries.end();it++){
			if(currentp.first<(*it).first){
				ptries.insert(it,currentp);
				break;
			}
		}
		if(it==ptries.end()){
			ptries.push_back(currentp);
		}
	}
	return ptries;
}

void alias(double probas[],int v[],int size_proba){
	int n=size_proba;
	int k=n;
	list<pair<double,int> > p_paires;
	double p[n];
	int y[n];

	list<pair<double,int> >::iterator it;

	for(int i=0;i<size_proba;i++){
		p_paires.push_back(pair<double,int>(probas[i],i+1));
	}
	while(k>0){
		p_paires = trie_p(p_paires);
		p[p_paires.front().second-1] = n*p_paires.front().first;
//		cout<<p_paires.front().second<<"["<<p[p_paires.front().second-1]<<",";
		y[p_paires.front().second-1] = v[p_paires.back().second-1];
//		cout<<y[p_paires.front().second-1]<<"]"<<endl;
		p_paires.back().first = p_paires.back().first-(1./n-p_paires.front().first);
		p_paires.pop_front();k--;
	}
	cout<<"j (P[j],Y[i])"<<endl;
	for(int i=0;i<n;i++){
		cout<<i<<" ("<<p[i]<<","<<y[i]<<")"<<endl;
	}
}

int main(int argc, char** argv){
	if(argc<4){
		cout<<"Veuillez entrer au moins 3 arguments : mode, p1 ou r, p2 ou n (, p3, p4...)"<<endl;
		return 0;
	}
	int size;
	string arg;
	if(atoi(argv[1])>1){
		arg = argv[2];
		double r = atoi(arg.substr(0,arg.find("/")).c_str())*1./atoi(arg.substr(arg.find("/")+1).c_str());
		size = atoi(argv[3])+1;
		double P[size];
		int V[size];
		for(int i=0;i<size;i++){
			P[i] = pow(r,i)*(1-r)/(1-pow(r,size));
			V[i] = i;
		}
		alias(P,V,size);
	}else{
		size = argc-2;
		double P[size];
		int V[size];
		for(int i=0;i<size;i++){
			arg = argv[i+2];
			P[i] = atoi(arg.substr(0,arg.find("/")).c_str())*1./atoi(arg.substr(arg.find("/")+1).c_str());
			V[i] = i+1;
		}
		alias(P,V,size);
	}
}
