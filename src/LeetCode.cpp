#include "LeetCode.h"

using namespace std;

/*************************************************************************
 * 						Part A										    *
 *************************************************************************/
//A.1 Two Sum
vector<int> twoSum(vector<int> &numbers, int target)
{
	sort(numbers.begin(), numbers.end());
	vector<int> vec;
	int p1 = 0;
	int p2 = numbers.size() - 1;

	while(p1 < p2)
	{
		if(numbers[p1] + numbers[p2] == target)
		{
			vec.push_back(p1 + 1);
			vec.push_back(p2 + 1);
			break;
		}
		else if(numbers[p1] + numbers[p2] < target)
			p1++;
		else
			p2--;
	}

	return vec;
}

void A_TwoSum()
{
	int ay[4] = {2, 7, 9, 11};
	vector<int> vec(ay, ay + 4);
	vector<int> v = twoSum(vec, 9);
	showVecInt(v);
}

//A.2 Median of two sorted array


//A.3 Longest Substring Without Repeating Characters
int lengthOfLongestSubstring(string s)
{
	if(s.size() == 0 || s.size() == 1)
		return s.size();

	set<char> checker;
	set<char>::iterator iter;
	checker.insert(s[0]);
	int max = 0;
	int beg = 0;
	int end = 1;

	while(end != s.size())
	{
		iter = checker.find(s[end]);
		if(iter == checker.end())
			checker.insert(s[end]);
		else
		{
			if(end - beg > max)
				max = end - beg;
			while(s[beg] != s[end])
			{
				checker.erase(s[beg]);
				beg++;
			}
			beg++;
		}
		end++;
	}

	if(end - beg > max)
		max = end - beg;

	return max;
}

void A_LongestSubWithoutDup()
{
	string s = "abcabcbb";
	cout << lengthOfLongestSubstring(s);
}

//A.4 Add numbers in 2 linked list

//A.5 Longest Palindromic Substring
string longestPalindrome(string s)
{
	if(s.size() == 0)
		return NULL;

	int len = s.size();
	bool table[1000][1000] = {false};
	int beg = -1;
	int end = -1;
	int max = 1;

	//populate table for base case 1: c[i,i] is palindrome
	for(int i = 0; i < len; i++)
		table[i][i] = true;

	//populate table for base case 2: c[i, i+1] is palindrom , if s[i] = s[i+1]
	for(int i = 0; i < len - 1; i++)
		if(s[i] == s[i + 1])
		{
			beg = i;
			end = i + 1;
			max = 2;
			table[i][i + 1] = true;
		}

	/*
	 * populate upper right table
	 * c[i, j] is true only if
	 *    1:  c[i + 1, j - 1] is true
	 *    2:  s[i] = s[j]
	 */
	for(int i = 0; i < len - 2; i++)
	{
		int x = 0;
		int y = 2 + i;
		for(int j = 0; j < len - 2 - i; j++)
		{
			if(s[x] == s[y] && table[x + 1][y - 1] == true)
			{
				table[x][y] = true;
				if( y - x + 1 > max)
				{
					beg = x;
					end = y;
					max = y - x + 1;
				}
			}
			x++;
			y++;
		}
	}

	if(beg == -1)
		return s.substr(0,1);
	else
		return s.substr(beg, end - beg + 1);
}

void A_LongestSubPalindrome()
{
	string s = "";
	cout << longestPalindrome(s);
}

//A.6 ZigZag Conversion
string convertZigZag(string s, int nRows)
{
	int paceA = nRows*2 - 2;
	int paceB = 0;
	bool A = true;
	string ret;

	for(int i = 0; i < nRows; i++)
	{
		int current = i;
		A = true;
		while(current < s.size())
		{
			if(A)
			{
				if(paceA > 0)
					ret += s[current];
				A = false;
				current += paceA;
			}
			else
			{
				if(paceB > 0)
					ret += s[current];
				A = true;
				current += paceB;
			}
		}

		paceA -= 2;
		paceB += 2;
	}

	return ret;
}

void A_ZigZagConvert()
{
	string s = "PAYPALISHIRING";
	cout << convertZigZag(s, 4);
}

//A.7 Reverse Integer

