#include<iostream>
#include<stdio.h>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;
#define outfile1 "group1.txt"
#define outfile2 "group2.txt"
#define infile "goods.txt"

struct goods{
    string key , item;
    int quant;
    float price;
};

void sort(goods g[] , int n){
    ofstream ods2;
    ods2.open(outfile2);
    for(int i = 0; i < n - 1; i++){
        for(int j = 0 ; j < n - i - 1 ; j++){
            if(g[j].price < g[j+1].price){
                goods temp = g[j];
                g[j] = g[j+1];
                g[j+1]=temp;
            }
        }
    }
    for (int i = 0 ; i < n ; i++){
        ods2 << g[i].key << setw(15) << g[i].item <<  setw(15) << g[i].quant <<  setw(15) << g[i].price << endl;
    }
    ods2.close();
}

void reorder(goods g[] , int n){
    int i;
    ofstream ods1;
    ods1.open(outfile1);
    if(ods1.fail()){
        cerr<< "Can't open " << infile <<endl;  
    }
    for (i = 0 ; i < n ; i++){
        if(g[i].quant < 100){
            ods1 << g[i].key << setw(15) << g[i].item <<  setw(15) << g[i].quant <<  setw(15) << g[i].price << endl;
        }
    }
    ods1.close();
}

int menu(goods g[] , int n){
    int choice;
    do {
        cout << "\n" << setw(15) << "Menu" << endl;
        cout << "1. Reorder" << endl;
        cout << "2. Sort by cost" << endl;
        cout << "3. Exit" << endl;
        cout << "Select 1 / 2 / 3: " << endl;
        for(int i = 0 ; i < n ; i++){
            cout << g[i].key << setw(15) << g[i].item <<  setw(15) << g[i].quant <<  setw(15) << g[i].price << endl;
        }
        cin >> choice;

        switch(choice) {
            case 1:
                reorder(g, n);
                break;
            case 2:
                sort(g, n);
                break;
            case 3:
                cout << "Exit" << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
                break;
        }
    } while(choice != 3);
    return choice;
}

int readfile(goods g[]){
    ifstream ids1;
    ids1.open(infile);
    if(ids1.fail()){
        cerr<< "Can't open " << infile <<endl;
    }
    int count = 0;
    while(ids1>>g[count].key>>g[count].item>>g[count].quant>>g[count].price){
        count++; // count = count + 1
    }
    ids1.close();
    return count;
}

int main(){
    goods g[100]; 
    int n = readfile(g);
    if (n <= 0) {
        cerr << "No data loaded. Exiting program." << endl;
        return 0;
    }
    menu(g , n);
}