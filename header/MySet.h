/*
Author  :   Ravi Shankar
Email   :   shankar.ravi.awesome@gmail.com
*/

#ifndef _MySet_H
#define _MySet_H
using namespace std;

template<class T>
class MySet
{
    public:
        MySet();                                   // constructor to initialize the empty set
        ~ MySet();                                 // destructor  to destuct the set object
        void clear();                              // to clear the set object
        int size() const;                          // to get the size of the set object
        void insert(const T &value);               // insert a element into set
        bool empty() const;                        // to check if set is empty
        void remove( T key);                       // to remove a key from set
        bool find ( const T &key ) const;          // to check if element is present in set
        void preorder() ;

    private:
        struct BSTNode
        {
            struct BSTNode * left, *right;
            T key;
        };

        int nodeCount;
        struct BSTNode* root;

        // Method to traverse the BST in preorder
        void traversePreorder( struct BSTNode* head )
        {
            if(head == NULL)
                return ;
            cout<< head->key<<" ";
            traversePreorder(head->left);
            traversePreorder(head->right);
        }

        // Method to delete complete BST
        void deleteBST(struct BSTNode * &root)
            {
                if(root!=NULL)
                {
                    deleteBST(root->left);
                    deleteBST(root->right);
                    delete root;
                }
            }
        // Method to remove a key from BST
        struct BSTNode* removeNode(struct BSTNode * root, T key)
            {
                if(root == NULL)
                    return root;
                else if(key < root->key)
                    root->left = removeNode(root->left, key);
                else if(key > root->key)
                    root->right = removeNode(root->right, key);
                else
                {
                    nodeCount--;
                    if(root->left == NULL or root->right == NULL)
                    {
                        struct BSTNode *tmp = root->left != NULL ? root->left: root->right;
                        if(tmp == NULL) // no child
                        {
                            tmp  = root;
                            root = NULL;
                            delete tmp;
                        }
                        else    //one child
                        {
                            *root = *tmp;
                            delete tmp;
                        }
                    }
                    else        // two child
                    {
                        struct BSTNode * nodeToReplaceWith = find_inorder_successor(root->right);
                        root->key = nodeToReplaceWith->key;
                        root->right= removeNode( root->right, nodeToReplaceWith->key);
                    }
                }

                    return root;
            }

        // Method to insert a key in BST
        struct BSTNode* insertNode(struct BSTNode * root, const T &key)
        {
            if(root == NULL)
            {
                struct BSTNode * node = new BSTNode;
                node->left = node->right= NULL;
                node->key = key;
                nodeCount++;
                return node;
            }
            if(key == root->key)
                return root;
            else if(key < root->key )
                root->left = insertNode( root->left, key);
            else
                root->right = insertNode( root->right, key);
            return root;
        }

        // Method to find a key in BST
        bool findNode(struct BSTNode* root, const T &key) const
            {
                if(root == NULL)
                    return false;
                else if(root->key == key)
                    return true;
                else if( key< root->key)
                    return findNode(root->left, key);
                else
                    return findNode(root->right, key);
            }
        // Method to find a inorder successor of a key in BST
        struct BSTNode* find_inorder_successor(struct BSTNode* root)
            {
                while(root->left!=NULL)
                    root = root->left;
                return root;
            }
};
#endif // _MySet_H


// Public member functions

// Constructor to initialize the empty set
// Parameter:       None
// Return type:     None
template<class T>
MySet<T>:: MySet()
{
   root = NULL;
   nodeCount = 0;
}

// Destructor to delete the BST
template<class T>
MySet<T>:: ~MySet()
{
    deleteBST(root);
    root = NULL;
    nodeCount=0;
}

// Method to delete all the elements from set
// Working description: deletes each node from the BST
// Parameter: None
// Return type: void
template<class T>
void MySet<T>:: clear()
{
    deleteBST(root);
    root = NULL;
    nodeCount=0;
}

// Method to get the size of the set
// Working description: get the size of the set
// Parameter: None
// Return type: int
template<class T>
int MySet<T>:: size() const
{
    return nodeCount;
}

// Method to insert a key in the set
// Working description: searches for position in BST and insert in it
// Parameter:
//          key: key which is to be inserted
// Return type: void
template<class T>
void MySet<T>:: insert(const T &key)
{
    root = insertNode(root,key);
}

// Method to find the key in the set
// Working description: searches for the key in BST and returns True if key is present else returns False
// Parameter:
//          key: key which is to be searched
// Return type: Boolean
template<class T>
bool MySet<T>:: find(const T &key) const
{
    return  findNode(root, key);
}

// Method to remove a key form the set
// Working description: searches the key to be deleted and deletes it
// Parameter:
//          key: key which is to be deleted
// Return type: void
template<class T>
void MySet<T>:: remove( T key)
{
   root =  removeNode(root, key);
}

// Method to checks if set is empty
// Working description: reutrns True if set is empty else returns False
// Parameter: None
// Return type: Boolean
template<class T>
bool MySet<T>:: empty() const
{
    return nodeCount==0;
}

// Method to do the preorder traversal of the BST
// Parameter:   None
// Return type: void
template<class T>
void MySet<T>:: preorder()
{
    traversePreorder(root);
}
