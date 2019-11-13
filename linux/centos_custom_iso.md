CentOS定制ISO
==
   本文描述如何对CentOS7.3系统安装镜像做修改，实现自定义的安装流程、界面和内置应用的自动安装。

一、准备
--

第一步，先把centos的iso文件复制到系统里，可以通过挂载iso的方式或者直接复制，这里使用前者。

```bash
# mounet 
```

二、自定义引导菜单
--

使用安装盘引导系统时会出现启动选项，可以使用tab选择下一步的操作。
![alt 启动选项](https://docs.centos.org/en-US/centos/install-guide/_images/boot/boot_screen.png)