//A.8 String to Integer

//A.9 Palindromic number
bool isPalindrome(int x)
{
	if(x < 0)
		x = -x;

	int div = 1;
	while(x/div >= 10)
		div *= 10;

	while(x >= 10)
	{
		if(x%10 != x/div)
			return false;
		x = x%div/10;
		div /= 100;
	}

	return true;
}

void A_isPalindrome()
{
	int numer = -1101011;
	cout << isPalindrome(numer);
}

//A.41 String Multiplication
string multiply(string str, char x)
{
	string ret;
	int carry = 0;

	for(int i = str.size() - 1; i >= 0; i--)
	{
		int num = (x - '0')*(str[i] - '0') + carry;
		if(num > 9)
		{
			carry = num/10;
			num = num%10;
		}
		else
			carry = 0;

		ret = (char)('0' + num) + ret;
	}

	if(carry > 0)
		ret = (char)('0' + carry) + ret;

	return ret;
}

void merge(string &ret, string s, int offset)
{
	if(ret.size() == 0)
	{
		ret = s;
		return;
	}

	int carry = 0;
	int i = ret.size() - 1 - offset;
	int j = s.size() - 1;

	while(j >= 0 || i >= 0 || carry == 1)
	{
		int num;
		if(j >= 0 && i >= 0)
			num = ret[i] - '0' + s[j] - '0' + carry;
		else if(j >= 0)
			num = s[j] - '0' + carry;
		else if(i >= 0)
			num = ret[i] - '0' + carry;
		else
			num = 1;

		if(num > 9)
		{
			num -= 10;
			carry = 1;
		}
		else
			carry = 0;


		if(i >= 0)
			ret[i] = '0' + num;
		else
			ret = (char)('0' + num) + ret;
		i--;
		j--;
	}



}
string stringMultiply(string str1, string str2)
{
	string ret;
	int offset = 0;
	for(int i = str2.size() - 1; i >= 0; i--)
	{
		string s = multiply(str1, str2[i]);
		merge(ret, s, offset);
		offset++;
	}
	return ret;
}

void A_StringMultiply()
{
	string s1 = "12345";
	string s2 = "12345";
	cout << stringMultiply(s1, s2);
}

//A.43 Jump Game II
void doJump(int ay[], int len, int ix, int &min, int count)
{
	if(ix >= len - 1)
	{
		if(count < min)
			min = count;
		return;
	}

	for(int i = ay[ix]; i > 0 ; i--)
	{
		doJump(ay, len, ix + i, min, count + 1);
	}
}
int Jump(int ay[], int len)
{
	int min = 1000;
	int count = 0;
	doJump(ay, len, 0, min, count);
	return min;
}

void A_Jump()
{
	int ay[5] = {2,3,1,1,4};
	cout << Jump(ay, 5);
}


//A.47 Anagram
vector<string> anagrams(vector<string> vec)
{
	map<string, int> mp;
	map<string, int>::iterator iter;
	for(int i = 0; i < vec.size(); i++)
	{
		string key = vec[i];
		sort(key.begin(), key.end());
		iter = mp.find(key);
		if(iter == mp.end())
			mp.insert(pair<string, int>(key, 1));
		else
			mp[key]++;
	}

	vector<string> ret;
	for(int i = 0; i < vec.size(); i++)
	{
		string key = vec[i];
		sort(key.begin(), key.end());
		if(mp[key] > 1)
			ret.push_back(vec[i]);
	}

	return ret;
}

void A_Anagram()
{
	vector<string> vec;
	vec.push_back("dog");
	vec.push_back("ogd");
	vec.push_back("cat");
	vec.push_back("tac");
	vec.push_back("good");
	vec.push_back("godo");
	vec.push_back("gdoo");
	vec.push_back("godd");
	showVecString(vec);

	showVecString(anagrams(vec));
}

/*************************************************************************
 * 						Part B										    *
 *************************************************************************/
//B.3 Jump Game
void doCanJump(int ay[], int len, int ix, bool &ret)
{
	if(ix >= len - 1)
	{
		ret = true;
		return;
	}

	for(int i = ay[ix]; i > 0 ;i--)
	{
		doCanJump(ay, len, ix + i, ret);
		if(ret)
			return;
	}
}

