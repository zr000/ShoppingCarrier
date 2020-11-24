
# 编译OpenSSL
- 编译版本     1.1.1e
- 下载地址 https://github.com/openssl/openssl/archive/OpenSSL_1_1_1e.tar.gz
- 编译环境 vs2017
- 依赖环境 perl

## 0x00 准备
下载OpenSSL源码后，在解压的目录中查看*Configure*文件，主要参数解释如下
* --prefix
    > 指定编译完成后的安装目录，Linux上默认/usr/local，包括 bin，lib，include，share/man， share/doc/openssl
* --api
    > 指定api的版本
* -no-asm
    > 不使用汇编
* -[no-]threads
    > 编译线程不安全的库，不推荐使用。默认-threads
* -[no-]shared
    > 是否编译动态链接库
* -[no-]zlib
    > 是否支持zlib
* -static
    > 编译静态链接库

## 0x01 配置
通过开始菜单进入到vs2017的命令行编译环境，进入OpenSSL解压目录，执行 *perl Configure -pic -shared -no-zlib -no-asm --prefix=install_dir VC-WIN32* , 显示 *Creating makefile*， *OpenSSL has been successfully configured* 表示编译成功

## 0x02 编译
执行nmake开始编译，大约10分钟后编译完成

