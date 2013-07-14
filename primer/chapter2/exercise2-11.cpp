/*************************************************************************
    > File Name: exercise2-11.cpp
    > Author: wolf
    > Mail: tiandewei07@163.com 
    > Created Time: Sun 14 Jul 2013 04:36:18 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int main()
{
	int value;
	int pow;
	long result = 1;

	cout << "input value and pow:";
	cin >> value >> pow;
	for(int i = 0; i != pow; i++)
		result = result * value;

	cout << "result=" << result << endl;

	return 0;
}
