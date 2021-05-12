/****************************************************************************
this hpp implements some routine algorithms
*****************************************************************************
* @author     This file is part of PGC, developed by Yu Chen
* @paper      https://eprint.iacr.org/2019/319
* @copyright  MIT license (see LICENSE file)
*****************************************************************************/
#ifndef __PRINT__
#define __PRINT__

#include <iostream>
using namespace std;

const int LINE_LEN = 120;     // the length of split line

/* print split line */
void print_line(char ch)
{
    for (auto i = 0; i < LINE_LEN; i++) cout << ch;  
    cout << endl;
}

#endif