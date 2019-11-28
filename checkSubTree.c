bool areIdentical(struct node * root1, struct node *root2) 
{ 
    /* base cases */
    if (root1 == NULL && root2 == NULL) 
        return true; 
  
    if (root1 == NULL || root2 == NULL) 
        return false; 
  
    /* Check if the data of both roots is same and data of left and right 
       subtrees are also same */
    return (root1->data == root2->data   && 
            areIdentical(root1->left, root2->left) && 
            areIdentical(root1->right, root2->right) ); 
} 
  
  
/* This function returns true if S is a subtree of T, otherwise false */
bool isSubtree(struct node *T, struct node *S) 
{ 
    /* base cases */
    if (S == NULL) 
        return true; 
  
    if (T == NULL) 
        return false; 
  
    /* Check the tree with root as current node */
    if (areIdentical(T, S)) 
        return true; 
  
    /* If the tree with root as current node doesn't match then 
       try left and right subtrees one by one */
    return isSubtree(T->left, S) || 
           isSubtree(T->right, S); 
} 
