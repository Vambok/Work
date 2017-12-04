//> g++ Projet.cc -std=c++11 -o Projet
//> ./Projet Rchaine

#include <iostream>
#include <fstream> //pour lire les fichiers
#include <string>
#include <map> //pour les tableaux associatifs
#include <math.h> //pour pow
#include <unistd.h> //pour window_size
#include <sys/ioctl.h> //pour window_size

using namespace std;
pair<int,int> arite(string P, bool mode_etendu=false, bool shutup=false, int shift=0){//DO 1 mode etendu
	pair<int,int> ari;
	switch(P[0]){
		case 'U':case '7':
			ari = arite(P.substr(1),mode_etendu,shutup,shift+1);if(ari.first==-1){return ari;}
			if(ari.first<1){
				if(!shutup){cout<<"U (char "<<shift<<") : Vous ne pouvez pas minimiser une fonction d'arite nulle (char "<<shift+1<<")"<<endl;}
				return pair<int,int>(-1,shift);
			}
			ari.first--;
			break;
		case 'R':case '6':{
			ari = arite(P.substr(1),mode_etendu,shutup,shift+1);if(ari.first==-1){return ari;}
			pair<int,int> ari_recurs = arite(P.substr(ari.second+1),mode_etendu,shutup,shift+ari.second+1);if(ari_recurs.first==-1){return ari_recurs;}
			if(ari_recurs.first!=ari.first+2){
				if(!shutup){cout<<"R (char "<<shift<<") : La fonction recursive (char "<<shift+ari.second+1<<") doit etre d'arite "<<ari.first+2<<" et non "<<ari_recurs.first<<endl;}
				return pair<int,int>(-1,shift);
			}
			ari.first++;
			ari.second += ari_recurs.second;
			break;}
		case 'C':case '5':{
			ari = arite(P.substr(1),mode_etendu,shutup,shift+1);if(ari.first==-1){return ari;}
			if(ari.first==0){
				if(!shutup){cout<<"C (char "<<shift<<") : Vous ne pouvez pas composer une fonction d'arite nulle (char "<<shift+1<<")"<<endl;}
				return pair<int,int>(-1,shift);
			}
			pair<int,int> ari_fonction = ari;
			ari.first = -1;
			for(int i=0;i<ari_fonction.first;i++){
				pair<int,int> current_ari = arite(P.substr(ari.second+1),mode_etendu,shutup,shift+ari.second+1);if(current_ari.first==-1){return current_ari;}
				if(ari.first<0){
					ari.first = current_ari.first;
				}else if(ari.first!=current_ari.first){
					if(!shutup){cout<<"C (char "<<shift<<") : L'arite "<<current_ari.first<<" (char "<<shift+ari.second+1<<") n'est pas compatible avec l'arite "<<ari.first<<" (char "<<shift+ari_fonction.second+1<<")"<<endl;}
					return pair<int,int>(-1,shift);
				}
				ari.second += current_ari.second;
			}
			break;}
		case '>':case '<':case '4':case '3':
			ari = arite(P.substr(1),mode_etendu,shutup,shift+1);if(ari.first==-1){return ari;}
			ari.first++;
			break;
		case 'S':case 'I':case '2':case '1':
			if(mode_etendu && (P.size()>1)){
				ari = arite(P.substr(1),mode_etendu,true,shift+1);if(ari.first==-1){ari = pair<int,int>(1,0);}
			}else{
				ari = pair<int,int>(1,0);
			}
			break;
		case '0':
			ari = pair<int,int>(0,0);
			break;
		default:
			if(!shutup){cout<<"(char "<<shift<<") : Caractere inconnu ou vide : "<<P[0]<<endl;}
			return pair<int,int>(-1,shift);
	}
	ari.second++;
	return ari;
}

pair<int,string> calcule(string P, bool mode_etendu=false){
if(arite(P,mode_etendu,true).first>-1){
//DO 2
}else{arite(P,mode_etendu);return pair<int,string>(0,"");}}

string inttochaine(int input){
	char buffer[12];
	int n = sprintf(buffer,"%o",input);
	return buffer;
}

//long long chainetoint(string input){
//	long long decimal = 0;int i = 0;
//	while(input.size()>0){
//		decimal += pow(8,i)*stoi(input.substr(input.size()-1));
//		input = input.substr(0,input.size()-1);
//		i++;
//	}
//	return decimal;
//}

