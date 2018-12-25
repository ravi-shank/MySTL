/*
Author  :   Ravi Shankar
Email   :   shankar.ravi.awesome@gmail.com
*/
#ifndef __MyMap_H
#define __MyMap_H
#include<algorithm>
using namespace std;
template<class T1, class T2>
class MyMap
{
    public:
         MyMap();                                 // constructor
         MyMap(const MyMap<T1, T2>&mapToCopy);    // paramaterized constructor
        ~MyMap();                                 // Destructor
        int size() const;                         // method to return the size of the map
        void clear();                             // method to clear the map
        bool empty() const;                       // method to check if map is empty
        void insert(T1, T2);                      // method to insert a key value pair
        T2& operator[](const T1 &key);            // overloaded operator [] for mutable map
        T2 operator[](const T1 &key) const;       // overloaded operator [] for immutable map
        T2 get(const T1& key) const;              // methtod to get the value fo ra key
        bool hasKey(const T1 &key) const;         // method to check if a specific key is present in map
        void removeKey(T1 key);                   // method to removeakey from map
        void preorder();                          // method to get preorder traversal of the map

    private:
        struct AVLNode
        {
            struct AVLNode * left, *right;
            T1 key;
            T2 value;
            int height;
        };

        int nodeCount;
        struct AVLNode* root;

        //method to traverse the AVLTree
        void traversePreorder( struct AVLNode* head )
        {
            if(head == NULL)
                return ;
            cout<< head->key<<" ";
            traversePreorder(head->left);
            traversePreorder(head->right);
        }

        // Method to delete the AVLTree
        void deleteAVLTree(struct AVLNode * &root)
        {
            if(root!=NULL)
            {
                deleteAVLTree(root->left);
                deleteAVLTree(root->right);
                delete root;
            }
        }

        // Method to calculate the height of a tree
        int getHeight(struct AVLNode* head)
        {
            return (head == NULL ? 0: head-> height);
        }

        // Method to calculate the balance factor of a subtree: balancefactor = height(leftSubTree)- height(rightSubTree)
        int getBalance(struct AVLNode* head)
        {
            if(head==NULL)
                return 0;
            else
                return getHeight(head-> left) - getHeight(head->right);
        }

            // Method to find a key in the tree, if present then function
            // reutrns the reference to the value of the key, else returns NULL
            T2* findNode(struct AVLNode* root, const T1 &key) const
            {
                if(root== NULL)
                    return NULL;
                else if(root->key == key)
                    return &root->value;
                else if( key< root->key)
                    return findNode(root->left, key);
                else
                    return findNode(root->right, key);
            }
            // Method to rotate the subtree by right
            struct AVLNode* rightRotation(struct AVLNode* head )
            {
                struct AVLNode *nodeT1= head->left;
                struct AVLNode *nodeT2 = nodeT1->right;
                nodeT1->right = head;
                head->left = nodeT2;
                head->height = max(getHeight(head->left), getHeight(head->right))+1;
                nodeT1->height = max(getHeight(nodeT1->left), getHeight(nodeT1->right))+1;
                return nodeT1;
            }
            // Method to rotate the subtree by left
            struct AVLNode* leftRotation( struct AVLNode* head )
            {
                struct AVLNode *nodeT1= head->right;
                struct AVLNode *nodeT2 = nodeT1->left;
                nodeT1->left = head;
                head->right = nodeT2;
                head->height = max(getHeight(head->left), getHeight(head->right))+1;
                nodeT1->height = max(getHeight(nodeT1->left), getHeight(nodeT1->right))+1;
                return nodeT1;
            }
            // Method to balance the AVL tree while insertion
            struct AVLNode* BalanceInsertionAVLTree(int balanceFactor, const T2 &key, struct AVLNode *head)
            {
                // 1. left left
              if( balanceFactor>1  and key < head->left->key)
                    {
                         return rightRotation(head);
                    }
            // 2. left right
              if( balanceFactor>1  and key> head->left->key)
                    {

                        head-> left = leftRotation(head->left);
                        return rightRotation(head);
                    }
             // 3. right right
              if( balanceFactor<-1  and key> head->right->key )
                    {
                        //cout<<"right right\n";
                         return leftRotation(head);
                    }

             // 4. Right left
              if( balanceFactor<-1  and key < head->right->key)
                    {
                        head->right = rightRotation(head->right);
                        return leftRotation(head);
                    }
                return head;
            }

            // Method to balance the AVL tree while deletion
            struct AVLNode* BalanceDeletionAVLTree( int balanceFactor, struct AVLNode *head )
            {
              if( balanceFactor>1  and getBalance(head->left)>=0 )
                    {
                        return rightRotation(head);
                    }
                // 2. left right
              if( balanceFactor>1  and getBalance(head->left)< 0)
                    {
                        head-> left = leftRotation(head->left);
                        return rightRotation(head);
                    }
                // 3. right right
              if( balanceFactor<-1  and getBalance(head->right)<=0 )
                    {
                        return leftRotation(head);
                    }

                // 4. Right left
              if( balanceFactor<-1  and getBalance(head->right)>0)
                    {
                        head->right = rightRotation(head->right);
                        return leftRotation(head);
                    }
                return head;
            }

        // Method to find the inorder successor of a node
        struct AVLNode* find_inorder_successor(struct AVLNode* head)
        {
            while(head->left!=NULL)
                head= head->left;
            return head;
        }

