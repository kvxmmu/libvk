//
// Created by kvxmmu on 5/22/20.
//

#include "libvk.hpp"


rapidjson::Document parse_json(const std::string &data) {
    rapidjson::Document document;

    document.Parse(data.c_str());

    return document;
}

std::string dumps_json(const rapidjson::Document &data) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    data.Accept(writer);

    return buffer.GetString();
}

std::string dumps_json(const rapidjson::Value &data) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

    data.Accept(writer);

    return buffer.GetString();
}


VkApi::VkApi(std::string _token, std::string _version) : token(std::move(_token)),
                                                         version(std::move(_version)) {

}

rapidjson::Document VkApi::custom_token_method(const std::string &method_name,
        const std::unordered_map<VkString, VkString> &params,
        const std::string &version_, const std::string &access_token) {

    std::string buffer;

    CURL *curl = curl_easy_init();
    CURLcode res;

    if (curl == nullptr) {
        throw std::runtime_error("Failed to initialize CURL instance");
    }

    std::string query_params = VkApi::make_query_params(params, curl, access_token,
            version_);

    curl_easy_setopt(curl, CURLOPT_URL, ("https://api.vk.com/method/"+method_name).c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, text_write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query_params.c_str());

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        throw std::runtime_error("Failed to request vk api");
    }

    curl_easy_cleanup(curl);

    return parse_json(buffer);
}

std::string VkApi::make_query_params(const std::unordered_map<VkString, VkString> &params,
        CURL *curl, const std::string &access_token, const std::string &version_) {
    std::string query;

    for (auto &value : params) {
        char *first = curl_easy_escape(curl, value.first.value.c_str(),
                value.first.value.size());
        char *second = curl_easy_escape(curl, value.second.value.c_str(),
                value.second.value.size());

        std::string key(first);
        std::string kvalue(second);

        curl_free(first);
        curl_free(second);

        query += key + '=' + second;
        query += '&';
    }

    query += "access_token=" + access_token + '&';
    query += "v="+version_;

    return query;
}

rapidjson::Document VkApi::method(const std::string &method_name,
        const std::unordered_map<VkString, VkString> &params) {
    return VkApi::custom_token_method(method_name, params, this->version, this->token);
}


VkString::VkString(float _value) {
    this->value = std::to_string(_value);
}

VkString::VkString(const char *_value) : value(_value) {

}

VkString::VkString(int _value) {
    this->value = std::to_string(_value);
}

VkString::VkString(long _value) {
    this->value = std::to_string(_value);
}

VkString::VkString(unsigned long _value) {
    this->value = std::to_string(_value);
}

VkString::VkString(unsigned int _value) {
    this->value = std::to_string(_value);
}
