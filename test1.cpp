#include <iostream>

#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

void sort(auto arr, auto begin, auto end){
    std::sort(begin,end);
    arr.erase(std::unique(begin,end),end);
}

template<typename A, typename B>
void sort2(A arr, B begin, B end){
    std::sort(begin,end);
    arr.erase(std::unique(begin,end),end);
}

void sort3(auto arr, auto begin, auto end){
    decltype(std::remove_reference(*arr.data())) v;
    std::set<decltype(v)> m(begin,end);
    for(auto e:arr){
        m.insert(std::move(e));
    }
    arr.clear();
    for(auto e:m){
        arr.push_back(std::move(e));
    }
}

int main(int argc, char **argv)
{
    std::vector<double> v;
    v.resize(1000);
    sort(v,v.begin(),v.end());
    sort2(v,v.begin(),v.end());
    sort3(v,v.begin(),v.end());
}
