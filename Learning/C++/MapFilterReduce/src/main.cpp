//
// Created by oonray on 22/10/2020.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main(){
    // Neer use loops!
    // Data
    std::vector<int> data { 1,2,3,4,5 };
    std::vector<int> out;
    std::vector<int> copy;

    //Map
    std::transform(data.begin(),data.end(),back_inserter(out),[](const int &value){return value * 2;});

    std::cout << "Out data:\n";
    std::for_each(out.begin(),out.end(),[](const int &data){ std::cout<<data<<" "; });
    std::cout << '\n';

    //filter
    std::copy_if(out.begin(),out.end(),back_inserter(copy),[](const int &data){return data<7;});

    std::cout << "Copy data:\n";
    std::for_each(copy.begin(),copy.end(),[](const int &data){ std::cout<<data<<" "; });
    std::cout << '\n';

    int sum = std::accumulate(out.begin(),out.end(),0,[](const int &prev,const int &next){return prev+next;});
    std::cout << "The sum of out is: " << sum << '\n';
}
