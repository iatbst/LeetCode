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



/*************************************************************************
 * 						Part B										    *
 *************************************************************************/

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


//////////////// TOOL ///////////////////////

void showVecInt(vector<int> &vec)
{
	vector<int>::iterator iter;
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
