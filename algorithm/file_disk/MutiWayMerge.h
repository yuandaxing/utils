/*
 * =====================================================================================
 *
 *       Filename:  MutiWayMerge.h
 *
 *    Description: you must implement operator>>(ifstream &ifs, item &i)
 *    comparator(item &l, item &r); 
 *
 *        Version:  1.0
 *        Created:  2012年10月05日 14时55分35秒
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
#include <tr1/memory>
#include <queue>
#include <vector>
#include <string>

/* you must implement istream >> item compare item to use this
 * class */
template <typename ItemType, typename ItemCompare>
class MergeTask;

template <typename ItemType, typename ItemCompare>
class ElemFile {
	private:
		friend class MergeTask<ItemType, ItemCompare>;
		ItemType cur_;
		std::ifstream fin_;
		ItemCompare comp_;
	public:
		explicit ElemFile(const char *fname, 
				ItemCompare comp) : fin_(fname), comp_(comp){
				if(fin_)
					fin_ >> cur_;
		}
		
		bool read( ) {
			return fin_ >> cur_;
		}

		bool operator<(const ElemFile &ef) const {
			return comp_(cur_, ef.cur_);
		}
		bool valid() {
			return fin_;	
		}
};

template <typename ItemType, typename ItemCompare>
class FileComparator {
	public:
		typedef ElemFile<ItemType, ItemCompare> ElemType;
		bool operator()(const ElemType * lhs, const ElemType * rhs) const {
			//because the default priority compare is less
			return ((*lhs) < (*rhs));
		}
};
template <typename ItemType, typename ItemCompare>
class MergeTask {
	private:
		typedef ElemFile<ItemType, ItemCompare>  ElemType;
		typedef FileComparator<ItemType, ItemCompare> Comparator;
		typedef std::tr1::shared_ptr<ElemType> elemHolder;


		std::priority_queue<ElemType *, std::vector<ElemType *>, Comparator > fileHeap_;
		std::vector<elemHolder> ve_;
		std::ofstream fout;


	public:
		explicit MergeTask(const char *s) :
			fout(s) { };
		MergeTask(const char *out, const char **ins, const char **ine, 
				ItemCompare comp = ItemCompare()) : fout(out) {
				for(  ; ins < ine ; ins++ )
				{
					ElemType *ef = new ElemType(*ins, comp);
					if( !ef->valid() )
					{
						delete ef;
						continue;
					}
					ve_.push_back(elemHolder(ef));
					fileHeap_.push(ef);
				}
			}

		void doMerge() {
			while(!fileHeap_.empty() ) {
				ElemType *top = fileHeap_.top();
				fout << (top->cur_) << " ";
				fileHeap_.pop();
				if(top->read()) {
					fileHeap_.push(top);
				}
			}
		}
};
