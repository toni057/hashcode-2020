/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: tblaslov
 *
 * Created on 11 February 2020, 15:45
 */

#include <cstdlib>
#include <iostream>
#include <fstream>

#include "Pizza.h"
#include "Pizza.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    cout << "Hello world" << endl;
    
    Pizza p1 = Pizza("a_example");
    Pizza p2 = Pizza("b_small");
    Pizza p3 = Pizza("c_medium");
    Pizza p4 = Pizza("d_quite_big");
    Pizza p5 = Pizza("e_also_big");

    return 0;
}