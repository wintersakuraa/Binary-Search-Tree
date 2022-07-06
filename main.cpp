#include <set>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;


long long generateRandLong()
{
    long long key = 0;
    long long grade = 1;
    
    for (int i = 0; i < 13; i++)
    {
        if (i == 12)
        {
            int temp = rand() % 9 + 1;
            key += temp * grade;
            grade *= 10;
        }
        else
        {
            int temp = rand() % 10;
            key += temp * grade;
            grade *= 10;
        }
    }
    
    return  key;
}


struct Data
{
    string nickName;
    int rank;
    int XP;
    double donateSize;
    
    
    Data()
    {
        nickName = "";
        rank = rand() % 11;
        XP = rand() % 101;
        donateSize = rand() % 1000000 / 100.0;
    }
};


template <typename T>
struct Node
{
    Node* left;
    Node* right;
    T data;
    
    
    Node()
    {
        left = nullptr;
        right = nullptr;
    }
    
    
    Node(T obj)
    {
        left = nullptr;
        right = nullptr;
        data = obj;
    }
};


template <typename T>
struct BinarySearchTree
{
    
private:
    
    Node<T>* root;
    int numOfElements;

    
    Node<T>* insert(Node<T>* tempRoot, T object)
    {
        if (tempRoot == nullptr)
        {
            numOfElements++;
            return new Node<T>(object);
        }
        else if (object < tempRoot->data)
        {
            tempRoot->left = insert(tempRoot->left, object);
        }
        else if (object > tempRoot->data)
        {
            tempRoot->right = insert(tempRoot->right, object);
        }
      
        return  tempRoot;
    }
    
    
    Node<T>* find(Node<T>* tempRoot, T object)
    {
        if (tempRoot == nullptr)
        {
            return nullptr;
        }
        else if (object == tempRoot->data)
        {
            return tempRoot;
        }
        else if (object < tempRoot->data)
        {
            return find(tempRoot->left, object);
        }
        else if (object > tempRoot->data)
        {
            return find(tempRoot->right, object);
        }
        
        return  tempRoot;
    }
    
    
    Node<T>* erase(Node<T>* tempRoot, T object)
    {
        if (tempRoot == nullptr)
        {
            return nullptr;
        }
        else if (object < tempRoot->data)
        {
            tempRoot->left = erase(tempRoot->left, object);
        }
        else if (object > tempRoot->data)
        {
            tempRoot->right = erase(tempRoot->right, object);
        }
        else
        {
            if (tempRoot->left == nullptr)
            {
                Node<T>* tempNode = tempRoot->right;
                delete tempRoot;
                numOfElements--;
                return tempNode;
            }
            else if (tempRoot->right == nullptr)
            {
                Node<T>* tempNode = tempRoot->left;
                delete tempRoot;
                numOfElements--;
                return tempNode;
            }
            
            Node<T>* tempNode;
            Node<T>* min = tempRoot->right;
            while (min->left)
            {
                min = min->left;
            }
            
            tempNode = min;
            tempRoot->data = tempNode->data;
            tempRoot->right = erase(tempRoot->right, tempNode->data);
        }
        
        return tempRoot;
    }
    
    
    void print(Node<T>* tempRoot)
    {
        if (tempRoot != nullptr)
        {
            if (tempRoot->left != nullptr)
            {
                print(tempRoot->left);
            }
            
            cout << "[ " << tempRoot->data <<" ]" << endl;
            
            if (tempRoot->right != nullptr)
            {
                print(tempRoot->right);
            }
        }
    }
    
    
    int height(Node<T>* tempRoot)
    {
        
        if (tempRoot == nullptr)
        {
            return 0;
        }
        else
        {
            int leftHeight = height(tempRoot->left);
            int rightHeight = height(tempRoot->right);
            
            return 1 + max(leftHeight, rightHeight);
        }
    }
    
    
    int findInRange(Node<T>* tempRoot, T minObject, T maxObject)
    {
        if (tempRoot == nullptr) { return  0; }
        else if (tempRoot->data < minObject)
        {
            return findInRange(tempRoot->right, minObject, maxObject);
        }
        else if (tempRoot->data > maxObject)
        {
            return findInRange(tempRoot->left, minObject, maxObject);
        }
      
        return 1 + findInRange(tempRoot->left, minObject, maxObject) + findInRange(tempRoot->right, minObject, maxObject);
    }
    
    
    Node<T>* free(Node<T>* tempRoot)
    {
        if (tempRoot != nullptr)
        {
            free(tempRoot->left);
            free(tempRoot->right);
            delete tempRoot;
        }
        
        return  nullptr;
    }
    
public:
    
    BinarySearchTree()
    {
        root = nullptr;
        numOfElements = 0;
    }
    
    
    ~BinarySearchTree()
    {
        root = free(root);
    }
    
    
    void insert(T object)
    {
        root = insert(root, object);
    }
    
    
    T* find(T object)
    {
        Node<T>* value = find(root, object);
        if (value) { return &value->data; }
        return nullptr;
    }

    
    void erase(T object)
    {
        root = erase(root, object);
    }
    
    
    int size()
    {
        return  numOfElements;
    }
    
    
    void print()
    {
        print(root);
    }
    
    
    int height()
    {
        int h = height(root);
        return h;
    }
    
    
    int findInRange(T minObject, T maxObject)
    {
        int objects = findInRange(root, minObject, maxObject);
        return objects;
    }
};


