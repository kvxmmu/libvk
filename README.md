# libvk
C++ vk library

# Example

```c++

#include <iostream>
#include "libvk/libvk.cpp"

int main() {
    VkApi vk("token", "5.103"); // access_token, version
    
    rapidjson::Document response = vk.method("users.get", {}); // get current account
    std::cout << dumps_json(response) << std::endl;

    response = vk.custom_token_method("users.get", {}, "token", "version");
    
    std::cout << dumps_json(response) << std::endl;
    
    return 0;
}
````