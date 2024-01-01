#include <string>
#include <vector>

const int BASE = 10;

const int power_ten = [] {
    int pow = 0;
    int base = BASE;
    while (base != 1) {
        base /= 10;
        pow++;
    }
    return pow;
}();

void delete_leading_zeros(std::vector<int> &number) {
    int non_zero_elem = number.size() - 1;
    while (number[non_zero_elem] == 0) {
        if (non_zero_elem == 0) {
            number = {0};
            return;
        }
        non_zero_elem -= 1;
    }

    number.erase(((non_zero_elem + 1) < number.size()
                      ? number.begin() + non_zero_elem + 1
                      : number.end()),
                 number.end());
}

class bigint {
private:
    std::vector<int> number;

public:
    bigint() {
        number.push_back(0);
    }

    bigint(const unsigned int value) : bigint(std::to_string(value)) {
    }

    bigint(const std::string &value) {
        int i = value.length();
        while (i > 0) {
            std::string new_string = value.substr(std::max(i - power_ten, 0),
                                                  std::min(power_ten, i));
            number.push_back(std::stoi(new_string));
            i -= power_ten;
        }
        delete_leading_zeros(number);
    }

    [[nodiscard]] std::string to_string() const {
        std::string str;
        if (number.size() == 1 && number[0] == 0) {
            return "0";
        }
        for (size_t i = number.size(); i > 0; --i) {
            std::string tmp = std::to_string(number[i - 1]);
            if (tmp.length() != power_ten && i != number.size()) {
                std::string zeros = std::string(power_ten - tmp.length(), '0');
                zeros += tmp;
                tmp = zeros;
            }
            str += tmp;
        }
        return str;
    }

    explicit operator unsigned int() const {
        return std::stoi(to_string());
    }

    bigint operator+=(const bigint &x_original) {
        bigint result = x_original;
        std::size_t const res_size = result.number.size();
        std::size_t const this_size = this->number.size();
        result.number.resize(std::max(this_size, res_size));

        for (std::size_t i = 0; i < result.number.size(); i++) {
            if (this->number.size() > i) {
                result.number[i] += this->number[i];
            }
            if (result.number[i] >= BASE) {
                if (i == result.number.size() - 1) {
                    result.number.push_back(result.number[i] / BASE);
                    result.number[i] %= BASE;
                } else {
                    result.number[i + 1] += (result.number[i] / BASE);
                    result.number[i] %= BASE;
                }
            }
        }

        delete_leading_zeros(result.number);
        *this = result;
        return *this;
    }

    friend bigint operator+(bigint first, const bigint &second) {
        first += second;
        return first;
    }

    bigint operator++(int) & {
        auto copy = *this;
        *this += 1;
        return copy;
    }

    bigint &operator++() {
        *this = *this + 1;
        return *this;
    }

    bigint operator-=(const bigint &x_original) {
        bigint result = *this;
        std::size_t const x_orig_size = x_original.number.size();
        std::size_t const this_size = this->number.size();
        result.number.resize(std::max(this_size, x_orig_size));

        for (std::size_t i = 0; i < result.number.size(); i++) {
            if (i < x_orig_size) {
                result.number[i] -= x_original.number[i];
            }
            if (result.number[i] < 0) {
                result.number[i + 1] -= 1;
                result.number[i] += BASE;
            }
        }

        delete_leading_zeros(result.number);

        *this = result;
        return *this;
    }

    friend bigint operator-(bigint first, const bigint &second) {
        first -= second;
        return first;
    }

    bigint &operator--() {
        *this = *this - 1;
        return *this;
    }

    bigint operator--(int) & {
        auto copy = *this;
        *this -= 1;
        return copy;
    }

    friend std::ostream &operator<<(std::ostream &os, const bigint &b) {
        os << b.to_string();
        return os;
    }

    friend std::istream &operator>>(std::istream &is, bigint &b) {
        std::string input;
        is >> input;
        b = bigint(input);
        return is;
    }

    // befriend all operators
    friend bool operator==(const bigint &first, const bigint &second);

    friend bool operator!=(const bigint &first, const bigint &second);

    friend bool operator<=(const bigint &first, const bigint &second);

    friend bool operator<(const bigint &first, const bigint &second);

    friend bool operator>=(const bigint &first, const bigint &second);

    friend bool operator>(const bigint &first, const bigint &second);
};

// define all operators
bool operator==(const bigint &first, const bigint &second) {
    return first.number == second.number;
}

bool operator!=(const bigint &first, const bigint &second) {
    return first.number != second.number;
}

bool operator<(const bigint &first, const bigint &second) {
    if (first.number.size() > second.number.size()) {
        return false;
    } else if (first.number.size() == second.number.size()) {
        size_t i = first.number.size();
        while (i > 0 && first.number[i - 1] == second.number[i - 1]) {
            --i;
        }
        return first.number[i - 1] < second.number[i - 1];
    } else {
        return true;
    }
}

bool operator>(const bigint &first, const bigint &second) {
    return (second < first);
}

bool operator<=(const bigint &first, const bigint &second) {
    return first < second || first == second;
}

bool operator>=(const bigint &first, const bigint &second) {
    return first > second || first == second;
}