bool operator<(const Data &p1, const Data &p2)
{
    if (p1.rank > p2.rank) { return false; }
    if (p1.rank == p2.rank)
    {
        if (p1.XP > p2.XP) { return false; }
        if (p1.XP == p2.XP)
        {
            if (p1.donateSize > p2.donateSize) { return false; }
            if (p1.donateSize == p2.donateSize)
            {
                if (p1.nickName >= p2.nickName) { return false; }
            }
        }
        
    }
    
    return true;
}


bool operator==(const Data &p1, const Data &p2)
{
    if (p1.rank != p2.rank) { return false; }
    if (p1.XP != p2.XP) { return false; }
    if (p1.donateSize != p2.donateSize) { return false; }
    if (p1.nickName != p2.nickName) { return false; }
    return true;
}


bool operator>(const Data &p1, const Data &p2)
{
    if (p1.rank < p2.rank) { return false; }
    if (p1.rank == p2.rank)
    {
        if (p1.XP < p2.XP) { return false; }
        if (p1.XP == p2.XP)
        {
            if (p1.donateSize < p2.donateSize) { return false; }
            if (p1.donateSize == p2.donateSize)
            {
                if (p1.nickName >= p2.nickName) { return false; }
            }
        }
        
    }
    
    return true;
}


ostream& operator<< (ostream &out, Data &player)
{
    out << "rank : " << player.rank << "|"
        << "XP : " <<player.XP << "|"
        << "donateSize : " <<player.donateSize << "|"
        << "nickName : " <<player.nickName;
    
    return out;
}


bool testBinarySearchTree()
{
    srand( (unsigned int)time(NULL));
    const int iters = 80000;
    const int keysAmount = iters * 2;
    const int itersToRangeQueries = 1000;
    vector<Data> data(keysAmount);
    vector<Data> dataToInsert(iters);
    vector<Data> dataToErase(iters);
    vector<Data> dataToFind(iters);
    vector<pair<Data, Data>> dataToRangeQueries;

    for (int i = 0; i < iters; i++)
    {
        dataToInsert[i] = data[generateRandLong() % keysAmount]; dataToErase[i] = data[generateRandLong() % keysAmount]; dataToFind[i] = data[generateRandLong() % keysAmount];
    }
    for (int i = 0; i < itersToRangeQueries; i++)
    {
        Data minData = Data();
        Data maxData = Data();
        if (maxData < minData)
        {
            swap(minData, maxData);
        }
        dataToRangeQueries.push_back({minData, maxData});
    }
    BinarySearchTree<Data> myTree;
    clock_t myStart = clock();
    for (int i = 0; i < iters; i++)
    {
        myTree.insert(dataToInsert[i]);
    }
    int myInsertSize = myTree.size();
    int myTreeHeight = myTree.height();
    int optimalTreeHeight = log2(myInsertSize) + 1;
    for (int i = 0; i < iters; i++)
    {
        myTree.erase(dataToErase[i]);
    }
    int myEraseSize = myInsertSize - myTree.size();
    int myFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (myTree.find(dataToFind[i]))
        {
            myFoundAmount++;
        }
    }
    clock_t myEnd = clock();
    float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;
    set<Data> stlTree;
    clock_t stlStart = clock();
    for (int i = 0; i < iters; i++)
    {
        stlTree.insert(dataToInsert[i]);
    }
    int stlInsertSize = (int)stlTree.size();
    for (int i = 0; i < iters; i++)
    {
        stlTree.erase(dataToErase[i]);
    }
    int stlEraseSize = (int)(stlInsertSize - stlTree.size());
    int stlFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (stlTree.find(dataToFind[i]) != stlTree.end())
        {
            stlFoundAmount++;
        }
    }
    clock_t stlEnd = clock();
    float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;

    clock_t myRangeStart = clock();
    int myRangeFoundAmount = 0;
    for (int i = 0; i < itersToRangeQueries; i++)
    {
        myRangeFoundAmount += myTree.findInRange(dataToRangeQueries[i].first, dataToRangeQueries[i].second);
    }
    clock_t myRangeEnd = clock();
    float myRangeTime = (float(myRangeEnd - myRangeStart)) / CLOCKS_PER_SEC;
    clock_t stlRangeStart = clock();
    int stlRangeFoundAmount = 0;
    for (int i = 0; i < itersToRangeQueries; i++)
    {
        const auto& low = stlTree.lower_bound(dataToRangeQueries[i].first);
        const auto& up = stlTree.upper_bound(dataToRangeQueries[i].second);
        stlRangeFoundAmount += distance(low, up);
    }
    clock_t stlRangeEnd = clock();
    float stlRangeTime = (float(stlRangeEnd - stlRangeStart)) / CLOCKS_PER_SEC;
    cout << "My BinaryTree: height = " << myTreeHeight << ", optimal height = " <<
    optimalTreeHeight << endl;
    cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize << ", found amount: " << myFoundAmount << endl;
    cout << "Range time: " << myRangeTime << ", range found amount: " << myRangeFoundAmount << endl << endl;
    cout << "STL Tree:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize << ", found amount: " << stlFoundAmount << endl;
    cout << "Range time: " << stlRangeTime << ", range found amount: " << stlRangeFoundAmount << endl << endl;
    if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize &&
            myFoundAmount == stlFoundAmount && myRangeFoundAmount == stlRangeFoundAmount)
    {
        cout << "The lab is completed" << endl;
        return true;
    }

    cerr << ":(" << endl;
    return false;
}


int main()
{
    testBinarySearchTree();
}
