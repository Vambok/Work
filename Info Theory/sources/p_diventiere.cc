#include <iostream>
#include <stdlib.h>
using namespace std;int f7( int xg0,int x0){return x0;}int f6( int x0,int xd0){return x0;}int f5( int x0,int xd0){return x0;}int f8( int xg0,int xg1){return 0;}int f39( int xg0,int x0,int xd0,int xd1){return x0;}int f38( int x0,int xd0,int xd1,int xd2){return x0;}int f113( int xg0,int xg1,int x0,int xd0){return x0;}int f338( int xg0,int xg1,int xg2,int x0){return x0;}int f337( int x0,int xd0,int xd1,int xd2){return x0;}int f672( int xg0){return 0;}int f1346( int x0){return x0;}int f1347( int xg0,int x0,int xd0){return x0+1;}int f673(int xg0,int x0,int x1){if(x0==0){return f1346(x1 );}else{return f1347(x0-1,f673(xg0,x0-1,x1 ),x1 );}}int f336(int x0,int x1){if(x0==0){return f672(x1 );}else{return f673(x0-1,f336(x0-1,x1 ),x1 );}}int f112( int x0,int x1,int x2,int x3){return f336(f337(x0,x1,x2,x3 ),f338(x0,x1,x2,x3 ));}int f670( int x0){return x0;}int f1342(){return 0;}int f1343( int x0,int xd0){return x0;}int f671(int xg0,int x0,int xd0){if(x0==0){return f1342();}else{return f1343(x0-1,f671(xg0,x0-1 ,xd0) );}}int f335(int x0,int x1){if(x0==0){return f670(x1 );}else{return f671(x0-1,f335(x0-1,x1 ),x1 );}}int f1004( int x0,int xd0){return x0;}int f1003( int xg0,int x0){return x0;}int f2004( int x0){return x0;}int f4010(){return 0;}int f4011( int x0,int xd0){return x0;}int f2005(int xg0,int x0,int xd0){if(x0==0){return f4010();}else{return f4011(x0-1,f2005(xg0,x0-1 ,xd0) );}}int f1002(int x0,int x1){if(x0==0){return f2004(x1 );}else{return f2005(x0-1,f1002(x0-1,x1 ),x1 );}}int f334( int x0,int x1){return f1002(f1003(x0,x1 ),f1004(x0,x1 ));}int f666( int x0){return x0;}int f667( int xg0,int x0,int xd0){return x0+1;}int f333(int x0,int x1){if(x0==0){return f666(x1 );}else{return f667(x0-1,f333(x0-1,x1 ),x1 );}}int f111( int x0,int x1){return f333(f334(x0,x1 ),f335(x0,x1 ));}int f37( int x0,int x1,int x2,int x3){return f111(f112(x0,x1,x2,x3 ),f113(x0,x1,x2,x3 ));}int f72( int x0,int xd0){return x0;}int f73( int xg0,int xg1,int xg2,int x0){return x0;}int f36(int x0,int x1,int x2){if(x0==0){return f72(x1,x2 );}else{return f73(x0-1,f36(x0-1,x1,x2 ),x1,x2 );}}int f9( int x0,int x1,int x2,int x3){return f36(f37(x0,x1,x2,x3 ),f38(x0,x1,x2,x3 ),f39(x0,x1,x2,x3 ));}int f4(int x0,int x1,int x2){if(x0==0){return f8(x1,x2 );}else{return f9(x0-1,f4(x0-1,x1,x2 ),x1,x2 );}}int f1( int x0,int x1){return f4(f5(x0,x1 ),f6(x0,x1 ),f7(x0,x1 ));}int main(int argc,char** argv){if(argc<1+2){cout<<"Vous devez entrer 2 arguments entiers !"<<endl;}else{cout<<"= "<<f1(atoi(argv[1]),atoi(argv[2]) )<<endl;}}