        //Method to remove a key from the AVL tree
        struct AVLNode* deleteNode(struct AVLNode *head, T2 key)
        {
            if(head == NULL)
                return head;
            else if(key < head->key)
                head->left = deleteNode(head->left,key);
            else if(key>head->key)
                head->right = deleteNode(head-> right,key);
            else
            {
                nodeCount--;
                // node with single child or no child
                if(head->left == NULL or head->right == NULL)
                {
                    struct AVLNode* tmp = (head->left!=NULL) ? head->left: head->right;
                    if(tmp == NULL)  // no child
                    {
                        tmp=head;
                        head = NULL;
                        delete tmp;
                    }
                    else    // one child case
                    {
                        * head = * tmp;
                        delete tmp;
                    }
                }
                else  // have 2 child
                {
                    struct AVLNode * nodeToBeReplacewith = find_inorder_successor(head->right);
                    head->key = nodeToBeReplacewith->key;
                    head->right = deleteNode(head->right, nodeToBeReplacewith->key);
                }
            }

            if(head==NULL)
                return head;

            head ->height = 1 + max( getHeight(head->left), getHeight(head->right) );
            int balanceFactor = getBalance(head);
            head = BalanceDeletionAVLTree(balanceFactor, head);

            return head;
        }

        // Method to insert a node in the AVL tree, retuns the reference to the value of the key addedd
        T2* insertNode (struct AVLNode* &head, const T2 &key)
        {
            // insert the new node in the BST
            if(head == NULL)
                {
                    head = new AVLNode();
                    head->left = head->right = NULL;
                    head->key = key;
                    head->value = T2();      // add default value of type T2 as of now
                    head->height = 1;       // height of newnode being added is considered as 1
                    nodeCount++;
                    return &head->value;
                }

            T2 *ret= NULL;
            if(key < head->key)
               {
                   ret =  insertNode(head->left, key);
               }
            else if(key > head->key)
               {
                   ret = insertNode(head->right, key);
               }
            else
                {
                    return &head->value; // return the existing node
                }

            // update height of current node
             head ->height = 1 + max( getHeight(head->left), getHeight(head->right) );
             int balanceFactor = getBalance(head);
             if(balanceFactor>1 or balanceFactor<-1)
                {
                    head= BalanceInsertionAVLTree(balanceFactor, key, head);
                }
                return ret;
        }
};

#endif // __MyMap_H

// Public Method definition

// Constructor to create map
template<class T1, class T2>
MyMap<T1, T2>:: MyMap()
{
    root = NULL;
    nodeCount = 0;
}

// Destructor to destruct map
template<class T1, class T2>
MyMap<T1, T2>:: ~MyMap()
{
    if(root!=NULL)
        deleteAVLTree(root);
    nodeCount = 0;
}

// Method to insert a key-value pair in map
// Working description: insert a node in AVL tree
// Parameter:
//          key: key to be inserted
//          value: value to be intersed for the key
// Return type: void
template<class T1, class T2>
void MyMap<T1, T2>:: insert(T1 key, T2 value)
{
    *(this->insertNode(root, key)) = value;
}

// Method to clear the map
// Working description: deletes all the node from AVL tree
// Parameter:   None
// Return type: void
template<class T1, class T2>
void MyMap<T1, T2>:: clear()
{
    if(root!= NULL)
        {
            deleteAVLTree(root);
            root = NULL;
            nodeCount = 0;
        }
}

// Method to check if map is empty
// Working description: check if the size of map is zero
// Parameter:   None
// Return type: Boolean
template<class T1, class T2>
bool MyMap<T1, T2>:: empty() const
{
    return nodeCount == 0;
}

// Method to return the size of the map
// Working description: returns the size of map
// Parameter:
// Return type: int
template<class T1, class T2>
int MyMap<T1, T2>:: size() const
{
    return nodeCount;
}

// Method to get the value for a key
// Working description: if the key is present then the value is returned
// else default value of the datatype (of "value") is returned
// Parameter:
//          key: key for which value is to be searched
// Return type: data type of the "value" for the key
template<class T1, class T2>
T2 MyMap<T1, T2>:: get( const T1 &key) const
{
    T2 * ret= findNode(root, key);
    if(ret == NULL)     // no key found then return default value of type T2 else return existing node value
        return T2();
    else
        return *ret;
}

// Overloaded Operator [] for mutable map
// Working description: if key not persent in AVL tree, then it inserts the key in AVL tree with its
// default value and returns  the reference to it.
// Parameter:
//          key: key to be inserted
// Return type: reference to the default value for the key inserted
template <class T1, class T2>
T2& MyMap<T1, T2>::operator[](const T1 & key)
{
    return *insertNode(root, key);
}

// Overloaded Operator [] for immutable map
// Working description: if key not persent in AVL tree, then it returns the
// default value for that key.
// Parameter:
//          key: key for which value is to be searched
// Return type: data type of the value for a key
template <class T1, class T2>
T2 MyMap<T1, T2>::operator[](const T1 &key) const
{
    return get(key);
}

// Method to check if map has a specific key
// Working description: searches for key in AVL tree, if present then returns True, else False
// Parameter:
//          key: key to be searched
// Return type: Boolean
template <class T1, class T2>
bool MyMap<T1, T2>::hasKey(const T1 &key) const
{
   if(findNode(root, key)!=NULL)
        return true;
   return false;
}

// Method to remove a key-value pair form the map
// Working description: searches for the key in AVL tree and deletes it
// Parameter:
//          key: key which is to be deleted
// Return type: void
template <class T1, class T2>
void MyMap<T1, T2>::removeKey( T1 key)
{
   root = deleteNode(root, key);
}

// Method to traverse the map in preorder way
// Parameter:   None
// Return Type: void
template <class T1, class T2>
void MyMap<T1, T2>::preorder()
{
    //cout<<"root node= "<< root->key<< endl;
    //if(root)
      //  cout<<"root ="<< root->key<< endl;
   traversePreorder(root);

}
