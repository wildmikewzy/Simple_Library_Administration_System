/*简易图书管理系统*/
#include<iostream>
#include<cstdio>
#include<fstream>
#include<cstring>
#include<iomanip>
using namespace std;
class Book{     /*定义书的类*/
    public:
            char Name[80];      //书的名字
            char Author[100];     //书的作者
            int Amount;         //该书在库数量,设定不超过9本书(包括9本)
}; Book booklist[20];       //Book类型的数组，假定不会超过20种图书
char ch;        /*操作符号*/
void GetData();     /*从库文件中读取数据并存储到书单类中(successful)*/
void MainMenu();            /*显示主菜单(successful)*/
void SearchBook();         /*查询模块(successful)*/
void BorrowBook();         /*借阅模块(successful)*/
void ReturnBook();          /*还书模块(successful)*/
void ListShow();            /*浏览模块(successful)*/
void ManageBook();          /*管理模块(successful)*/
void Quit();                /*退出模块(successful)*/

int main(){
    for(int i=0;i<20;i++){      //初始化booklist数组
        booklist[i].Name[0]='\0';
        booklist[i].Author[0]='\0';
        booklist[i].Amount=0;
    }
    for(;;){
        MainMenu();     //显示主菜单
        char ch;
        cin>>ch;
        if(ch=='s' || ch=='S'){        //触发查询模块
            cin.get(ch);    //吸收回车符
            SearchBook();
        }
        if(ch=='b' || ch=='B'){        //触发借阅模块
            cin.get(ch);    //吸收回车符
            BorrowBook();
        }
        
        if(ch=='r' || ch=='R'){        //触发还书模块
            cin.get(ch);    //吸收回车符
            ReturnBook();
        }
        if(ch=='l' || ch=='L'){        //触发浏览模块
            cin.get(ch);    //吸收回车符
            ListShow();
        }
        if(ch=='m' || ch=='M'){        //触发管理模块
            cin.get(ch);    //吸收回车符
            ManageBook();
        }
        if(ch=='q' || ch=='Q'){     //退出图书管理系统
            Quit();
            break;
        }
    }
    return 0;
}
void GetData(){
    ifstream ifile("E:\\C++\\Homework coding\\Simple Library adminstratoin System\\Library Imformation database.txt");  //数据库路径需根据文件实际路径进行修改
    char a[35],number[5];       //number用来暂存数量字符
    int i=0,j=0,k=0;        //i 遍历书本，j 遍历书名字符串，k遍历作者字符串
    while(ifile.get(a[i])){     //读取提示符，不计入数组，用a来临时存储
        if(a[i]=='\n')
            break;
    }
    i=0;
    /*读取信息模块*/
    bool state_Name=false,state_Author=false,state_Amout=false;
    char ch;
    while(ifile.get(ch)){      //用i遍历书本，用j遍历书名数组
        if(ch==':'){
            state_Name=true;        //当检测到':' 的时候，说明可以开始录入书名
            ifile.get(ch);          //':'下一位开始才是书名
        }
        /*录入书名*/
        if(ch==','){
            state_Name=false;       //当检测到',' 的时候，说明书名录入完毕
            booklist[i].Name[j]='\0';   //字符串结束符
            j=0;        //重置j，准备录入作者
            state_Author=true;     //开始录入作者
            ifile.get(ch);      //','下一位开始才是作者名
        }
        if(state_Name){
            booklist[i].Name[j]=ch;         //当state_start状态为true的时候，才录入书本信息
            j++;
        }
        /*录入作者*/
        if(ch==';'){
            state_Author=false;        //当检测到';' 的时候，说明作者录入完毕
            booklist[i].Author[j]='\0';     //字符串结束符
            j=0;        //重置j，准备录入数量
            state_Amout=true;       //开始录入数量
            ifile.get(ch);      //';'下一位开始才是数量
        }
        if(state_Author){
            booklist[i].Author[j]=ch;       //当state_start状态为true的时候，才录入书本信息
            j++;
        }
        /*录入数量*/
        if(state_Amout){
            if(ch=='\n'){       //当检测到换行符，说明数量录入完毕
                state_Amout=false;
                i++;        //准备录入下一本书
                j=0;        //重置j，准备录入下一本书的书名
            }
            else{
                number[j]=ch;      //当state_start状态为true的时候，才录入书本信息
                j++;
                number[j]='\0';    //字符串结束符
                booklist[i].Amount=atoi(number);    //将字符串转换为整数存入Amount
            }
        }
    }
    ifile.close();
}
void MainMenu(){        /*显示主菜单界面*/
    cout<<"************************************"<<endl;
    cout<<"* 欢 迎 进 入 图 书 管 理 系 统 *"<<endl;
    cout<<"************************************"<<endl;
    cout<<"\n";cout<<"\n";
    cout<<"s 查询"<<endl;
    cout<<"\n";
    cout<<"b 借书"<<endl;
    cout<<"\n";
    cout<<"r 还书"<<endl;
    cout<<"\n";
    cout<<"l 浏览"<<endl;
    cout<<"\n";
    cout<<"m 管理"<<endl;
    cout<<"\n";
    cout<<"q 退出"<<endl;
    cout<<"\n";cout<<"\n";
    cout<<"请输入符号(大小写均可): ";
}
void SearchBook(){      /*查询模块*/
    
    //将书库信息读入数组
    GetData();
    for(;;){        //可以连续查询多次
        //输入待查询书名bookName;
        cout<<"请输入查询书名:"<<endl;
        char searchName[80];
        cin.getline(searchName,80,'\n');        //输入查询书名bookName
        //如果找到输出该书所有信息，否则cout<<endl<<"库中无此书!";
        bool found=false;
        for(int i=0;i<20;i++){
            if(strcmp(searchName,booklist[i].Name)==0){      //找到书名,注意，输入书名的时候需要输入完整书名，包括《》
                found=true;
                cout<<"书名:"<<booklist[i].Name<<endl;
                cout<<"作者:"<<booklist[i].Author<<endl;
                cout<<"在馆数量:"<<booklist[i].Amount<<endl;
                break;
            }
        }
        if(!found){
            cout<<endl<<"库中无此书!"<<endl;
        }
        cout<<"继续查询吗?按n键退出, 回车键继续查询...... ";
		cin.get(ch);
		if(ch=='n'||ch=='N')
            break;
    }
    MainMenu();     //显示主菜单
}
void BorrowBook(){      /*借阅模块*/
    //读取书库信息
    GetData();
	if(booklist[0].Name[0]=='\0')     //库中无书
        cout<<"库中无图书，暂不能借阅！";
	else{    //库中有书
		for(;;){         //可连续重复借阅
			//输入待借书名bookName;
            cout<<"请输入借阅书名:"<<endl;
            char borrowName[80];
            cin.getline(borrowName,80,'\n');        //输入查询书名bookName
			//在数组中查找匹配项
            bool found=false;
            for(int i=0;i<20;i++){
                if(strcmp(borrowName,booklist[i].Name)==0){      //找到书名,注意，输入书名的时候需要输入完整书名
                    //如果在库数量>0，cout<<"借阅成功!"，在库数量--，否则cout<<"抱歉,该书全部借出.";
                    if(booklist[i].Amount>0){
                        cout<<"借阅成功!"<<endl;
                        booklist[i].Amount--;      //在库数量--
                    }
                    else{
                        cout<<"抱歉,该书全部借出."<<endl;
                    }
                    found=true;
                    break;
                }
            }
            if(!found){
                cout<<endl<<"库中无此书!"<<endl;
            }
			cout<<"继续借阅吗?按n键退出, 回车键继续借阅......";
			cin.get(ch);
			if(ch=='n'||ch=='N')
                break;
		}
       //更新书库信息
        ofstream ofile("E:\\C++\\Homework coding\\Simple Library adminstratoin System\\Library Imformation database.txt");  //数据库路径需根据文件实际路径进行修改
        ofile<<"序号,书名,作者,在馆数量"<<endl;    //写入提示符
        for(int i=0;i<20;i++){
            if(booklist[i].Name[0]=='\0')    //跳出循环条件
                break;
            ofile<<i+1<<":"<<booklist[i].Name<<",";
            ofile<<booklist[i].Author<<";";
            ofile<<booklist[i].Amount<<endl;
        }
        ofile.close();
	}
}
void ReturnBook(){          /*还书模块*/
    //读取书库信息
    GetData();
    for(;;){         //可重复还书
		//输入待还书名bookName;
        cout<<"请输入还书书名:"<<endl;
        char returnName[80];
        cin.getline(returnName,80,'\n');        //输入还书书名returnName
        bool found=false;
		//查找匹配项
        for(int i=0;i<20;i++){
            if(strcmp(returnName,booklist[i].Name)==0){      //找到书名,注意，输入书名的时候需要输入完整书名
                //cout<<"还书成功!"，该书在库数量++
                cout<<"还书成功!"<<endl;
                booklist[i].Amount++;      //在库数量++
                found=true;
                break;
            }
        }
        if(!found){
            cout<<endl<<"库中无此书!"<<endl;
        }
		cout<<"继续还书吗?按n键退出, 回车键继续还书 ......";
	    cin.get(ch);
		if(ch=='n'||ch=='N')
            break;
	}
    //更新书库信息
    ofstream ofile("E:\\C++\\Homework coding\\Simple Library adminstratoin System\\Library Imformation database.txt");  //数据库路径需根据文件实际路径进行修改
    ofile<<"序号,书名,作者,在馆数量"<<endl;    //写入提示符
    for(int i=0;i<20;i++){
        if(booklist[i].Name[0]=='\0')    //跳出循环条件
            break;
        ofile<<i+1<<":"<<booklist[i].Name<<",";
        ofile<<booklist[i].Author<<";";
        ofile<<booklist[i].Amount<<endl;
    }
    ofile.close();
}
void ListShow(){            /*浏览模块*/
    //读取书库信息
    GetData();
    if(booklist[0].Name[0]=='\0'){     //库中无书
        cout<<"库中无图书!"<<endl;
        return;
    }
    cout<<"书库现有图书如下:"<<endl;
    cout<<left<<setw(30)<<"书名:"<<setw(50)<<"作者:"<<setw(20)<<"在馆数量:"<<endl;
    for(int i=0;i<20;i++){
        if(booklist[i].Name[0]=='\0')    //跳出循环条件
            break;
        cout<<left<<setw(30)<<booklist[i].Name<<setw(50)<<booklist[i].Author<<setw(20)<<booklist[i].Amount<<endl;
    }
    cout<<endl;
    cout<<"按回车键返回......";
    cin.get(ch);    //吸收回车符
}
void ManageBook(){     /*管理模块*/
    bool passward_correct=false;
    //输入管理口令password;
	for(int i=0;i<3;i++){      //有三次输入机会
		//输入口令
        cout<<"请输入管理口令:"<<endl;
        char password[80];
        cin.getline(password,80,'\n');        //输入管理口令password
		//检查口令是否正确
        if(strcmp(password,"admin123")==0){      //口令正确
            passward_correct=true;
            break;
        }
        else{       //口令错误
            cout<<"口令错误，请重新输入！剩余输入次数:"<<(2-i)<<endl;
        }
	}
	if(!passward_correct){    //无权限
		cout<<"抱歉，无此权限，按回车返回主菜单......";
		char ch;
		cin.get(ch);
		return;
	}
	else{    //进入管理
        cout<<"口令正确，欢迎进入图书管理模块！"<<endl;
       //读出书库信息
        GetData();
		for(;;){     //可连续添加多种图书
			//输入添加图书的书名Name、作者Author、在库数量amount;
            cout<<"请输入添加图书的书名:"<<endl;
            char addName[80];
            cin.getline(addName,80,'\n');        //输入添加书名addName	
			//查找匹配项
            bool found=false;
            for(int i=0;i<20;i++){
                if(strcmp(addName,booklist[i].Name)==0){      //找到书名,注意，输入书名的时候需要输入完整书名
                    //该书在库数量+=amount;
                    int addAmount;
                    cout<<"库中已有此书，请输入添加该图书的在库数量:"<<endl;
                    cin>>addAmount;        //输入添加数量addAmount
                    booklist[i].Amount+=addAmount;
                    found=true;
                    break;
                }
            }
            if(!found){     //未找到该书，添加新书
                cout<<"请输入添加图书的作者:"<<endl;
                char addAuthor[100];
                cin.getline(addAuthor,100,'\n');        //输入添加作者addAuthor
                cout<<"请输入添加图书的在库数量:"<<endl;
                int addAmount;
                cin>>addAmount;        //输入添加数量addAmount
                for(int i=0;i<20;i++){
                    if(booklist[i].Name[0]=='\0'){    //找到空位，添加新书
                        strcpy(booklist[i].Name,addName);
                        strcpy(booklist[i].Author,addAuthor);
                        booklist[i].Amount=addAmount;
                        break;
                    }
                }
            }
			cout<<"继续添加吗?按n键退出,回车键继续添加......";
			cin.get(ch);
            cin.get(ch);
			if(ch=='n'||ch=='N')
                break;
		}
        //更新图书库信息
        ofstream ofile("E:\\C++\\Homework coding\\Simple Library adminstratoin System\\Library Imformation database.txt");  //数据库路径需根据文件实际路径进行修改
        ofile<<"序号,书名,作者,在馆数量"<<endl;    //写入提示符
        for(int i=0;i<20;i++){
            if(booklist[i].Name[0]=='\0')    //跳出循环条件
                break;
            ofile<<i+1<<":"<<booklist[i].Name<<",";
            ofile<<booklist[i].Author<<";";
            ofile<<booklist[i].Amount<<endl;
        }   
	}
}
void Quit(){                /*退出模块*/
    cout<<"感谢使用图书管理系统，祝您生活愉快！"<<endl;
    //更新图书库信息
    ofstream ofile("E:\\C++\\Homework coding\\Simple Library adminstratoin System\\Library Imformation database.txt");  //数据库路径需根据文件实际路径进行修改
    ofile<<"序号,书名,作者,在馆数量"<<endl;    //写入提示符
    for(int i=0;i<20;i++){
        if(booklist[i].Name[0]=='\0')    //跳出循环条件
            break;
        ofile<<i+1<<":"<<booklist[i].Name<<",";
        ofile<<booklist[i].Author<<";";
        ofile<<booklist[i].Amount<<endl;
    }   
}