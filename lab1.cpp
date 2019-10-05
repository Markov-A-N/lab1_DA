#include <iostream>
#include <cassert>
#include <algorithm>

const int SIZE = 65;

struct TKeyValue {
	unsigned int key;
	char value[SIZE];
	TKeyValue();
	TKeyValue(int i, char *str);
	void Fill(char ch = '\0');
	TKeyValue &operator=(TKeyValue &other);
	friend std::istream &operator>>(std::istream &in, TKeyValue &obj);
	friend std::ostream &operator<<(std::ostream &out, TKeyValue &obj);
};

TKeyValue::TKeyValue() {
	key = 0;
	Fill();
}

TKeyValue::TKeyValue(int i, char *str) {
	key = i;
	Fill();
	for (register unsigned int i = 0; i < sizeof(str) / sizeof(char); i++) {
		value[i] = str[i];
	}
}

void TKeyValue::Fill(char ch) {
	for (register unsigned int i = 0; i < sizeof(value) / sizeof(char); i++) {
		value[i] = ch;
	}
}

TKeyValue &TKeyValue::operator=(TKeyValue &other) {
	this->Fill();
	key = other.key;
	for (register unsigned int i = 0; i < sizeof(other.value) / sizeof(char); i++) {
		value[i] = other.value[i];
	}

	return *this;
}

std::istream &operator>>(std::istream &in, TKeyValue &obj) {
	in >> obj.key >> obj.value;

	return in;
}

std::ostream &operator<<(std::ostream &out, TKeyValue &obj) {
	out << obj.key << "\t" << obj.value << "\n";

	return out;
}

template <typename T> class TVector {
public:
	using TValue_type = T;
	using TIterator = TValue_type *;
	TVector();
	TVector(unsigned int size);
	unsigned int Size() const;
	bool Empty() const;
	TIterator Begin() const;
	TIterator End() const;
	template <typename U> friend void Swap(TVector<U> &first, TVector<U> &second);
	TVector &operator=(TVector other);
	~TVector();
	TValue_type &operator[](int index) const;
	void PushBack(TValue_type &value);
	template <typename U> friend TVector<U> CountingSort(const TVector<U> &inputVector, unsigned int max);
private:
	int storageSize;
	int already_used_;
	TValue_type *storage;
};

template <typename T> TVector<T>::TVector() {
	storageSize = already_used_ = 0;
	storage = nullptr;
}

template <typename T> TVector<T>::TVector(unsigned int size) : TVector() {
	assert(size >= 0);

	if (size == 0) {
		return;
	}
	storageSize = already_used_ = size;
	storage = new typename TVector<T>::TValue_type[size];
}

template <typename T> unsigned int TVector<T>::Size() const {
	return already_used_;
}

template <typename T> bool TVector<T>::Empty() const {
	return Size() == 0;
}

template <typename T> typename TVector<T>::TIterator TVector<T>::Begin() const {
	return storage;
}

template <typename T> typename TVector<T>::TIterator TVector<T>::End() const {
	if (storage) {
		return storage + already_used_;
	}
	return nullptr;
}

template <typename U> void Swap(TVector<U> &first, TVector<U> &second) {
	using std::swap;

	swap(first.already_used_, second.already_used_);
	swap(first.storageSize, second.storageSize);
	swap(first.storage, second.storage);
}

template <typename T> TVector<T> &TVector<T>::operator=(TVector<T> other) {
	Swap(*this, other);

	return *this;
}

template <typename T> TVector<T>::~TVector() {
	already_used_ = storageSize = 0;
	delete[] storage;
	storage = nullptr;
}

template <typename T> typename TVector<T>::TValue_type &TVector<T>::operator[](int index) const {
	if (index < 0 || index > already_used_) {
		throw std::out_of_range("You are doing this wrong!");
	}

	return storage[index];
}

template <typename T> void TVector<T>::PushBack(TValue_type &value) {
	if (already_used_ < storageSize) {
		storage[already_used_] = value;
		++already_used_;
		return;
	}

	unsigned int next_size = 1;
	if (storage) {
		next_size = storageSize * 2;
	}

	TVector<T> next{next_size};
	next.already_used_ = already_used_;

	if (storage) {
		std::copy(storage, storage + storageSize, next.storage);
	}
	next.PushBack(value);
	Swap(*this, next);
}

template <typename U> TVector<U> CountingSort(const TVector<U> &inputVector, unsigned int max) {
	TVector<unsigned int> c{max + 1};
	for (register unsigned int i = 0; i <= max; i++) {
		c[i] = 0;
	}
	for (register unsigned int i = 0; i < inputVector.Size(); ++i) {
		++c[inputVector[i].key];
	}
	for (register unsigned int i = 1; i <= max; i++) {
		c[i] += c[i-1];
	}
	TVector<U> b{inputVector.Size()};
	for (register int i = inputVector.Size() - 1; i >= 0; i--) {
		b[--c[inputVector[i].key]] = inputVector[i];
	}

	return b;
}


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	TVector<TKeyValue> v;
	TKeyValue temp;

	unsigned int maxKey = 0;
	while(std::cin >> temp) {
		v.PushBack(temp);
		if (temp.key > maxKey) {
			maxKey = temp.key;
		}
		temp.Fill();
	}

	TVector<TKeyValue> res = CountingSort(v, maxKey);

	for (size_t i = 0; i < res.Size(); ++i) {
		std::cout << res[i];
	}

	return 0;
}