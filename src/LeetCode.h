#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

vector<int> twoSum(vector<int> &numbers, int target);
void A_TwoSum();
void A_LongestSubWithoutDup();
void A_LongestSubPalindrome();
void A_ZigZagConvert();
void A_isPalindrome();
void A_Jump();
void A_StringMultiply();
void A_Anagram();


void B_minDistance();
void B_UniquePaths();
void B_CanJump();

void C_WeiQi();
void C_numDistinct();
void C_PascalTriangle();
void C_MinimumTotal();
void C_IsPalindrome();
void C_WordLadder();
void C_levelOrder();
void C_SortedArrayToBST();
void C_ZigzagLevelOrder();
void C_MaxDepth();
void C_BuildTree();
void C_BuildTree2();


void D_LIS();
void D_maxSubsequence();

// Struct
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x):val(x), left(NULL), right(NULL) {}
};

void showBST(TreeNode *root);
TreeNode* buildBST(int ay[], int beg, int end);

// TOOL function
void showVecInt(vector<int> &vec);
int minimum3(int x, int y, int z);
void showMatrixInt(int **table, int row, int col);
void showMatrixChar(vector<vector<char> > &table);
void showVecString(vector<string> vec);
