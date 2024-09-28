#include <iostream>

using namespace std;
#include <vector>

struct TrieNode{
    
    TrieNode* childNode[26];
    bool endOfWord;

    TrieNode(){
        endOfWord = false;
        for(int i=0;i<26;i++)
            childNode[i] = NULL;
    }

};

void insertWord(TrieNode* root,string &word){

    TrieNode *currNode = root;

    for(auto &c : word){
        if(currNode->childNode[c-'a']==NULL){
            TrieNode *newNode = new TrieNode();
            currNode->childNode[c-'a'] = newNode;
        }
        currNode = currNode->childNode[c-'a'];
    }

    currNode->endOfWord = true;

}


bool searchWord(TrieNode* root,string &word){

    TrieNode *currNode = root;

     for(auto &c : word){
         if(currNode->childNode[c-'a']==NULL){
            cout<<"word not found"<<endl;
            return false;
         }
            

        currNode = currNode->childNode[c-'a'];
     }

    if(currNode->endOfWord)
        cout<<"word found"<<endl;
    
     return currNode->endOfWord;
}

bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < 26; i++)
        if (root->childNode[i])
            return false;

    return true;
}

TrieNode* removeWord(TrieNode* root, string &word, int depth = 0)
{
   
    if (!root)
        return NULL;
 
 
    if (depth == word.size()) {

        if (root->endOfWord)
            root->endOfWord = false;
 
        if (isEmpty(root)) {
            delete (root);
            root = NULL;
        }
 
        return root;
    }
  
    int index = word[depth] - 'a';

    root->childNode[index] = removeWord(root->childNode[index], word, depth + 1);
 
    if (isEmpty(root) && root->endOfWord == false) {
        delete (root);
        root = NULL;
    }
 
    return root;
}


int main()
{

    TrieNode* root = new TrieNode();
    vector<string>words =  {"and", "animal", "do", "does", "dont", "donkey"};

    for (auto &s : words) {
        insertWord(root, s);
    }

    vector<string> searchWords = {"do", "donk", "dontee"};

    for (auto &s : searchWords) {
        cout<<"seaching for word : " <<s<<endl;
        searchWord(root, s);      
    }

    string removingWord = "donkey";
    removeWord(root,removingWord);
    string findWord = "donkey";
    searchWord(root, findWord); 

return 0;
}