//> g++ Projet.cc -std=c++11 -o Projet
//> ./Projet chaine

#include <iostream>
#include <fstream> //pour lire les fichiers
#include <string>
#include <map> //pour les tableaux associatifs
#include <math.h> //pour pow
#include <unistd.h> //pour window_size
#include <sys/ioctl.h> //pour window_size

using namespace std;
int amax = 100;
int arite(string P, bool shutup=false, int shift=0){
	int ari;
	switch(P[0]){
		case 'U':case '7':
			ari = arite(P.substr(1),shutup,shift+1);if(ari==-1){return -1;}
			if(ari%amax<1){
				if(!shutup){cout<<"U (char "<<shift<<") : Vous ne pouvez pas minimiser une fonction d'arite nulle (char "<<shift+1<<")"<<endl;}
				return -1;
			}
			ari--;
			break;
		case 'R':case '6':{
			int n = arite(P.substr(1),shutup,shift+1);if(n==-1){return -1;}
			int newshift = n/amax; ari = n%amax;
			int oldshift = newshift;
			n = arite(P.substr(newshift+1),shutup,shift+newshift+1);if(n==-1){return -1;}
			newshift += n/amax; n = n%amax;
			if(n!=ari+2){
				if(!shutup){cout<<"R (char "<<shift<<") : La fonction recursive (char "<<shift+oldshift+1<<") doit etre d'arite "<<ari+2<<" et non "<<n<<endl;}
				return -1;
			}
			ari += newshift*amax+1;
			break;}
		case 'C':case '5':{
			int n = arite(P.substr(1),shutup,shift+1);if(n==-1){return -1;}
			int newshift = n/amax; n = n%amax;
			if(n==0){
				if(!shutup){cout<<"C (char "<<shift<<") : Vous ne pouvez pas composer une fonction d'arite nulle (char "<<shift+1<<")"<<endl;}
				return -1;
			}
			int olshift = newshift;
			ari=-1;
			for(int i=0;i<n;i++){
				int currentari = arite(P.substr(newshift+1),shutup,shift+newshift+1);if(currentari==-1){return -1;}
				int oldshift = newshift;
				newshift += currentari/amax; currentari = currentari%amax;
				if(ari<0){
					ari=currentari;
				}else if(ari!=currentari){
					if(!shutup){cout<<"C (char "<<shift<<") : L'arite "<<currentari<<" (char "<<shift+oldshift+1<<") n'est pas compatible avec l'arite "<<ari<<" (char "<<shift+olshift+1<<")"<<endl;}
					return -1;
				}
			}
			ari += newshift*amax;
			break;}
		case '>':case '<':case '4':case '3':
			ari = 1+arite(P.substr(1),shutup,shift+1);if(ari==0){return -1;}
			break;
		case 'S':case 'I':case '2':case '1':
			ari = 1;
			break;
		case '0':
			ari = 0;
			break;
		default:
			if(!shutup){cout<<"(char "<<shift<<") : Caractere inconnu ou vide : "<<P[0]<<endl;}
			return -1;
	}
	return ari+amax;
}
