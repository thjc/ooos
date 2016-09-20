//#include "stdio.h"
#include "videodriver.h"
#include "global.h"

//void printfb(const char *arg, ...);

void OutChar(char v) {
	wchar_t w_v[2];
	w_v[0] = v;
	w_v[1] = 0;
	pDisp->WriteString(w_v);
}



/*int main(void) {
	printfb("--> %c --> %s, --> %d\n",'a',"yay",0x00000042);

	return 1;
}*/


void printf(const char *arg, ...) {
	int cnt=0;

	unsigned int coffset=(((unsigned int)&arg)+0x00000004);	//address of first argument

	if(arg[cnt]==0) {
		return /*-1*/;
	}

	while(arg[cnt]!=0) {
		if(arg[cnt+1]!=0) {
			if(arg[cnt]=='%'&&arg[cnt+1]=='d') {
				int val=(int)(*(int *)coffset);
				cnt+=2;
				coffset+=0x00000004;

				unsigned int foo=1000000000;
				do {
					OutChar('0'+val/foo);
					val=val%foo;
					if(foo==1)
						foo=0;
					else 
						foo/=10;
				} while (foo!=0);


			}
			else if (arg[cnt]=='%'&&arg[cnt+1]=='c') {
				OutChar((char)(*(char *)coffset));
				coffset+=0x00000004;
				cnt+=2;
			}
			else if (arg[cnt]=='%'&&arg[cnt+1]=='s') {
				char *str=(char *)*(int *)coffset;
				while ((*str)!=0) {
					OutChar(*str);
					str++;
				}
				coffset+=0x00000004;
				cnt+=2;
			}
			else {
				OutChar(arg[cnt]);
				cnt++;
			}
		}
		else {
			OutChar(arg[cnt]);
			cnt++;
		}
	}

}