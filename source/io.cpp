inline ll read() {
    ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch>'9'; ch = getchar())
        if(ch == '-') f = -f;
    for(; ch >= '0' && ch <= '9'; ch = getchar())
        x = x * 10 + ch - '0';
    return x * f;
}
inline void print(ll x){
    if(!x)
        return;
    print(x/10);
    putchar(x%10+'0');
}
inline void write(ll x){
    if(x<0) putchar('-'), x=-x;
    if(!x) putchar('0');
    print(x);
}
inline void writeln(ll x){
    write(x); putchar('\n');
}

//用的时候记得改<<里的内容
struct FastIO{//不可与scanf,printf,getchar,putchar,gets,puts,cin,cout混用
private:
    static const int BUFSIZE=1e5;
    char buf[BUFSIZE];int pos,len;//读入buffer(缓冲器)以及读入指针
    int wpos;char wbuf[BUFSIZE];//输出指针以及输出buffer
    char a[21];//储存输出的数字 
#define gc() (pos == len && (len=(pos=0) 
    +fread(buf,1,BUFSIZE,stdin),!len)?EOF:buf[pos++])   
#define pc(c) (wpos == BUFSIZE ? 
    fwrite(wbuf,1,BUFSIZE,stdout),wpos=0,
    wbuf[wpos++]=c:wbuf[wpos++]=c)
public:
    FastIO():wpos(0),pos(0),len(0){}
    ~FastIO(){if(wpos)fwrite(wbuf,1,wpos,stdout),wpos=0;}   
    inline char getc(){return gc();}//读取char
    inline void putc(char c){pc(c);}//输出字符
    inline long long rd(){//读取long long
        long long x=0;char c=gc();bool f=0;
        for(;c<'0'||c>'9';c=gc())f|=c=='-';
        for(;c>='0'&&c<='9';c=gc())x=(x<<3)+(x<<1)+(c^48);
        return f?~x+1:x;
    }
    template<typename T>inline bool read(T &x){//多测读整数while(io.read(n))work();本地测试请输入两次ctrl Z 
        x=0;char c=gc();bool f=0;
        for(;c<'0'||c>'9';c=gc()){if(c==EOF)return false;f|=c=='-';}
        for(;c>='0'&&c<='9';c=gc())x=(x<<3)+(x<<1)+(c^48);
        if(f)x=~x+1;return true;
    }
    template<typename T>inline void wt(T x){//输出整数
        if(x<0)pc('-'),x=-x;short h=0;
        for(a[++h]='0'+x%10,x/=10;x;x/=10)a[++h]='0'+x%10;
        while(h)pc(a[h--]);
    }
    template<typename T>inline void wtl(T x){wt(x);pc('\n');}//write line输出整数并换行
    template<typename T>inline void wtb(T x){wt(x);pc(' ');}//write blank输出整数并空格
    inline int gets(char *s){
        int l=0;char c=gc();for(;c<=' ';c=gc());
        for(;c>' ';c=gc())s[l++]=c;s[l]=0;
        return l;
    }
    inline void puts(const char *s){
        const char *p=s;while(*p)pc(*p++);
    }//输出字符串 (不带换行)
    template<typename T>inline FastIO & operator >> (T &a){
        return read(a),*this;
    }//io>>a>>b;只能输入整数
    template<typename T>inline FastIO & operator << (T a){
        return wtl(a),*this;
    }//io<<a<<b;输出整数并带有回车
}io;//本地测试出入结束后请输入一次ctrl Z