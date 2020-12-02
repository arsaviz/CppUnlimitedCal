#include <iostream>
#include <string.h>
#include <bits/stdc++.h> 

using namespace std;

// Global Variables for Parametric Programming
int deqat=0;
int lim =60000;
// remove zeroes before number
void remo(string &a){
	int i=0;
	for (;i<a.length()-1;i++){
		if (a[i]!='0'){
			break;
		}
	}	
	a.erase(0,i);
}
//compare without swaping return 1 if num1>num2 return 2 if num1=num2
int compa(string num1,string num2){
	remo(num1);
	remo(num2);
	int n1=num1.length(),n2=num2.length();
	if(n1>n2){
	return 1;
	}else if(n2>n1){
	return 0;
	}else if (n1==n2){
		for (int i=0;i<n1;i++){
			if (num1[i]!=num2[i]){
				if(num1[i]>num2[i]){
					return 1;
				}
				if (num1[i]<num2[i]){
					return 0;
				}
			}
		}

	}
	
	return 2;
}
//function to put larger number first and return 0 if swaped
int comp(string &num1,string &num2){
	remo(num1);
	remo(num2);
	int flag=compa(num1,num2);
	if (flag==0){
		swap(num1,num2);
	}
	return flag;
}
//regulate two numbers
void reg(string &num1,string &num2){
	int n1=num1.length(),n2=num2.length();
	if (n1>n2){
		for (int i=1;i<=n1-n2;i++){
			num2.insert(0,"0");
		}
	}else if(n2>n1){
		for (int i=1;i<=n2-n1;i++){
			num1.insert(0,"0");
		}
	}
}
//addition function
string add(string num1,string num2){
	string result;
	comp(num1,num2);
	reg(num1,num2);
	int carry=0;
	for (int l=num1.length()-1;l>=0;l--)
	{
		int temp=(num1[l]-'0')+(num2[l]-'0')+carry;
		carry=temp/10;
		temp=temp%10;
		result.push_back(temp+'0');	
		if (result.length()>lim) return "Out of Range!";
	}
	if(carry>0){
		result.push_back(carry+'0');
	}
	
	reverse(result.begin(),result.end());
	remo(result);
	return result;	
}
//subtraction function
string sub(string num1,string num2){
	string result;
	int flag=comp(num1,num2),temp;
	remo(num1);
	remo(num2);
	reg(num1,num2);
	for (int l = num1.length()-1;l>=0;l--){
		if (num1[l]<num2[l]){
			num1[l]+=10;
			int i=l-1;
			while (num1[i]=='0'){
				num1[i]='9';
				i--;
			}
			num1[i]-=1;
		}
		temp = (num1[l]-'0')-(num2[l]-'0');
		result.push_back(temp+'0');	
		
	}
	
	if (flag ==0){
		result.push_back('-');
	}
	reverse(result.begin(),result.end());
	remo(result);
	return result;
}
//multiplication function
string multi(string num1,string num2){
	remo(num1);
	remo(num2);
	string result;
	comp(num1,num2);
	int n1=num1.length(),n2=num2.length();
	int carry=0;
	for (int i=n2-1;i>=0;i--){
		string temp;
		temp.append(n2-i-1,'0');
		carry=0;
		for (int j=n1-1;j>=0;j--){
			int x=(num2[i]-'0')*(num1[j]-'0')+carry;
			carry=x/10;
			temp.push_back((x%10)+'0');
		}	
		temp.push_back(carry+'0');
		reverse(temp.begin(),temp.end());
		result=add(result,temp);
		if (result.length()>lim) return "Out of Range!";
	}
	
	return result;
}
//remainder function
string remainder(string num1,string num2){
	remo(num1);
	remo(num2);
	string result,temp;
	if (num2=="0"){
		return "Error";
	}
	int n1=num1.length(),n2=num2.length();
	for (int x=0;x<n1;x++){
		temp.push_back(num1[x]);
		remo(temp);
		
		int i = 0;
		while (compa(temp,num2)){
			temp = sub(temp,num2);
			i++;
		}
		result.push_back(i+'0');
	}
	remo(temp);
	return temp;
}
//division function original
string divi(string num1,string num2){
	remo(num1);
	remo(num2);
	if(deqat!=0){
		for(int i=0;i<=deqat;i++)
			num1.append("0");
	}
	string result,temp;
	if (num2=="0"){
		return "Error";
	}
	int n1=num1.length(),n2=num2.length();
	for (int x=0;x<n1;x++){
		temp.push_back(num1[x]);
		remo(temp);
		
		int i = 0;
		while (compa(temp,num2)){
			temp = sub(temp,num2);
			i++;
		}
		result.push_back(i+'0');
	}
	remo(result);
	if(deqat!=0){
		result.insert(result.length()-1-deqat,".");
	}
	return result;
}
// power function
string power(string num1,string num2){
	remo(num1);
	remo(num2);
	string temp="1";
	string result="1";
	while(compa(num2,temp)){
		result=multi(result,num1);
		temp=add(temp,"1");
		if (result=="Out of Range!") return "Out of Range!";
		if (result.length()>lim) return "Out of Range!";
	}
	return result;
}
// square root function
string sq(string num){
	string result="0",temp;
	remo(num);
	if(deqat!=0){
		for(int i=0;i<=deqat;i++)
			num.append("00");
	}
	int n=num.length();
	if(n%2!=0){
		temp.push_back(num[0]);
		num.erase(0,1);	
	}else{
		temp.push_back(num[0]);
		temp.push_back(num[1]);
		num.erase(0,2);
	}
    for(int i=1;i<=(n+1)/2;i++){
		while(compa(temp,power(result,"2"))){
			result=add(result,"1");		
		}
		result=sub(result,"1");
		result.append("0");
		temp.push_back(num[0]);
		temp.push_back(num[1]);
		num.erase(0,2);
	}
	result.erase(result.length()-1,1);
	remo(result);
	if(deqat!=0){
		result.insert(result.length()-1-deqat,".");
	}
	return result;
}
//factorial function
string fact(string num){
	string result="1",temp="1";
	while(compa(num,temp)){
		if (result=="Out of Range!") return "Out of Range!";
		if (result.length()>lim) return "Out of Range!";
		result=multi(result,temp);
		temp=add(temp,"1");
	}
	return result;
}
//fuction to check if string is a number
int check(string a){
	
	int x=a.find_first_not_of("1234567890");	
	if (x<=a.length()-1){
		return 0;
	}
	return 1;
	if(a.length()>lim) return -1;
}
//function to get operations in one line
void oneline(string a,string &num1,string &num2,string &op){
	int x=a.find_first_not_of("1234567890");
	num1.append(a.substr(0,x));
	a.erase(0,x);
	op.push_back(a[0]);
	a.erase(0,1);
	num2=a;
}
//fuction to check ops
int checkop(string op){
	int x=op.find_first_not_of("+-/*^%b");	
	if (x==0){
		return 0;
	}
	return 1;
}
//Base
string base(string num,string b){
	string result;
	if (compa(b,"17")||compa("1",b)){
		return "base should be 1 - 16 ";
	}
	int temp=deqat;
	deqat=0;
	while(compa(num,"1")){
		string x=remainder(num,b);
		if(compa(x,"10")){
			x=sub(x,"10");
			x[0]+='A'-'0';
			result.insert(0,x);
		}else{
			result.insert(0,x);
		}
		num=divi(num,b);
	}
	deqat=temp;
	return result;
}
//main function
int main(){
	string a,num1,num2,op;
	cout<<"Supported Format:	number[op]number op=\"+ - * / ^ % b\"  operator b is for base change(base 2 - 16)"<<endl<<"[op] number op=\"sqrt fact bin\" "<<endl;
	cout<<"Range limit is: "<<lim<<"\t"<<"Decimal Range is: "<<deqat<<endl<<endl;
	while(a!="exit"){
		a="",num1="",num2="",op="";
		getline(cin,a);
		oneline(a,num1,num2,op);
		if (a.substr(0,5)=="sqrt "){
			op="sqrt";
			a.erase(0,5);
			if(check(a))
				cout<<sq(a);
			else
				cout<<"Wrong format!";
		}else if(a.substr(0,5)=="fact "){
			op="fact";
			a.erase(0,5);
			if(check(a))
				cout<<fact(a);
			else
				cout<<"Wrong format!";
		}else if(a.substr(0,4)=="bin "){
			op="bin";
			a.erase(0,4);
			if (check(a))
				cout<<base(a,"2");
			else
				cout<<"Wrong format!";
		}else if((checkop(op)&&check(num1)&&check(num2))||op=="sqrt"||op=="fact"||op=="bin"){
				if(op=="+")
					cout<<add(num1,num2);
				if(op=="-")
					cout<<sub(num1,num2);
				if(op=="*")
					cout<<multi(num1,num2);
				if(op=="/")
					cout<<divi(num1,num2);
				if(op=="%")
					cout<<remainder(num1,num2);
				if(op=="^")
					cout<<power(num1,num2);
				if(op=="b")
					cout<<base(num1,num2);
		}else{
			if(a!="exit")
				cout<<"Wrong format!";
		}
		cout<<endl;
	}
	return 0;
}

