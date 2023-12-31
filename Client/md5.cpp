#include "md5.h"

#define A 0x67452301
#define B 0xefcdab89
#define C 0x98badcfe
#define D 0x10325476

MD5::MD5()
{
    this->tempA=A;
    this->tempB=B;
    this->tempC=C;
    this->tempD=D;
    this->strlength=0;
}

//加密
string MD5::encode(string src)
{
    vector<unsigned int> rec=padding(src);
    for(unsigned int i=0; i<strlength/16;i++)
    {
        unsigned int num[16];
        for(unsigned int j = 0; j < 16; j++)
        {
            num[j] = rec[i*16+j];
        }
        iterateFunc(num, 16);
    }
    return format(tempA) + format(tempB) + format(tempC) + format(tempD);
}

//F迭代
unsigned int MD5::F(unsigned int b, unsigned int c, unsigned int d)
{
    return ((b&c) | ((~b)&d));
}

//G迭代
unsigned int MD5::G(unsigned int b, unsigned int c, unsigned int d)
{
    return ((b&d) | (c&(~d)));
}

//H迭代
unsigned int MD5::H(unsigned int b, unsigned int c, unsigned int d)
{
    return (b^c^d);
}

//I迭代
unsigned int MD5::I(unsigned int b, unsigned int c, unsigned int d)
{
    return (c ^ (b|(~d)));
}

unsigned int MD5::shift(unsigned int a, unsigned int n)
{
    return ((a<<n) | (a>>(32-n)));
}

//迭代函数
void MD5::iterateFunc(unsigned int *X, int size)
{
    unsigned int a=tempA, b=tempB, c=tempC, d=tempD, rec=0, g, k;
    for(unsigned int i=0;i<64;i++)
    {
        if(i<16)
        {
            //F迭代
            g=F(b,c,d);
            k=i;
        }
        else if(i<32)
        {
            //G迭代
            g=G(b,c,d);
            k=(1+5*i)%16;
        }
        else if(i<48)
        {
            //H迭代
            g=H(b,c,d);
            k=(5+3*i)%16;
        }
        else
        {
            // I迭代
            g=I(b,c,d);
            k=(7*i)%16;
        }
        rec=d;
        d=c;
        c=b;
        b=b+shift(a+g+X[k]+T[i],s[i]);
        a=rec;
    }
    tempA+=a;
    tempB+=b;
    tempC+=c;
    tempD+=d;
}

vector<unsigned int> MD5::padding(string src)
{
    //以512位,64个字节为一组
    unsigned int num=((src.length()+8)/64)+1;
    vector<unsigned int> rec(num*16);
    this->strlength=num*16;
    for(unsigned int i=0;i<src.length();i++)
    {
        // 一个unsigned int对应4个字节，保存4个字符信息
        rec[i>>2] |= (int)(src[i])<<((i%4)*8);
    }
    // 补充1000...000
    rec[src.length()>>2] |= (0x80<<((src.length()%4)*8));
    // 填充原文长度
    rec[rec.size()-2]=(src.length()<<3);
    return rec;
}

//格式转换
string MD5::format(unsigned int num)
{
    string res="";
    unsigned int base=1<<8;
    for(int i=0;i<4;i++)
    {
        string tmp = "";
        unsigned int b = (num >> (i * 8)) % base & 0xff;
        for(int j = 0; j < 2; j++)
        {
            tmp=str16[b%16]+tmp;
            b/=16;
        }
        res+=tmp;
     }
     return res;
}

