
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

class Email {
private:
        std::string value;
        bool movedFrom{false};


public:
    Email(const std::string& v) : value(std::move(v)) {
        assert(value.find('@') != std::string::npos);
    }

    const std::string& getValue() const& {
        assert(!movedFrom);
        return value;
    }

    std::string getValue() && {
        assert(!movedFrom);
        return std::move(value);
    }

    std::string getDomain() const {
        assert(!movedFrom);
        return value.substr(value.find('@'));
    }

    //disable move semantics. This also disables backward mechanism in move semantics.
    //Email(Email&&) = delete;
    //Email& operator=(Email&&) = delete;


    Email(const Email&) = default;
    Email& operator=(const Email&) = default;

    //Option 2:
    // - fix the move operations. But thsse two functions are no better than the std::vector move semantics implementations.
    Email(Email&& e) noexcept : value{std::move(e.value)},
                        movedFrom{e.movedFrom} {
        e.movedFrom = true;
    }

    Email operator=(Email&& e) noexcept {
        value = std::move(e.value);
        movedFrom = e.movedFrom;
        e.movedFrom = true;
        return *this;
    }

    friend std::ostream& operator<< (std::ostream& strm,
                                     const Email& e) {
        return strm << e.value;
    }

    //~Email() = default;

};
