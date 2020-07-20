#include <ctre.hpp>
#include <string_view>

namespace re{
    constexpr std::string_view rexp = "^l";

    bool matching(std::string_view text){
        return ctre::match<rexp>(text).matched();
    }
}

int main(){
    printf("%s\n",re::matching("loool")?"True":"False");
}
