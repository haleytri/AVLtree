#include <algorithm>
#include <fstream>
#include <iostream>
#include "ArgumentManager.h"
#include "tree.h"

using namespace std;

int main(int argc, char *argv[]){
    ArgumentManager am(argc, argv);
    string input = am.get("input");
    string output = am.get("output");

    //string input = "input4.txt";
    //string output = "AAA.txt";

    ifstream ifs(input);
    ofstream ofs(output);

    string data, type;
    twee tree;

    while(getline(ifs, data)){
        data.erase(remove(data.begin(), data.end(), '\n'), data.end());
        data.erase(remove(data.begin(), data.end(), '\r'), data.end());
        data.erase(remove(data.begin(), data.end(), ' '), data.end());
        string helper = "";
        helper = data.substr(0, 6);
        if(helper == "Insert"){
            string num = data.substr(7);
            num.erase(num.length()-1, 1);
            cout << "inserting " << num << endl;
            int ins = stoi(num);
            //cout << tree.root->val << endl;
            tree.root = tree.insert(tree.root, ins);
            cout << endl << "now: " << endl;
            //tree.printLevel(tree.root, ofs); 
            cout << endl;

        }
        else if(helper == "Remove"){
            string num = data.substr(7);
            num.erase(num.length()-1, 1);
            cout << "removing " << num << endl;
            int rem = stoi(num);
            tree.root = tree.remove(tree.root, rem);
        }
    }

    //cout << endl << "Final: " << endl;
    tree.printLevel(tree.root, ofs);
}