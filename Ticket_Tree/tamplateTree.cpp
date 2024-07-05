#include <iostream>
#include "classTicket.cpp"
using namespace std;

template <class Key> class Tree{
    class Node {
        public:
            Node* left;
            Node* right;
            Key* key;

            Node(Key* data){
                this->key = data;
                this->left = NULL;
                this->right = NULL;
            }

            ~Node(){
                delete this->key;
            }
    };

    public:
        Node* root;

        bool setRoot(Node* Root){
            this->root = Root;
            if(getRoot() == Root){
                return true;
            }
            else return false;
        }

        Tree(){
            this->setRoot(NULL);
        }

        Node* getRoot(){
            return this->root;
        }

        bool addNode(Node* rootSubtree, Key* object){
            if(this->getRoot() == NULL){
                Node* newNode = new Node(object);
                this->setRoot(newNode);
                return true;
            }

            if(*(rootSubtree->key) > *object){
                if(rootSubtree->left != NULL)
                    this->addNode(rootSubtree->left, object);
                else{
                    Node* newNode = new Node(object);               
                    rootSubtree->left = newNode;
                    return true;
                }
            }
            else if( *object > *(rootSubtree->key) || *(rootSubtree->key) == *object){
                if(rootSubtree->right != NULL)
                    this->addNode(rootSubtree->right, object);
                else{
                    Node* newNode = new Node(object);
                    rootSubtree->right = newNode;
                    return true;
                }
            }
            return false;
        }

        Node* deleteNode(Key* objectSearch, Node* rootSubtree){
            if(rootSubtree == NULL){
                return rootSubtree;
            }

            if(*objectSearch > *(rootSubtree->key)){
                rootSubtree->right = deleteNode(objectSearch, rootSubtree->right);
            }
            else if(!(*objectSearch > *(rootSubtree->key)) && !(*objectSearch == *(rootSubtree->key))){
                rootSubtree->left = deleteNode(objectSearch, rootSubtree->left);
            }
            else{
                if(TicketM::comparisonDateNumber(*objectSearch, *(rootSubtree->key))){
                    if(rootSubtree->left == NULL && rootSubtree->right == NULL){ // совпадение с листом
                        delete rootSubtree;
                        return NULL;
                    }
                    else if(rootSubtree->left == NULL && rootSubtree->right != NULL){ // у совпавшего ключа нет левого потомка
                        Node* temp = rootSubtree->right;
                        delete rootSubtree;
                        return temp;
                    }
                    else if(rootSubtree->left != NULL && rootSubtree->right == NULL){// у совпавшего ключа нет правого потомка
                        Node* temp = rootSubtree->left;
                        delete rootSubtree;
                        return temp;
                    }
                    else if(rootSubtree->left != NULL && rootSubtree->right != NULL)// у совпавшего ключаесть оба потомка
                    {
                        rootSubtree->key = this->findMinNodeDelete(rootSubtree);
                        return rootSubtree;
                    }
                }
                else
                    rootSubtree->left = deleteNode(objectSearch, rootSubtree->left); // если не совпал номер рейса, продолжаем искать
                    rootSubtree->right = deleteNode(objectSearch, rootSubtree->right);
            }
            
            return rootSubtree;
        }
    
        Key* findMinNodeDelete (Node* root){
            Key* buf;

            if((root->right)->left != NULL){
                Node* minNode = root->right;
                Node* predMinNode;

                while(minNode->left != NULL){
                    predMinNode = minNode;
                    minNode = minNode->left;
                }

                if(minNode->right == NULL){ // First exemple
                    buf =  minNode->key;
                    predMinNode->left = NULL;
                }
                else if(minNode->right != NULL){
                    predMinNode->left = minNode->right;
                    buf =  minNode->key;
                    delete minNode;
                }

                return buf;
            }
            else{
                if((root->right)->right == NULL){
                    buf =  (root->right)->key;
                    delete root->right;
                    root->right = NULL;
                }
                else if((root->right)->right != NULL){
                    buf =  (root->right)->key;
                    Node* bufNode = root->right; 
                    root->right = (root->right)->right;
                    delete bufNode;
                }
                return buf;
            }
        }

        void entedByKey(Node* rootSubtree, Key* objectSearch, int* findKey){
            if(rootSubtree == NULL){
                return;
            }

            if(*objectSearch > *(rootSubtree->key)){
                entedByKey(rootSubtree->right, objectSearch, findKey);
            }
            else if(!(*objectSearch > *(rootSubtree->key)) && !(*objectSearch == *(rootSubtree->key))){
                entedByKey(rootSubtree->left, objectSearch, findKey);
            }
            else
            {
                if(TicketM::comparisonDateNumber(*objectSearch, *(rootSubtree->key)))
                {
                    *findKey += 1;
                    (rootSubtree->key)->entedTicketInfo();
                    entedByKey(rootSubtree->right, objectSearch, findKey);
                    entedByKey(rootSubtree->left, objectSearch, findKey);
                }
                else{
                    entedByKey(rootSubtree->right, objectSearch, findKey);
                    entedByKey(rootSubtree->left, objectSearch, findKey);
                }
            }

        }

        void entedTree(Node* rootSubtree){
            if(rootSubtree->left != NULL){
                entedTree(rootSubtree->left);
            }
            
            (rootSubtree->key)->entedTicketInfo();

            if(rootSubtree->right != NULL){
                entedTree(rootSubtree->right);
            }

        }

        void clearTree(Node* rootSubtree){
            if(rootSubtree->left != NULL){
                clearTree(rootSubtree->left);
            }
            if(rootSubtree->right != NULL){
                clearTree(rootSubtree->right);
            }
            
            
            if(rootSubtree->left != NULL)
                delete rootSubtree->left;
            if(rootSubtree->right != NULL)
                delete rootSubtree->right;
        }
};