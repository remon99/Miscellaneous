#include <bits/stdc++.h>
using namespace std;
#define pys cout << "YES" << endl
#define pyn cout << "NO" << endl
#define loop(i, n) for (int i = 0; i < n; ++i)
#define MOD 1000000007
#define pb push_back
#define mp make_pair
#define nl cout << endl
typedef vector<int> vi;
typedef long long ll;

struct node
{
  int data;
  node *left;
  node *right;
};

// node* root=NULL;

node *newnode(int val)
{
  node *temp = new node;
  temp->data = val;
  temp->left = temp->right = NULL;
  return temp;
}

node *findmin(node *root)
{
  while (root->left != NULL)
    root = root->left;
  return root;
}

node *Insert(node *root, int data)
{
  if (root == NULL)
  {
    root = newnode(data);
  }
  else if (root->data > data)
  {
    root->left = Insert(root->left, data);
  }
  else
    root->right = Insert(root->right, data);
  return root;
}

node *Delete(node *root, int data)
{
  if (root == NULL)
    return root;
  else if (data < root->data)
    root->left = Delete(root->left, data);
  else if (data > root->data)
    root->right = Delete(root->right, data);
  else
  {
    if (root->left == NULL and root->right == NULL)
    {
      delete root;
    }
    else if (root->left == NULL)
    {
      node *temp = root;
      root = root->right;
      delete temp;
    }
    else if (root->right == NULL)
    {
      node *temp = root;
      root = root->left;
      delete temp;
    }
    else
    {
      node *temp = findmin(root->right);
      root->data = temp->data;
      root->right = Delete(root->right, temp->data);
    }
  }
  return root;
}

void inorder(node *root)
{
  if (root == NULL)
    return;
  inorder(root->left);
  cout << root->data << endl;
  inorder(root->right);
  // cout<<root->right->data;
}

int main()
{
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  srand(chrono::high_resolution_clock::now().time_since_epoch().count());

  node *root = NULL;
  root = Insert(root, 5);
  root = Insert(root, 10);
  root = Insert(root, 3);
  root = Insert(root, 4);
  root = Insert(root, 1);
  root = Insert(root, 11);
  inorder(root);
  root = Delete(root, 5);
  inorder(root);
  return 0;
}
