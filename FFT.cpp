//CodeForces - 632E

#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;
#define up(i, j, k) for (int i = j; i < k; i++)
#define uup(i, j, k) for (int i = j; i >= k; i--)
#define mem(i, j) memset(i, j, sizeof i)
#define ll long long
#define sfi(i) scanf("%d", &i)
#define sfl(i) scanf("%lld", &i)
#define sfs(i) scanf("%s", i)
#define sfd(i) scanf("%lf", &i)
#define sfc(i) scanf("%c", &i)
#define sfu(i) scanf("%I64u", &i);
#define mod(x) x % mod
#define sf() cout << "This is a flag!!" << endl;
#define ull unsigned long long

const int mod = 1e9 + 7;
const double eps = 1e-5;
const int MAX = (1 << 21) + 5;
const double pi = acos(-1.0);
const int inf = 0x7f7f7f7f;
const ll INF = 0x7f7f7f7f7f7f7f7f;

int Coefficient[MAX];
int A1_Size, A2_Size, Sum;
int n, m;

const double PI = acos(-1.0);
//复数结构体
struct complex
{
    double r, i;
    complex(double _r = 0.0, double _i = 0.0)
    {
        r = _r;
        i = _i;
    }
    complex operator+(const complex &b)
    {
        return complex(r + b.r, i + b.i);
    }
    complex operator-(const complex &b)
    {
        return complex(r - b.r, i - b.i);
    }
    complex operator*(const complex &b)
    {
        return complex(r * b.r - i * b.i, r * b.i + i * b.r);
    }
} A1[MAX], A2[MAX];
/*
* 进行FFT和IFFT前的反转变换。
* 位置i和 （i二进制反转后位置）互换
* len必须取2的幂
*/
void change(complex y[], int len)
{
    int i, j, k;
    for (i = 1, j = len / 2; i < len - 1; i++)
    {
        if (i < j)
            swap(y[i], y[j]);
        //交换互为小标反转的元素，i<j保证交换一次
        //i做正常的+1，j左反转类型的+1,始终保持i和j是反转的
        k = len / 2;
        while (j >= k)
        {
            j -= k;
            k /= 2;
        }
        if (j < k)
            j += k;
    }
}
int rev(int id, int len)
{
    int ret = 0;
    for (int i = 0; (1 << i) < len; i++)
    {
        ret <<= 1;
        if (id & (1 << i))
            ret |= 1;
    }
    return ret;
}

/*
* 做FFT
* len必须为2^k形式，
* on==1时是DFT，on==-1时是IDFT
*/
complex A[MAX];
void fft(complex *a, int len, int DFT)
{ //对a进行DFT或者逆DFT, 结果存在a当中
    //Complex* A = new Complex[len]; 这么写会爆栈
    for (int i = 0; i < len; i++)
        A[rev(i, len)] = a[i];
    for (int s = 1; (1 << s) <= len; s++)
    {
        int m = (1 << s);
        complex wm = complex(cos(DFT * 2 * PI / m), sin(DFT * 2 * PI / m));
        for (int k = 0; k < len; k += m)
        {
            complex w = complex(1, 0);
            for (int j = 0; j < (m >> 1); j++)
            {
                complex t = w * A[k + j + (m >> 1)];
                complex u = A[k + j];
                A[k + j] = u + t;
                A[k + j + (m >> 1)] = u - t;
                w = w * wm;
            }
        }
    }
    if (DFT == -1)
        for (int i = 0; i < len; i++)
            A[i].r /= len, A[i].i /= len;
    for (int i = 0; i < len; i++)
        a[i] = A[i];
    return;
}

int a1[MAX], a2[MAX];

int main()
{
    while (~sfi(n))
    {
        sfi(m);
        int xx;
        mem(a1, 0);
        mem(a2, 0);
        up(i, 0, n)
        {
            sfi(xx);
            a1[xx] = 1;
            a2[xx] = 1;
            A1_Size = max(A1_Size, xx);
        }
        A2_Size = A1_Size;
        memset(Coefficient, 0, sizeof(Coefficient));
        m--;
        int len = 1;
        int len1 = 1;
        while (m)
        {
            if (m & 1)
            {
                while (len1 < A1_Size + A2_Size + 1)
                    len1 <<= 1;
                up(i, 0, len1)
                {
                    A1[i] = complex(a1[i], 0);
                    A2[i] = complex(a2[i], 0);
                }
                fft(A1, len1, 1);
                fft(A2, len1, 1);
                up(i, 0, len1)
                {
                    A2[i] = A1[i] * A2[i];
                }
                fft(A2, len1, -1);
                up(i, 0, len1)
                {
                    if (A2[i].r > 0.5)
                        a2[i] = 1;
                    else
                        a2[i] = 0;
                }
                A2_Size += A1_Size;
            }
            while (len < A1_Size + A1_Size + 1)
                len <<= 1;
            up(i, 0, len)
            {
                A1[i] = complex(a1[i], 0);
                A2[i] = complex(a2[i], 0);
            }
            fft(A1, len, 1);
            up(i, 0, len)
            {
                A1[i] = A1[i] * A1[i];
            }
            fft(A1, len, -1);
            up(i, 0, len)
            {
                if (A1[i].r > 0.5)
                    a1[i] = 1;
                else
                    a1[i] = 0;
            }
            A1_Size *= 2;
            m >>= 1;
        }
        for (int i = 0; i < A2_Size + 1; i++)
        {
            if (a2[i] != 0)
            {
                printf("%d ", i);
            }
        }
        printf("\n");
    }
    return 0;
}