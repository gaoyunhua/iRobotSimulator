#ifndef __cpp_lib_make_unique
#define __cpp_lib_make_unique


#include <functional>
#include <memory>
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<typename T>
std::unique_ptr<T> make_unique_array( std::size_t size ) {
    return std::unique_ptr<T>(new typename std::remove_extent<T>::type[size]());
}

#endif