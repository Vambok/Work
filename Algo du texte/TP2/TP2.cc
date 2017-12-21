/*==========================================================================
Cours d'algorithmique du texte HMSN116M - Universite Montpellier 2 - 2017-18

Cree par Severine Berard, modifie par Peter-Mikhael Richard
==========================================================================*/
#include <iostream>
#include <fstream> //pour lire les fichiers
#include <string>
#include <map> //pour les tableaux associatifs
#include <algorithm> //pour min, max et fill_n
#include <list>
#include <math.h> //pour log

#include "Arbre.cpp"
using namespace std;

bool affich_mode;
int steppretrait;

// affichage
void affichage(list<int> mots[], int size){
	int nb_occur;
	list<int>::iterator it;
	for(int i=0;i<size;i++){
		nb_occur = mots[i].size();
		if(nb_occur>0){
			cout<<nb_occur<<" occurences du motif "<<i;
			if(affich_mode){
				cout<<" :";
				for(it=mots[i].begin();it!=mots[i].end();it++){
					cout<<" "<<*it<<",";
				}
			}
			cout<<endl;
		}
	}
}
void affichage(list<int> occurences){
	list<int> mots[1];
	mots[0] = occurences;
	affichage(mots, 1);
}

// NAIF
void naif(string P, int m, string T, int n){
	list<int> occurences;
	int j,stepreads=0,steps=0;
	steps+=5;

	for(int i=0;i<n-m+1;i++){
		steps+=5;
		for(j=0;j<m;j++){
			steps+=4;
			stepreads++;
			if(T[i+j]!=P[j]){
				break;
			}
			steps++;
		}
		if(j==m){
			steps++;
			occurences.push_back(i);
		}
	}

	affichage(occurences);
	cout<<"T = "<<steppretrait<<"+"<<steps<<"("<<stepreads<<")"<<endl;steppretrait=0;
}

// MP
int* calcule_MP_next(string P, int m){
	int* MP_next=new int[m+1];
	int j=-1;
	steppretrait+=9;

	MP_next[0]=-1;
	for(int i=0;i<m;i++){
		steppretrait+=8;
		while((j>=0)&&(P[i]!=P[j])){
			steppretrait+=6;
			j=MP_next[j];
		}
		j++;
		MP_next[i+1]=j;
	}

	return MP_next;
}

void MP(string P, int m, string T, int n, int* MP_next){
	list<int> occurences;
	int j=0,stepreads=0,steps=0;
	steps+=7;

	for(int i=0;i<n-m+1;i++){
		steps+=5;
		while(j>=0){
			steps+=4;
			stepreads++;
			if(T[i]!=P[j]){
				steps+=2;
				j=MP_next[j];
			}else{
				break;
			}
		}
		j++;
		if(j==m){
			steps+=3;
			occurences.push_back(i-m+1);
			j=MP_next[j];
		}
	}

	delete [] MP_next;
	affichage(occurences);
	cout<<"T = "<<steppretrait<<"+"<<steps<<"("<<stepreads<<")"<<endl;steppretrait=0;
}

// KMP
int * calcule_KMP_next(string P, int m){
	int* KMP_next=new int[m+1];
	int j=-1;
	steppretrait+=9;

	KMP_next[0]=-1;
	for(int i=0;i<m;i++){
		steppretrait+=9;
		while((j>=0)&&(P[i]!=P[j])){
			steppretrait+=6;
			j=KMP_next[j];
		}
		j++;
		if(i>m-2){
			KMP_next[i+1]=j;
		}else if(P[i+1]!=P[j]){
			steppretrait+=3;
			KMP_next[i+1]=j;
		}else{
			steppretrait+=4;
			KMP_next[i+1]=KMP_next[j];
		}
	}

	return KMP_next;
}

// Boyer-Moore
int * calcule_suff(string P, int m){
	int* suff = new int[m];suff[m-1] = m;
	int g = m;int f;
	steppretrait+=10;

	for(int i=m-1;i>0;i--){
		steppretrait+=8;
		if((i>g)&&(suff[i+m-f-1]!=i-g)){
			suff[i-1]=min(suff[i+m-f-1],i-g);
		}else{
			steppretrait+=5;
			f=i;g=min(g,i);
			while((g>0)&&(P[g-1]==P[g+m-f-1])){steppretrait+=5;g--;}
			suff[i-1]=f-g;
		}
	}

	return suff;
}

