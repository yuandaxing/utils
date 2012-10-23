/*
 * =====================================================================================
 *
 *       Filename:  virtual.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012Äê04ÔÂ05ÈÕ 14ʱ40·Ö19Ãë
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <stdlib.h>

using namespace std;

class ClxBase
{
	public:
		    ClxBase() {};
		     ~ClxBase() {cout<<"what is the fuck"<<endl;};

			    virtual void DoSomething() { cout << "Do something in class ClxBase!" << endl; };
};

class ClxDerived : public ClxBase
{
	public:
		    ClxDerived() {};
		        ~ClxDerived() { cout << "Output from the destructor of class ClxDerived!" << endl; }; 

			    void DoSomething() { cout << "Do something in class ClxDerived!" << endl; };
};

int main()
{
	ClxBase *pTest = new ClxDerived;
	pTest->DoSomething();
	delete pTest;

	return 0;
}