string chainetotokens(string input){
	char token;
	for(int i=0;i<input.size();i++){
		switch(input[i]){
			case '1':
				token='I';
				break;
			case '2':
				token='S';
				break;
			case '3':
				token='<';
				break;
			case '4':
				token='>';
				break;
			case '5':
				token='C';
				break;
			case '6':
				token='R';
				break;
			case '7':
				token='U';
				break;
			default:
				token='0';
		}
		input[i]=token;
	}
	return input;
}

string tokenstochaine(string input){
	char token;int j=0;
	for(int i=0;i<input.size();i++){
		switch(input[i]){
			case '0':
				token='0';
				break;
			case 'I':
				token='1';
				break;
			case 'S':
				token='2';
				break;
			case '<':
				token='3';
				break;
			case '>':
				token='4';
				break;
			case 'C':
				token='5';
				break;
			case 'R':
				token='6';
				break;
			case 'U':
				token='7';
				break;
			default:
				token='0';
				j++;
		}
		if(token!='0'){input[i-j]=token;}
	}
	return input.substr(0,input.size()-j);
}

void premieres_chaines_valides(int maxsearch, bool mode_etendu=false, int win_width=80){
	string chaine;pair<int,int> ari;string log="0";
	cout<<"Chaines valides parmi les "<<maxsearch+1<<" premieres chaines :"<<endl;
	for(int i=1;i<=maxsearch;i++){
		chaine = inttochaine(i);
		ari = arite(chaine,mode_etendu,true);
		if((ari.first>-1)&&(chaine.size()<=ari.second)){
			if(log.size()+chaine.size()<win_width-2){
				log+=" | "+chainetotokens(chaine);
			}else{
				cout<<log<<endl;
				log = chainetotokens(chaine);
			}
		}
	}
	cout<<log<<endl;
}

void derniere_chaine_valide(int maxsearch, bool mode_etendu=false){
	string chaine;string last;pair<int,int> ari;
	cout<<"Derniere chaine valide parmi les "<<maxsearch+1<<" premieres chaines :"<<endl;
	for(int i=0;i<=maxsearch;i++){
		chaine = inttochaine(i);
		ari = arite(chaine,mode_etendu,true);
		if((ari.first>-1)&&(chaine.size()<=ari.second)){
			last = chainetotokens(chaine);
		}
	}
	cout<<last<<endl;
}

string chaine_to_operateur(string chaine,int operateur){
//DO 3
}

int main(int argc, char** argv){
	bool mode_etendu = false;
	string input = "";
	if(argc > 1){
		if(argv[1]=="e"){
			mode_etendu = true;
			if(argc > 2){input = argv[2];}
		}else{
			input = argv[1];
		}
	}
	if(input==""){
		cout<<"Que voulez-vous faire ? (R: analyse du fichier ; n: liste des premieres chaines valides jusqu'a n ; dn: derniere chaine <= n valide) : ";
		getline(cin,input);
	}
	int param;
	switch(input[0]){
		case 'R':{
			if(input.size()==1){
				cout<<"Entrez le nom du fichier contenant la chaine a analyser : ";
				getline(cin,input);
			}else{
				input = input.substr(1);
			}
			ifstream IfFicChaine(input.c_str(),ios::in);
			if(!IfFicChaine){cout<<endl<<"Impossible d'ouvrir le fichier : "<<input<<endl;return(0);}
			IfFicChaine>>input;
			cout<<"Chaine de jetons n°0"<<tokenstochaine(input)<<" : "<<input<<endl;
			pair<int,int> ari = arite(input,mode_etendu);
			if(ari.first>-1){
				if(ari.second<input.size()){cout<<"Sans les "<<input.size()-ari.second<<" derniers caracteres inutiles on a : ";}
				cout<<"Arite : "<<ari.first<<endl;
			}
			break;}
		case 'd':
			if(input[1]=='n'){
				cout<<"Entrez l'entier maximal a tester : ";
				getline(cin,input);
			}else{
				input=input.substr(1);
			}
			try{param = stoi(input);}catch(...){param = 0;}
			derniere_chaine_valide(param,mode_etendu);
			break;
		case 'n':
			cout<<"Entrez l'entier maximal a tester : ";
			getline(cin,input);
		default:
			try{param = stoi(input);}catch(...){param = 0;}
			struct winsize size;ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);
			premieres_chaines_valides(param,mode_etendu,size.ws_col);
	}
}
