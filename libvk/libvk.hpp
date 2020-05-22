//
// Created by kvxmmu on 5/22/20.
//

#ifndef LIBVK_LIBVK_HPP
#define LIBVK_LIBVK_HPP

#include <curl/curl.h>
#include <string>
#include <stdexcept>

#include <unordered_map>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"


static size_t text_write_callback(void *contents, size_t size,
        size_t nmemb, void *userp) {
    reinterpret_cast<std::string *>(userp)->append(reinterpret_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

rapidjson::Document parse_json(const std::string &data);
std::string dumps_json(const rapidjson::Document &data);
std::string dumps_json(const rapidjson::Value &data);

class VkString {
public:
    std::string value;

    VkString(float _value);
    VkString(const char *_value);
    VkString(int _value);
    VkString(long _value);
    VkString(unsigned long _value);
    VkString(unsigned int _value);
};

namespace std {
    template <>
    struct hash<VkString> {
        std::size_t operator()(const VkString &str) const {
            return std::hash<std::string>()(str.value);
        }
    };
}

class VkApi {
public:
    std::string token;
    std::string version;

    VkApi(std::string _token, std::string _version);

    static std::string make_query_params(const std::unordered_map<VkString, VkString> &params,
            CURL *curl, const std::string &access_token, const std::string &version_);

    static rapidjson::Document custom_token_method(const std::string &method_name,
                                            const std::unordered_map<VkString, VkString> &params,
                                            const std::string &version_, const std::string &access_token);

    rapidjson::Document method(const std::string &method_name,
                               const std::unordered_map<VkString, VkString> &params);
};


#endif //LIBVK_LIBVK_HPP