int * calcule_D(string P, int m){
	int* suff = calcule_suff(P,m);
	int* D = new int[m];fill_n(D,m,m);
	int j = 0;
	steppretrait+=14+m;

	for(int i=m-1;i>=0;i--){
		steppretrait+=5;
		if((i==0)||(suff[i-1]==i)){
			steppretrait++;
			while(j<m-i){
				steppretrait+=3;
				D[j] = m-i;
				j++;
			}
		}
	}
	for(int i=1;i<m;i++){
		steppretrait+=4;
		D[m-suff[i-1]-1] = m-i;
	}

	delete [] suff;
	return D;
}

map<char,list<int> > calcule_R(string P, int m){
	map<char,list<int> > table;
	steppretrait+=5;

	for(int i=0;i<m;i++){
		steppretrait+=7+((table.size()>0)?(int)log(table.size()):0);
		if(table[P[i]].size()==0){
			table[P[i]] = list<int>(1,i+1);
		}else{
			steppretrait+=(int)log(table.size());
			table[P[i]].push_front(i+1);
		}
	}

//	for(int i=0;i<m;i++){
//		list<int>::iterator it;
//		for(it=table[P[i]].begin();it!=table[P[i]].end();it++){
//			cout<<*it<<endl;
//		}
//	}
	return table;
}

void BM(string P, int m, string T, int n, bool forte=false){
	int* D=calcule_D(P,m);
	map<char,list<int> > R=calcule_R(P,m);
	list<int> occurences;
	int i=0,stepreads=0,steps=0;
	steps+=9;

	while(i<n-m+1){
		steps+=8;
		int j = m-1;
		while(j>=0){
			steps+=4;
			stepreads++;
			if(P[j]!=T[i+j]){break;}
			j--;
			steps++;
		}
		if(j<0){
			occurences.push_back(i);
			i+=D[0];
		}else{
			steps+=2+((R.size()>0)?(int)log(R.size()):0);
			if(forte){
				steps+=6;
				list<int> k = R[T[i+j]];
				list<int>::iterator it;
				for(it=k.begin();it!=k.end();it++){
					steps+=3;
					if(*it<j+1){break;}
					steps++;
				}
				i+=max(D[j],j-*it+1);
			}else{
				i+=max(D[j],j-R[T[i+j]].front()+1);
			}
		}
	}

	delete [] D;
	affichage(occurences);
	cout<<"T = "<<steppretrait<<"+"<<steps<<"("<<stepreads<<")"<<endl;steppretrait=0;
}

// TVSBS
// Decalage :
// m+2-max(R(ab),R(b))
// =
// MVB	 TVSBS=R(ab)
// avec R:
// max:  min:
// m+1	  1		: P[m]='a'
// i+1	m-i+1	: P[i]P[i+1]='ab'
//  1	 m+1	: P[1]='b'
//  0	 m+2
map<unsigned short,int> calcule_biR(string P, int m){
	map<unsigned short,int> table;
	unsigned char currentchar = P[0];
	steppretrait+=10;

	table[currentchar] = 1; //P[0]='b'
	for(int i=1;i<m;i++){
		steppretrait+=6;
		table[currentchar<<8|(unsigned char)P[i]] = i+1; //P[i-1]P[i]='ab'
		currentchar = P[i];
	}
	table[currentchar<<8] = m+1; //P[m-1]='a'

	return table;
}

