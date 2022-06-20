参考链接：[https://zhuanlan.zhihu.com/p/106353082]()

**珂朵莉树** （Chtholly Tree）起源于[CF896C](https://link.zhihu.com/?target=https%3A//codeforces.com/problemset/problem/896/C)，那道题要求我们实现一种数据结构，可以较快地实现：

* 区间加
* 区间赋值
* 求区间第k大值
* 求区间n次方和

原题如下：

( **CF896C Willem, Chtholly and Seniorious** )

![](https://pic1.zhimg.com/80/v2-dab9afe9114971ed82c27e5516af35b8_720w.jpg)

> Seniorious is made by linking special talismans in particular order.
> After over 500 years, the carillon is now in bad condition, so Willem decides to examine it thoroughly.
> Seniorious has *n* pieces of talisman. Willem puts them in a line, the  *i* -th of which is an integer  *ai* .
> In order to maintain it, Willem needs to perform *m* operations.
> There are four types of operations:
>
> 1 *l* *r*  *x* : For each *i* such that *l* ≤ *i* ≤  *r* , assign *ai* + *x* to  *ai* .
> 2 *l* *r*  *x* : For each *i* such that *l* ≤ *i* ≤  *r* , assign *x* to  *ai* .
> 3 *l* *r*  *x* : Print the  *x* -th smallest number in the index range [ *l* ,  *r* ], i.e. the element at the  *x* -th position if all the elements *ai* such that *l* ≤ *i* ≤ *r* are taken and sorted into an array of non-decreasing integers. It's guaranteed that 1 ≤ *x* ≤ *r* - *l* + 1.
> 4 *l* *r* *x*  *y* : Print the sum of the  *x* -th power of *ai* such that *l* ≤ *i* ≤  *r* , modulo  *y* , i.e. ![[公式]](https://www.zhihu.com/equation?tex=%5Csum_%7Bi%3Dl%7D%5E%7Br%7D%7Ba_i%5Ex%7D%5Cbmod+y) .
>
> **Input**
> The only line contains four integers  *n* ,  *m* ,  *seed* , *vmax* (1 ≤  *n* , *m* ≤ 105, 0 ≤ *seed* < 109 + 7, 1 ≤ *vmax* ≤ 109).
> The initial values and operations are generated using following pseudo code:
>
> def rnd():
>
> ret = seed
> seed = (seed * 7 + 13) mod 1000000007
> return ret
>
> for i = 1 to n:
>
> a[i] = (rnd() mod vmax) + 1
>
> for i = 1 to m:
>
> op = (rnd() mod 4) + 1
> l = (rnd() mod n) + 1
> r = (rnd() mod n) + 1
>
> if (l > r):
> swap(l, r)
>
> if (op == 3):
> x = (rnd() mod (r - l + 1)) + 1
> else:
> x = (rnd() mod vmax) + 1
>
> if (op == 4):
> y = (rnd() mod vmax) + 1
>
> Here *op* is the type of the operation mentioned in the legend.
> **Output**
> For each operation of types 3 or 4, output a line containing the answer.

就此需求来说，普通的树状数组、线段树等显然难以胜任，看上去需要一种相当复杂的数据结构。然而，在这位珂学家出题人的题解中，他实现的数据结构却很简单，甚至看起来有点……暴力。他一开始用自己的id把这种数据结构命名为ODT，后又改而定名为珂朵莉树。

珂朵莉树的适用范围是有**区间赋值**操作且**数据随机**的题目。其实珂朵莉树看上去并不像是树状数据结构，但因为一般要用到std::set，而std::set是用红黑树实现的，所以也不算名不副实。在随机数据下，珂朵莉树可以达到 ![[公式]](https://www.zhihu.com/equation?tex=O%28n%5Clog%5Clog+n%29) 的复杂度（参见[这篇文章](https://zhuanlan.zhihu.com/p/102786071)）。

---

珂朵莉树的思想在于随机数据下的区间赋值操作很可能让大量元素变为同一个数。所以我们以三元组<l,r,v>的形式保存数据（区间 ![[公式]](https://www.zhihu.com/equation?tex=%5Bl%2Cr%5D) 中的元素的值都是v）：

![](https://pic2.zhimg.com/80/v2-e2bfb654e0549283734097606845b695_720w.jpg)

翻译成代码：

```cpp
struct node
{
    ll l, r;
    mutable ll v; // 这里mutable要写不然可能会CE
    node(ll l, ll r, ll v) : l(l), r(r), v(v) {} // 构造函数
    bool operator<(const node &o) const { return l < o.l; } // 重载小于运算符
};
```

然后把这些三元组存储到set里（也可以用链表，但set更优秀）：

```cpp
set<node> tree;
```

要把结构体放进set里需要重载小于运算符，set会保证内部元素有序（插入、删除和查询的时间复杂度都是 ![[公式]](https://www.zhihu.com/equation?tex=O%28%5Clog+n%29) ）。而mutable使得当整个结构体为const时，标为mutable的成员仍可变（因为可能有区间加等操作）。

然而，我们进行区间操作时并不总是那么幸运，可能会把原本连续的区间断开。我们需要一个函数来实现“断开”的操作，把<l,r,v>断成<l,pos-1,v>和<pos,r,v>：

```cpp
auto split(ll pos)
// 若不支持C++14，auto须改为set<node>::iterator
{
    auto it = tree.lower_bound(node(pos, 0, 0)); // 寻找左端点大于等于pos的第一个节点
    // 若不支持C++11，auto须改为set<node>::iterator
    if (it != tree.end() && it->l == pos) // 如果已经存在以pos为左端点的节点，直接返回
        return it;
    it--; // 否则往前数一个节点
    ll l = it->l, r = it->r, v = it->v;
    tree.erase(it); // 删除该节点
    tree.insert(node(l, pos - 1, v)); // 插入<l,pos-1,v>和<pos,r,v>
    return tree.insert(node(pos, r, v)).first; // 返回以pos开头的那个节点的迭代器
                                               // insert默认返回值是一个pair，第一个成员是我们要的
}
```

例如刚刚的情况，如果要split(4)会发生什么？

![](https://pic2.zhimg.com/80/v2-e2bfb654e0549283734097606845b695_720w.jpg)
再放一次图免得往上滑

首先lower_bound，找到左端点大于等于4的节点，<5,6,3>。它的左端点不是4，所以回退，得<2,4,2>。我们把节点<2,4,2>删除，然后插入<2,3,2>及<4,4,2>即可。是不是很简单？

![](https://pic3.zhimg.com/80/v2-f8d3b687974d1a054e0812acd58d5626_720w.jpg)

---

珂朵莉树的精髓在于 **区间赋值** 。而区间赋值操作的写法也极其简单：

```cpp
void assign(ll l, ll r, ll v)
{
    auto end = split(r + 1), begin = split(l); // 顺序不能颠倒，否则可能RE
    tree.erase(begin, end); // 清除一系列节点
    tree.insert(node(l, r, v)); // 插入新的节点
}
```

无非就是把范围内的节点全部删除，然后换上新的（范围较大的）节点而已。只是需要注意求end和begin的顺序不能颠倒，因为split(end)可能把begin原来所在的节点断开。

到此为止，已经可以轻松A掉这道紫题了：

（**CF915E Physical Education Lessons **洛谷@小粉兔译）

> Alex高中毕业了，他现在是大学新生。虽然他学习编程，但他还是要上体育课，这对他来说完全是一个意外。快要期末了，但是不幸的Alex的体育学分还是零蛋！
> Alex可不希望被开除，他想知道到期末还有多少天的工作日，这样他就能在这些日子里修体育学分。但是在这里计算工作日可不是件容易的事情：
> 从现在到学期结束还有 ![[公式]](https://www.zhihu.com/equation?tex=n) 天(从 ![[公式]](https://www.zhihu.com/equation?tex=1) 到 ![[公式]](https://www.zhihu.com/equation?tex=n) 编号)，他们一开始都是工作日。接下来学校的工作人员会**依次**发出 ![[公式]](https://www.zhihu.com/equation?tex=q) 个指令，每个指令可以用三个参数 ![[公式]](https://www.zhihu.com/equation?tex=l%2Cr%2Ck) 描述：
> 如果 ![[公式]](https://www.zhihu.com/equation?tex=k%3D1) ，那么从 ![[公式]](https://www.zhihu.com/equation?tex=l) 到 ![[公式]](https://www.zhihu.com/equation?tex=r) （包含端点）的所有日子都变成**非**工作日。
> 如果 ![[公式]](https://www.zhihu.com/equation?tex=k%3D2) ，那么从 ![[公式]](https://www.zhihu.com/equation?tex=+l) 到 ![[公式]](https://www.zhihu.com/equation?tex=+r) （包含端点）的所有日子都变成 **工作日** 。
> 帮助Alex统计每个指令下发后，剩余的工作日天数。
> **输入格式**
> 第一行一个整数 ![[公式]](https://www.zhihu.com/equation?tex=+n) ，第二行一个整数 ![[公式]](https://www.zhihu.com/equation?tex=q+%281%5Cle+n%5Cle+10%5E9%2C%5C%3B1%5Cle+q%5Cle+3%5Ccdot+10%5E5%29) ，分别是剩余的天数和指令的个数。
> 接下来 ![[公式]](https://www.zhihu.com/equation?tex=q) 行，第 ![[公式]](https://www.zhihu.com/equation?tex=i) 行有 ![[公式]](https://www.zhihu.com/equation?tex=3) 个整数 ![[公式]](https://www.zhihu.com/equation?tex=l_i%2Cr_i%2Ck_i) ，描述第 ![[公式]](https://www.zhihu.com/equation?tex=i) 个指令 ![[公式]](https://www.zhihu.com/equation?tex=%281%5Cle+l_i%2Cr_i%5Cle+n%2C%5C%3B1%5Cle+k%5Cle+2%29)。
> **输出格式**
> 输出 ![[公式]](https://www.zhihu.com/equation?tex=q) 行，第 ![[公式]](https://www.zhihu.com/equation?tex=i) 行表示第 ![[公式]](https://www.zhihu.com/equation?tex=i+) 个指令被下发后剩余的工作日天数。

只需要在assign过程中求一下和即可，部分代码如下：

```cpp
int sum;
void assign(int l, int r, int v)
{
    int tot = 0, len = 0;
    auto end = split(r + 1), it = split(l), begin = it;
    for (it; it != end; it++)
    {
        len += (it->r - it->l + 1);
        tot += it->v * (it->r - it->l + 1);
    }
    tree.erase(begin, end);
    tree.insert(node(l, r, v));
    if (v == 1)
        sum += (len - tot);
    else
        sum -= tot;
}
int main()
{
    int n = read(), q = read();
    tree.insert(node(1, n, 1));
    sum = n;
    while (q--)
    {
        int l = read(), r = read(), k = read();
        assign(l, r, k == 1 ? 0 : 1);
        printf("%d\n", sum);
    }
    return 0;
}
```

---

那么，文章开头那些复杂的操作，要如何实现呢？实际上一点都不复杂，就两个字， **暴力** 。

区间加（就挨个加）：

```cpp
void add(ll l, ll r, ll v)
{
    auto end = split(r + 1);
    for (auto it = split(l); it != end; it++)
        it->v += v;
}
```

求区间k大值（直接扔到vector里排下序）：

```cpp
ll kth(ll l, ll r, ll k)
{
    auto end = split(r + 1);
    vector<pair<ll, ll>> v; // 这个pair里存节点的值和区间长度
    for (auto it = split(l); it != end; it++)
        v.push_back(make_pair(it->v, it->r - it->l + 1));
    sort(v.begin(), v.end()); // 直接按节点的值的大小排下序
    for (int i = 0; i < v.size(); i++) // 然后挨个丢出来，直到丢出k个元素为止
    {
        k -= v[i].second;
        if (k <= 0)
            return v[i].first;
    }
}
```

求区间n次方和（用快速幂直接求）：

```cpp
ll sum_of_pow(ll l, ll r, ll x, ll y)
{
    ll tot = 0;
    auto end = split(r + 1);
    for (auto it = split(l); it != end; it++)
        tot = (tot + qpow(it->v, x, y) * (it->r - it->l + 1)) % y; // qpow自己写一下
    return tot;
}
```

真是一个比一个暴力……然而因为随机数据中大量赋值操作的存在，整个珂朵莉树上也没有太多节点，所以速度还是很可观的。需要注意的是，如果题目不保证随机数据， **非常容易hack** 。所以很多时候，珂朵莉树也许只能当作一种**对拍**方法或者**骗分**算法。

 *（更新）* 但是……事实上，还有一种**暴力+暴力**法。就是，先把数据**离线**下来，然后，根据输入数据的 **特点** （比如有多少次大范围的赋值），选择直接暴力或使用珂朵莉树。因为，如果一个数据具有卡珂朵莉树的特点，那么它肯定大范围赋值较少，那么暴力的复杂度也许就可以接受。

CF896C的完整代码如下（题目专门给了一个随机数生成器就是防hack...）：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read()
{
    ll ans = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
    {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    return ans;
}
struct node
{
    ll l, r;
    mutable ll v;
    node(ll l, ll r, ll v) : l(l), r(r), v(v) {}
    bool operator<(const node &o) const { return l < o.l; }
};
set<node> tree;
auto split(ll pos)
{
    auto it = tree.lower_bound(node(pos, 0, 0));
    if (it != tree.end() && it->l == pos)
        return it;
    it--;
    ll l = it->l, r = it->r, v = it->v;
    tree.erase(it);
    tree.insert(node(l, pos - 1, v));
    return tree.insert(node(pos, r, v)).first;
}
void assign(ll l, ll r, ll v)
{
    auto end = split(r + 1), begin = split(l);
    tree.erase(begin, end);
    tree.insert(node(l, r, v));
}
ll qpow(ll a, ll n, ll p)
{
    ll ans = 1;
    a %= p;
    while (n)
    {
        if (n & 1)
            ans = ans * a % p;
        n >>= 1;
        a = a * a % p;
    }
    return ans;
}
ll n, m, seed, vmax;
ll rnd()
{
    ll ret = seed;
    seed = (seed * 7 + 13) % 1000000007;
    return ret;
}
void add(ll l, ll r, ll v)
{
    auto end = split(r + 1);
    for (auto it = split(l); it != end; it++)
        it->v += v;
}
ll kth(ll l, ll r, ll k)
{
    auto end = split(r + 1);
    vector<pair<ll, ll>> v;
    for (auto it = split(l); it != end; it++)
        v.push_back(make_pair(it->v, it->r - it->l + 1));
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++)
    {
        k -= v[i].second;
        if (k <= 0)
            return v[i].first;
    }
}
ll sum_of_pow(ll l, ll r, ll x, ll y)
{
    ll tot = 0;
    auto end = split(r + 1);
    for (auto it = split(l); it != end; it++)
        tot = (tot + qpow(it->v, x, y) * (it->r - it->l + 1)) % y;
    return tot;
}
int main()
{
    n = read(), m = read(), seed = read(), vmax = read();
    for (int i = 1; i <= n; ++i)
    {
        int r = rnd();
        tree.insert(node(i, i, r % vmax + 1));
    }
    for (int i = 1; i <= m; ++i)
    {
        ll opr = rnd() % 4 + 1, l = rnd() % n + 1, r = rnd() % n + 1, x, y;
        if (l > r)
            swap(l, r);
        if (opr == 3)
            x = rnd() % (r - l + 1) + 1;
        else
            x = rnd() % vmax + 1;
        if (opr == 4)
            y = rnd() % vmax + 1;
        switch (opr)
        {
        case 1:
            add(l, r, x);
            break;
        case 2:
            assign(l, r, x);
            break;
        case 3:
            printf("%lld\n", kth(l, r, x));
            break;
        case 4:
            printf("%lld\n", sum_of_pow(l, r, x, y));
        }
    }
    return 0;
}
```
