
# 编译zlib
- 编译版本 1.2.11
- 下载地址 https://www.zlib.net/zlib-1.2.11.tar.gz
- 编译环境 vs2017
- 依赖包 null

## 0x00 编译 
通过开始菜单进入到vs2017的命令行编译环境，进入zlib解压目录，执行nmake -f win32/Makefile.msc，使用默认参数编译

## 0x01 使用
编译完成后，在解压目录中会生成链接文件
zdll.lib        动态库
zlib.lib        静态库
zlib1.dll       runtime文件
zlib.pdb        源码包含文件
zlib1.pdb       crash debug文件