void TVSBS(string P, int m, string T, int n){
if(m<2){
	cout<<"TVSBS ne peut pas chercher un motif de taille 1 !"<<endl;
}else{
	map<unsigned short,int> R=calcule_biR(P,m);
	unsigned short nextchar_a;
	unsigned char nextchar_b;
	list<int> occurences;
	int i=0,stepreads=0,steps=0,j; //i:premier indice de T dans fenetre ; j:indice dans fenetre
	steps+=9;

	while(i<n-m+1){
	// Stage1:
		steps+=5;
		stepreads++;
		if(T[i+m-1]==P[m-1]){
			steps+=3;
			stepreads++;
			if(T[i]==P[0]){
			// Stage2:
				steps+=3;
				for(j=m-2;j>0;j--){
					steps+=4;
					stepreads++;
					if(T[i+j]!=P[j]){break;}
					steps++;
				}
				if(j<1){steps++;occurences.push_back(i);}
			}
		}
	// Stage3:
		if(i>n-m-1){
			i++;
		}else{
			steps+=9+3*((R.size()>0)?(int)log(R.size()):0);
			if(i==n-m-1){nextchar_b = 0;}else{steps++;stepreads++;nextchar_b = (unsigned char)T[i+m+1];} //gestion de fin de chaine
			stepreads++;
			nextchar_a = (unsigned char)T[i+m]<<8;
			i += m+2-max(R[nextchar_a|nextchar_b],max(R[nextchar_a],R[nextchar_b]));
		}
	}

	affichage(occurences);
	cout<<"T = "<<steppretrait<<"+"<<steps<<"("<<stepreads<<")"<<endl;steppretrait=0;
}}
/*
map<unsigned short,list<int> > calcule_MVbiR(string P, int m){
	map<unsigned short,list<int> > table;
	unsigned char currentchar = P[0];

	table[currentchar].push_back(1); //P[0]='b'
	for(int i=1;i<m;i++){
		table[currentchar<<8|(unsigned char)P[i]].push_front(i+1); //P[i-1]P[i]='ab'
		currentchar = P[i];
	}

	return table;
}

void MTVSBS(string P, int m, string T, int n){
if(m<2){
	cout<<"MTVSBS ne peut pas chercher un motif de taille 1 !"<<endl;
}else if(m>64){
	cout<<"MTVSBS ne peut pas chercher un motif de taille > 64 !"<<endl;
}else{
	map<unsigned short,list<int> > R=calcule_biR(P,m);
	list<int> foundpos;
	long long compared=0;
	long long mask=~(-1<<m);
	unsigned short nextchar_a;
	unsigned char nextchar_b;
	list<int> occurences;
	int i=0,stepreads=0,j; //i:premier indice de T dans fenetre ; j:indice dans fenetre

	while(i<n-m+1){
		stepreads++;
		nextchar_a = (unsigned char)T[i+m-2]<<8;
		stepreads++;
		nextchar_b = (unsigned char)T[i+m-1];
		j = m-max(R[nextchar_a|nextchar_b],R[nextchar_b].size());
		i += j;
		if(j<m){
			compared = ((compared+3)<<j)&~3;
			j = 0;
			def saved_a = nextchar_a>>8;
			while((compared>>j&3)!=3){ /*TODO PARTIE 1 comparedtruc==3 n'implique pas une comparaison valide si le decalage a ete fait apres la premiere comparaison, meme probleme que dans la partie 2
Exemple : (apres 1 decalage sl va etre le premier compared==3 mais faux)
	ghnoeisl
	fiezhnslisldgbsieuvbfvu

				if((compared>>j&3)==2){
					j--;
					nextchar_b = nextchar_a>>8;
					compared -= 3<<j;
				}else{
					stepreads++;
					nextchar_b = (unsigned char)T[i+m-1-j];
				}
				stepreads++;
				nextchar_a = (unsigned char)T[i+m-2-j]<<8;
				foundpos = R[nextchar_a|nextchar_b];
				def pointeur elem = find(foundpos.begin(),foundpos.end(),m-j);
				def int posit = elem-foundpos.begin();
				if(posit<foundpos.size()){
					if(posit>0){
						def max_decalage = max(max_decalage,(*elem--)-m+j);
					}else{
						max_decalage = max(max_decalage,j+2);
					}
					compared += 3<<j;
					j+=2;
				}else{
					max_decalage = max(max_decalage,j+2);
					def bool exit = true;
					break;
				}
			}
			if(!exit){
				if(j<m-2){
					if((m-j)%2==1){
						j++;
						nextchar_b = saved_a;
						exit = true;
					}else{
						j+=2;
					}
					while(j<m){
						if((compared>>j&3)==3){//TODO PARTIE 2 comment savoir si la comparaison a toujours la bonne position ?
							exit = false;
						}else{
							if(exit){
								exit = false;
							}else{
								stepreads++;
								nextchar_b = (unsigned char)T[i+m-1-j];
							}
							stepreads++;
							nextchar_a = (unsigned char)T[i+m-2-j]<<8;
							foundpos = R[nextchar_a|nextchar_b];
							def elem = find(foundpos.begin(),foundpos.end(),m-j);
							def posit = elem-foundpos.begin();
							if(posit<foundpos.size()){
								if(posit>0){
									def max_decalage = max(max_decalage,(*elem--)-m+j);
								}else{
									max_decalage = max(max_decalage,j+2);
								}
								compared += 3<<j;
								j+=2;
							}else{
								max_decalage = max(max_decalage,j+2);
								exit = true;
								break;
							}
						}
					}
				}
				//TODO FOUND
			}
		}
	}

	affichage(occurences);
	cout<<"stepreads = "<<stepreads<<endl;
}}
*/
// Aho Corasick
void recherche_multi(list<string> P, int m, string T, int n, bool echecsameliores = false){
	Arbre* tree = new Arbre(P);
	Noeud* racine = (*tree).getRacine();
	Noeud* noeudcourant = racine;
	Noeud* noeudsuivant;
	char currentchar;
	bool alreadyread=false;
	int i=0,motif,stepreads=0,steps=0;
	int taillemot[P.size()];
	list<int> occurences[P.size()];
	steps+=22;

	(*tree).calculeErreur(echecsameliores);
	steppretrait+=(*tree).getTime();

//	(*tree).afficheArbre(noeudcourant);cout<<endl;
	for(list<string>::iterator mot=P.begin();mot!=P.end();mot++){
		steps+=6;
		taillemot[i] = (*mot).size();
		i++;
	}i = 0;
	while(i<n){
		steps+=10+5*(*noeudcourant).lesFils().size();
		if(alreadyread){
			alreadyread = false;
		}else{
			steps++;
			stepreads++;
			currentchar = T[i];
		}
		noeudsuivant = (*noeudcourant).trouveFils(currentchar);
		if(!noeudsuivant){
			steps+=4;
			if(noeudcourant!=racine){
				steps+=5;
				if((*noeudcourant).estFinMotif()){
					steps+=5;
					motif = (*noeudcourant).quelMotif();
					occurences[motif].push_back(i-taillemot[motif]);
//					cout<<"Occurence du motif "<<(*noeudcourant).quelMotif()<<" a la position de fin "<<i<<endl;
				}
				i--;
				alreadyread = true;
			}
			noeudsuivant = (*noeudcourant).getEchec();
			if(i+m>=n){steps++;if(noeudsuivant==racine){steps++;break;}} //si on commence une recherche trop loin pour trouver un motif
		}
		steps+=3;
		noeudcourant = noeudsuivant;
		i++;
	}
	steps+=(*tree).getTime();

	delete(tree);
	affichage(occurences,P.size());
	cout<<"T = "<<steppretrait<<"+"<<steps<<"("<<stepreads<<")"<<endl;steppretrait=0;
}

