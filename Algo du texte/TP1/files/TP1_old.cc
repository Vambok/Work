/*========================================================================
Fichier Canevas_TP.cc 
Cours d'algorithmique du texte GMIN109 - Universite Montpellier 2
Année 2013-14

Cree par Severine Berard, modifie par Peter-Mikhael Richard
=========================================================================*/
#include <iostream>
#include <fstream> //pour lire les fichiers
#include <string>
#include <map> //pour les tableaux associatifs
#include <algorithm> //pour min et fill_n
#include <list> //pour list

using namespace std;

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// NAIF ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void naif(string P, int m, string T, int n)
{
int j,occurences=0,steps=0;
	for(int i=0;i<n-m+1;i++){
		for(j=0;j<m;j++){
			steps++;
			if(T[i+j+1]!=P[j+1]){
				break;
			}
		}
		if(j==m){
			occurences++;
		}
	}
	cout<<"J'ai trouve "<<occurences<<" occurences de P dans T en "<<steps<<" etapes."<<endl;
}

//////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// MP /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
int * calcule_MP_next(string P, int m)
{
int* MP_next=new int[m+1];
int j=-1;
	MP_next[0]=-1;
	for(int i=0;i<m;i++){
		while((j>=0)&&(P[i+1]!=P[j+1])){
			j=MP_next[j];
		}
		j++;
		MP_next[i+1]=j;
	}
return MP_next;
}

void MP(string P, int m, string T, int n, int* MP_next)
{
int j=0,steps=0,occurences=0;
	for(int i=0;i<n-m+1;i++){
		while(j>=0){
			steps++;
			if(T[i+1]!=P[j+1]){
				j=MP_next[j];
			}else{
				break;
			}
		}
		j++;
		if(j==m){
			occurences++;
			j=MP_next[j];
		}
	}
	cout<<"J'ai trouve "<<occurences<<" occurences de P dans T en "<<steps<<" etapes."<<endl;
delete [] MP_next;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// KMP /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
int * calcule_KMP_next(string P, int m)
{
int* KMP_next=new int[m+1];
int j=-1;
	KMP_next[0]=-1;
	for(int i=0;i<m;i++){
		while((j>=0)&&(P[i+1]!=P[j+1])){
			j=KMP_next[j];
		}
		j++;
		if(i>m-2){
			KMP_next[i+1]=j;
		}else if(P[i+2]!=P[j+1]){
			KMP_next[i+1]=j;
		}else{
			KMP_next[i+1]=KMP_next[j];
		}
	}
return KMP_next;
}

//////////////////////////////////////////////////////////////////////////////
////////////////////////////// Boyer-Moore ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

int * calcule_suff(string P, int m)
{
int* suff = new int[m];suff[m-1] = m;
int g = m;int f;
	for(int i=m-1;i>0;i--){
		if((i>g)&&(suff[i+m-f-1]!=i-g)){
			suff[i-1]=min(suff[i+m-f-1],i-g);
		}else{
			f=i;g=min(g,i);
			while((g>0)&&(P[g]==P[g+m-f])){g--;}
			suff[i-1]=f-g;
		}
	}
return suff;
}

int * calcule_D(string P, int m)
{
int* suff = calcule_suff(P,m);
int* D = new int[m+1];fill_n(D,m,m);
int j = 1;
	for(int i=m-1;i>=0;i--){
		if((i==0)||(suff[i-1]==i)){
			while(j<=m-i){
				D[j] = m-i;
				j++;
			}
		}
	}
	for(int i=1;i<m;i++){
		D[m-suff[i-1]] = m-i;
	}
delete [] suff;
return D;
}

map<char,list<int> > calcule_R(string P, int m)
{
map<char,list<int> > table;
	for(int i=1;i<=m;i++){
		if(table[P[i]].size()==0){
			table[P[i]] = list<int>(1,i);
		}else{
			table[P[i]].push_front(i);
		}
	}
/*for(int i=1;i<m+1;i++){
	list<int>::iterator it;
	for(it=table[P[i]].begin();it!=table[P[i]].end();it++){
		cout<<*it<<endl;
	}
}*/
return table;
}

void BM(string P, int m, string T, int n, bool forte=false)
{
int* D=calcule_D(P,m);
map<char,list<int> > R=calcule_R(P,m);
int i=1, occurences=0, steps=0;
	while(i<n-m+2){
		int j = m;
		while(j>0){
			steps++;
			if(P[j]!=T[i+j-1]){break;}
			j--;
		}
		if(j==0){
			occurences++;cout<<i<<endl;
			i+=D[1];
		}else{
			if(forte){
				list<int> k = R[T[i+j-1]];
				list<int>::iterator it;
				for(it=k.begin();it!=k.end();it++){
					if(*it<j){break;}
				}
				i+=max(D[j],j-*it);
			}else{
				i+=max(D[j],j-R[T[i+j-1]].front());
			}
		}
	}
	cout<<"J'ai trouve "<<occurences<<" occurences de P dans T en "<<steps<<" etapes."<<endl;
delete [] D;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// main ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
if (argc != 3)
	{
	cout<<"Mauvaise utilisation du programme "<<argv[0]<<", on attend :"<<endl;
	cout<<argv[0]<<" ficMotif ficTexte"<<endl;
	}
else
	{
	/* Lecture du motif */
	string line;
	string nomFicMotif (argv[1]);
	ifstream IfFicMotif (nomFicMotif.c_str(), ios::in);
	if (!IfFicMotif)
		{
		cout<<endl<<"Impossible d'ouvrir le fichier : "<<nomFicMotif<<endl<<endl;
		return(0);
		}
	string P = "#"; //Pour que la première lettre de P soit à l'indice 1
	while(getline(IfFicMotif,line)){P+=line+'\n';}
	P=P.substr(0,P.size()-1);
	int m=P.size()-1;

	/* Lecture du texte */
	string nomFicTexte(argv[2]);
	ifstream IfFicTexte (nomFicTexte.c_str(), ios::in);
	if (!IfFicTexte)
		{
		cout<<endl<<"Impossible d'ouvrir le fichier : "<<nomFicTexte<<endl<<endl;
		return(0);
		}
	string T = "#"; //Pour que la première lettre de T soit à l'indice 1
	while(getline(IfFicTexte,line)){T+=line+'\n';}
	T=T.substr(0,T.size()-1);
	int n=T.size()-1;

	cout<<"********************************************************************"<<endl;
	cout<<"Recherche du motif de taille "<<m<<" P="<<P.substr(1,P.size())<<endl;
	cout<<"Dans le texte de taille "<<n<<" T="<<T.substr(1,T.size())<<endl;
	cout<<"********************************************************************"<<endl<<endl<<endl;

	cout<<"************* Recherche naive *************"<<endl;
	naif(P,m,T,n);
	cout<<"###############################"<<endl<<endl;

	cout<<"************* Recherche avec MP *************"<<endl;
	MP(P,m,T,n,calcule_MP_next(P,m));
	cout<<"################################"<<endl<<endl;

	cout<<"************* Recherche avec KMP *************"<<endl;
	MP(P,m,T,n,calcule_KMP_next(P,m));
	cout<<"################################"<<endl<<endl;

	cout<<"************* Recherche avec Boyer-Moore *************"<<endl;
	BM(P,m,T,n);
	cout<<"************* Recherche avec Boyer-Moore (R forte) *************"<<endl;
	BM(P,m,T,n,true);
	cout<<"################################"<<endl;
	}
}
