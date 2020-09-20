#include <iostream>

namespace err {
enum bool Status { OK = true, ERROR = false };
enum int C_Status { OK = 0, ERROR = 1 };

template <typename T>
class Error {
private:
    std::optional<T> out;
    bool st;

public:
    Error(const bool &state, const T &output) : st(state), out(output) {}
    ~Error() {}
    T opperator() const {}
    const bool check_error() const { return st; }
}
}  // namespace err

