/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pizza.h
 * Author: tblaslov
 *
 * Created on 13 February 2020, 16:19
 */

#ifndef PIZZA_H
#define PIZZA_H

#include <iostream>
#include <vector>
#include <math.h>
#include <utility>
#include <fstream>

using namespace std;


class Pizza {
public:
    long num_slices, num_pizzas;
    vector<long> slices;
    vector<long> slices_cs;
    vector<bool> mask;
    vector<bool> best_mask;
    
    long best_upper = 0;
    long best_real = 0;
    
    const bool start_mask_value = false;
     
    void load_data(string infile) {
        ifstream f;
        f.open("inputs/" + infile + ".in");
        
        f >> num_slices >> num_pizzas;

        slices = vector<long>(num_pizzas);
        slices_cs = vector<long>(num_pizzas+1);
        mask = vector<bool>(num_pizzas, start_mask_value);
        best_mask = vector<bool>(num_pizzas, start_mask_value);
        
        slices_cs[num_pizzas] = 0L;
        long x;
        for (int i = 0; i < num_pizzas; i++) {
            f >> x;
            slices[num_pizzas-i-1] = x;
            slices_cs[num_pizzas-i-1] = x + slices_cs[num_pizzas-i];
        }
        f.close();
    }
    
    void output_data(string outfile) {
        ofstream f;
        f.open("outputs/" + outfile + ".out", std::ios_base::out);
        
        long total_pizzas = 0;
        for (vector<bool>::iterator it = best_mask.begin(); it != best_mask.end(); ++it) total_pizzas += *it;
        f << total_pizzas << endl;
        
        for (int i=mask.size()-1; i >=0 ; i--) {
            if (best_mask[i]) f << num_pizzas-i-1 << " ";
        } 
        f.close();
    }
    
    void print_loaded_data() {
        cout << num_slices << " " << num_pizzas << endl;
        for (vector<long>::iterator it = slices.begin(); it != slices.end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }
    
    long sum_mask(vector<bool> &mask) {
        long tot = 0;
        for (int i=0; i < mask.size(); i++) tot += mask[i] * slices[i];
        return tot;
    }
    
    
    void print_mask(vector<bool> &mask) {
        for (vector<bool>::iterator it=mask.begin(); it != mask.end(); ++it) cout << *it << " ";
        cout << endl;
//        for (int i=0; i < mask.size(); i++) if (mask[i]) cout << "(" << i << "," << slices[i] << ") ";
//        cout << endl;
    }
    
    Pizza(string infile) {
        this->load_data(infile);
        print_loaded_data();

//        for (vector<long>::iterator it=slices_cs.begin(); it < slices_cs.end(); it++) cout << *it << " ";
//        cout << endl;
        
        this->split(0);
//        this->greedy();
        cout << endl << "FINAL" << endl;
        print_mask(best_mask);
//        cout << "(best upper, best real) = " << calc_best_upper(this->best_mask).first << " " << calc_best_upper(this->best_mask).second << endl;
        cout << "best_real: " << best_real << "   num_slices: " << num_slices << endl;

        this->output_data(infile);
    };
    
    void split(int n, long val) {     
        if ((val > num_slices) || (best_real >= num_slices) || (n > num_pizzas)) { return; }
        if ((val >= best_real) && (val <= num_slices)) {
//            cout << "updating...  " << val << endl;
//            cout << n << " " << val << ", best_real: " << best_real << endl;
            best_real = val;
            best_mask = mask;
        }
            
        long val1 = val + slices[n];
        long cost_1 = min(num_slices, val1 + slices_cs[n+1]);
        if (cost_1 >= best_real) { 
            mask[n] = !mask[n];
            split(n+1, val1);
            mask[n] = !mask[n];
        }
        
        long val0 = val;
        long cost_0 = min(num_slices, val0 + slices_cs[n+1]);
        if (cost_0 >= best_real) { 
            split(n+1, val0);
        }
        
        return;
    }
    
    
    void split(int i) {
        split(i, 0L);
    }
    
    void greedy() { 
        for (int i = 0; (i < num_pizzas) && (best_real < num_slices); i++) {
            if ((best_real + slices[i]) <= num_slices) {
                best_real += slices[i];
                mask[i] = !mask[i];
            } else {
                break;
            };
        }
        best_mask = mask;
        return;
    }
    
    
};

#endif /* PIZZA_H */

