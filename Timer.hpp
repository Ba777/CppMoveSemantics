
#if __cplusplus > 199711L   /// C++11

#include <chrono>

class Timer {
public:
    Timer() : beg_(clock_::now()) {}

    void reset() { beg_ = clock_::now(); }

    double elapsed() const {
        return std::chrono::duration_cast<second_> (clock_::now() - beg_).count();
    }

private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};

#else   /// C++

#include <ctime>

class Timer {
public:
    Timer() { clock_gettime(CLOCK_REALTIME, &beg_); }

    void reset() { clock_gettime(CLOCK_REALTIME, &beg_); }

    double elapsed() {
        clock_gettime(CLOCK_REALTIME, &end_);
        return end_.tv_sec - beg_.tv_sec + (end_.tv_nsec - beg_.tv_nsec) / 1e9;
    }

private:
    timespec beg_, end_;
};

#endif

/** Example usage */
#if 0
#include <iostream>
int main() {
    Timer tmr;
    double t = tmr.elapsed();
    std::cout << t << std::endl;
    tmr.reset();
    double t = tmr.elapsed();
    std::cout << t << std::endl;
    return 0;
}
#endif
