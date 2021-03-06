/*	@author 杜博识Dubos

NOIP 04 指针与引用Pointers and References 
	以《CCF基础篇》第4章为主；
	以 C++ Primer第2.3节、《新标准C++程序设计教程》第7章为辅；
	以《信息学奥赛一本通》第8章、
		https://isocpp.org/wiki/faq/references
		http://www.cplusplus.com/doc/tutorial/pointers/
		http://www.cplusplus.com/doc/tutorial/dynamic/
		为参考；
	
	本章主要讲指针，顺带讲引用。
 */

#include <iostream>

using namespace std;

//这几个全局变量是例4中用到的，请从例0开始读 
const int MAX = 100001;
int x [MAX], y [MAX], d [MAX];	//x是行坐标数组，y是列坐标数组，d是数据值数组 
int col [MAX]; 					//col是记录每列数据个数的数组
int *a [MAX];					//建立一个指针数组，给每列一个指针，用于申请
								//“动态数组”

int main()
{
	printf("例0：复合数据类型，指针\n");
		/*【复合数据类型Compound data types】是建立在其他数据类型基础之上的数据类型。
			与其相对的概念是基本数据类型Primitive data types。我们学过的int、double、
			bool、char都是基本数据类型，而数组Array就是符合数据类型。现在我们要再
			学习两种重要的数据类型：指针Pointer和引用Reference。
			
		【指针】变量指向一个内存空间，指针变量储存的是内存地址。
			1. 指针的初始化：下面例子中建立指针变量p1，并使p1指向存储整数类型变量n
				的内存地址，注意指针是p1，而不是*p1。指针可以只定义，暂不赋值。 
			2. &是【引用运算符reference operator】或【取地址运算符address-of operator】，
				例如&n是存储整数变量n的内存地址
			3. *是【解除引用运算符dereference operator】,*&n就是对&n解除引用，
				跟n相等
			4. 指针变量可以被重新赋值 */
		
		int n=3, m=5;
		
		//指针的初始化，可以分成两行写：int *p1; p1 = &n; 
		int *p1 = &n;
		
		//指针p的值与&n相同，不同情况下这个值很可能发生变化，但无论如何它代表的是内存地址
		cout<<"n = "<<n<<endl;		//3
		cout<<"&n = "<<&n<<endl;	//0x6ffe2c 
		cout<<"p1 = "<<p1<<endl;	//0x6ffe2c，与&n相同 
		
		//*&n与n相等；若p1=&n，则*p1也与n相等
		cout<<"*p1 = "<<*p1<<endl;	//3		

		//指针变量p1被重新赋值，下面p1就指向整数变量m的内存地址，不再指向n的内存地址 
		p1 = &m;
		cout<<"m = "<<m<<endl;		//5
		cout<<"&m = "<<&m<<endl;	//0x6ffe28
		cout<<"p1 = "<<p1<<endl;	//0x6ffe28，p1值变为&m，说明P1重新指向m
		cout<<"*p1 = "<<*p1<<endl;	//5
	printf("\n");
	
	printf("例1：引用\n");
		/*【引用】变量指向一个变量，引用变量是其所指向变量的别名。
			1. 引用的初始化：与指针不同，引用必须在定义的同时赋值，不可以先定义暂不
				赋值。例如int &r = n;说明r是n的引用和别名，初始化不可以分成两行； 
			2. 引用变量的内存地址与其指向的变量所占的内存地址相同， 
			3. 与指针不同，引用不可以被重新赋值 */
		
		//引用的初始化，不可以分成两行写
		int &r = n; 
		cout<<"r = "<<r<<endl;		//3 
		cout<<"&r = "<<&r<<endl;	//0x6ffe2c，与&n是一样的
		
		//假设我们尝试给r重新赋值，例如赋值为m，这样做的结果并不是把r变成m的引用，
		//而是会给r所引用的n重新赋以m值，所以引用不能被重新赋值。 
		r = m;
		cout<<"r = "<<r<<endl;		//r被重新赋值，与m相等为5 
		cout<<"n = "<<r<<endl;		//n也被重新赋值，与m相等为5 
		cout<<"&r = "<<&r<<endl;	//0x6ffe2c，依然与&n是一样的，而与&m不同，
									//说明引用变量r无法被重新赋值 
	printf("\n");
	
	printf("例2：无类型指针，空指针\n");
		/*指针变量与普通变量的关系，常量指针 */
		
		/*【无类型指针】
			1. 无类型指针的作用和初始化：有时候我们建立一个指针，但可能之后要它
				指向不同类型的变量，那么我们可以把它定义为一个无类型指针，
				例如void *p2。显然无类型指针可以先定义，再赋值；
			2. 无类型指针的赋值：无类型指针指向变量之后，如果我们要用其所指向的
				变量，例如*p2，就必须使用强制类型转换*/
		void *p2;
		
		char c = 'c';
		p2 = &c;
		cout<<"p2 = "<<p2<<endl;
		cout<<"*p2 = "<<*(char*)p2<<endl;	//强制转换为字符指针 
		
		p2 = &n;
		cout<<"p2 = "<<p2<<endl;
		cout<<"*p2 = "<<*(int*)p2<<endl;	//强制转换为整数指针
		
		/*【空指针（零指针）】
			当我们把指针赋值为NULL或者0时，指针值将会变为特殊地址0，之后指针
			不指向任何实际的对象或者函数。 */
		p1 = NULL;
		p2 = 0;
		cout<<"p1 = "<<p1<<endl;	//0
		cout<<"p2 = "<<p2<<endl;	//0
	printf("\n");
	
	printf("例3：指针与数组，动态内存分配\n");
		/*在C++语言中，我们可以将数组名看作指针，也可以将指针看作数组名。但是两者
			还有本质的区别。
			
			1. 将数组名看作指针，指针的+-运算 
				例如我们建立整数数组arr包含10个元素：从arr[0] ~ arr[9]为0到18，
				这时候arr就是指向arr[0]的指针，arr+5就是指向arr[5]的指针，所以
				指针的+运算就是把指针指向原地址之后的地址。
				
				注意：*(arr+5)跟*arr+5不同，详见下例。 
				注意：数组名与指针不同之处在于，数组名只能当作常量指针，不能当作
					变量，而指针变量则是名副其实的变量。例如下面例子中p1 = arr，
					之后我们可以用++p1改变p1的值，却不能用++arr改变arr的值，因此
					我们也称数组是静态数据结构，而指针是动态数据结构。 */
		int arr [10] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18};
		int i;
		for (i=0; i<10; i++)					//输出数组arr各个元素的内存地址 
		{										//可见每个元素占4字节（32位）内存 
			cout<<&arr[i]<<" ";
		}
		cout<<endl;
		p1 = arr;
		cout<<"*arr = "<<*arr<<endl;			//0，即a[0]
		cout<<"arr = "<<arr<<endl;				//0x6ffdf0，a[0]的内存地址
		cout<<"*p1 = "<<*p1<<endl;				//0，即a[0]
		cout<<"p1 = "<<p1<<endl<<endl;			//0x6ffdf0，a[0]的内存地址
		
		cout<<"*(arr+5) = "<<*(arr+5)<<endl;	//10，即a[0+5]
		cout<<"arr+5 = "<<arr+5<<endl;			//0x6ffdf4, a[5]的内存地址 
		cout<<"*arr+5 = "<<*arr+5<<endl<<endl;	//5，即a[0]+5，注意不是a[5]
		
		//cout<<"*(++arr) = "<<*(++arr)<<endl;	//++arr不可用 
		cout<<"*(++p1) = "<<*(++p1)<<endl<<endl;//2，*(++p1)即是a[1]
		
		/*	2. 将指针看作数组名
				之前我们建立数组时，在编译时就必须指定数组的大小，否则就会编译
				出错。这样的机制很不实用。
				为了解决这个问题，C++提供了一种“动态内容分配机制”：
				
				用指针申请多个变量空间，由于系统给的地址是连续的，这些空间就可以
				当作数组使用，这就是所谓“动态数组”。“动态数组”的大小可以在
				程序运行的时候再确定，而无需在编译时就确定。 
				
				【注意】“动态数组”使用之后必须释放，否则系统不会将其分配给其他
				程序，这样可用内存就会变小，直至计算机重新启动。释放方法为：
				delete [] p1;
		*/
		p1 = new int [10];			//用指针p1一次申请10个连续的int类型内存空间1
		for (i=0; i<10; i++)		//可见每个int内存空间为占4字节（32位）
		{
			cout<<&p1[i]<<" ";
		}
		cout<<endl;
		
		for (i=0; i<10; i++)
		{
			p1[i] = 3*i;			//把p1当作数组名，为数组赋值
			cout<<p1[i]<<" ";		//0 3 6 9 12 15 18 21 24 27 
		}
		cout<<endl;
		
		i=0;
		while (i<10)				//这个while循环与上面把p1当数组名的for循环
		{							//效果一样
			*p1 = 4*i;				//把p1指针所指的元素赋值为4*i
			cout<<*p1<<" ";			//输出p1指针所值的元素值
			p1++;					//指针p1指向下一个元素
			i++;					//序号i也加1
		}
		cout<<endl;
		
		p1 -= 10;					//之前p1指向了p1+10的内存空间，现在退回去 
		delete [] p1;				//释放p1申请的“动态数组”空间 
	printf("\n");
	
	printf("例4：指针与数组的应用 - 巨大稀疏矩阵的行列转换\n");
		/*（《CCF基础篇》P92例4.8）
			
		巨大稀疏的矩阵的行列转换： 
		
		现有一个N行*M列矩阵，N和M取值范围是[1, 100000]，但仅有其中K个位置有
		数据（数据值为整数），K范围是[1, 100000]，其他绝大多数位置都是空的，
		所以这是个巨大而稀疏的矩阵。
		
		我们向矩阵输入数据时，先输入第1行从左到右，再输入第2行...直至第N行；
		而输出时则先输出第1列从上到下，再输出第2列...直至第M列。
		
		输入：一共K+1行，第一行三个整数分别是N、M、K，用空格分隔；第二行至
			第K+1行都是要输入的数据信息，每行三个整数：行坐标、列坐标、数据值，
			也用空格分隔。
		输出：1行，K个数据值，用空格分隔。
		
		输入样例：
			100000 100000 4
			1 3 1
			2 2 2
			3 1 3
			3 3 4
		输出样例：
			3 2 1 4
		
		解题思路：
			目前，一见到矩阵我们就会想到二维数组，但是之前做过的题目都会注明行列数
			不超过100，而这道题行列数达到了10^5，一个int元素的二维数组最多需要 
			4*10^10 bytes = 37GB内存，2018年6月你的电脑不能处理这样的程序，而
			这道题目的内存限制更是只有64MB，很显然不能建立整个矩阵，否则会溢出，
			其实只需按照K的实际值创建数组即可，这时候我们刚刚讲过的“动态数组”
			就派上用场了：
			
			由于题目要求按列输出，我们要想办法记录每列有多少个数据，然后为每列建
			立一个合适长度的“动态数组”，再一次输出各个“动态数组”即可。
			
			我们需要4个静态整数数组，分别用来存储每个数据的行坐标、列坐标、数据值、
			每列数据个数，以及1个静态整数指针数组，给每列一个指针用于申请“动态
			数组”。这几个数组都有100001位，分别会占400004、400004、400004、
			400004、800008 bytes（指针在32位系统占4字节，在64位则占8字节），
			加起来大概是2.2888MB（可以通过sizeof来看它们所占的内存空间）。
			我们要把它们建立成全局变量，而不是局部变量。
			
			因为局部变量所用的内存为栈区stack segment，空间限制为2M，所以建立为
			局部变量会导致栈溢出stack overflow
			（著名计算机问答网站stackoverflow.com就是以此命名），全局区空间限制
			要大得多，32位电脑可以达到4GB，64位则更大。
		*/

		cout<<
		double(sizeof(x)+sizeof(y)+sizeof(d)+sizeof(col)+sizeof(a))/(1024*1024)
		<<" MB"<<endl;
		
		//首先建立变量，数组建立在main外作为全局变量 
		int N, M, K;
					
		//输入：
		cin>>N>>M>>K;
		for(i=0; i<K; i++)
		{
			cin>>x[i]>>y[i]>>d[i];
			col[y[i]]++;			//记录各列有多少个数据 
		}
		
		//为每列建立一个合适长度的“动态数组”： 
		for (int j=1; j<=M; j++)	//注意题目说行列数从1开始，而非从0开始 
		{
			a[j] = new int [col[j]];//把指针看作数组名：用指针a[j]为第j列申请合适
		}							//的长度，其长度等于第j列的数据个数col[j]
		
		//把K个数据分别赋值给所在列对应的“动态数组”： 
		for (i=0; i<K; i++)
		{
			*a[y[i]] = d[i];		//第i个元素所在列y[i]对应的“动态数组”是指针
									//a[y[i]]所申请的，长度为col[y[i]]；
									 
									//数组第一个元素可以用指针表示为*a[y[i]]， 
									//或者把指针a[y[i]]当作数组名表示为a[y[i]][0]
									
			a[y[i]]++;				//赋值之后，指针指向“动态数组”中的下一元素， 
									//这时下一个元素就变成*a[y[i]]
		}
		
		//按列输出：
		for (int j=1; j<=M; j++)
		{
			a[j] -= col[j];			//之前a[j]指向a[j][col[j]]，要先把a[j]指回 
			for (i=0; i<col[j]; i++)//每个“动态数组”的首元素 
			{
				cout<<a[j][i]<<" ";
			}
		}
		cout<<endl;
		
		//释放“动态数组”： 
		for (int j=1; j<=M; j++)
		{
			delete a[j];
		}
	printf("\n");
	
	printf("例5：指针与cstring\n");
		/*我们已经知道，c语言中字符串是储存在以'0'为结束符的字符数组里，那么指针
		用于字符数组就如用在数组中一样，cstring库函数正是基于指针与字符数组写成的。
		至于具体库函数的功能请阅读NOIP 03 5 cstring*/
	printf("\n"); 
	
	
	printf("例6：指针数组\n");
		/*我们可以建立一个以指针为元素的数组，实际上在例4中建立的int *a [100001]
		就是一个以整数指针为元素的【指针数组】。
		
		值得注意的，也是我们在例4中做过的是：指针数组中每一个元素指针都可以申请
		一段内存空间作为“动态数组”，所以指针数组可以起到与二维数组类似的作用，
		而且更为灵活。*/
	printf("\n");
	
	printf("例7：指向指针的指针\n");
		/*int **p就是指向某个整数指针的指针，当然还有更多重指针，我们目前比较少用到
		二重乃至多重指针，就不详细介绍了。 */
	printf("\n"); 
		
	printf("例8：指针与函数\n");
		/*函数指针，函数指针数组，指针作为函数参数等内容放在函数里面讲*/ 
	printf("\n");
	
	printf("例9：指针与结构体\n");
		/*指向结构体变量的指针放在结构体一起讲*/ 
	printf("\n");

	return 0;
}

/*	作业：
		本章属于C++语言基础知识，没有单独作业题。 
*/
