NOIP 08 b 线性数据结构，STL顺序容器和容器适配器（未完成）  
======

|Author|杜博识Dubos|
|---|---|
|E-mail|dubos@foxmail.com|

本文是[NOIP 08 a 普及组数据结构和STL容器](/NOIP%20Junior/NOIP%2008%20a%20数据结构普及组.md)正文的一部分。  

我们已经知道数据结构可以按照逻辑分为集合、线性、树形、图状四类，也可以按存储分为顺序、链式两类。这一节我们学习几种线性数据结构，他们的共同点是从逻辑上讲，在数据元素的非空有限集中：  
* 存在唯一一个“**第一个first数据元素**”；
* 存在唯一一个“**最后一个last数据元素**”；
* 每个数据元素（first数据元素可以例外）只有一个**直接前驱immediate predecessor**；
* 每个数据元素（last数据元素可以例外）只有一个**直接后继immediate successor**。  

他们的不同点是：
* 其中有的属于**顺序存储**：逻辑上相邻的数据在硬件（例如内存）上占据的物理空间也相邻，**寻秩访问（call-by-rank）**；
* 另外一些属于**链式存储**：逻辑上相邻的数据在硬件（例如内存）上占据的物理空间不一定相邻，**循链访问（call-by-link）**。  

我们学习每种数据结构都是先了解其**特征**，然后学习其实现**原理**（用已有C++编程实现其中一些特征），最后学习如何直接使用相应的**STL容器**。
#### 全文较长，目录如下：  
* [数组](#数组array)
* [顺序表](#顺序表sequence-list)
* [向量](#向量或称动态数组vector)
* [链表](#链表linked-list)
* [](#)  
* [](#)  
* [](*)  
* [](*)

------  
## 数组array
之前讲过，现在就不重复了。数组是一种**线性、顺序存储的数据结构**，是顺序表的一个具体例子，顺序表的实现也是通过数组。  

## 顺序表sequence list  
* **特征**：
	* 顺序表从逻辑来讲是**线性**数据结构，从存储来讲是**顺序**数据结构，数组特征与之相同，所以我们**用数组来实现顺序表**。）。顺序表中逻辑相邻的数据元素存储位置也相邻，如下图：  
	![](/diagrams/NOIP%2008%20b%20顺序表1.jpg)  
	* 访问：**寻秩访问（call-by-rank）** 是指，如果想要知道某个特定数据元素的存储位置或者访问某个元素，只需确定顺序表的起始位置和这个特定数据元素的**秩（rank，也就是序号）**，即可按照上图中的推导方法找到这个特定数据元素的存储位置（数组的元素序号从0开始，但为了与日常编号习惯保持一致，我们在图中选择从第1位（而非第0位）元素开始存储数据元素）。**顺序表访问操作的时间复杂度为O(1)，访问效率高是顺序表的优势**。  
	* 插入：在长度为n的顺序表中第i位元素**之前**前插入新元素new，则结果应该是一个长度为n+1的新顺序表，原a<sub>i</sub>被重新赋值为new，原a<sub>i</sub>至a<sub>n</sub>（共n-i+1个）元素的依次向后移动1位，变成新a<sub>i+1</sub>至a<sub>n+1</sub>元素。假设在任何位置前插入新元素的概率相等，则插入导致的移动次数平均为  
	![](/diagrams/NOIP%2008%20b%20顺序表2.gif)  
	所以**顺序表插入操作的时间复杂度为O(n)** ，每次插入都要对多个其他元素进行操作，效率不理想。
	* 删除：在长度为n的顺序表中删除第i位元素，则结果应该是一个长度为n-1的新顺序表，原a<sub>i</sub>元素被删掉，原a<sub>i+1</sub>至a<sub>n</sub>（共n-i个）元素的依次向前移动1位，变成新a<sub>i</sub>至a<sub>n-1</sub>元素。假设在任何位置删除元素的概率相等，则删除导致的移动次数平均为  
	![](/diagrams/NOIP%2008%20b%20顺序表3.gif)  
	所以**顺序表删除操作的时间复杂度为O(n)** ，每次删除都要对多个其他元素进行操作，效率不理想。

* **原理**：  
	* [例1：oj.noi.cn 1109 《维护序列》（1. 顺序表解法）](https://github.com/Duboshi/OJ-solutions/blob/master/oj.noi.cn/1109%20%E7%BB%B4%E6%8A%A4%E5%BA%8F%E5%88%97.md#1-顺序表解法)，我们通过这个例题的“1. 顺序表解法”用数组实现顺序表的访问、插入和删除。  
	
* **容器**：数组  

[↑回到页首目录](#全文较长目录如下)  

## 向量（或称动态数组）vector  

* **特征**：向量也是一种顺序表，但相对于数组，向量的长度可变，所以向量也被称为“动态数组”，这个特征使得向量在实际中比数组更实用。虽然向量是用数组实现的，但实际使用时只需要用STL容器vector及其库函数即可，具体库函数下面会介绍。  

* **原理**：
访问、插入、删除的原理跟顺序表的一样，需要另外说明的是向量改变长度的原理。数组所占物理空间的容量不能调整，这称为“**静态空间管理策略**”。向量的扩容、缩容原理则体现了“**动态空间管理策略**”：  
	* 每当对向量插入一个元素时，如果实现向量的数组还有可用空间，那么操作正常进行；一旦可用空间耗尽（将会导致上溢overflow），就另行申请一个长度更大的数组，例如是原数组长度的二倍。（这个倍数叫做增长因子growth factor，不同语言和环境下不一样，例如Microsoft Visual C++ 2013编译和Java环境下都是1.5，而信息学竞赛常用的G++编译环境下就是2）。原来实现向量的数组复制到新数组再插入元素，而原数组所占的空间被释放并归还给操作系统，这是**向量的扩容原理**。  
	* 反过来，每当向量元素被删除，虽然不会上溢，但如果剩下的元素太少，实现向量的数组所占大部分空间会被浪费（这种情况叫下溢underflow），所以要检查向量实际长度与数组所占空间的比值（这个比值叫做装填因子load factor），如果低于某个值（例如25%、10%等等），就把一部分多余空间归还给操作系统，这是**向量的缩容原理**。  

* **容器**：  
	* STL容器```vector```，这个容器使用**随机访问迭代器**，支持```++i;```、```--i;```、```i+=c;```、```i-=c;```、```i1 < i 2```、```i1 - i2```等命令（i是迭代器，c是整数常量）。我们常用的库函数如下：  

		|函数名|功能|  
		|---|---|  
		|(constructor)|构造函数：分为默认构造函数、填充构造函数、范围构造函数、复制构造函数4种|  
		|=|赋值符号：之前讲过，数组只能用```a={};```进行初始化赋值，不能用```a=b;```(a和b都是数组)赋值。向量与数组不同，向量可以用```a=b```（a和b都是向量）赋值。|  
		|**Iterators:**||  
		|iterator begin()|迭代器函数：指向容器中第一个元素的正向迭代器|  
		|iterator end()|迭代器函数：指向最后一个元素【之后一个位置】的正向迭代器|  
		|reverse_iterator rbegin()|迭代器函数：指向容器中最后一个元素的反向迭代器|  
		|reverse_iterator rend()|迭代器函数：rend()则是指向第一个元素【之前一个位置】的反向迭代器|  
		|**Capacity:**||  
		|size_type size()|返回向量的长度：所包含元素的个数。（size_type数据类型是一种无符号整数）|  
		|size_type capacity()|返回向量的容量：目前向量所占内存空间足以容纳的元素个数|  
		|void resize()|```v.resize(n)```使向量v长度变为n，若为扩大至n则新增元素的默认值，若为缩小至n则删除多余元素。```v.resize(n, value)```使向量长度变为n，若为扩大至n则新增元素值均为value，若为缩小至n则删除多余元素。|  
		|bool empty()|若向量为空（size()==0）则函数返回值为true，否则为false|  
		|**Element access:**|| 
		|[]|访问符号：向量除了用迭代器访问之外，也可以向数组一样用[]符号访问符号，数组v的首个元素是```v[0]```。跟数组一样，向量的[]访问也有可能造成越界，但是系统不会提示|  
		|at()|访问函数：```v.at(0)```和```v[0]```都是向量v的第一个元素（的引用），但是at()函数会检查参数是否越界，如有越界程序会中止运行并提示out_of_range|  
		|front()|访问函数：返回向量首元素的引用，注意不要与迭代器函数```begin()```混淆|  
		|back()|访问函数：返回向量末元素的引用，注意不要与迭代器函数```end()```混淆|  
		|**Modifiers:**||  
		|void push_back()|修改函数：```v.push_back(value)```在向量v末尾新增一个值为value的元素，向量长度增加1|  
		|void pop_back()|修改函数：```v.pop_back()```把向量v末位元素删掉，向量长度减少1|  
		|void assign()|修改函数：为向量重新赋值，原有的元素都删除。```v.assign(n, value)```将n个值为value的元素赋值给向量v；```v.assign(first, last)```将向量迭代器区间（或是数组指针区间）[first, last)内的元素赋值给向量v|  
		|insert()|修改函数：三种情况都是在向量v中迭代器pos指向的元素【之前】插入。```iterator v.insert(pos, value)```插入一个值为value的元素，注意其返回值为迭代器pos；```void v.insert(pos, n, value)```插入n个值为value的元素；```void v.insert(pos, first, last)```插入向量迭代器区间（或是数组指针区间）[first, last)内的元素|  
		|iterator erase()|修改函数：```v.erase(pos)```删除向量v中迭代器pos指向的元素，```v.erase (first, last)```删除向量v中迭代器区间[first,last)指向的元素，注意是左闭右开区间|  
		|void clear()|修改函数：删除向量中的所有元素|  
		|void swap()|修改函数：```v1.swap(v2)```会将向量v1和v2的内容相互交换，这个函数并不要求v1和v2长度相等，但是要求两个向量元素的数据类型相同|  

	* 例2：vector常见库函数
		```cpp  
		#include <iostream>
		#include <vector>

		using namespace std;

		//i是正向迭代器，r是反向迭代器 
		vector<int>::iterator i;
		vector <int>::reverse_iterator r;
		int j;

		//printVector用于输出向量内容，在下面各个例子可以调用printVector以便查验各个库函数作用 
		void printVector(vector <int> v)
		{
			for (i=v.begin(); i!=v.end(); ++i)
				cout <<*i <<" ";
			cout <<endl;
		}

		int main()
		{	
			//默认构造函数：向量v1的元素为int类型，v1长度为0
				vector <int> v0;

			//填充构造函数（不赋值）：向量v1的长度为1，但是没有赋值 
				vector <int> v1(1);

			//填充构造函数（赋值）：向量v3的长度为3，各元素值为1，即{1, 1, 1}
				//【注意】vector <int> v3 = {1, 1, 1};也可以得到同样效果 
				vector <int> v3(3, 1);

			//范围构造函数：向量v2包含[v3.begin(), v3.begin()+2)区间内迭代器指向的元素，
				//【注意】是左闭右开区间，所以这个例子中v4包含2个元素，值为1，即{1, 1}
				vector <int> v2(v3.begin(), v3.begin()+2);

			//复制构造函数，push_back()函数：
				vector <int> v4(v3);	//向量v4复制v3，即{1, 1, 1} 
				v4.push_back(1);		//在v4末尾增加一个元素值为1，变成{1, 1, 1, 1} 

			//= 赋值符号：
				vector <int> v5 = v4;	//向量v5被赋值与v4相同，即{1, 1, 1, 1}
				//【注意】之前讲过，这种赋值方式对于数组不可行
				//如果v5和v3都是普通数组而不是向量，就不可以直接用=将v4赋值给v5

				//【注意】向量不能用= {1, 1, 1, 1}赋值

				v5.push_back(1);	//将v5变为{1, 1, 1, 1, 1}

			//迭代器函数：
				//begin()和end()用于正向迭代器
				int n=0;
				for	(i=v3.begin(); i!=v3.end(); ++i)
				{
					*i += n;
					++n;
					cout <<*i <<" ";	//v3变成{1, 2, 3}
				}
				cout <<endl;

				//rbegin()和rend()用于反向迭代器
				for (r=v3.rbegin(); r!=v3.rend(); ++r)
					cout <<*r <<" ";	//反向迭代器遍历输出v3：3 2 1
				cout <<endl;

			//size()和capacity()有区别 
				cout <<v5.size() <<endl;		//5：v5原本只有4个元素，后来新增1个；
				cout <<v5.capacity() <<endl;	//8：新增1个时扩容，容量变为原来的2倍 

			//resize()函数： 
				vector <int> v10 = v5;
				v10.resize(8);		//v10长度变成 8：{1, 1, 1, 1, 1, 0, 0, 0} 
				v10.resize(10, 1);	//v10长度变成10：{1, 1, 1, 1, 1, 0, 0, 0, 1, 1}

			//empty()函数：	
				if (v0.empty())
					cout <<"v0 is empty." <<endl;		//会输出这一行 
				else
					cout <<"v0 is NOT empty." <<endl;	//不会输出这一行 

			//[]访问符号： 
				for (j=0; j<10; ++j)
					v10[j] = j+1;		//把v10变成{1, 2, 3, 4, 5, 6, 7, 8, 9, 10} 

			//at()函数： 
				for (j=0; j<5; ++j)
					v5.at(j) = j+1;	//把v5变成{1, 2, 3, 4, 5}

				//for (j=0; j<5; ++j)
				//	v4.at(j) = j+1;		//这里有越界，如果执行会输出out_of_range提示

			//front()和back()函数：
				cout <<v10.front() <<endl;	//1
				cout <<v5.back() <<endl; 	//5

			//push_back()和pop_back()函数：
				v4.pop_back(); v4.pop_back(); v4.pop_back();	//v4变成{1}
				for (j=2; j<5; ++j)
					v4.push_back(j);			//v4变成{1, 2, 3, 4} 

			//assign()函数：
				v5.assign(5, 10);				//v5变成{10, 10, 10, 10, 10}
				v5.assign(v10.begin()+5, v10.begin()+10);	//v5变成{6, 7, 8, 9, 10} 

				int arr [10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
				v5.assign(arr, arr+5);				//v5变成{10, 20, 30, 40, 50}

			//insert()函数：
				i = v2.insert(v2.begin()+1, 2);	//v2由{1, 1}变成{1, 2, 1}，i=v2.begin()+1
				v2.insert(i+2, 2, 0);			//v2变成{1, 2, 1, 0, 0}，i值失效 
				//【注意】由于插入过程中伴随着扩容，迭代器i指向的地址已经失效

				i = v2.begin()+2;
				v2.insert(i, v5.begin(), v5.begin()+2); //v2变成{1, 2, 10, 20, 1, 0, 0}

			//erase()函数：
				v2.erase(v2.begin()+2);				//v2变成{1, 2, 20, 1, 0, 0}
				v2.erase(v2.begin()+2, v2.end());		//v2变成{1, 2}

			//clear()函数：
				v2.clear();	//v2变成空向量

			//swap()函数：
				v2.swap(v5);	//两者互换：v5变成空向量，v2变成{10, 20, 30, 40, 50}
				
			//二维向量：与二维数组类似，我们也可以建立二维向量。例如二维向量vv有3个元素，
			//每个元素都是一个vector <int>向量。 
			vector<vector <int> > vv(3);
			
			return 0;
		}
		```  
	
	* [例3：UVa 101 The Blocks Problem](https://github.com/Duboshi/OJ-solutions/blob/master/UVa/UVa%20101%20The%20Blocks%20Problem.md)，我们通过这个例题应用vector容器及其部分库函数。  

[↑回到页首目录](#全文较长目录如下)  

## 链表linked list
* **历史**：链表的发明与人工智能的起源关系非常密切。1956年暑假，大约20位学者（其中主要参与者见上图）在达特茅斯学院召开名为"Summer Research Project on Artificial Intelligence"的会议，研究关于用机器模拟学习以及人类其他智能的问题。[达特茅斯会议](https://en.wikipedia.org/wiki/Dartmouth_workshop)是人工智能领域的开端。在这次会议上，Herbert Simon和Allen Newell报告了他们与Cliff Shaw一同开发的Logic Theory Machine，链表就是他们开发这个“逻辑理论机”过程中发明的。  
![](/diagrams/NOIP%2008%20b%201956%20Dartmouth%20Conference.jpg)  
	* Simon和Newell的合作始于1952年，当时卡耐基工学院（卡耐基梅隆大学前身）工业管理系主任和教授[Herbert A. Simon](https://en.wikipedia.org/wiki/Herbert_A._Simon)（1916-2001）和普林斯顿大学博士生[Allen Newell](https://en.wikipedia.org/wiki/Allen_Newell)（1927-1992）都在RAND公司访问。Simon在那不久前（1949年）刚参与创建了工业管理系，1965年他还将与Newell以及数学系主任Alan J. Perlis一同创建卡耐基工学院计算机系并将其发展成世界顶尖水平。Simon一生的研究都围绕人类决策行为，这是个多学科交叉的领域，所以他一生取得了多个学科的辉煌成就：在芝加哥大学跟从经济学家Henry Schultz取得政治学专业博士学位，最终获得计算机科学（与Newell一起获得1975年图灵奖）、经济学（1978年经济学纪念诺贝尔奖）和心理学（1993年美国心理学会终身贡献奖）三个学科的最高奖项。他认为人类尽管有做出理性决策的意愿，但很多情况下信息不完备或者没有做出完全理性决策的必要性，所以人们的实际决策往往只是令自己满意的而非客观最优的，即有限理性（bounded rationality）。有限理性决策过程中，人们使用的并非穷举式分析方法，而是**启发式（Heuristic）分析方法（或称为探索法）**：结合自己已掌握的信息（而非全部对做决策有用的信息）做出判断。数学教育家、斯坦福大学教授George Polya在《怎样解题》中传授的解题思路也是启发式分析方法：“你以前见过它吗？你是否见过相同的问题而形式稍有不同？” Newell曾在斯坦福读本科，深受Polya启发式分析方法的影响，所以他与Simon见面时，两人一拍即合，决定写一个计算机程序模拟人类的启发式分析方法来解决问题（具体来讲是证明 Bertrand Russell和Alfred North Whitehead所著《数学原理》中的定理）。本来Newell是在普林斯顿大学学习博弈论的，结果这样一来就转到了卡耐基工学院成为Simon的博士生。  
	![](https://upload.wikimedia.org/wikipedia/commons/thumb/7/70/Gates-Hillman_Complex_at_Carnegie_Mellon_University_3.jpg/800px-Gates-Hillman_Complex_at_Carnegie_Mellon_University_3.jpg)  
	(图为卡耐基梅隆大学计算机学院Gates-Hillman Complex，建于2009年)  
	* 根据启发式思维的特点，决策要根据已有的信息集合做出，而信息集合本身可以通过学习、取舍等思维过程发生变化。所以他们需要编程语言支持一种重要的功能：**可以对信息列表高效地添加、删除、插入、重新排列信息元素**，我们知道顺序表数据结构不适合执行这些功能，**顺序表的优势是访问效率高（常数时间复杂度），劣势是插入、删除等效率不理想（线性时间复杂度）**。当时没有其他编程语言支撑高效插入/删除，所以Simon和Newell需要先设计一种编程语言，然后才能用这门语言写出程序。他们找到RAND公司的计算机专家[Cliff Shaw](https://en.wikipedia.org/wiki/Cliff_Shaw)，三人一起于1956年设计出了
IPL语言并做出Logic Theory Machine，该程序证明出《数学原理》中前52个定理中的38个，其中有些证明方法比原书证明更加简洁，而链表数据结构正是IPL语言最重要的特征。下图出自1957年阐述Logic Theory Machine编程原理的论文，现在所有教材中链表的示意图都发源于此：  

		|原文图4|原文图7|  
		|---|---|  
		|![](/diagrams/NOIP%2008%20b%20List%20of%20elements.JPG)|![](/diagrams/NOIP%2008%20b%20Deletion%20from%20a%20List.JPG)|  
		|元素之间不像顺序表那样直接相连，而是用location联系起来|只需改变location联系方式，不需要像顺序表那样移动其他元素即可实现高效删除，添加、插入、重新排列等功能同理|  
		
		Newell, Allen; Shaw, F. C. (1957). "Programming the Logic Theory Machine". Proceedings of the Western Joint Computer Conference: 230–240.  
	
* **特征**：  
	* 链表中逻辑相邻的元素存储位置并不相邻，它们靠指针彼此联系起来，Simon和Newell给出的链表中元素的联系是单向的，被称为**单向链表Singly linked list**，我们目前常用的是**双向链表Doubly linked list**（如下图）。**头节点Head**和**尾节点Tail**统称为**哨兵节点Sentinel nodes**，其意义在于：仅将信息存储在它们之间的节点（例如图中的a<sub>1</sub>、a<sub>2</sub>、a<sub>4</sub>），而所有这些中间节点都有前驱和后继，于是设计任何操作时就无需再考虑第一个和最后一个元素可能没有前驱或者后继的边界情况。如果头节点和尾节点中间没有节点，则链表为空。  
	![](/diagrams/NOIP%2008%20b%20双向链表.jpg)  
	* 访问：循链访问的效率低于顺序表的寻秩访问，例如当我们想知道第i个元素的值时，必须从头开始，沿着图中蓝色链箭头逐个访问，直至第i个（或者从尾开始沿着黄色链箭头逐个访问）。对于长度为n的链表，如果访问各个元素的概率相等，那么**访问操作的时间复杂度为O(n)**  
	* 插入：**只要指定了插入位置**，则插入一个元素需要改变4个指针的值，即为**常数时间复杂度O(1)**。例如上图，在a<sub>2</sub>后面插入了a<sub>4</sub>元素  
	* 删除：**只要指定了删除位置**，则插入一个元素需要改变4个指针的值，即为**常数时间复杂度O(1)** 。例如上图，插入a<sub>4</sub>之后删除了a<sub>2</sub>元素  
	* **插入、删除等操作是链表的效率优势所在，也是Simon、Newell和Shaw发明这种数据结构的目的所在**。  
* **原理**：  
	* 单链表  
		* [例4：oj.noi.cn 1109 《维护序列》（2. 单向链表解法）](https://github.com/Duboshi/OJ-solutions/blob/master/oj.noi.cn/1109%20%E7%BB%B4%E6%8A%A4%E5%BA%8F%E5%88%97.md#2-%E5%8D%95%E5%90%91%E9%93%BE%E8%A1%A8%E8%A7%A3%E6%B3%95)，我们通过这个例题用数组实现单向链表的访问、插入和删除。  
		* [例5：oj.noi.cn 1110 《小A的烦恼》](https://github.com/Duboshi/OJ-solutions/blob/master/oj.noi.cn/1110%20%E5%B0%8FA%E7%9A%84%E7%83%A6%E6%81%BC.md)，这道题是用数组实现单向链表的应用题，有些麻烦。如果感觉有难度可以略过，因为我们很少用数组实现链表，而是用STL容器直接实现。  
		* 《算法竞赛入门经典》P143-144 例6.4《破损的键盘》  
	* 双向链表
		* 《算法竞赛入门经典》P144-147 例6.5《移动盒子》
* **容器**：  
	* STL容器```list```（**双向链表**）:  
		* ```list```容器使用双向迭代器（而不像```vector```容器使用随机访问迭代器），所以只能用```++i;```、```--i```、```i != l.end();```（i是迭代器，l是某个list），不能使用```i+=c;```（c是整数常量）、```i<l.end();```、```i2-i1```等命令  
		* ```list```库函数包含了我们上面介绍的```vector```库函数，用法几乎相同。另外```list```还包含一些```vector```没有的库函数：```void push_front;```，```void pop_front();```，```void sort();```，```void remove();```，```void unique();```，```void merge();```，```void splice();```  
	* 我们常用的库函数如下：  

		|函数名|功能|  
		|---|---|  
		|a|啊|  

	* 《新标准》例19.1 约瑟夫问题的list容器解法  
		
[↑回到页首目录](#全文较长目录如下)  

## 双端队列deque
* 《入》P139例6-1

## 队列queue
* r《基》P138-141，P233例9.3
* 《入》P117-119，例5-6  

## 优先队列priority_queue
* 《入》P119-120，例5-7 

[↑回到页首目录](#全文较长目录如下)  

## 栈stack
* 《入》P115-117  

[↑回到页首目录](#全文较长目录如下)  

###### 参考文献  
> |文献|章节|  
> |---|---|
> |江涛, 宋新波, 朱全民. (2016). CCF中学生计算机程序设计基础篇. 科学出版社.|第6、9章.|  
> |刘汝佳. (2014). 算法竞赛入门经典(第2版). 清华大学出版社.|第5.2、6.1、6.2节.|  
> |郭炜. (2012). 新标准C++程序设计教程. 清华大学出版社.|第19章.|  
> |邓俊辉. (2012). 数据结构（C++语言版）第2版 .清华大学出版社.|第1-6章.|  
> |严蔚敏, 吴伟民. (2012). 数据结构 C语言版. 清华大学出版社.|第1-6章.|  
> |Halim, S., & Halim, F. (2013). _Competitive Programming_ (3rd ed.). Raleigh, NC: Lulu.|第2章|  
> |Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). _Introduction to Algorithms_ (3rd ed.). Cambridge, MA: The MIT Press.|第1、第10章|  
> |Lippman, S. B., Lajoie, J., & Moo, B. E. (2013). _C++ Primer_ (5th ed.). Upper Saddle River, NJ: Addison-Wesley.|第9、11章|  
> |Josuttis, N. M. (2012). _The C++ Standard Library_ (2nd ed.). Upper Saddle River, NJ: Addison-Wesley.|第6-12章|  
> |Newell, A., Shaw, F. C. (1957). _Programming the Logic Theory Machine_. Proceedings of the Western Joint Computer Conference: 230–240.||  
