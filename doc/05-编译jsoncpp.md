
# 编译jsoncpp #
- 编译版本 1.8.4
- 下载地址 https://github.com/open-source-parsers/jsoncpp/archive/1.8.4.tar.gz 
- 编译环境 vs2017 
- 依赖环境 cmake

## 0x00 编译##
解压后创建*build/release*目录，cd到release目录，执行*cmake -DCMAKE_BUILD_TYPE=release -DBUILD_STATIC_LIBS=ON -DBUILD_SHARED_LIBS=OFF -DARCHIVE_INSTALL_DIR=. -G "" ../..*

## 0x01 使用 ##
编译完成后会生成vs2017的解决方案文件，打开后选择release编译，完成后lib文件在*src\lib_json\Release*中