bool canJump(int ay[], int len)
{
	bool ret = false;
	doCanJump(ay, len, 0, ret);
	return ret;
}

void B_CanJump()
{
	int ay[5] = {3,2,1,0,4};
	cout << canJump(ay, 5);
}



//B.21 Edit Distance
int minDistance(string word1, string word2)
{
	// prepare table
	int **table = new int*[word1.size() + 1];
	for(int i = 0; i < word1.size() + 1; i++)
		table[i] = new int[word2.size() + 1];

	// base case
	for(int i = 0; i < word2.size() + 1; i++)
		table[0][i] = i;
	for(int i = 0; i < word1.size() + 1; i++)
		table[i][0] = i;

	// normal case
	for(int i = 1; i < word1.size() + 1; i++)
		for(int j = 1; j < word2.size() + 1; j++)
		{
			int x;
			if(word1[i - 1] == word2[j - 1])
			    x = 0;
			else
				x = 1;
			table[i][j] = minimum3(1 + table[i - 1][j], 1 + table[i][j - 1], x + table[i-1][j-1]);
		}
	int dis = table[word1.size()][word2.size()];

	showMatrixInt(table, word1.size() + 1, word2.size() + 1);

	// delete table
	for(int i = 0; i < word1.size() + 1; i++)
	{
		delete[] table[i];
	}
	delete[] table;


	return dis;

}

int minimum3(int x, int y, int z)
{
	if(x<y && x<z)
		return x;
	else if(y<x && y <z)
		return y;
	else
		return z;
}

void B_minDistance()
{
    string str1 = "sailn";
    string str2 = "failing";

    cout <<  minDistance(str1, str2);
}

//B.10 Unique Path
int uniquePaths(int m, int n)
{
	int **table = new int*[m];
	for(int i = 0; i < m; i++)
		table[i] = new int[n];

	//base case
	for(int i = 0; i < m; i++)
		table[i][n - 1] = 1;
	for(int i = 0; i < n; i++)
		table[m - 1][i] = 1;

	//normal case
	for(int i = m - 2; i >= 0; i--)
		for(int j = n - 2; j >= 0; j--)
			table[i][j] = table[i + 1][j] + table[i][j + 1];

	int paths = table[0][0];

	// delete table
	for(int i = 0; i < m; i++)
		delete[] table[i];
	delete[] table;

	return paths;
}

void B_UniquePaths()
{
	int m = 3;
	int n = 7;
	cout << uniquePaths(3, 7);
}


/*************************************************************************
 * 						Part C										    *
 *************************************************************************/
//C.1 Binary Tree
vector<vector<int> > levelOrder(TreeNode *root)
{
	queue<TreeNode*> que;
	que.push(root);
	que.push(NULL);
	vector<int> vec;
	vector<vector<int> > vecs;

	while(!que.empty())
	{
		TreeNode* current = que.front();
		que.pop();
		if(current == NULL)
		{
			vecs.push_back(vec);
			vec.clear();
			if(que.empty())
				break;
			que.push(NULL);
			continue;
		}

		vec.push_back(current->val);
		if(current->left)
			que.push(current->left);
		if(current->right)
			que.push(current->right);
	}

	return vecs;
}

void C_levelOrder()
{
	int ay[] = {1, 3, 5, 7, 9, 10};
	TreeNode* root = buildBST(ay, 0, 5);
	showBST(root);
	vector<vector<int> > vecs = levelOrder(root);
	for(int i = 0; i < vecs.size(); i++)
		showVecInt(vecs[i]);
}

//C.2 Binary Tree Zigzag Level Order Traversal
vector<vector<int> > zigzagLevelOrder(TreeNode *root)
{
	queue<TreeNode*> que;
	stack<TreeNode*> stk;
	que.push(root);
	que.push(NULL);
	bool leftToRight = true;
	vector<int> vec;
	vector<vector<int> > vecs;

	while(!que.empty())
	{
		TreeNode* current = que.front();
		que.pop();
		if(current == NULL)
		{
			while(!stk.empty())
			{
				que.push(stk.top());
				stk.pop();
			}
			leftToRight = leftToRight == true ? false : true;
			vecs.push_back(vec);
			vec.clear();
			if(que.empty())
				break;
			que.push(NULL);
			continue;
		}

		vec.push_back(current->val);

		if(leftToRight)
		{
			if(current->left)
				stk.push(current->left);
			if(current->right)
				stk.push(current->right);
		}
		else
		{
			if(current->right)
				stk.push(current->right);
			if(current->left)
				stk.push(current->left);
		}
	}

	return vecs;
}

