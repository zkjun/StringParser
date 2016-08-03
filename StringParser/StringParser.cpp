// streamreadwrite1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <io.h>
#include "streamreadwrite1.h"
using namespace std;


//int main()
//{
//	filebuf buffer;
//	ostream output(&buffer);
//	istream input(&buffer);
//
//	buffer.open("example.dat", ios::in | ios::out | ios::trunc);
//
//	for (int i = 1; i <= 100; i++) {
//		output << i << ". line" << endl;
//
//		input.seekg(0);
//		char c;
//
//		while (input.get(c)) {
//			cout.put(c);
//		}
//		cout << endl;
//		input.clear();
//	}
//    return 0;
//}

int main()
{
	_finddata_t file;
	int k;
	long HANDLE;
	k = HANDLE = _findfirst("D:\\com\\*.cpp", &file);

	while (k != -1)
	{
		cout << file.name << endl;

		string line;
		vector<string> lines;
		int chartoken = 0;
		string comment;

		string soucrFile = "D:\\com\\" + (string)file.name;
		string destFile = "F:\\com\\" + (string)file.name;
		ifstream infile(soucrFile);
		ofstream outfile(destFile);

		string fileName = (string)file.name;
		int cpp = fileName.rfind(".cpp");
		string className = fileName.substr(0, cpp);
		className += "::";

		if (infile.is_open())
		{
			while (getline(infile, line))
			{
				string text;
				int s = line.rfind(className);
				if (s != string::npos)
				{
					s = line.rfind("(");
					if (s != string::npos)
					{
						text = line.substr(0, s);
						s = text.rfind(" ");
						if (s != string::npos)
						{
							comment = text.substr(s + 1, text.length());
						}
						else
						{
							comment = text;
						}
					}
				}

				int jni = line.rfind("JNIEXPORT");
				if (jni != string::npos)
				{
					s = line.rfind("(");
					if (s != string::npos)
					{
						text = line.substr(0, s);
					}
					else
					{
						text = line;
						s = text.find_last_of("_");
						string prex;
						string nextv;
						string nextv1;
						if (s != string::npos)
						{
							prex = text.substr(0, s);
							nextv = text.substr(s, text.length());
							s = prex.find_last_of("_");
							if (s != string::npos)
							{
								nextv1 = prex.substr(s + 1, prex.length());
							}
							else
							{
								nextv1 = prex;
							}

							comment = nextv1 + nextv;
						}
					}
				}


				int oldComment = line.rfind("_YJCBService->DebougOutPut");
				if (oldComment == string::npos)
				{
					lines.push_back(line);
				}

				int first = line.find_first_of("{");
				if (first != string::npos) {
					++chartoken;
					if (chartoken == 1) {
						string co = "\t_YJCBService->DebougOutPut(_T(\"";
						co += comment;
						co += "\"),__LINE__);";
						lines.push_back(co);
					}
				}
				int last = line.find_first_of("}");
				if (last != string::npos) {
					--chartoken;
				}
				//cout << line << endl;
			}
			infile.close();
		}

		if (outfile.is_open())
		{
			for (vector<string>::const_iterator iter = lines.begin(); iter != lines.end(); ++iter) {
				//cout << *iter << endl; // print each element in text
				outfile << *iter << endl;
			}
			outfile.close();
		}
		k = _findnext(HANDLE, &file);
	}
	_findclose(HANDLE);
	return 0;
}