void recherche_multi_naif(list<string> P, int m, string T, int n){
	list<int> occurences[P.size()];
	Arbre* tree = new Arbre(P);
	Noeud* noeudcourant;
	Noeud* noeudsuivant = (*tree).getRacine();
	int j,i=0,stepreads=0,steps=0;
	steps+=11;
	steppretrait+=(*tree).getTime();

	while(i<n-m+1){
		steps+=8;
		j = 0;
		while(noeudsuivant){
			steps+=3;
			noeudcourant = noeudsuivant;
			if(i+j>=n){break;}
			steps+=8+5*(*noeudcourant).lesFils().size();
			stepreads++;
			noeudsuivant = (*noeudcourant).trouveFils(T[i+j]);
			j++;
		}
		if((*noeudcourant).estFinMotif()){
			steps+=3;
			occurences[(*noeudcourant).quelMotif()].push_back(i);
		}
		noeudsuivant = (*tree).getRacine();
		i++;
	}
	steps+=(*tree).getTime();

	delete(tree);
	affichage(occurences,P.size());
	cout<<"T = "<<steppretrait<<"+"<<steps<<"("<<stepreads<<")"<<endl;steppretrait=0;
}

///////////////////////////////////////
int main(int argc, char** argv){
if(argc < 3){
	cout<<"! ERREUR : Mauvaise utilisation du programme "<<argv[0]<<", on attend : "<<argv[0]<<" fichierMotif fichierTexte !"<<endl;
}else{
	string line;

	/* Lecture du texte */
	string nomFicTexte(argv[2]);
	ifstream IfFicTexte (nomFicTexte.c_str(), ios::in);
	if(!IfFicTexte){
		cout<<"! ERREUR : Impossible d'ouvrir le fichier du texte ("<<nomFicTexte<<") !"<<endl;
		return(0);
	}
	string T;
	while(getline(IfFicTexte,line)){T += line+'\n';}
	int n = T.size()-1;
	T = T.substr(0,n);
	if(n<1){
		cout<<"! ERREUR : Fichier du texte ("<<nomFicTexte<<") vide !"<<endl;
		return(0);
	}
	/* Lecture du/des motif(s) */
	string nomFicMotif(argv[1]);
	ifstream IfFicMotif(nomFicMotif.c_str(),ios::in);
	if(!IfFicMotif){
		cout<<"! ERREUR : Impossible d'ouvrir le fichier motif ("<<nomFicMotif<<") !"<<endl;
		return(0);
	}
	list<string> P_multi;
	list<string>::iterator it;
	int i=1,m_min = n;
	while(getline(IfFicMotif,line)){
		if(line.size()>0){
			if(line.size()<n+1){
				P_multi.push_back(line);
				if(line.size()<m_min){m_min = line.size();}
			}else{
				cout<<". AVERTISSEMENT : Ligne "<<i<<" du fichier des motifs ignoree (motif plus long que le texte)."<<endl;
			}
		}else{
			cout<<". AVERTISSEMENT : Ligne "<<i<<" du fichier des motifs ignoree (motif vide)."<<endl;
		}
		i++;
	}
	IfFicMotif.close();
	if(P_multi.size()<1){
		cout<<"! ERREUR : Aucun motif compatible avec le texte dans "<<nomFicMotif<<" !"<<endl;
		return(0);
	}
	string P = P_multi.front();
	int m = P.size();
	if(argc > 3){
		affich_mode = true;
	}else{
		affich_mode = false;
	}

	cout<<"********************************************************************"<<endl;
	cout<<"Recherche d"<<((P_multi.size()==1)?"u motif":"es motifs");
	for(it=P_multi.begin();it!=P_multi.end();it++){cout<<" ; "<<*it;}cout<<endl;
	cout<<"Dans un texte de taille "<<n<<endl;
	cout<<"********************************************************************"<<endl;
	cout<<"Timers : pretraitement+steps(reads)"<<endl<<endl;
	steppretrait=0;
	cout<<"************ Recherche naive *************"<<endl;
	naif(P,m,T,n);
	cout<<"##########################################"<<endl<<endl;
	cout<<"*********** Recherche avec MP ************"<<endl;
	MP(P,m,T,n,calcule_MP_next(P,m));
	cout<<"##########################################"<<endl<<endl;
	cout<<"*********** Recherche avec KMP ***********"<<endl;
	MP(P,m,T,n,calcule_KMP_next(P,m));
	cout<<"##########################################"<<endl<<endl;
	cout<<"******* Recherche avec Boyer-Moore *******"<<endl;
	BM(P,m,T,n);
	cout<<"** Recherche avec Boyer-Moore (R forte) **"<<endl;
	BM(P,m,T,n,true);
	cout<<"##########################################"<<endl<<endl;
	cout<<"********** Recherche avec TVSBS **********"<<endl;
	TVSBS(P,m,T,n);
	cout<<"##########################################"<<endl<<endl;
	cout<<"****** Recherche Aho Corasick naive ******"<<endl;
	recherche_multi_naif(P_multi,m_min,T,n);
	cout<<"********* Recherche Aho Corasick *********"<<endl;
	recherche_multi(P_multi,m_min,T,n);
	cout<<"**** Recherche Aho Corasick amelioree ****"<<endl;
	recherche_multi(P_multi,m_min,T,n,true);
	cout<<"##########################################"<<endl;
}}
