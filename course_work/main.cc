#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <iomanip>

#include "simple_fractions/simple_fractions.h"

using namespace std;

const int WIDTH = 8;

void printTable(const vector<vector<SimpleFractions>> &matrix, vector<int> bazis) {
	cout << setw(WIDTH) << "\\"<<" |";
	for(int i=0; i<matrix[0].size(); ++i) {
		string str="X";
		if(i==0) {
			str = "1";
		} else {
			str+=i+'0';
		}
		cout << setw(WIDTH) << str<<" |";
	}
	cout << endl;
	bool flag = true;
	for(int rowIndex=0; rowIndex< matrix.size(); ++rowIndex) {
		auto &row = matrix[rowIndex];
		string str="X";
		if(bazis[rowIndex]>=0) {
			str+=bazis[rowIndex]+'0';
		} else {
			if(flag) {
				flag=false;
				str="Z";
			} else {
				str="M";
			}
		}
		cout << setw(WIDTH) << str << " |"; 
		for(int j =0; j<row.size(); ++j) {
			cout << setw(WIDTH)<< row[j] << " |";
		}
		cout << endl;
	}
	cout << endl;
}

void printTable(const vector<vector<SimpleFractions>> &matrix, vector<int> bazis, set<int> ignoredColumns, vector<SimpleFractions> CO, int selectedColumns, int selectedRows) {
	cout << setw(WIDTH) << "\\"<<" |";
	for(int i=0; i<matrix[0].size(); ++i) {
		if(ignoredColumns.count(i)) continue;
		string str="X";
		if(i==0) {
			str = "1";
		} else {
			str+=i+'0';
		}
		cout << setw(WIDTH) << str<<" |";
	}
	cout << setw(WIDTH) << "CO" << " |";
	cout << endl;
	bool flag = true;
	for(int rowIndex=0; rowIndex< matrix.size(); ++rowIndex) {
		auto &row = matrix[rowIndex];
		string str="X";
		if(bazis[rowIndex]>=0) {
			str+=bazis[rowIndex]+'0';
		} else {
			if(flag) {
				flag=false;
				str="Z";
			} else {
				str="M";
			}
		}
		cout << setw(WIDTH) << str << " |"; 
		for(int j =0; j<row.size(); ++j) {
			if(ignoredColumns.count(j)) continue;
			cout << setw(WIDTH)<< row[j] << " |";
		}
		if(CO[rowIndex] == 0) {
			cout << setw(WIDTH) << "-" << " |";
		}
		else {
			cout << setw(WIDTH) << CO[rowIndex] << " |";
		}
		if(rowIndex == selectedRows) {
			cout << "<--";
		}
		
		cout << endl;
	}
	for(int i=0; i<=matrix[0].size(); ++i) {
		if(selectedColumns+1 == i) {
			cout << setw(WIDTH) << "/|\\" << "  ";
			continue;
		}
		cout << setw(WIDTH) << " " << "  ";
	}
	cout << endl;
	for(int i=0; i<=matrix[0].size(); ++i) {
		if(selectedColumns+1 == i) {
			cout << setw(WIDTH) << "| " << "  ";
			continue;
		}
		cout << setw(WIDTH) << " " << "  ";
	}
	cout << endl;
	cout << endl;
}

vector<vector<SimpleFractions>> squareMethod(const vector<vector<SimpleFractions>> &matrix, int row, int col) {
	int n = matrix.size();
	int m = matrix[0].size();
	vector<vector<SimpleFractions>> nmatrix(n, vector<SimpleFractions>(m));
	for(int i=0; i<n; ++i) {
		if(i==row) {
			for(int j=0; j<m; ++j) {
				if(j==col) {
					nmatrix[i][j]=1;
					continue;
				}
				nmatrix[i][j] = matrix[i][j]/matrix[row][col];
			}
			continue;
		}
		for( int j=0; j<m; ++j) {
			if(j==col) {
				nmatrix[i][j] = 0;
				continue;
			}
			nmatrix[i][j] = matrix[i][j] - (matrix[i][col]*matrix[row][j])/matrix[row][col];
		}
	}
	return nmatrix;
}

