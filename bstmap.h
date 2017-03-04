#ifndef __BSTMAP_H__
#define __BSTMAP_H__
#include <stdexcept>
#include "map.h"

template<typename K, typename V>
  class BstMap : public Map<K,V> {
 private:
  class Node{
  public:
    K key;
    V value;
    Node* left;
    Node* right;
    // Constructors for Node
  Node(const K& key_var, const V& value_var): key(key_var), value(value_var), left(NULL), right(NULL){}
  Node(const K& key_var, const V& value_var, Node* l, Node* r): key(key_var), value(value_var), left(l), right(r){}
  };
  Node* root;
 public:
  // Constructor for BstMap
 BstMap(): root(NULL){}
  
  // Add new Node
  virtual void add(const K & key_var, const V & value_var){

    Node * t = new Node(key_var,value_var);
    /*t->key = key_var;
    t->value = value_var;
    t->left = NULL;
    t->right = NULL;
    */
    Node * parent = NULL;

    // Check if Tree is Empty
    if (root == NULL){
      root = t;
    }
    // If it is not Empty
    else{
      Node * curr;
      curr = root;
      while(curr != NULL){
	parent = curr;
	if(t->key > curr->key){
	  curr = curr->right;
	}
	else if(t->key < curr->key){
	  curr = curr->left;
	}
	// If we find key, just replace value
	else if(t->key == curr->key){
	  curr->value = t->value;
	  delete t;
	  return;
	}
      }

      if(t->key < parent->key){
	parent->left = t;
      }
      else if(t->key > parent->key){
	parent->right = t;
      }
    }
  }

  
  // Lookup value of certain key, if not present throw exception
  virtual const V & lookup(const K& key_var) const throw (std::invalid_argument) {

    //Node * parent;

    // Check if Tree is Empty
    if (root == NULL){
      //throw;
      throw std::invalid_argument("Tree is empty");
    }
    // If it is not Empty
    else{
      Node * curr = root;
      while(curr != NULL){
	//parent = curr;
	if(key_var > curr->key){
	  curr = curr->right;
	}
	else if(key_var < curr->key){
	  curr = curr->left;
	}
	// If we find key, just replace value
	else if(key_var == curr->key){
	  return curr->value;
	}
      }
      throw std::invalid_argument("Key does not exist");
      //throw;
    }
  }
  
  /*// Remove a key
  virtual void remove(const K& key_var) {
    // Check if Tree is Empty
    if (root == NULL){
      return;
    }
    // If it is not Empty
    else{
      Node * curr;
      Node * parent;
      //parent->left = NULL;
      //parent->right = NULL;
      curr = root;
      parent = curr;
      bool key_found = false;
      while (curr != NULL){
	//parent = curr;
	if (curr->key == key_var){
	  //parent = curr;
	  key_found = true;
	  break;
	}
	else{
	  parent = curr;
	  if(key_var > curr->key){
	    curr = curr->right;
	  }
	  else if(key_var < curr->key){
	    curr = curr->left;
	  }
	}
      }
      // Exit fxn if key is not found
      if (key_found == false){
	return;
      }
      
      // If node has 1 child
      if((curr->left == NULL && curr->right != NULL) || (curr->left != NULL && curr->right == NULL)){
	// Right child, no left
	if(curr->left == NULL && curr->right != NULL){
	  if (parent->left == curr){
	    parent->left = curr->right;
	    delete curr;
	  }
	  else if (parent->right == curr){
	    parent->right = curr->right;
	    delete curr;
	  }
	  else{
	    root = parent->right;
	    delete curr;
	  }
	}
	// Left child, no right
	else if(curr->left != NULL && curr->right == NULL){
	  if (parent->left == curr){
	    parent->left = curr->left;
	    delete curr;
	  }
	  else if (parent->right == curr){
	    parent->right = curr->left;
	    delete curr;
	  }
	  else{
	    root = parent->left;
	    delete curr;
	  }
	}
	return;
      }

      // Leaf node
      else if (curr->left == NULL && curr->right == NULL){
	if (parent->left == curr){
	  parent->left = NULL;
	  delete curr;
	}
	else if (parent->right == curr){
	  parent->right = NULL;
	  delete curr;
	}
	else{
	  root = NULL;
	  delete curr;
	}
	return;
      }
   
      // Node has 2 children
      else if(curr->left != NULL && curr->right != NULL){
	Node * tmp = curr->right;
	// Right child has no children
	if(tmp->left == NULL and tmp->right == NULL){
	  curr->key = tmp->key;
	  curr->value = tmp->value;
	  delete tmp;
	  curr->right = NULL;
	}
	//Right child has children
	else if(tmp->left != NULL){
	  Node * l_tmp= tmp->left;
	  while(l_tmp->left != NULL){
	    tmp = l_tmp;
	    l_tmp = tmp->left;
	  }
	  curr->key = l_tmp->key;
	  curr->value = l_tmp->value;
	  delete l_tmp;
	  tmp->left =  NULL;
	}
	else{
	  curr->key = tmp->key;
	  curr->value = tmp->value;
	  curr->right = tmp->right;
	  delete tmp;
	}
      }

      return;

    }
  }

  */

  virtual void remove(const K& key_var) {
    root = Delete(root,key_var);
  }

  Node * Delete(Node * root , const K& key_var){
    if (root == NULL){
      return root;
    }
    else if (key_var < root->key){
      root->left = Delete(root->left,key_var);
    }
    else if (key_var > root->key){
      root->right = Delete(root->right,key_var);
    }

    else{
      // Leaf node
      if (root->left == NULL && root->right == NULL){
	delete root;
	root = NULL;
      }
      // One child
      else if (root->right == NULL){
	Node * tmp = root;
	root = root->left;
	delete tmp;
      }
      else{
	Node * tmp = FindMin(root->right);
	root->key = tmp->key;
	root->value = tmp->value;
	root->right = Delete(root->right,tmp->key);
      }
    }
    return root;
  }
  
  Node * FindMin(Node * root){
    while(root->left != NULL){
      root = root->left;
    }
    return root;
  }
  
  // Add Items to BST in Pre-order traversal
  void addPreorder(Node * current){
    if (current!= NULL){
      add(current->key, current->value);
      addPreorder(current->left);
      addPreorder(current->right);
    }
  }
  
  /*
  // Remove Items from BST in Pre-order traversal
  void removePreorder(Node * current){
    if (current!= NULL){
      remove(current->key);
      removePreorder(current->left);
      removePreorder(current->right);
    }
  }
  */

  // Copy Constructor  
  BstMap<K,V>(const BstMap<K,V> & rhs) : root(NULL) {   
    addPreorder(rhs.root);
    /*Node * curr = rhs.head;
    while (curr != NULL){
      addBack(curr->data);
      curr = curr->next;
      }*/ 
  }

  virtual BstMap<K,V>& operator=(const BstMap<K,V> & rhs) {
    if(this != &rhs){
      BstMap temp(rhs);
      std::swap(root,temp.root);
    }
    return *this;
  }
  
  void destroy(Node * current){
    if (current != NULL){
      destroy(current->left);
      destroy(current->right);
      delete current;
    }
  }

  // Destructor 
  virtual ~BstMap<K,V>() {
    Node * current = root;
    destroy(current);
    //removePreorder(current);
  }

};
#endif

