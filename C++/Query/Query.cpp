/*
 * =====================================================================================
 *
 *       Filename:  TextQuery.cpp
 *
 *    Description:  to implement c++ prime the text query revisited
 *
 *        Version:  1.0
 *        Created:  2012年09月10日 18时14分52秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yuan DaXing (http://goo.gl/VpwzO), mryuan0@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>
#include "TextQuery.h"

class Query;
class WordQuery;
class OrQuery;
class AndQuery;

//Query class could be replace by shared_ptr<Query_base> 
class Query_base {
		friend class Query;
	protected:
		typedef TextQuery::line_no line_no;
		virtual ~Query_base() { };
	private:
		virtual std::set<line_no> 
			eval(const TextQuery&) const = 0;
		virtual std::ostream&
			display(std::ostream& out = std::cout) const = 0;
};

//Handler Class to to hold everything
class Query {
		friend Query operator~(const Query& ) ;
		friend Query operator|(const Query& , const Query& ) ;
		friend Query operator&(const Query& , const Query& ) ;
	public:
		Query(const std::string& );
		Query(const Query & );
		~Query() { decr_use(); }
		Query& operator=(const Query& );
		std::set<TextQuery::line_no>
			eval(const TextQuery &t) const {
				return q->eval(t);
			}
		std::ostream& display(std::ostream &os) const {
			return q->display(os);
		}

	private:
		Query(Query_base *query) :
			q(query), use(new std::size_t(1)){ }
		Query_base *q;
		std::size_t *use;
		void decr_use() {
			if( --*use == 0 )
			{
				delete q;
				delete use;
			}
		}
};
Query::Query(const Query& q ) : q(q.q),
   	use(q.use) {
		++*use;
}
inline Query& Query::operator=(const Query &rhs)
{
	++*rhs.use; 
	decr_use(); 
	q = rhs.q; 
	use = rhs.use; 
	return *this; 
}
inline std::ostream& operator<<( std::ostream& os, 
		const Query &q ) {
	return q.display(os);
}

class WordQuery: public Query_base {
	friend class Query;
	WordQuery(const std::string &s) : query_word(s) { }
	std::set<line_no> eval(const TextQuery &t) const {
		return t.run_query(query_word);
	}
	std::ostream& display(std::ostream& os) const {
		return os << query_word;
	}
	std::string query_word;
};

Query::Query(const std::string& s) :
	q(new WordQuery(s)), use(new std::size_t(1)) { }

class NotQuery : public Query_base {
	friend Query operator~(const Query& );
	NotQuery(const Query&q): query(q) { }
	std::set<line_no> eval(const TextQuery& ) const;
	std::ostream& display(std::ostream& out) const {
		return out << "~(" << query << ")";
	}
	const Query query;
};

class BinaryQuery: public Query_base {
	protected:
		BinaryQuery(const Query& lhs, const Query& rhs,
			   	const std::string& op): lhs_(lhs), rhs_(rhs),
		op_(op) { }
		std::ostream& display(std::ostream& os) const {
			return os << "(" << lhs_ << " " << op_
				<< " " << rhs_ << ")";
		}
		const Query lhs_, rhs_;
		const std::string op_;
};

class AndQuery: public BinaryQuery {
	friend Query operator&(const Query&, const Query&);
	AndQuery(const Query& l, const Query& r) :
		BinaryQuery(l, r, "&") { }
	std::set<line_no> eval(const TextQuery& ) const;
};

class OrQuery: public BinaryQuery {
	friend Query operator|(const Query&, const Query& );
	OrQuery(const Query& l, const Query& r):
		BinaryQuery(l, r, "|") { }
	std::set<line_no> eval(const TextQuery& ) const;
};

inline Query operator&(const Query& lhs, const Query& rhs) {
	return new AndQuery(lhs, rhs);
}
inline Query operator|(const Query& lhs, const Query& rhs) {
	return new OrQuery(lhs, rhs);
}
inline Query operator~(const Query& q) {
	return new NotQuery(q);
}

std::set<TextQuery::line_no>
OrQuery::eval(const TextQuery& tq) const {
	std::set<line_no> r = rhs_.eval(tq),
		l = lhs_.eval(tq);
	l.insert(r.begin(), r.end());
	return l;
}

std::set<TextQuery::line_no>
AndQuery::eval(const TextQuery& tq) const {
	std::set<line_no> l = lhs_.eval(tq),
		r = rhs_.eval(tq);
	std::set<line_no> ret;
	std::set_intersection(l.begin(), l.end(),
			r.begin(), r.end(),
			std::inserter(ret, ret.begin()));
	return ret;
}

std::set<TextQuery::line_no>
NotQuery::eval(const TextQuery& tq) const {
	std::set<TextQuery::line_no> v = query.eval(tq);
	std::set<line_no> ret;
	for( TextQuery::line_no n = 0 ; n != tq.size() ; n++ )
	{
		if( v.find(n) == v.end() )
		{
			ret.insert(n);
		}
	}
	return ret;
}

int main(int argc, char *argv[])
{
	std::string s1("the"), s2("Her"), s3("in");
	const std::string file("text.txt");;
	TextQuery tq;
	std::ifstream fin(file.c_str());
	tq.read_file(fin);
	Query q = Query(s1) & Query(s2) | Query(s3);
	std::set<TextQuery::line_no> set = q.eval(tq);
	typedef std::set<TextQuery::line_no>::iterator iter_stq;
	for( iter_stq iter= set.begin() ; iter != set.end() ; iter++ )
	{
		std::cout << tq.text_line(*iter) << std::endl;
	}
	return 0;
}
