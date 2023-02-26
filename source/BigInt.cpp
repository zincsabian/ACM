const int MAXN = 200;//字符大小， 没压位
struct BigInt 
{  
    int len, s[MAXN];  
    BigInt ()  //初始化
    {  
        memset(s, 0, sizeof(s));  
        len = 1;  
    }  
    BigInt (int num) { *this = num; }  
    BigInt (const char *num) { *this = num; }  //让this指针指向当前字符串
    BigInt operator = (const int num)  
    {  
        char s[MAXN];  
        sprintf(s, "%d", num);  //sprintf函数将整型映到字符串中
        *this = s;  
        return *this;  //再将字符串转到下面字符串转化的函数中
    }  
    BigInt operator = (const char *num)  
    {  
        for(int i = 0; num[i] == '0'; num++) ;  //去前导0  
        len = strlen(num);  
        for(int i = 0; i < len; i++) s[i] = num[len-i-1] - '0'; //反着存
        return *this;
    }  
    BigInt operator + (const BigInt &b) const //对应位相加，最为简单
    {  
        BigInt c;  
        c.len = 0;  
        for(int i = 0, g = 0; g || i < max(len, b.len); i++)  
        {  
            int x = g;  
            if(i < len) x += s[i];  
            if(i < b.len) x += b.s[i];  
            c.s[c.len++] = x % 10;  //关于加法进位
            g = x / 10;  
        }  
        return c;  
    }  
    BigInt operator += (const BigInt &b)  //如上文所说，此类运算符皆如此重载
    {  
        *this = *this + b;  
        return *this;  
    }  
    void clean()  //由于接下来的运算不能确定结果的长度，先大而估之然后再查
    {  
        while(len > 1 && !s[len-1]) len--;  //首位部分‘0’故删除该部分长度
    }   
    BigInt operator * (const BigInt &b) //乘法重载在于列竖式，再将竖式中的数转为抽象，即可看出运算法则。
    {  
        BigInt c;  
        c.len = len + b.len;  
        for(int i = 0; i < len; i++)  
        {  
            for(int j = 0; j < b.len; j++)  
            {  
                c.s[i+j] += s[i] * b.s[j];//不妨列个竖式看一看
            }  
        }  
        for(int i = 0; i < c.len; i++) //关于进位，与加法意同 
        {  
            c.s[i+1] += c.s[i]/10;
            c.s[i] %= 10;
        }  
        c.clean();  //我们估的位数是a+b的长度和，但可能比它小（1*1 = 1）
        return c;  
    }  
    BigInt operator *= (const BigInt &b)  
    {  
        *this = *this * b;  
        return *this;  
    }  
    BigInt operator - (const BigInt &b)  //对应位相减，加法的进位改为借1
    {  //不考虑负数
        BigInt c;  
        c.len = 0;  
        for(int i = 0, g = 0; i < len; i++)  
        {  
            int x = s[i] - g;  
            if(i < b.len) x -= b.s[i];  //可能长度不等
            if(x >= 0) g = 0;  //是否向上移位借1
            else  
            {  
                g = 1;  
                x += 10;  
            }  
            c.s[c.len++] = x;  
        }  
        c.clean();  
        return c;   
    }  
    BigInt operator -= (const BigInt &b)  
    {  
        *this = *this - b;  
        return *this;  
    }  
    BigInt operator / (const BigInt &b)  //运用除是减的本质，不停地减，直到小于被减数
    {  
        BigInt c, f = 0; //可能会在使用减法时出现高精度运算 
        for(int i = len-1; i >= 0; i--)  //正常顺序，从最高位开始
        {  
            f = f*10;  //上面位的剩余到下一位*10
            f.s[0] = s[i];  //加上当前位
            while(f >= b)  
            {  
                f -= b;  
                c.s[i]++;  
            }  
        }  
        c.len = len;  //估最长位
        c.clean();  
        return c;  
    }  
    BigInt operator /= (const BigInt &b)  
    {  
        *this  = *this / b;  
        return *this;  
    }  
    BigInt operator % (const BigInt &b)  //取模就是除完剩下的
    {  
        BigInt r = *this / b;  
        r = *this - r*b;  
        r.clean();
        return r;  
    }  
    BigInt operator %= (const BigInt &b)  
    {  
        *this = *this % b;  
        return *this;  
    }  
    bool operator < (const BigInt &b) //字符串比较原理 
    {  
        if(len != b.len) return len < b.len;  
        for(int i = len-1; i != -1; i--)  
        {  
            if(s[i] != b.s[i]) return s[i] < b.s[i];  
        }  
        return false;  
    }  
    bool operator > (const BigInt &b)  //同理
    {  
        if(len != b.len) return len > b.len;  
        for(int i = len-1; i != -1; i--)  
        {  
            if(s[i] != b.s[i]) return s[i] > b.s[i];  
        }  
        return false;  
    }  
    bool operator == (const BigInt &b)  
    {  
        return !(*this > b) && !(*this < b);  
    }  
    bool operator != (const BigInt &b)  
    {  
        return !(*this == b);  
    }  
    bool operator <= (const BigInt &b)  
    {  
        return *this < b || *this == b;  
    }  
    bool operator >= (const BigInt &b)  
    {  
        return *this > b || *this == b;  
    }  
    string str() const  //将结果转化为字符串（用于输出）
    {  
        string res = "";  
        for(int i = 0; i < len; i++) res = char(s[i]+'0')+res;  
        return res;  
    }  
};  

istream& operator >> (istream &in, BigInt &x) //重载输入流 
{  
    string s;  
    in >> s;  
    x = s.c_str();  //string转化为char[]
    return in;  
}  

ostream& operator << (ostream &out, const BigInt &x)  //重载输出流
{  
    out << x.str();  
    return out;  
}