void C_ZigzagLevelOrder()
{
	int ay[] = {1, 3, 5, 7, 9, 10, 11, 12, 13, 14, 15};
	TreeNode* root = buildBST(ay, 0, 10);
	showBST(root);
	vector<vector<int> > vecs = zigzagLevelOrder(root);
	for(int i = 0; i < vecs.size(); i++)
		showVecInt(vecs[i]);
}

//C.3 Maximum Depth of Binary Tree
int maxDepth(TreeNode *root)
{
	if(root == NULL)
		return 0;
	int leftDepth = maxDepth(root->left);
	int rightDepth = maxDepth(root->right);
	if(leftDepth > rightDepth)
		return leftDepth + 1;
	else
		return rightDepth + 1;
}

void C_MaxDepth()
{
	int ay[] = {1, 3, 5, 7, 9, 10, 11, 12, 13, 14, 15};
	TreeNode* root = buildBST(ay, 0, 10);
	showBST(root);
	cout << "Max Depth: " << maxDepth(root);
}

//C.4 Construct Binary Tree from Preorder and Inorder Traversal
int findPos(vector<int> &vec, int beg, int end, int target)
{
	for(int i = beg; i <= end; i++)
		if(vec[i] == target)
			return i;
	return -1;
}
TreeNode *doBuildTree(vector<int> &preorder, int beg1, int end1, vector<int> &inorder, int beg2, int end2)
{
	if(beg1 > end1 || beg2 > end2)
		return NULL;

	TreeNode *newNode = new TreeNode(preorder[beg1]);
	int pos = findPos(inorder, beg2, end2, preorder[beg1]);
	int leftLen = pos - beg2;
	newNode->left = doBuildTree(preorder, beg1 + 1, beg1 + leftLen, inorder, beg2, pos - 1);
	newNode->right = doBuildTree(preorder, beg1 + leftLen + 1, end1, inorder, pos + 1, end2);
	return newNode;
}
TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
{
	return doBuildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
}

void C_BuildTree()
{
	int pre[] = {5,1,3,9,7,10};
	int in[] = {1,3,5,7,9,10};
	vector<int> preVec(pre, pre + 6);
	vector<int> inVec(in, in + 6);

	TreeNode *root = buildTree(preVec, inVec);
	showBST(root);
}

//C.5 Construct Binary Tree from Postorder and Inorder Traversal
TreeNode *doBuildTree2(vector<int> &postorder, int beg1, int end1, vector<int> &inorder, int beg2, int end2)
{
	if(beg1 > end1 || beg2 > end2)
		return NULL;

	TreeNode *newNode = new TreeNode(postorder[end1]);
	int pos = findPos(inorder, beg2, end2, postorder[end1]);
	int leftLen = pos - beg2;
	newNode->left = doBuildTree2(postorder, beg1, beg1 + leftLen - 1, inorder, beg2, pos - 1);
	newNode->right = doBuildTree2(postorder, beg1 + leftLen, end1 - 1, inorder, pos + 1, end2);
	return newNode;
}
TreeNode *buildTree2(vector<int> &postorder, vector<int> &inorder)
{
	return doBuildTree2(postorder, 0, postorder.size() - 1, inorder, 0, inorder.size() - 1);
}

void C_BuildTree2()
{
	int post[] = {3,1,7,10,9,5};
	int in[] = {1,3,5,7,9,10};
	vector<int> postVec(post, post + 6);
	vector<int> inVec(in, in + 6);

	TreeNode *root = buildTree2(postVec, inVec);
	showBST(root);
}

