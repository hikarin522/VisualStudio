// C_spirit.cpp
// hikari

#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace phoenix = boost::phoenix;
namespace spirit = boost::spirit;
namespace qi = boost::spirit::qi;

template<typename Iterator>
struct pars : qi::grammar<Iterator, int()>
{
	qi::rule<Iterator, int(), qi::locals<std::priority_queue<int>>> start;
	pars() : pars::base_type(start)
	{
		using phoenix::push_back;
		using phoenix::at_c;
		using namespace qi::labels;

		start = +('[' >> qi::int_[push_back(_val, _1)] >> ']')
			| +('[' >> start[push_back(at_c<0>(_val), _1)] >> ']');
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
		constituency tree;
		qi::parse(it, str.end(), p, tree);
		std::cout << boost::apply_visitor(calculator(), tree) << std::endl;
	}

	return 0;
}
