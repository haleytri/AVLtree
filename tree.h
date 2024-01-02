#ifndef TREE_H
#define TREE_H
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;
struct node{
    int val;
    node * left;
    node * right;
    node(){
        val = -999;
        left = right = nullptr;
    }
    node(int v){
        val = v;
        left = right = nullptr;
    }
};

class twee{
    public:
        node * root;
        twee(){
            root = nullptr;
        }  
        
        int height(node * root){
            if(root == nullptr){
                return -1;
            }
            int lh = height(root->left);
            int rh = height(root->right);
            return 1 + max(lh,rh);
        }
        int bf(node * root){
            if(root == nullptr){
                return 0;
            }
            return height(root->left) - height(root->right);
        }
        node * sLR(node * root){
            node * newRoot = root->right;
            node * newRight = newRoot->left;
            newRoot->left = root;
            root->right = newRight;
            return newRoot;
        }
        node * sRR(node * root){
            node * newRoot = root->left;
            node * newLeft = newRoot->right;
            newRoot->right = root;
            root->left = newLeft;
            return newRoot;
        }
        node * insert(node * root, int value){
            if(root == nullptr){
                cout << "Hi";
                node * newNode = new node(value);
                return newNode;
            }
            else if(value < root->val){
                cout << "Hi1";
                root->left = insert(root->left, value);
            }
            else if(value > root->val){
                cout << "Hi2";
                root->right = insert(root->right, value);
            }
            else{
                cout << "Hi3";
                return root;
            }
            int balf = bf(root);
            if(balf>1 && value < root->left->val){
                return sRR(root);
            }
            else if(balf<-1 && value > root->right->val){
                return sLR(root);
            }
            else if(balf > 1 && value > root->left->val){
                root->left = sLR(root->left);
                return sRR(root);
            }
            else if(balf < -1 && value < root->right->val){
                root->right = sRR(root->right);
                return sLR(root);
            }

            
            return root;
        }
        node * predecessor(node * cur){
            if(cur==nullptr)
                return nullptr;
            cur = cur->left;
            while(cur->right != nullptr)
                cur = cur->right;
            return cur;
        }
        node *successor(node *cur)
        {
            if (cur == nullptr)
                return nullptr;
            cur = cur->right;
            while (cur->left != nullptr)
                cur = cur->left;
            return cur;
        }

        node * remove(node * cur, int v){
            if(cur == nullptr)
                return cur;
            else if (cur->val < v)
                cur->right = remove(cur->right, v);
            else if (cur->val > v)
                cur->left = remove(cur->left, v);
            else{
                if(cur->left == nullptr && cur->right == nullptr){
                    delete cur;
                    cur = nullptr;
                }
                else if(cur->left == nullptr){
                    node * temp = cur;
                    cur = cur->right;
                    delete temp;
                }
                else if (cur->right == nullptr){
                    node * temp = cur;
                    cur = cur->left;
                    delete temp;
                }
                else{
                    node * temp = successor(cur);
                    cur->val = temp->val;
                    cur->right = remove(cur->right, temp->val);
                }

                int balf = bf(cur);
                if(balf>1 && bf(root->left) >= 0){
                    return sRR(root);
                }
                else if(balf<-1 && bf(root->right) <= 0){
                    return sLR(root);
                }
                else if(balf > 1 && bf(root->left) < 0){
                    root->left = sLR(root->left);
                    return sRR(root);
                }
                else if(balf < -1 && bf(root->right) > 0){
                    root->right = sRR(root->right);
                    return sLR(root);
                }
            }
            

            root = cur;
            return cur;
        }

        void printLevel(node * root, ofstream &ofs){
            if(root == nullptr){
                return;
            }
            queue<node*> q;
            q.push(root);
            while(!q.empty()){
                int levelSize = q.size();
                for(int i = 0; i < levelSize; i++){
                    node * cur = q.front();
                    q.pop();
                    ofs  << cur-> val << " ";
                    if(cur->left != nullptr)
                        q.push(cur->left);
                    if(cur->right != nullptr)
                        q.push(cur->right);
                }
                ofs << endl;
            }
        }
};



#endif