//C.7 Convert Sorted Array to Binary Search Tree
TreeNode* doSortedArrayToBST(vector<int> &num, int beg, int end)
{
	if(beg > end)
		return NULL;

	int mid = (beg + end)/2;
	TreeNode *newNode = new TreeNode(num[mid]);
	newNode->val = num[mid];
	newNode->left = doSortedArrayToBST(num, beg, mid - 1);
	newNode->right = doSortedArrayToBST(num, mid + 1, end);
	return newNode;
}
TreeNode* sortedArrayToBST(vector<int> &num)
{
	return doSortedArrayToBST(num, 0, num.size() - 1);
}

void C_SortedArrayToBST()
{
	int ay[] = {1, 3, 5, 7, 9, 10};
	vector<int> vec(ay, ay + 6);
	TreeNode* root = sortedArrayToBST(vec);
	showBST(root);
}

//C.14 Distinct Subsequence
void doNumDistinct(string S, string T, int ixS, int ixT, int &count, map<char, vector<int> > &mp)
{
	if(ixT == T.size())
	{
		count++;
		return;
	}

	vector<int> vec;
	vec = mp[T[ixT]];
	for(int i = 0; i < vec.size(); i++)
	{
		if(vec[i] >= ixS)
		{
			doNumDistinct(S, T, vec[i] + 1, ixT + 1, count, mp);
		}
	}
}

int numDistinct(string S, string T)
{
	map<char, vector<int> > mp;
	for(int i = 0; i < T.size(); i++)
	{
		if(mp.find(T[i]) == mp.end())
		{
			vector<int> vec;
			for(int j = 0; j < S.size(); j++)
			{
				if(S[j] == T[i])
					vec.push_back(j);
			}
			mp.insert(pair<char, vector<int> >(T[i], vec));
		}
	}

	int count = 0;

	doNumDistinct(S, T, 0, 0, count, mp);

	return count;
}

void C_numDistinct()
{
	string S = "aabbcabc";
	string T = "abc";

	cout << numDistinct(S, T);
}


//C.17 Pascal's Triangle
vector<vector<int> > pascalTriangle(int numRows)
{
	vector<vector<int> > vecs;
	vector<int> vec;
	vec.push_back(1);
	vecs.push_back(vec);

	for(int i = 0; i < numRows - 1; i++)
	{
		vector<int> v;
		v.push_back(1);
		vector<int> last = vecs[vecs.size() - 1];
		for(int j = 0; j < last.size() - 1; j++)
		{
			v.push_back(last[j] + last[j + 1]);
		}
		v.push_back(1);
		vecs.push_back(v);
	}

	return vecs;
}

void C_PascalTriangle()
{
	vector<vector<int> > vecs = pascalTriangle(5);
	for(int i = 0; i < vecs.size(); i++)
	{
		for(int j = 0; j < vecs[i].size(); j++)
		{
			cout << vecs[i][j] << " ";
		}
		cout << endl;
	}
}

//C.19 Triangle
void doMinimumTotal(vector<vector<int> > &triangle, int level, int ix, int count, int &min)
{
	if(level == triangle.size())
	{
		if(count < min)
			min = count;
		return;
	}

	doMinimumTotal(triangle, level + 1, ix, count + triangle[level][ix], min);
	doMinimumTotal(triangle, level + 1, ix + 1, count + triangle[level][ix], min);
}

int minimumTotal(vector<vector<int> > &triangle)
{
	int min = 100;
	int count = 0;
	doMinimumTotal(triangle, 0, 0, count, min);
	return min;
}

void C_MinimumTotal()
{
	vector<vector<int> > vecs;
	vector<int> vec0;
	vec0.push_back(2);
	vector<int> vec1;
	vec1.push_back(3);
	vec1.push_back(4);
	vector<int> vec2;
	vec2.push_back(6);
	vec2.push_back(5);
	vec2.push_back(7);
	vector<int> vec3;
	vec3.push_back(4);
	vec3.push_back(1);
	vec3.push_back(8);
	vec3.push_back(3);

	vecs.push_back(vec0);
	vecs.push_back(vec1);
	vecs.push_back(vec2);
	vecs.push_back(vec3);

	cout << minimumTotal(vecs);

}

//C.23 Valid Palindrome
bool isAlpha(char c)
{
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return true;
	else
		return false;
}

