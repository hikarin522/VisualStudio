// Source.cpp
//hikari

#include <iostream>
#include <string>
#include <vector>

#include <boost/format.hpp>
#include <boost/version.hpp>

using namespace std;
using namespace boost;

int main(int argc, char *argv[], char *envp[])
{
	vector<string> args(argv, argv + argc);
	vector<string> envs(envp, [](char *i[]) {while (*++i); return i; }(envp));

	cout << format("hello boost : version %1%.%2%.%3%\n")
		% (BOOST_VERSION / 100000) % (BOOST_VERSION / 100 % 1000) % (BOOST_VERSION % 100) << endl;

	cout << "�R�}���h���C������" << endl;


	for (auto &i : args)
		cout << i << endl;
	
	cout << "\n���ϐ�" << endl;
	for (auto &i : envs)
		cout << i << endl;

	cout << "\n�����" << endl;
	return 0;
}