vector<vector<SimpleFractions>> simplexMethod(vector<vector<SimpleFractions>> matrix, vector<int> &basiz, vector<bool> fakeCol) {
	int n = matrix.size();
	int m = matrix[0].size();
	
	bool flag=true;
	set<int> ignoredColumns;
	while(flag) {	
		
		int col=-1;
		for(int i=1; i<m; ++i) {
			if(ignoredColumns.count(i)>0) continue;
			if(SimpleFractions(0)>matrix[n-1][i] && (col==-1 || matrix[n-1][col]>matrix[n-1][i])) {
				col = i;
			}
		}
		
		if(col==-1) break;
		
		vector<SimpleFractions> CO(matrix.size());
		//SimpleFractions CO(0,1);
		int row = -1;
		
		for(int i=0; i<n; ++i) {
			if(basiz[i]>=0 && matrix[i][col]>0) {
				SimpleFractions val = matrix[i][0]/matrix[i][col];
				CO[i] = val;
				if(row ==-1 || CO[row] > val) {
					row = i;
				}
			}
		}
		if(row==-1) break;
		
		printTable(matrix, basiz, ignoredColumns, CO, col, row);
		
		vector<vector<SimpleFractions>> nmatrix = squareMethod(matrix, row, col);
		
		if(fakeCol[basiz[row]]) {
			ignoredColumns.insert(basiz[row]);
		}
		basiz[row]=col;
		
		matrix = nmatrix;
	}
	vector<vector<SimpleFractions>> nmatrix(n);
	for(int i=0; i<n; ++i) {
		for(int j=0; j<matrix[i].size(); ++j) {
			if(ignoredColumns.count(j)>0) {
				continue;
			}
			nmatrix[i].push_back(matrix[i][j]);
		}
	}
	return nmatrix;
}

vector<vector<SimpleFractions>> getInput(string filename) {
	vector<vector<SimpleFractions>> res;
	ifstream f(filename);
	string str;
	while(getline(f, str)) {
		vector<SimpleFractions> tmp;
		stringstream ss(str);
		SimpleFractions x;
		while(ss >> x) {
			tmp.push_back(x);
		}
		res.push_back(tmp);
	}
	
	return res;
}