bool sameAlpha(char a, char b)
{
	if(a == b || abs(a - b) == abs('A' - 'a'))
		return true;
	else
		return false;
}
bool isPalindrome(string s)
{
	if(s.size() == 0)
		return true;

	int i = 0;
	int j = s.size() - 1;

	while(i < j)
	{
		while(!isAlpha(s[i]))
			i++;
		while(!isAlpha(s[j]))
			j--;
		if(!sameAlpha(s[i], s[j]))
			return false;
		i++;
		j--;
	}

	return true;
}

void C_IsPalindrome()
{
	//string s = "A man, a plan, a canal: Panama";
	string s = "race a car";
	cout << isPalindrome(s);
}


//C.24 Word Ladder
bool diffOne(string word1, string word2)
{
	if(word1.size() != word2.size())
		return false;

	int count = 0;
	for(int i = 0; i < word1.size(); i++)
	{
		if(word1[i] != word2[i])
			count++;
	}

	return count == 1 ? true : false;
}

vector<string> findNeighbor(string current, vector<string> &dict)
{
	vector<string> vec;
	for(int i = 0; i < dict.size(); i++)
	{
		if(diffOne(dict[i], current))
				vec.push_back(dict[i]);
	}

	return vec;
}
void doLadderLength(string current, string last, string end, vector<string> &dict, int count, int &min)
{
	if(current == end)
	{
		if(count < min)
			min = count;
		return;
	}

	vector<string> vec = findNeighbor(current, dict);

	for(int i = 0; i < vec.size(); i++)
	{
		if(vec[i] != last)
		{
			doLadderLength(vec[i], current, end, dict, count + 1, min);
		}
	}
}

int ladderLength(string start, string end, vector<string> &dict)
{
	int count = 1;
	int min = 100;
	doLadderLength(start, "xxx", end, dict, 0, min);
	return min;

}

void C_WordLadder()
{
	string di[] = {"hot","dot","dog","lot","log"};
	vector<string> dict(di, di + 5);
	cout << ladderLength("hit", "cog", dict);
}

//C.28 Surrounded Region

void doWeiQi(vector<vector<char> > &board, bool **table, int row, int col, bool &border)
{
	if(border == false)
		board[row][col] = 'X';
	table[row][col] = true;

	//0. check if reach border
	if(row == 0 || col == 0 || row == board.size() - 1 || col == board[0].size() - 1)
		border = true;

	//1. go right
	if(col < board[0].size() - 1 && board[row][col + 1] == 'O')
		doWeiQi(board, table, row, col + 1, border);


	//2. go down
	if(row < board.size() - 1 && board[row + 1][col] == 'O')
		doWeiQi(board, table, row + 1, col, border);
	cout << 2 << endl;

	//3. go left
	if(col > 0 && board[row][col - 1] == 'O')
		doWeiQi(board, table, row, col - 1, border);
	cout << 3 << endl;

	//4. go up
	if(row > 0 && board[row - 1][col] == 'O')
		doWeiQi(board, table, row - 1, col, border);
	cout << 4 << endl;

	if(border == true)
		board[row][col] = 'O';
}


void weiQi(vector<vector<char> > &board)
{
	bool **table = new bool*[board.size()];
	for(int i = 0; i < board.size(); i++)
	{
		table[i] = new bool[board[0].size()];
		for(int j = 0; j < board[0].size(); j++)
			table[i][j] = false;
	}



	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
		{
			if(board[i][j] == 'O' && table[i][j] == false)
			{
				bool border = false;
				doWeiQi(board, table, i, j, border);
			}

		}
}


