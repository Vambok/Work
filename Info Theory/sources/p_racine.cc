#include <iostream>
#include <stdlib.h>
using namespace std;int f5( int x0){return x0;}int f4( int x0){return x0;}int f6( int xg0){return 0;}int f39( int xg0,int x0,int xd0){return x0;}int f38( int x0,int xd0,int xd1){return x0;}int f37( int xg0,int xg1,int x0){return x0;}int f110( int x0){return x0;}int f109( int x0){return x0;}int f216( int xg0){return 0;}int f434( int x0){return x0;}int f435( int xg0,int x0,int xd0){return x0+1;}int f217(int xg0,int x0,int x1){if(x0==0){return f434(x1 );}else{return f435(x0-1,f217(xg0,x0-1,x1 ),x1 );}}int f108(int x0,int x1){if(x0==0){return f216(x1 );}else{return f217(x0-1,f108(x0-1,x1 ),x1 );}}int f36( int x0,int xd0,int xd1){return f108(f109(x0 ),f110(x0 ));}int f143( int xg0,int xg1,int x0,int xd0){return x0;}int f142( int xg0,int xg1,int xg2,int x0){return x0;}int f425( int xg0,int x0,int xd0,int xd1){return x0;}int f424( int x0,int xd0,int xd1,int xd2){return x0;}int f1271( int x0,int xd0){return x0;}int f1270( int xg0,int x0){return x0;}int f2538( int x0){return x0;}int f5078(){return 0;}int f5079( int x0,int xd0){return x0;}int f2539(int xg0,int x0,int xd0){if(x0==0){return f5078();}else{return f5079(x0-1,f2539(xg0,x0-1 ,xd0) );}}int f1269(int x0,int x1){if(x0==0){return f2538(x1 );}else{return f2539(x0-1,f1269(x0-1,x1 ),x1 );}}int f423( int x0,int x1){return f1269(f1270(x0,x1 ),f1271(x0,x1 ));}int f141( int x0,int x1,int x2,int x3){return f423(f424(x0,x1,x2,x3 ),f425(x0,x1,x2,x3 ));}int f280( int xg0,int x0){return x0;}int f281( int xg0,int xg1,int x0,int xd0){return x0;}int f140(int x0,int x1,int x2){if(x0==0){return f280(x1,x2 );}else{return f281(x0-1,f140(x0-1,x1,x2 ),x1,x2 );}}int f35( int x0,int x1,int x2,int x3){return f140(f141(x0,x1,x2,x3 ),f142(x0,x1,x2,x3 ),f143(x0,x1,x2,x3 ));}int f7( int x0,int x1,int x2){return f35(f36(x0,x1,x2 ),f37(x0,x1,x2 ),f38(x0,x1,x2 ),f39(x0,x1,x2 ));}int f3(int x0,int x1){if(x0==0){return f6(x1 );}else{return f7(x0-1,f3(x0-1,x1 ),x1 );}}int f1( int x0){return f3(f4(x0 ),f5(x0 ));}int main(int argc,char** argv){if(argc<1+1){cout<<"Vous devez entrer 1 arguments entiers !"<<endl;}else{cout<<"= "<<f1(atoi(argv[1]) )<<endl;}}