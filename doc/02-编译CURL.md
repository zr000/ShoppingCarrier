# 编译CURL 
- 编译版本 7.73.0 
- 下载地址 https://curl.se/download/curl-7.62.0.tar.gz 
- 编译环境 vs2017 
- 依赖包 zlib openssl 

## 0x00
在解压目录中打开vs命令行，进入winbuild目录，执行 *nmake /f Makefile.vc mode=dll VC=15 WITH_SSL=static WITH_ZLIB=static GEN_PDB=yes DEBUG=no MACHINE=x86 SSL_PATH=< path to OpenSSL > ZLIB_PATH=< path to zlib >*