int main(int argc, char *argv[]) {
	string filename = "../files/ZLP_1.txt";
	if(argc>1) {
		filename = argv[1];
	}
	vector<vector<SimpleFractions>> matrix = getInput(filename);
	cout << endl;
	for(auto &row: matrix) {
		for(auto &x: row) {
			cout << x << ";";
		}
		cout << '\n';
	}
	vector<SimpleFractions> zRow = matrix[0];
	for(int i=1; i<zRow.size(); ++i) {
		zRow[i] = -zRow[i];
	}
	matrix.erase(matrix.begin());
	
	const int Nbegin = matrix[0].size()-1;
	
	for(int row=0; row<matrix.size(); ++row) {
		matrix[row].insert(matrix[row].begin(), matrix[row].back());
		matrix[row].erase(matrix[row].begin()+matrix[row].size()-1);
	}
	
	vector<int> basiz(matrix.size(), -1);
	for(int column=0; column< matrix[0].size(); ++column) {
		int baza = -1;
		bool flag = true;
		for(int row=0; row<matrix.size(); ++row) {
			if(matrix[row][column] != 0 && matrix[row][column]!=1) {
				flag = false;
				break;
			} else {
				if(matrix[row][column]==1) {
					if(baza==-1) {
						baza=row;
					} else {
						flag=false;
						break;
					}
				}
			}
		}
		if(flag && baza >=0) {
			if(basiz[baza]==-1) {
				basiz[baza]=column;
			}
		}
	}
	
	vector<bool> fakeColumns(matrix[0].size(), false);
	
	vector<SimpleFractions> mTask(matrix[0].size());
	
	for(int i=0; i<basiz.size(); ++i) {
		if(basiz[i]!=-1) continue;
		for(int row=0; row<matrix.size(); ++row) {
			if(i==row) matrix[row].push_back(1);
			else matrix[row].push_back(0);
		}
		mTask.push_back(0);
		zRow.push_back(0);
		fakeColumns.push_back(true);
		for(int j=0; j<matrix[i].size()-1; ++j) {
			
			mTask[j] = mTask[j] - matrix[i][j];
		}
		basiz[i]=matrix[i].size()-1;
	}
	
	for(int i=0; i< matrix.size(); ++i) {
		if(basiz[i]>=0 && zRow[basiz[i]] != 0) {
			int index = basiz[i];
			for(int j=0; j< zRow.size(); ++j) {
				if(j==index) continue;
				zRow[j]=zRow[j]-matrix[i][j]*zRow[index];
			}
			zRow[index]=0;
			
		}
	}
	
	for(auto &x: basiz) {
		cout << x << endl;
	}
	basiz.push_back(-1);
	matrix.push_back(zRow);
	basiz.push_back(-1);
	matrix.push_back(mTask);
	
	
	printTable(matrix, basiz);
	
	matrix = simplexMethod(matrix, basiz, fakeColumns);
	
	bool flag=true;
	for(int i=0; i<fakeColumns.size(); ++i) {
		if(fakeColumns[i]) {
			for(int j=0; j<basiz.size(); ++j) {
				if(basiz[j]==i) {
					flag = false;
					break;
				}
			}
		}
	}
	
	for(auto &col: matrix.back()) {
		if(col != 0) {
			flag = false;
			break;
		}
	}
	
	printTable(matrix, basiz);
	
	if(flag) {
		cout << "Sovmestno" << endl;
		matrix.erase(matrix.begin()+matrix.size()-1);
		printTable(matrix, basiz);
		matrix = simplexMethod(matrix, basiz, fakeColumns);
		printTable(matrix, basiz);
		int mnoga = -1;
		for(int i=1; i<matrix[0].size(); ++i) {
			if(matrix.back()[i] < 0) {
				flag = false;
				break;
			} else if(matrix.back()[i]==0) {
				bool inbasiz = false;
				for(auto &x: basiz) {
					if(x == i) {
						inbasiz=true;
						break;
					}
				}
				if(!inbasiz) {
					mnoga = i;
				}
			}
		}
		
		
		if(flag) {
			cout << "Sovmestno!" << endl;
			if(mnoga>=0) {
				cout << "Neskolko resheniy" << endl;
				cout << "X1=(";
			} else cout << "X=(";
			vector<SimpleFractions> XSol(Nbegin);
			for(int i=0; i<basiz.size(); ++i) {
				if(basiz[i]>=0 && basiz[i]<=Nbegin) {
					XSol[basiz[i]-1] = matrix[i][0];
				}
			}
			for(int i=0; i<XSol.size(); ++i) {
				cout << XSol[i];
				if(i==XSol.size()-1) continue;
				cout << ";";
			}
			cout <<")"<<endl;
			if(mnoga>=0) {
				int colIndex = mnoga;
				int rowIndex = -1;
				vector<SimpleFractions> CO(matrix.size());
				for(int i=0; i<matrix.size()-1; ++i) {
					if(matrix[i][colIndex] > 0) {
						CO[i]=matrix[i][0]/matrix[i][colIndex];
						if(rowIndex == -1 || CO[rowIndex] > CO[i]) {
							rowIndex = i;
						}
					}
				}
				printTable(matrix, basiz, {}, CO, colIndex, rowIndex);
				basiz[rowIndex]=colIndex;
				matrix = squareMethod(matrix, rowIndex, colIndex);
				printTable(matrix, basiz);
				vector<SimpleFractions> XSol2(Nbegin);
				cout << "X2=(";
				for(int i=0; i<basiz.size(); ++i) {
					if(basiz[i]>=0 && basiz[i]<=Nbegin) {
						XSol2[basiz[i]-1] = matrix[i][0];
					}
				}
				for(int i=0; i<XSol2.size(); ++i) {
					cout << XSol2[i];
					if(i==XSol.size()-1) continue;
					cout << ";";
				}
				cout <<")"<<endl;
				cout << "X=(";
				for(int i=0; i<Nbegin; ++i) {
					cout << XSol[i];
					SimpleFractions val = XSol2[i]-XSol[i];
					if(val>0) cout<<" + ";
					else if(val<0) cout << " - ";
					if(val != 0) cout << val.ABS_sf() << "L";
					if(i==XSol.size()-1) continue;
					cout << ";";
				}
				cout <<")"<<endl;
			}
			cout << "Z(X)="<<matrix.back()[0] << endl;
			
		} else {
			cout << "Ne ogranichena	" << endl;
		}
	} else {
		cout << "Ne sovmestno" << endl;
	}
	
	return 0;
}

