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
pair<int,int> arite(string P, bool shutup=false, int shift=0){
	pair<int,int> ari;
	switch(P[0]){
		case 'U':case '7':
			ari = arite(P.substr(1),shutup,shift+1);if(ari.first==-1){return ari;}
			if(ari.first<1){
				if(!shutup){cout<<"U (char "<<shift<<") : Vous ne pouvez pas minimiser une fonction d'arite nulle (char "<<shift+1<<")"<<endl;}
				return pair<int,int>(-1,shift);
			}
			ari.first--;
			break;
		case 'R':case '6':{
			ari = arite(P.substr(1),shutup,shift+1);if(ari.first==-1){return ari;}
			pair<int,int> ari_recurs = arite(P.substr(ari.second+1),shutup,shift+ari.second+1);if(ari_recurs.first==-1){return ari_recurs;}
			if(ari_recurs.first!=ari.first+2){
				if(!shutup){cout<<"R (char "<<shift<<") : La fonction recursive (char "<<shift+ari.second+1<<") doit etre d'arite "<<ari.first+2<<" et non "<<ari_recurs.first<<endl;}
				return pair<int,int>(-1,shift);
			}
			ari.first++;
			ari.second += ari_recurs.second;
			break;}
		case 'C':case '5':{
			ari = arite(P.substr(1),shutup,shift+1);if(ari.first==-1){return ari;}
			if(ari.first==0){
				if(!shutup){cout<<"C (char "<<shift<<") : Vous ne pouvez pas composer une fonction d'arite nulle (char "<<shift+1<<")"<<endl;}
				return pair<int,int>(-1,shift);
			}
			pair<int,int> ari_fonction = ari;
			ari.first = -1;
			for(int i=0;i<ari_fonction.first;i++){
				pair<int,int> current_ari = arite(P.substr(ari.second+1),shutup,shift+ari.second+1);if(current_ari.first==-1){return current_ari;}
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
			ari = arite(P.substr(1),shutup,shift+1);if(ari.first==-1){return ari;}
			ari.first++;
			break;
		case 'S':case 'I':case '2':case '1':
			ari = pair<int,int>(1,0);
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

pair<string,int> prog(string P, int tempg=0, int tempd=0, int idf=1){
	pair<int,int> ari;
	pair<string,int> fonct;
	string chaine;
	string suitechaine = "";
	int i,j;
	switch(P[0]){
		case 'U':case '7':
			ari = arite(P.substr(1),true);
			chaine = "int f"+idf+"( ";
			for(i=0;i<tempg;i++){
				chaine += "int xg"+i+",";
			}
			for(i=0;i<ari.first-1;i++){
				chaine += "int x"+i+",";
				suitechaine += ",x"+i;
			}
			for(i=0;i<tempd;i++){
				chaine += "int xd"+i+",";
			}
			chaine = chaine.substr(0,chaine.size()-1) + "){int i=0;while(f"+(idf*2)+"(i"+suitechaine+")!=0){i++;}return i;}";
			fonct = prog(P.substr(1),0,0,idf*2);
			fonct.first += chaine;
			break;
		case 'R':case '6':{
			ari = arite(P.substr(1),true);
			chaine = "int f"+idf+"(";
			for(i=0;i<tempg;i++){
				chaine += "int xg"+i+",";
			}
			for(i=0;i<ari.first+1;i++){
				chaine += "int x"+i+",";
				suitechaine += ",x"+i;
			}
			for(i=0;i<tempd;i++){
				chaine += "int xd"+i+",";
			}
			suitechaine += " ";
			chaine = chaine.substr(0,chaine.size()-1) + "){if(x0==0){return f"+(idf*2)+"("+suitechaine.substr(4)+");}else{return f"+(idf*2+1)+"(x0-1,f"+idf+"(x0-1"+suitechaine.substr(3)+")"+suitechaine.substr(3)+");}}";
			fonct = prog(P.substr(ari.second+1),0,0,idf*2+1);
			chaine = fonct.first + chaine;
			j = fonct.second;
			fonct = prog(P.substr(1),0,0,idf*2);
			fonct.first += chaine;
			fonct.second += j;
			break;}
		case 'C':case '5':{
			ari = arite(P.substr(1),true);
			pair<int,int> ari2 = arite(P.substr(ari.second+1),true);
			chaine = "int f"+idf+"( ";
			for(i=0;i<tempg;i++){
				chaine += "int xg"+i+",";
			}
			for(i=0;i<ari2.first;i++){
				chaine += "int x"+i+",";
				suitechaine += ",x"+i;
			}
			for(i=0;i<tempd;i++){
				chaine += "int xd"+i+",";
			}
			suitechaine += " ";
			chaine = chaine.substr(0,chaine.size()-1) + "){return f"+(idf*(ari.first+1))+"(";
			for(i=0;i<ari.first;i++){
				chaine += "f"+(idf*(ari.first+1)+i+1)+"("+suitechaine.substr(1)+"),";
			}
			chaine = chaine.substr(0,chaine.size()-1) + ");}";
			fonct = prog(P.substr(1),0,0,idf*(ari.first+1));
			chaine = fonct.first + chaine;
			j = fonct.second;
			for(i=0;i<ari.first;i++){
				fonct = prog(P.substr(ari.second+1),0,0,idf*(ari.first+1)+i+1);
				chaine = fonct.first + chaine;
				j += fonct.second;
				ari.second += fonct.second;
			}
			fonct.first = chaine;
			fonct.second = j;
			break;}
		case '>':case '4':
			fonct = prog(P.substr(1),tempg,tempd+1,idf);
			break;
		case '<':case '3':
			fonct = prog(P.substr(1),tempg+1,tempd,idf);
			break;
		case 'S':case '2':
			chaine = "int f"+idf+"( ";
			for(i=0;i<tempg;i++){
				chaine += "int xg"+i+",";
			}
			chaine += "int x0,";
			for(i=0;i<tempd;i++){
				chaine += "int xd"+i+",";
			}
			fonct = pair<string,int>(chaine.substr(0,chaine.size()-1) + "){return x0+1;}",0);
			break;
		case 'I':case '1':
			chaine = "int f"+idf+"( ";
			for(i=0;i<tempg;i++){
				chaine += "int xg"+i+",";
			}
			chaine += "int x0,";
			for(i=0;i<tempd;i++){
				chaine += "int xd"+i+",";
			}
			fonct = pair<string,int>(chaine.substr(0,chaine.size()-1) + "){return x0;}",0);
			break;
		default:
			chaine = "int f"+idf+"( ";
			for(i=0;i<tempg;i++){
				chaine += "int xg"+i+",";
			}
			for(i=0;i<tempd;i++){
				chaine += "int xd"+i+",";
			}
			fonct = pair<string,int>(chaine.substr(0,chaine.size()-1) + "){return 0;}",0);
	}
	fonct.second++;
	return fonct;
}

pair<int,string> calcule(string P){
if(arite(P,true).first>-1){
//DO 2
}else{arite(P);return pair<int,string>(0,"");}}

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

void premieres_chaines_valides(int maxsearch, int win_width=80){
	string chaine;pair<int,int> ari;string log="0";
	cout<<"Chaines valides parmi les "<<maxsearch+1<<" premieres chaines :"<<endl;
	for(int i=1;i<=maxsearch;i++){
		chaine = inttochaine(i);
		ari = arite(chaine,true);
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

void derniere_chaine_valide(int maxsearch){
	string chaine;string last;pair<int,int> ari;
	cout<<"Derniere chaine valide parmi les "<<maxsearch+1<<" premieres chaines :"<<endl;
	for(int i=0;i<=maxsearch;i++){
		chaine = inttochaine(i);
		ari = arite(chaine,true);
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
	string input = "";
	if(argc > 1){
		input = argv[1];
	}
	if(input==""){
		cout<<"Que voulez-vous faire ? (R: analyse du fichier ; P: programmation de chaine ; n: liste des premieres chaines valides jusqu'a n ; dn: derniere chaine <= n valide) : ";
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
			pair<int,int> ari = arite(input);
			if(ari.first>-1){
				if(ari.second<input.size()){cout<<"Sans les "<<input.size()-ari.second<<" derniers caracteres inutiles on a : ";}
				cout<<"Arite : "<<ari.first<<endl;
			}
			break;}
		case 'P':{
			if(input.size()==1){
				cout<<"Entrez le nom du fichier contenant la chaine a programmer : ";
				getline(cin,input);
			}else{
				input = input.substr(1);
			}
			ifstream IfFicChaine(input.c_str(),ios::in);
			if(!IfFicChaine){cout<<endl<<"Impossible d'ouvrir le fichier : "<<input<<endl;return(0);}
			IfFicChaine>>input;
			cout<<"Chaine de jetons n°0"<<tokenstochaine(input)<<" : "<<input<<endl;
			pair<string,int> fonct = prog(input);
			ofstream myfile("output.txt");
			if(myfile.is_open()){
				myfile<<fonct.first;
				myfile.close();
				cout<<"Programme cree dans output.txt !"<<endl;
				if(fonct.second<input.size()){cout<<input.size()-fonct.second<<" caracteres inutiles a la fin."<<endl;}
			}else{cout<<"Unable to open file";}
			break;}
		case 'd':
			if(input[1]=='n'){
				cout<<"Entrez l'entier maximal a tester : ";
				getline(cin,input);
			}else{
				input=input.substr(1);
			}
			try{param = stoi(input);}catch(...){param = 0;}
			derniere_chaine_valide(param);
			break;
		case 'n':
			cout<<"Entrez l'entier maximal a tester : ";
			getline(cin,input);
		default:
			try{param = stoi(input);}catch(...){param = 0;}
			struct winsize size;ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);
			premieres_chaines_valides(param,size.ws_col);
	}
}
