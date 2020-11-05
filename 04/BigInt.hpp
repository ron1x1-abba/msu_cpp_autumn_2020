#include <iostream>
#include <string>

class BigInt {
	char* _data;
	size_t size;
	bool minus;
public:
	BigInt(); //+
	BigInt(const std::string& str); //+
	BigInt(const int& a); //+
	BigInt(const BigInt& a); //+
	~BigInt(); //+
	BigInt operator+(const BigInt& a);//+
	BigInt operator+(const BigInt& a) const;
	BigInt operator*(const BigInt& a);
	BigInt operator*(const BigInt& a) const;
	BigInt operator-(const BigInt& a);//+
	BigInt operator-(const BigInt& a) const;
	BigInt operator-() const;//+
	BigInt& operator=(const BigInt& a); //+
	bool operator<(const BigInt& a) const;//+
	bool operator<=(const BigInt& a) const;//+
	bool operator>(const BigInt& a) const;//+
	bool operator>=(const BigInt& a) const;//+
	bool operator==(const BigInt& a) const;//+
	bool operator!=(const BigInt& a) const;//+
	size_t len() const;//+
	//moving constructor
	friend std::ostream& operator<<(std::ostream& s, const BigInt& a); //+
private:
	void SearchZero(BigInt& a);
};
