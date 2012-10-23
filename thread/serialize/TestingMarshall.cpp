/*
 * =====================================================================================
 *
 *       Filename:  TestingMarshall.cpp
 *
 *    Description:  testing all the data type
 *
 *        Version:  1.0
 *        Created:  2012年09月19日 11时18分04秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "Marshall.h"
#include <stdio.h>
#include <string>
#include "../../Common.h"
int main(int argc, char *argv[])
{
	bool t = true, f = false;
	uint8_t u1 = 0x0, u2 = 0x1, u3 = 0xff;
	int8_t i1 = 0x0, i2 = 0x1, i3 = -1;
	uint16_t u4 = 0x0, u5 = 0x1, u6= 0xff, u7 = 0xfff, u8 = 0xffff;
	int16_t i4 = 0x0, i5 = 0x1, i6 = 0xff, i7 = 0xfff, i8 = -1;
	uint32_t u9 = 0x0, u10 = 0x1, u11 = 0xff, u12 = 0xfff, u13 = 0xfffffff0;

	int32_t i9=0x0, i10=0x1, i11=0xff, i12=0xfff, i13=0xfffffff0;

	uint64_t u14=0xf0, u15=0xff0, u16= 0xffffffffffffffff,
			u17 = 0xf0f0f0f0f0f0f0f0,u18=0x0f0f0f0f0f0f0f0f; 
	int64_t i14=0xf0, i15=0xff0, i16= 0xffffffffffffffff,
			i17 = 0xf0f0f0f0f0f0f0f0,i18=0x0f0f0f0f0f0f0f0f; 
	const std::string s1="", s2="aaaaaaaaaa", s3="    \t\r  \n";
	const std::string  strs[] = {"abc", "bcd", "sss", "fff", "lef", "1111111"};
	const std::string  str2[] = {"ass", "dbbb", "aaa", "fff", "kkk", "222222"};
	const int SLEN = sizeof(strs) / sizeof(strs[0]);
	std::set<std::string> setStr(strs, strs + SLEN);

	std::map<std::string, std::string> mapStr;
	for( int i = 0 ; i < SLEN ; i++ )
	{
		mapStr[strs[i]] = str2[i];
	}

	std::tr1::unordered_map<std::string, std::string> umapStr;
	for( int i = 0 ; i < SLEN ; i++ )
	{
		umapStr[strs[i]] = str2[i];
	}
	


	uint16_t a[] = {1, 2, 100, 0xffff, 0xf000, 0xabcd};
	const int len = sizeof(a) / sizeof(a[0]);
	std::vector<uint16_t> vi(a, a+len);
	std::list<uint16_t> list(a, a+len);

	Marshall m;
	m << t << f;
	m << u1 << u2 << u3;
	assert(m.getBuffSize() == 9);

	m << i1 << i2 << i3;
	assert(m.getBuffSize() == 12);

	m << u4 << u5 << u6 << u7 << u8;
	assert(m.getBuffSize() == 22);

	m << i4 << i5 << i6 << i7 << i8;
	assert(m.getBuffSize() == 32);

	m << u9 << u10 << u11 << u12 << u13;
	assert(m.getBuffSize() == 52);

	m << i9 << i10 << i11 << i12 << i13;
	assert(m.getBuffSize() == 72);

	m << u14 << u15 << u16 << u17 << u18 ;
	assert(m.getBuffSize() == 112);
	m << i14 << i15 << i16 << i17 << i18 ;
	assert(m.getBuffSize() == 152);

	m << s1 << s2 << s3;

	m << vi << list;
	std::cout << vi << std::endl << list << std::endl;

	m << setStr ;
	m << mapStr;
	m << umapStr;

	m.complete();
	UnMarshall um(m.getBuff(), m.getBuffSize());
	bool b;
	um >> b;
	assert(b == true);
	um >> b;
	assert(b == false);
	uint8_t r1, r2, r3;
	um >> r1 >> r2 >> r3;
	assert(r1 == u1 && r2 == u2 && r3 == u3);


	int8_t ri1, ri2, ri3;
	um >> ri1 >> ri2 >> ri3;
	assert(ri1 == i1 && ri2 == i2 && ri3 == i3);

	uint16_t r4, r5, r6, r7, r8;
	um >> r4 >> r5 >> r6 >> r7 >> r8;

	std::cout << "r4:" << r4 << " r5:" << r5 << std::endl;
	printf("%x %x %x\n", r6, r7, r8);
	assert(r4 == u4 && r5 == u5 && r6 == u6
			&& r7 == u7 && r8 == u8);
	int16_t ri4, ri5, ri6, ri7, ri8;
	um >> ri4 >> ri5 >> ri6 >> ri7 >> ri8;

	assert(ri4 == i4 && ri5 == i5 && ri6 == i6
			&& ri7 == i7 && ri8 == i8);

	uint32_t r9, r10, r11, r12, r13;
	um >> r9 >> r10 >> r11 >> r12 >> r13;
	assert(r9 == u9 && r10 == u10 && r11 == u11
			&& r12 == u12 && r13 == u13);

	int32_t ri9, ri10, ri11, ri12, ri13;
	um >> ri9 >> ri10 >> ri11 >> ri12 >> ri13;
	assert(ri9 == i9 && ri10 == i10 && ri11 == i11
			&& ri12 == i12 && ri13 == i13);

	uint64_t r14, r15, r16,r17,r18; 
	int64_t ri14, ri15, ri16,ri17,ri18;

	um >> r14 >> r15 >> r16 >> r17 >> r18;
	um >> ri14 >> ri15 >> ri16 >> ri17 >> ri18;

	assert(r14 == u14 && r15 == u15 && r16 == u16
			&& r17==u17 && r18==u18);
	assert(ri14 == i14 && ri15 == i15 && ri16 == i16
			&& ri17==i17 && ri18==i18);

	std::string st1, st2, st3;
	um >> st1 >> st2 >> st3;
	assert(st1 == s1 && st2 == s2 && st3 == s3);

	std::vector<uint16_t> vi1;
	std::list<uint16_t> list1;
	um >> vi1 >> list1;
	std::cout << vi1 << std::endl << list1 << std::endl;

	std::set<std::string> setStr1;
	um >> setStr1;
	std::cout << setStr1 << std::endl;

	std::map<std::string, std::string> mapStr1;
	um >> mapStr1;
	std::cout << mapStr1 << std::endl;

	std::tr1::unordered_map<std::string, std::string> umap;
	um >> umap ;
	std::cout << umap << std::endl;

	std::cout << "succeed" << std::endl;
	return 0;
}
