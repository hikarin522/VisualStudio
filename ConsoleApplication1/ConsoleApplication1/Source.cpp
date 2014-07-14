// C_spirit.cpp
// hikari

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

#define BOOST_RESULT_OF_USE_DECLTYPE
#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/foreach.hpp>

namespace phoenix = boost::phoenix;
namespace spirit = boost::spirit;
namespace qi = boost::spirit::qi;

template<typename Iterator>
struct pars : qi::grammar<Iterator, int()>
{
	typedef std::priority_queue<int, std::vector<int>, std::greater<int>> que;
	qi::rule<Iterator, int()> first;
	qi::rule<Iterator, que()>  mid;
	qi::rule<Iterator, int()> start;

	pars() : pars::base_type(start)
	{
		using namespace qi::labels;

		first = '[' >> qi::int_[_val = (_1 + 1) / 2] >> ']';

		mid = +first[[](que &q, int &i) {q.push(i); }]
								   | +('[' >> start[phoenix::bind(&set_que,
								   spirit::_val,
								   spirit::_1)]
								   >> ']');
			

		start = mid[_val = (phoenix::bind(&que_front,
			spirit::_1))
		];
	}

	static void set_que(que &q, int &i)
	{
			q.push(i);
	}

	static int que_front(que &q)
	{
		return q.top();
	}

};

int main()
{
	int n;
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		std::string str;
		std::cin >> str;

		auto it = str.begin();
		pars<decltype(it)> p;
		int tree;
		qi::parse(it, str.end(), p, tree);
		std::cout << tree << std::endl;
	}

	return 0;
}

