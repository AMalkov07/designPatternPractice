#include <stack>
#include <queue>
#include <iostream>

class Tree{
public:
    int val;
    Tree* left = nullptr;
    Tree* right = nullptr;
};

class Iterator {
public:
    virtual int getNext() = 0;
    virtual bool hasNext() = 0;
};

class Dfs : public Iterator {
    std::stack<Tree*> s;
    Tree *m_tree;
public:
    Dfs(Tree *tree) {
            s.push(tree);
        }
    virtual int getNext(){
        m_tree = s.top();
        s.pop();
        if (m_tree->right != nullptr) {
            s.push(m_tree->right);
        }
        if (m_tree->left != nullptr) {
            s.push(m_tree->left);
        }
        return m_tree->val;
    }
    virtual bool hasNext() {
        return !(s.empty());
    }
};

class Bfs : public Iterator {
    std::queue<Tree*> q;
    Tree *m_tree;
public:
    Bfs(Tree *tree) {
            q.push(tree);
        }
    virtual int getNext(){
        m_tree = q.front();
        q.pop();
        if (m_tree->left != nullptr) {
            q.push(m_tree->left);
        }
        if (m_tree->right != nullptr) {
            q.push(m_tree->right);
        }
        return m_tree->val;
    }
    virtual bool hasNext() {
        return !(q.empty());
    }
};

class Collection{
    Iterator* iterator;
public:
    Collection(Iterator* it)
        : iterator(it){}
    
    void iterate(){
        while(iterator->hasNext()) {
            std::cout << iterator->getNext() << std::endl;
        }
    }
};

int main(){
    Tree* myTree = new Tree();
    myTree->val = 1;
    myTree->left= new Tree();
    myTree->right= new Tree();
    myTree->left->val = 2;
    myTree->right->val = 3;
    myTree->left->left = new Tree();
    myTree->left->left->val = 4;
    
    Iterator *iterator = new Dfs(myTree);
    Iterator *iteratorBfs = new Bfs(myTree);

    Collection *collection = new Collection(iterator);
    collection->iterate();

    Collection *collection2 = new Collection(iteratorBfs);
    collection2->iterate();
    return 0;
}