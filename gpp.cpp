#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <chrono>
using namespace std;

string ftime(int t) {
	int minutes=t/60;
	int seconds=t%60;
	if(t<0 || minutes>99) {
		return "--:--";
	}
	string fstr="";
	if(minutes<10) {
		fstr+="0";
		fstr+=char(minutes+'0');
	} else {
		fstr+=char(minutes/10+'0');
		fstr+=char(minutes%10+'0');
	}
	fstr+=":";
	if(seconds<10) {
		fstr+="0";
		fstr+=char(seconds+'0');
	} else {
		fstr+=char(seconds/10+'0');
		fstr+=char(seconds%10+'0');
	}
	return fstr;
}

//更新计划: 逐参数判断完前置选项再进行文件路径列表判断,允许控制台使用自定义参数编译,允许配置自定义编译器路径 
int main(int argc,char* argv[]) {
	if(argc<=1) {
		cout<<"\n>> 空参数不可取!"<<endl;
		return 0;
	}
	int begini=1;
	
	bool endly_pause=1;
	if(string(argv[1])=="-a") {
		begini=2;
		endly_pause=0;
		if(argc<=2) {
			cout<<"\n>> 参数缺失!"<<endl;
			return 0;
		} 
	}
	
	string gpp_args="";
	ifstream inifin("./gpp.ini");
	if(inifin.good()) {
		getline(inifin,gpp_args);
	} else {
		ofstream inifout("./gpp.ini");
		gpp_args="-O2 -std=c++17";
		inifout<<gpp_args;
		printf(">> 配置文件 gpp.ini 不存在,已自动创建并使用默认参数!\n");
	}
	
	for(int i=begini;i<argc;i++) {
		string codefile=argv[i];
		ifstream codefin(codefile.data());
		if(!codefin.good()) {
			char bufb[MAX_PATH]={0};
			GetCurrentDirectoryA(MAX_PATH,bufb);
			string trypath=(string(bufb)+codefile);
			ifstream codefinb(trypath.data());
			if(codefinb.good()) {
				codefile=trypath;
			} else {
				cout<<">> 文件 "<<codefile<<" 不存在!\n"<<endl;
				continue;
			}
		}
		string cmdstr=("g++.exe "+codefile);
		while(codefile.back()!='\\' && codefile.back()!='/') {
			if(codefile.back()=='.') {
				codefile+="exe";
				cmdstr+=(" -o "+codefile+" "+gpp_args);
				cout<<">> 正在尝试调用 g++.exe 编译 "<<argv[i]<<" ......"<<endl<<endl;
				system(cmdstr.data());
				cout<<endl;
				break;
			}
			codefile.pop_back();
		}
	}
	
	if(endly_pause) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x04);
		cout<<">> 操作结束,等待十分钟或按下回车键退出本次操作,按ESC键取消倒计时.....\n"<<endl;
		auto start_=chrono::system_clock::now();
		int old_sec=-1;
		while(1) {
			if(kbhit()) {
				char ch=getch();
				if(ch=='\n' || ch=='\r') {
					break;
				}
				else if(ch==27) {
					cout<<"\n\n>> 已取消倒计时,等待按下回车键结束本次操作"<<endl;
					while(1) {
						if(kbhit()) {
							char chb=getch();
							if(chb=='\n' || chb=='\r') {
								break;
							}
						}
					}
					break;
				}
			}
			auto here_=chrono::system_clock::now();
			double now_sec=chrono::duration<double>(here_-start_).count();
			if(old_sec!=int(now_sec)) {
				old_sec=now_sec;
				cout<<"\b\b\b\b\b";
				cout<<ftime(old_sec);
				fflush(stdout);
			}
			if(now_sec>=600.2) {
				break;
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x07);
	
	return 0;
}
