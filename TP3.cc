#include <iostream>
#include <stdlib.h>
#include <utility>
#include <math.h>
#include <stdlib.h>

using namespace std;

int pick_X(pair<double,int> xi[],int size_proba){
	double tirage = rand()*1./RAND_MAX;
	double proba = 0;
	for(int i=0;i<size_proba;i++){
		proba += xi[i].first;
		if(tirage<proba){return xi[i].second;}
	}
}

int GW(pair<double,int> xi[],int size_proba,int size,bool print){
	int last_z=1,z,x;
	if(print){cout<<1<<endl;}
	for(int i=0;i<size;i++){
		z = 0;
		for(int j=1;j<=last_z;j++){
			x=pick_X(xi,size_proba);
			if(print){cout<<x<<" ";}
			z+=x;
		}
		if(print){cout<<endl;}
		last_z=z;
		if(z==0){return z;}
	}
	return z;
}

int main(int argc, char** argv){
	if(argc<4){
		cout<<"Veuillez entrer au moins 3 arguments : p0, p1, p2(, profondeur, precision)"<<endl;
		return 0;
	}
	int profondeur = (argc>4) ? atoi(argv[4]) : 50;
	int precision = (argc>5) ? atoi(argv[5]) : 10000;

	int size = 3;
	srand(time(NULL));

	int value;
	double z50=0;
	double sdev=0;
	int pext=0;

	pair<double,int> P[size] = {pair<double,int>(1./atoi(argv[1]),0),pair<double,int>(1./atoi(argv[2]),1),pair<double,int>(1./atoi(argv[3]),2)};
	for(int i=0;i<precision;i++){
		value=GW(P,size,profondeur,false);
		if(value==0){pext++;}
		z50+=value;
	}
	z50/=precision;
	cout<<"Moyenne de z"<<profondeur<<" : "<<z50<<" | Proba d'ext a "<<profondeur<<" : "<<pext*1./precision;
	for(int i=0;i<precision;i++){
		sdev+=pow(GW(P,size,profondeur,false)-z50,2);
	}
	sdev/=precision;
	cout<<" | Variance : "<<sdev<<endl;

	GW(P,size,min(profondeur,20),true);
}
