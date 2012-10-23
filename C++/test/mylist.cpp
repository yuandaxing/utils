#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <stdint.h>

template <typename T>
class _list {
		private:
				class _node {
						public:
								_node *prev, *next;
								T data;
						public:
								_node(_node *pr, _node *nt, const T &d): prev(pr), 
										next(nt), data(d) {}

								//call placement new         
								_node(const T &d) { new (this)_node(NULL, NULL, d); }

								_node& _insert_after(_node &n) {
										if(next != NULL) {
												next->prev = &n;
										}

										n.next = next;
										n.prev = this;
										next = &n;
										return *this;
								} 

								_node & _insert_before(_node &n) {
										if(prev != NULL) {
												prev->next = &n;
										}

										n.next = this;
										n.prev = prev;
										prev = &n;

										return n;
								}

								void remove() {
										if(next != NULL)
												next->prev = prev;
										if(prev != NULL)
												prev->next = next;
								}

								friend std::ostream & operator<<(std::ostream &os, 
												const _node &n) {
										os << n.data;
										return os;
								}
				};

				typedef struct {
						_node *head;
						_node *tail;
				} head;

				head h;

		public:
				_list() { h.head = h.tail = NULL; }

				template <typename it>
						_list(it const begin, it const end) {
								new (this)_list();
								it start = begin;
								for(; start != end; ++start) {
										push_back(*start);
								}
						}

				_list(const _list &lst) {
						new (this)_list(lst.begin(), lst.end());
				}

				_list& push_back(const T &d) {
						_node *n = new _node(d);

						if(h.tail == NULL) {
								h.head = h.tail = n;
						} else {
								h.tail->_insert_after(*n);
								h.tail = n;
						}
						return *this;
				}

				_list& push_front(const T &d) {
						_node *n = new _node(d);

						if(h.head == NULL) {
								h.head = h.tail = n;
						} else {
								h.head->_insert_before(*n);
								h.head = n;
						}
						return *this;
				}

				friend std::ostream & operator<<(std::ostream &os, 
								const _list &lst) {
						_node *n = lst.h.head;

						while(n != NULL) {
								os << *n << " ";     
								n = n->next;     
						}
						return os;
				}

				~_list() {
						_node *n = h.head, *next = NULL;
						while(n != NULL) {
								next = n->next;
								delete n;        
								n = next;
						}
				}

				class iterator {
						private:
								_node *cur;
								iterator( _node *const n):cur(n){};
								friend class _list;
						public:
								iterator(const _list &hd): cur(hd.h.head) { };

								T& operator*() { return cur->data; }
								iterator& operator++() { 
										if(cur != NULL)
												cur = cur->next;
										return *this;
								} 

								iterator operator++(int) {
										iterator ret(*this);
										if(cur != NULL)
												cur = cur->next;
										return ret;
								}

								iterator& operator--() {
										if(cur != NULL)
												cur = cur->prev;
										return *this;
								}

								iterator operator--(int) {
										iterator ret(*this);
										if(cur != NULL)
												cur = cur->prev;
										return ret;
								}

								bool operator==(const iterator &iter) const {
										return cur == iter.cur;
								}

								bool operator!=(const iterator &iter) const {
										return !(*this == iter);
								}
				};

/*  			class const_iterator{
						private:
								_node const * cur;
						public:
				};*/

				const iterator begin() const {
						return iterator(*this);
				}


				const iterator end() const {
						return iterator(NULL);
				}               

				iterator remove(const iterator rem) {
						iterator iter(rem);

						if(rem == end()) {
								return iter;
						}

						++iter;
						_node *n = rem.cur;

						if(h.head == n) {
								h.head = h.head->next;
						}

						if(h.tail == n) {
								h.tail = h.tail->prev;
						}

						n->remove();
						delete n;
						
						return iter;
				}

				iterator remove(const iterator start, const iterator end) {
						iterator iter = start;
						while(iter != end) {
								iter = remove(iter);
						}

						return iter;
				}

