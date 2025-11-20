#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <chrono>
using namespace std;

string ftime(int t) {
	//时间格式化
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
 
int main(int argc,char* argv[]) {
	//参数存在性判断 
	if(argc<=1) {
		cout<<">> 空参数不可取!"<<endl; 
		return 0;
	}
	string arg1=argv[1];
	if(arg1=="/cd") {
		//切换自定义编译器路径
		if(argc<=2) {
			//切回默认路径 
			ofstream inifout("./gpp.ini");
			inifout<<"";
			cout<<">> 已切换编译器路径为 g++.exe"<<endl;
		} else {
			ifstream gpp_exe(argv[2],ios::binary);
			if(gpp_exe.good()) {
				ofstream inifout("./gpp.ini");
				inifout<<argv[2];
				cout<<">> 已切换编译器路径为 "<<argv[2]<<endl;
			} else {
				cout<<">> 切换失败:无效的路径!"<<endl;
			}
		}
		return 0; 
	}
	if(arg1=="/cfg") {
		//切换自定义编译参数 
		if(argc<=2) {
			//切回默认编译参数 
			ofstream cfgfout("./gpp.cfg");
			cfgfout<<"-O2 -std=c++17 -s -DNDEBUG";
			cout<<">> 已切换编译参数为 -O2 -std=c++17 -s -DNDEBUG"<<endl;
		} else {
			string args="";
			for(int i=2;i<argc;i++) {
				args+=(string(argv[i])+" ");
			}
			ofstream cfgfout("./gpp.cfg");
			cfgfout<<args;
			cout<<">> 已切换编译参数为 "<<args<<endl;
		}
		return 0; 
	}
	bool endly_pause=1;
	int begini=1;
	if(arg1=="/a") {
		//取消结束确认 
		endly_pause=0;
		begini=2;
	}
	
	//读取自定义编译器路径
	string gpp_root="g++.exe";
	ifstream inifin("./gpp.ini");
	if(inifin.good()) {
		getline(inifin,gpp_root);
		ifstream gpp_exe(gpp_root.data(),ios::binary);
		if(!gpp_exe.good()) {
			cout<<">> 找不到编译器路径 "<<gpp_root<<" ,默认使用 g++.exe"<<endl;
			gpp_root="g++.exe";
		} else if(gpp_root.empty()) {
			gpp_root="g++.exe";
		}
	}
	//读取自定义编译参数
	string gpp_args="";
	ifstream cfgfin("./gpp.cfg");
	if(cfgfin.good()) {
		getline(cfgfin,gpp_args);
		if(gpp_args.empty()) {
			gpp_args="-O2 -std=c++17";
		}
	} else {
		gpp_args="-O2 -std=c++17";
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
		string cmdstr=(gpp_root+" "+codefile);
		while(codefile.back()!='\\' && codefile.back()!='/') {
			if(codefile.back()=='.') {
				codefile+="exe";
				cmdstr+=(" -o "+codefile+" "+gpp_args);
				cout<<">> 正在尝试调用 "<<gpp_root<<" 编译 "<<argv[i]<<" ......"<<endl<<endl;
				system(cmdstr.data());
				cout<<endl;
				break;
			}
			codefile.pop_back();
		}
	}
	
	if(endly_pause && begini<argc) {
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