void C_WeiQi()
{
	vector<vector<char> > board;

	vector<char> vec0;
	vec0.push_back('X');
	vec0.push_back('X');
	vec0.push_back('X');
	vec0.push_back('X');
	vec0.push_back('X');
	vec0.push_back('X');

	vector<char> vec1;
	vec1.push_back('X');
	vec1.push_back('O');
	vec1.push_back('X');
	vec1.push_back('X');
	vec1.push_back('X');
	vec1.push_back('X');

	vector<char> vec2;
	vec2.push_back('X');
	vec2.push_back('O');
	vec2.push_back('O');
	vec2.push_back('O');
	vec2.push_back('O');
	vec2.push_back('X');

	vector<char> vec3;
	vec3.push_back('X');
	vec3.push_back('X');
	vec3.push_back('X');
	vec3.push_back('X');
	vec3.push_back('X');
	vec3.push_back('O');

	vector<char> vec4;
	vec4.push_back('X');
	vec4.push_back('O');
	vec4.push_back('X');
	vec4.push_back('X');
	vec4.push_back('O');
	vec4.push_back('O');

	vector<char> vec5;
	vec5.push_back('X');
	vec5.push_back('X');
	vec5.push_back('X');
	vec5.push_back('X');
	vec5.push_back('X');
	vec5.push_back('O');

	board.push_back(vec0);
	board.push_back(vec1);
	board.push_back(vec2);
	board.push_back(vec3);
	board.push_back(vec4);
	board.push_back(vec5);

	weiQi(board);

	showMatrixChar(board);

}


/*************************************************************************
 * 						Part D ( Other Questions )					    *
 *************************************************************************/

//D.1 Longest Increasing Subsequence
int longestIncreaseSub(vector<int> vec)
{
	vector<int> ref;
	ref.push_back(1);
	int maxmium = 1;

	for(int i = 1; i < vec.size(); i++)
	{
		int max = 0;
		for(int j = 0; j < i; j++)
		{
			if(vec[j] < vec[i] && ref[j] > max)
				max = ref[j];
		}
		ref.push_back(max + 1);
		if(max + 1 > maxmium)
			maxmium = max + 1;
	}

	return maxmium;
}

void D_LIS()
{

	int ay[] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
	vector<int> vec(ay, ay + 16);

	cout << longestIncreaseSub(vec);
}

//D.2 max non-adjecent subsequence
int maxSubsequence(vector<int> vec)
{
	int exPrev = vec[0];
	int inPrev  = vec[1];
	for(int i = 2; i < vec.size(); i++)
	{
		int newExPrev = max(exPrev, inPrev);
		int newInPrev = vec[i] + exPrev;
		exPrev = newExPrev;
		inPrev = newInPrev;
	}

	return max(inPrev, exPrev);
}

void D_maxSubsequence()
{
	int ay[] = {3, 2, 5, 10, 7};
	vector<int> vec(ay, ay + 5);

	cout << maxSubsequence(vec);
}
//////////////// TOOL ///////////////////////

void showVecInt(vector<int> &vec)
{
	vector<int>::iterator iter;
	for(iter = vec.begin(); iter != vec.end(); iter++)
		cout << *iter << " ";
	cout << endl;

}

void showVecString(vector<string> vec)
{
	vector<string>::iterator iter;
	for(iter = vec.begin(); iter != vec.end(); iter++)
		cout << *iter << " ";
	cout << endl;
}

void showMatrixInt(int **table, int row, int col)
{
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
			cout << table[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

void showMatrixChar(vector<vector<char> > &table)
{
	for(int i = 0; i < table.size(); i++)
	{
		for(int j = 0; j < table[0].size(); j++)
			cout << table[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

TreeNode* insertTreeNode(TreeNode* root, int x)
{
	if(root == NULL)
	{
		TreeNode *newNode = new TreeNode(x);
		return newNode;
	}

	if(x < root->val)
		root->left = insertTreeNode(root->left, x);
	else
		root->right = insertTreeNode(root->right, x);

	return root;
}

TreeNode* buildBST(int ay[], int beg, int end)
{
	if(beg > end)
		return NULL;

	int mid = (beg + end)/2;
	TreeNode *newNode = new TreeNode(ay[mid]);
	newNode->left = buildBST(ay, beg, mid - 1);
	newNode->right = buildBST(ay, mid + 1, end);
	return newNode;
}

void doShowBST(TreeNode *root, int level, bool right)
{
	if(root == NULL)
		return;

	for(int i = 0; i < level; i++)
		cout << "	";
	if(right)
		cout << "--R:";
	else
		cout << "--L:";
	cout << root->val << endl;
	doShowBST(root->right, level + 1, true);
	doShowBST(root->left, level + 1, false);
}

void showBST(TreeNode *root)
{
	doShowBST(root, 0, true);
}