				iterator find_if(const T &t) const {
						iterator iter(*this);
						for(iter = begin(); iter != end(); ++iter) {
								if(*iter == t)
										break;
						}
						return iter;
				}

				/*  template <class Predicate>
						iterator find_if(Predicate pred) const {
								iterator iter(*this);
								while(iter != end()) {
										if(pred(*iter) == true)
												return iter;
								}

								return iter;
						}*/

				//this function is just for check                
				bool check() const {
						_node *nf = h.head, *nb = h.tail;

						if(nf != NULL) {
								if(nf->prev != NULL || nb->next != NULL)
										return false;
						} 

						while(nf != nb) {
								if(nf->next->prev != nf)
										return false;
								nf = nf->next;
						}
						return true;
				}
};

template <typename iterator, typename predicate>
iterator find_if(iterator begin, iterator end, predicate pred) {
	while(begin != end) {
			if(pred(*begin) == true)
					return begin;
	}
	return end;
}

class test{
		private:
				std::string str;
		public:
				test(const char *s=""):str(s) {}
				test(const std::string &s): str(s) {}
				friend std::ostream & operator<<(std::ostream &os, 
								const test& t) {
						os << t.str;
						return os;
				}

				bool operator<(const test &t) const {
						return str < t.str;
				}

				bool operator==(const test &t) const {
						return str == t.str;
				}

				bool operator!=(const test &t) const {
						return !(*this == t);
				}
};
class functor{
		public:
				bool operator()(const test &t) const {
						return t < test("notgood");
				}
};

bool notGood(const std::string &str) {
	return str <= "notgood";
}
int main()
{

		typedef uint64_t type;


		type a[] = {0, 1, 2, 3, 4, 5, 6, 7};
		const int len = sizeof(a) / sizeof(a[0]);

		std::cout << "len:" << len << std::endl; 
		_list<type> lst1, lst2;

		_list<type> lst3(a, a+len);

		std::cout << lst3 << std::endl;

		assert(lst1.check() && lst2.check());

		for(int i = 0; i < len; i++) {
				lst1.push_back(a[i]);
				lst2.push_front(a[i]);
		}
		assert(lst1.check() && lst2.check());

		for(_list<type>::iterator cur = lst1.begin(); 
						cur != lst1.end();
						cur++) {
				std::cout << *cur << " ";
		}

		std::cout << std::endl;

		std::cout << lst1 << std::endl;
		std::cout << lst2 << std::endl;

		_list<type> lst4(lst3);

		std::cout << lst4 << std::endl;

		std::vector<type> ivec;
		std::list<type> ilst;
		for(type i = 0; i < 10; i++) {
				ivec.push_back(i);
				ilst.push_back(i);
		}
		_list<type> lst5(ivec.begin(), ivec.end());
		_list<type> lst6(ilst.begin(), ilst.end());

		std::cout << lst5 << std::endl;
		std::cout << "lst6:" << lst6 << std::endl;

		std::string strs[] = {"laoyu", "chenhui", "ydx", "zhucheng"};
		const int slen = sizeof(strs) / sizeof(strs[0]);
		_list<std::string> lstr(strs, strs+slen);
		std::cout << lstr << std::endl;

		const char *laoyu = "laoyu";
		const char *ydx = "ydx";
		_list<std::string>::iterator iters = lstr.find_if(laoyu);
		_list<std::string>::iterator itere = lstr.find_if(ydx);

		if(iters == lstr.end()) {
				std::cout << "could not find " << laoyu << std::endl;
		} else {
				std::cout << "find " << *iters << std::endl;
		}
		_list<std::string>::iterator notgood = find_if(lstr.begin(), 
						lstr.end(), notGood);
		std::cout << *notgood << "is less than not good" << std::endl;
		//lstr.remove(iter);
		lstr.remove(iters, itere);

		std::cout << "after remove " << laoyu 
				<< "we have " << lstr << std::endl;


		_list<test> lstest(strs, strs + slen);
		_list<test>::iterator iter = find_if(lstest.begin(), lstest.end(), functor()) ;

		std::cout << *iter << std::endl;

		return 0;
}
