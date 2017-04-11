#include "stdafx.h"
#include "head.h"
void Show_Index_Page()
{
	puts("\n--------------------------------------------------------------------------------");
	puts("|                                                                              |");
	puts("|         Copyright (C) 2016 Yanzhe Lee. All rights reserved.                  |");
	puts("|                                                                              |");
	puts("|                       Harbin Institute of Technology                         |");
	puts("|                                                                              |");
	puts("|         License GPLv3+: GNU GPL version 3 or later                           |");
	puts("|                                                                              |");
	puts("|         This is free software: you are free to change and redistribute it    |");
	puts("|                                                                              |");
	puts("|         Email: lee.yanzhe@yanzhe.org           Version 1.2.2                 |");
	puts("|                                                                              |");
	puts("--------------------------------------------------------------------------------");
	puts("--------------------------------------------------------------------------------");
	puts("|                       ---- Expression Calculator ----                        |");
	puts("--------------------------------------------------------------------------------");
}



void strcut(string& str, char ch)
{
	for (size_t i = 0; i < str.size(); )
	{
		size_t chPos = 0;
		chPos = str.find(' ', i);
		if (chPos != string::npos)
		{
			str.erase(chPos, 1);
			i = chPos + 1;
		}
		else break;
	}
}

inline void strrpl(string& str, char16_t src_ch, char des_ch)
{
	for (size_t i = 0; i < str.size(); ++i)
		if (str[i] == src_ch) str[i] = des_ch;
}