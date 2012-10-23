#include <iostream>
#include <string.h>

void removeSpace(char *str)
{
	char *p1 = str, *p2 = str;
	while(1){
		while(*p2 == ' ')
			p2++;
		*p1 = *p2;
		if(*p2 == '\0')
			break;
		p1++, p2++;
	}
}
void removeSpace2(char *str)
{
	char *p1 = str, *p2 = str;
	if(str == NULL || *str == '\0')
		return ;
	do{
		while(*p2 == ' ')
			p2++;
	}while((*p1++ = *p2++) != '\0');
}

void removeSpace3(char *str)
{
	char *p = str;

	if(str == NULL)
		return ;

	while(*p){
		if(*p != ' ')
			*str++ = *p;
		p++;
	}
	*str = *p;
}

void remove2Space(char *str)
{
	bool inSpace = false;
	char *cur = str;
	if(str == NULL)
		return ;

	while(*str){
		if(inSpace == false && *str == ' '){
			inSpace = true;
			*cur++ = *str;
		}else if(*str != ' '){
			inSpace = false;
			*cur++ = *str;
		}
		str++;
	}
	*cur = *str;

}
int f(char * a) {

	int i = 0, j = 0;
	// 
	if(a == NULL || a[0] == '\0')
		return 0;

	a[i++] = a[j++];

	while(a[j] != '\0') {
		if((a[j]==a[j-1]) && (a[j]==' ')) {
			j++;
		} else {
			a[i++]=a[j++];
		}
	}
	a[i]='\0';
	return i;	
}
int main()
{
	using namespace std;
	const char *str1 = "    aaaa     ccccccc ";
	char tmp[200];

	strcpy(tmp, str1);
	removeSpace3(tmp);
	cout<<tmp<<endl;
	cout<<str1<<endl;

	strcpy(tmp, str1);
	remove2Space(tmp);
	cout<<tmp<<endl;
	return 0;
}
