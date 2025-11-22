# gpp
为了方便使用已有的g++.exe编译器批量将C/C++语言源代码编译为.exe文件，我编写了这个程序。实际上，如果需要的话，它可以代理任何.exe文件的批量运行。

## Releases中包含：
- gpp源代码编译得到的.exe文件，您可以尝试拖动多个源代码文件到它的图标上释放，这将使用您已安装配置好的g++.exe编译器批量编译这些源代码。

## 配置文件
- gpp.ini 存放您的g++.exe安装路径(精确到文件名)
- gpp.cfg 存放您的编译参数，默认使用 -O2 -std=c++17 -s -DNDEBUG
- 您也可以直接在环境变量Path中添加您的g++.exe安装路径，之后便无需配置 gpp.ini

## 友情链接
- 如果您苦于没有合适趁手的编辑器或编译器，可以参考我的另一个仓库：https://github.com/JularDepick/TDM-GCC-10.3.0-Installer-with-MY-CUSTOM-Dev-Cpp-5.11-Config-and-Libs
