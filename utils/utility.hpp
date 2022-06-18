#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft {
	template<typename T>
	void swap(T & lhs, T & rhs) {
		T buf(rhs);
		rhs = lhs;
		lhs = buf;
	}

	// std::pair is a class template that provides a way to store two heterogeneous objects as a single unit.
	// A pair is a specific case of a std::tuple with two elements.
	template<class T1, class T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		pair() : first(), second() {}
		pair(first_type const &t1, second_type const &t2) : first(t1), second(t2) {}

		template<class U1, class U2>
		pair(ft::pair<U1, U2> const &p) : first(p.first), second(p.second) {} 
		pair &operator=(pair const& p) {
			this->first = p.first;
			this->second = p.second;
			return *this;
		}

		void swap(ft::pair<first_type, second_type> &p) {
			swap(this->first, p.first);
			swap(this->second, p.second);
		}
	};
	
	template<class T1, class T2>
	ft::pair<T1, T2> make_pair(T1 x, T2 y) {
		return pair<T1, T2>(x, y);
	}

	// std::integral_constant wraps a static constant of specified type. It is the base class for the C++ type traits.
	// The behavior of a program that adds specializations for integral_constant is undefined.
	// This template is designed to provide compile-time constants as types.
	template<typename T, T v>
    struct integral_constant {
        static const T                      value = v;
        typedef T                           value_type;
        typedef integral_constant<T, v>     type;
        operator value_type() const { return value; }
    };

	// const volatile object - an object whose type is const-volatile-qualified, a non-mutable subobject of a const volatile object, 
	// a const subobject of a volatile object, or a non-mutable volatile subobject of a const object. Behaves as both a const object and as a volatile object.
	template<typename> struct remove_cv;

    template<typename T> struct remove_const { typedef T	type; };

    template<typename T> struct remove_const<T const> { typedef T	type; };

	// Volatile is a C/C++ keyword that informs the compiler 
	// that the value of a variable can be changed from outside and that the compiler will not optimize that variable.
	//
	// (Volatile — ключевое слово языков C/C++, которое информирует компилятор о том, 
	// что значение переменной может меняться из вне и что компилятор не будет оптимизировать эту переменную).
    template<typename T> struct remove_volatile { typedef T	type; };

    template<typename T> struct remove_volatile<T volatile> { typedef T	type; };

    template<typename T>
	struct remove_cv {
		typedef typename
		remove_const<typename remove_volatile<T>::type>::type     type;
	};

	// The type used as a compile-time boolean with true value.
    typedef integral_constant<bool, true> true_type;

	// The type used as a compile-time boolean with false value.
    typedef integral_constant<bool, false> false_type;

	// If B is true, std::enable_if has a public member typedef type, equal to T; otherwise, there is no member typedef.
	// This metafunction is a convenient way to leverage SFINAE prior to C++20's concepts, in particular for conditionally 
	// removing functions from the candidate set based on type traits, allowing separate function overloads or specializations based on those different type traits.
	//
	// (Аббревиатура SFINAE расшифровывается как substitution failure is not an error и означает следующее: 
	// при определении перегрузок функции ошибочные инстанциации шаблонов не вызывают ошибку компиляции, 
	// а отбрасываются из списка кандидатов на наиболее подходящую перегрузку.)
    template<bool B, class T = void> struct enable_if {};

    template<class T> struct enable_if<true, T> { typedef T type; };

    template<typename> struct is_integral_helper : public false_type {};

    template<> struct is_integral_helper<bool> : public true_type {};

    template<> struct is_integral_helper<char> : public true_type {};

    template<> struct is_integral_helper<signed char> : public true_type {};

    template<> struct is_integral_helper<unsigned char> : public true_type {};

	#ifdef _GLIBCXX_USE_WCHAR_T
    template<> struct is_integral_helper<wchar_t>: public true_type { };
	#endif

    template<>
    struct is_integral_helper<char16_t> : public true_type {};

    template<> struct is_integral_helper<char32_t> : public true_type {};

    template<> struct is_integral_helper<short> : public true_type {};

    template<> struct is_integral_helper<unsigned short> : public true_type {};

    template<> struct is_integral_helper<int> : public true_type {};

    template<> struct is_integral_helper<unsigned int> : public true_type {};

    template<> struct is_integral_helper<long> : public true_type {};

    template<> struct is_integral_helper<unsigned long> : public true_type {};

    // template<> struct is_integral_helper<long long> : public true_type {};

    // template<> struct is_integral_helper<unsigned long long> : public true_type {};

	#if !defined(__STRICT_ANSI__) && defined(_GLIBCXX_USE_INT128)
    template<> struct is_integral_helper<__int128>: public true_type { };

    template<>  struct is_integral_helper<unsigned __int128>: public true_type { };
	#endif

	// Checks whether T is an integral type
    template<typename T> 
	struct is_integral : public integral_constant<bool, (is_integral_helper<typename ft::remove_cv<T>::type>::value)> {};
}

#endif
