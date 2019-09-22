#include <iostream>
#include <cassert>

struct key_value
{
	unsigned int key;
	char value[65];
	key_value();
	key_value(int i, char *str);
	void fill(char ch = '\0');
	key_value &operator=(key_value &other);
	friend std::istream &operator>>(std::istream &in, key_value &obj);
	friend std::ostream &operator<<(std::ostream &out, key_value &obj);
};

key_value::key_value()
{
	key = 0;
	fill();
}

key_value::key_value(int i, char *str)
{
	key = i;
	fill();
	for (register unsigned int i = 0; i < sizeof(str) / sizeof(char); i++)
	{
		value[i] = str[i];
	}
}

void key_value::fill(char ch)
{
	for (register unsigned int i = 0; i < sizeof(value) / sizeof(char); i++)
	{
		value[i] = ch;
	}
}

key_value &key_value::operator=(key_value &other)
{
	this->fill();
	for (register unsigned int i = 0; i < sizeof(other.value) / sizeof(char); i++)
		value[i] = other.value[i];

	return *this;
}

std::istream &operator>>(std::istream &in, key_value &obj)
{
	in >> obj.key >> obj.value;

	return in;
}

std::ostream &operator<<(std::ostream &out, key_value &obj)
{
	out << obj.key << "\t" << obj.value << "\n";

	return out;
}

template <typename T> class vector
{
public:
	using value_type = T;
	using iterator = value_type *;
	vector();
	vector(unsigned int size);
	unsigned int size() const;
	bool empty() const;
	iterator begin() const;
	iterator end() const;
	template <typename U> friend void swap(vector<U> &first, vector<U> &second);
	vector &operator=(vector other);
	~vector();
	value_type &operator[](int index) const;
	void push_back(value_type &value);
	value_type *copy(typename vector<T>::value_type *first, typename vector<T>::value_type *second, typename vector<T>::value_type *d_first);
	template <typename U> friend vector<U> counting_sort(const vector<U> &input_vector, unsigned int max);
private:
	int storage_size_;
	int already_used_;
	value_type *storage_;
};

template <typename T> vector<T>::vector()
{
	storage_size_ = already_used_ = 0;
	storage_ = nullptr;
}

template <typename T> vector<T>::vector(unsigned int size) : vector()
{
	assert(size >= 0);

	if (size == 0) return;

	storage_size_ = already_used_ = size;
	storage_ = new value_type[size];
}

template <typename T> unsigned int vector<T>::size() const
{
	return already_used_;
}

template <typename T> bool vector<T>::empty() const
{
	return size() == 0;
}

template <typename T> typename vector<T>::iterator vector<T>::begin() const
{
	return storage_;
}

template <typename T> typename vector<T>::iterator vector<T>::end() const
{
	if (storage_)
		return storage_ + already_used_;
	return nullptr;
}

template <typename U> void swap(vector<U> &first, vector<U> &second)
{
	int temp_already_used_ = first.already_used_;
	int temp_storage_size_ = first.storage_size_;
	typename vector<U>::value_type *temp_storage_ = first.storage_;

	first.already_used_ = second.already_used_;
	first.storage_size_ = second.storage_size_;
	first.storage_ = second.storage_;

	second.already_used_ = temp_already_used_;
	second.storage_size_ = temp_storage_size_;
	second.storage_ = temp_storage_;
}

template <typename T> vector<T> &vector<T>::operator=(vector<T> other)
{
	swap(*this, other);

	return *this;
}

template <typename T> vector<T>::~vector()
{
	already_used_ = storage_size_ = 0;
	delete[] storage_;
	storage_ = nullptr;
}

template <typename T> typename vector<T>::value_type &vector<T>::operator[](int index) const
{
	if (index < 0 || index > already_used_)
		throw std::out_of_range("You are doing this wrong!");

	return storage_[index];
}

template <typename T> void vector<T>::push_back(value_type &value)
{
	if (already_used_ < storage_size_)
	{
		storage_[already_used_] = value;
		++already_used_;
		return;
	}

	unsigned int next_size = 1;
	if (storage_) next_size = storage_size_ * 2;

	vector<T> next{next_size};
	next.already_used_ = already_used_;

	if (storage_)
		copy(storage_, storage_ + storage_size_, next.storage_);
	next.push_back(value);
	swap(*this, next);
}

template <typename T> typename vector<T>::value_type *vector<T>::copy(typename vector<T>::value_type *first, typename vector<T>::value_type *second, typename vector<T>::value_type *d_first)
{
	while (first != second) {
        *d_first++ = *first++;
    }
    return d_first;
}

template <typename U> vector<U> counting_sort(const vector<U> &input_vector, unsigned int max)
{
	vector<unsigned int> c{max};
	for (register unsigned int i = 0; i <= max; i++)
	{
		c[i] = 0;
	}
	for (register unsigned int i = 0; i < input_vector.size(); ++i)
	{
		++c[input_vector[i].key];
	}
	for (register unsigned int i = 1; i <= max; i++)
	{
		c[i] += c[i-1];
	}
	vector<U> b{input_vector.size()};
	for (register unsigned int i = input_vector.size(); i >= 0; i--)
	{
		b[--c[input_vector[i].key]] = input_vector[i];
	}

	return b;
}


int main()
{
	vector<key_value> v;
	key_value temp;

	unsigned int max_key = -1;
	while(std::cin >> temp)
	{
		v.push_back(temp);
		if (temp.key > max_key) max_key = temp.key;
		temp.fill();
	}

	vector<key_value> res = counting_sort(v, max_key);

	for (size_t i = 0; i < res.size(); ++i)
	{
		std::cout << res[i];
	}
	return 0;
}