
# 椭圆曲线公钥密码算法-数字签名  
利用椭圆曲线上点运算的不可逆实现公私钥系统，曲线存在k倍点\[k\]P，用k可以推导出P的k倍点，由\[k\]P无法反向推导出k

## 0x00  数学基础  

### 有限域
F<sub>p</sub>，q是奇素数或者是2的方幂，当q是奇素数时，要求p>2<sup>191</sup>

### 素域
F<sub>p</sub>，当p是奇素数时，素域中的元素用整数0,1,2,...,p-1表示

### 素域上的椭圆曲线
定义在F<sub>p</sub>(p是大于3的素数)上的椭圆曲线方程为：y<sup>2</sup>=x<sup>3</sup>+ax+b  

### 椭圆曲线多倍点
椭圆曲线上同一个点的多次加称为该点的多倍点运算，设k是一个正整数，P是椭圆曲线上的点，称点P的k次加为点P的k倍点运算，记为Q = \[k\]P 

## 0x01 密钥算法  
### 1.1椭圆曲线多倍点运算

### 1.2生成密钥对
* 输入：一个有效的椭圆曲线系统的参数集合
* 输出：(d, P)
    * 随机一个整数d，d∈[1,n-2]
    * G为奇点，计算点P=(x<sub>p</sub>, y<sub>p</sub>)=[d]G
        * 1.1 椭圆曲线多倍点运算
    * 密钥对是(d, P)，其中d为私钥，P为公钥  

## 0x02 国密SM2

国密SM2签名使用的椭圆曲线参数：  
p：FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFF  
a：FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFC  
b：28E9FA9E9D9F5E344D5A9E4BCF6509A7F39789F515AB8F92DDBCBD414D940E93  
Gx：32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7  
Gy：BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0  
n：FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123  

## 0x03 签名算法
* N=Z<sub>A</sub> || M；
* 计算e = H<sub>v</sub>(N)，将e的数据类型转换为整数
* 用随机数发生器产生随机数k∈[1,n-1]
* 计算椭圆曲线点(x<sub>1</sub> ,y<sub>1</sub>)=[k]G，将x<sub>1</sub>的数据类型转换为整数
* 计算r=(e+x<sub>1</sub>) mod n，若r=0或r+k=n则返回A3
* 计算s=((1 + d<sub>A</sub>)<sup>−1</sup> * (k−r · d<sub>A</sub>)) mod n，若s=0则返回A3
* 将r、s转换为字节串

