
#include <iostream>
#include <string>
#include <vector>
#include <boost/fusion/tuple.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

using namespace std;
using namespace boost;
using namespace boost::spirit;

//
// 例3: 少しちゃんとした例。数式を計算します
//	 文法定義
//	   expr ::= term ('+' term | '-' term)*
//	   term ::= fctr ('*' fctr | '/' fctr)*
//	   fctr ::= int | '(' expr ')'
//	 開始記号
//	   expr
//

template<typename Iterator>
struct calc : qi::grammar<Iterator, double(), ascii::space_type>
{
	qi::rule<Iterator, double(), ascii::space_type> expr, term, fctr;

	calc() : calc::base_type(expr)
	{
		expr = term[_val = _1] >> *(('+' >> term[_val += _1]) | ('-' >> term[expr.val -= _1]));
		term = fctr[_val = _1] >> *(('*' >> fctr[_val *= _1]) | ('/' >> fctr[_val /= _1]))[&Oops];
		fctr = double_ | '(' >> expr >> ')';
	}

	// 計算ついでに、* と / を見ると意味もなく Oops! と叫ぶコード
	static void Oops()
	{
		cout << "Oops!" << endl;
	}

};

int main()
{
	for (string str; getline(cin, str) && str.size() > 0;)
	{
		calc<string::iterator> c;
		double result = -1;

		auto it = str.begin();

		if (qi::phrase_parse(it, str.end(), c, ascii::space, result))
			cout << result << endl;
	}
}
