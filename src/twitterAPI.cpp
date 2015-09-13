//
//  twitterAPI.cpp
//  
//
//  Created by Akiyuki Kamiura on 2015/09/11.
//
//

#include "twitterAPI.h"

//
// UTF-8をURLエンコードする
//
string TwitterAPI::percentEncode(string str){
    const int NUM_BEGIN_UTF8 = 48;
    const int CAPITAL_BEGIN_UTF8 = 65;
    const int LOWER_BEGIN_UTF8 = 97;
    
    int charCode = -1;
    string encoded_string;
    stringstream out;
    
    for (int i = 0; str[i] != 0; i++){
        charCode = (int)(unsigned char)str[i];
        
        if((NUM_BEGIN_UTF8 <= charCode && charCode <= NUM_BEGIN_UTF8 + 9)
           || (CAPITAL_BEGIN_UTF8 <= charCode && charCode <= CAPITAL_BEGIN_UTF8 + 25)
           || (LOWER_BEGIN_UTF8 <= charCode && charCode <= LOWER_BEGIN_UTF8 + 25)
           || str[i] == '.' || str[i] == '_' || str[i] == '-' || str[i] == '~')
        {
            out << str[i];
        }else{
            out << '%' << std::hex << std::uppercase <<charCode;
        }
    }
    encoded_string = out.str();
    return encoded_string;
}

//
// hmac_sha1でハッシュ値を生成
//
string TwitterAPI::hmac_sha1(string key, string data){
    unsigned char res[SHA_DIGEST_LENGTH + 1];
    unsigned int reslen;
    size_t  keylen = key.length();
    int  datalen = data.length();
    
    //これで計算
    HMAC (EVP_sha1(), (const unsigned char*)key.c_str(), keylen, (const unsigned char*)data.c_str(), datalen, res, & reslen);
    
    string result((char*)res);
    result.erase(reslen);
    
    return result;
}


//
//
//
void TwitterAPI::getTimeline(){
    
    // キーの作成
    string signature_key = percentEncode(oauth_consumer_secret) + "&" + percentEncode(oauth_token_secret);
    
    // リクエストメソッド(URLエンコード)
    string request_method = "GET";
    
    // リクエストURL(URLエンコード)
    string request_token_url = "https://api.twitter.com/oauth/request_token";
    
    string authorize_url     = "https://api.twitter.com/oauth/authorize";
    string access_token_url  = "https://api.twitter.com/oauth/access_token";
    string update_url        = "https://api.twitter.com/1.1/statuses/update.json";
    
    // パラメータ作成
    map<string, string> params;
    params["oauth_consumer_key"] = percentEncode(oauth_consumer_key);
    params["oauth_nonce"] = percentEncode("mauagents");
    params["oauth_signature_method"] = percentEncode("HMAC-SHA1");
    params["oauth_timestamp"] = time(NULL);
    params["oauth_version"] = percentEncode("1.0");
    params["oauth_token"] = percentEncode(oauth_token);
    
    // パラメータからリクエスト文字列の作成
    string params_str = "";
    for (map<string, string>::iterator pairstring = params.begin(); pairstring != params.end(); pairstring++){
        string params_key = pairstring -> first;
        string params_value = pairstring -> second;
        
        params_str += params_key + "=" + params_value + "&";
    }
    params_str.resize(params_str.size() - 1);
    
    // リクエスト文字列をURLエンコードして&でつなぐ
    string signature_data = percentEncode(request_method) + "&" + percentEncode(request_token_url) + "&" + percentEncode(params_str);
    
    cout << signature_data << endl;
    cout << endl << signature_key << endl;
    
    // signatureをハッシュ化
    string oauth_signature = hmac_sha1(signature_key, signature_data);
    
    // paramsにoauth_signatureを追加
    params["oauth_signature"] = percentEncode(oauth_signature);
    
    cout << endl << oauth_signature << endl;
    
    
    
}

//
//
//
void TwitterAPI::createSignature(){
    
    string signature_key = percentEncode(oauth_consumer_secret) + "&" + percentEncode(oauth_token_secret);
    
    
    
    
    
    
    
    
    
}