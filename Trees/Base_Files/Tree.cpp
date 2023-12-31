#include "Tree.h"

Tree::Tree(int val)
{
  root = new Node(nullptr, val);
}

Tree::~Tree()
{
  destructTree();
}

/**
 * @brief Swap the two nodes places.
 *
 * @param node1 First node.
 * @param node2 Second node.
 */
void Tree::swap(Node *node1, Node *node2)
{
  if (!node1 || !node2)
    throw "Swapping null nodes";
  Node *temp = new Node();
  if (!temp)
    return;
  temp->parent = node1->parent;
  temp->left = node1->left;
  temp->right = node1->right;

  if (node2->parent != node1)
  {
    node1->parent = node2->parent;
    if (node2->parent && node2->parent->left == node2)
      node2->parent->left = node1;
    else if (node2->parent)
      node2->parent->right = node1;
  }
  if (node2->left != node1)
  {
    node1->left = node2->left;
    if (node2->left)
      node2->left->parent = node1;
  }
  if (node2->right != node1)
  {
    node1->right = node2->right;
    if (node2->right)
      node2->right->parent = node1;
  }

  if (temp->parent != node2)
  {
    node2->parent = temp->parent;
    if (temp->parent && temp->parent->left == node1)
      temp->parent->left = node2;
    else if (temp->parent)
      temp->parent->right = node2;
  }
  if (temp->left != node2)
  {
    node2->left = temp->left;
    if (temp->left)
      temp->left->parent = node2;
  }
  if (temp->right != node2)
  {
    node2->right = temp->right;
    if (temp->right)
      temp->right->parent = node2;
  }
}

/**
 * @brief Copy source node to destination.
 *
 * @param src First node.
 * @param dest Second node.
 */
void Tree::copy(Node *src, Node *dest)
{
  if (!src || !dest)
    throw "Copying null nodes";
  dest->parent = src->parent;
  dest->left = src->left;
  dest->right = src->right;
  dest->val = src->val;
}

/**
 * @brief Fills the buffer with the tree.
 *
 * @param node Current node.
 * @param offset The offset of the value in the buffer.
 * @param depth The current level.
 * @param s The buffer.
 *
 * @returns the offset for the parent node.
 */
int Tree::recPrintTree(const Node *node, size_t offset, size_t depth, char **s)
{
  if (!node)
    return 0;
  char value[6]; // (XXX)
  size_t width, left, right;
  width = sprintf(value, "(%03d)", node->val);
  left = recPrintTree(node->left, offset, depth + 1, s);
  right = recPrintTree(node->right, offset + left + width, depth + 1, s);
  for (size_t i = 0; i < width; i++)
    s[depth][offset + left + i] = value[i];
  // If left sibling
  if (depth && node->parent && node->parent->left == node)
  {
    for (size_t i = 0; i < width + right; i++)
      s[depth - 1][offset + left + width / 2 + i] = '-';
    s[depth - 1][offset + left + width / 2] = '.';
  }
  // If right sibling
  else if (depth)
  {
    for (size_t i = 0; i < width + left; i++)
      s[depth - 1][offset - width / 2 + i] = '-';
    s[depth - 1][offset + left + width / 2] = '.';
  }

  return left + width + right;
}

/**
 * @brief Measures the height of a tree.
 *
 * @param node Pointer to the node to measure its tree height.
 *
 * @returns The height of the tree starting at @node.
 */
size_t Tree::getHeight(const Node *node)
{
  if (!node)
    return 0;
  size_t height_l, height_r;
  height_l = getHeight(node->left);
  height_r = getHeight(node->right);
  return 1 + (height_l > height_r ? height_l : height_r);
}

/**
 * @brief Deallocate all nodes before deconstructing the class.
 */
void Tree::destructTree()
{
  if (!root)
    return;
  std::queue<Node *> q;
  q.push(root);
  while (!q.empty())
  {
    Node *curr = q.front();
    q.pop();
    if (curr->left)
      q.push(curr->left);
    if (curr->right)
      q.push(curr->right);
    delete curr;
  }
}

/**
 * @brief Insert a new node to the tree.
 */
void Tree::InsertNode(int value)
{
}
/**
 * @brief If found, delete a node from the tree.
 */
void Tree::DeleteNode(int value)
{
}

/**
 * @brief Prints the tree in the console.
 */
void Tree::printTree()
{
  char **s;
  if (!root)
    return;
  size_t height = getHeight(root);
  s = new char *[height + 1];
  if (!s)
    return;
  for (size_t i = 0; i < height + 1; i++)
  {
    s[i] = new char[255];
    if (!s[i])
      return;
    memset(s[i], ' ', 255);
  }
  recPrintTree(root, 0, 0, s);
  for (size_t i = 0; i < height + 1; i++)
  {
    for (size_t j = 254; j > 1; j--)
    {
      if (s[i][j] != ' ')
        break;
      s[i][j] = '\0';
    }
    printf("%s\n", s[i]);
    free(s[i]);
  }
  free(s);
}