#ifndef TESTING_HPP
# define TESTING_HPP

/* ------------------------------ Testing class ----------------------------- */
class Test {
	public:
		Test() : some_(0) { this->str_ = (char*)malloc(10); }

		Test(int s) : some_(s) { this->str_ = (char*)malloc(10); }

		Test(Test const & x) : some_(x.some_) { this->str_ = (char*)malloc(10); }

		~Test() {
			if (this->str_ != 0)
				free(this->str_);
			this->some_ = 0;
			this->str_  = 0;
		}

		Test &operator=(Test const & x) {
			if (this == &x)
				return (*this);
			this->str_ = (char*)malloc(10);
			this->some_ = x.some_;
			return (*this);
		}

		bool operator==(const Test & x) { return this->some_ == x.some_; }

		bool operator==(int & val) { return this->some_ == val; }

		int   some_;
		char* str_;
};
/* -------------------------------------------------------------------------- */

#endif
