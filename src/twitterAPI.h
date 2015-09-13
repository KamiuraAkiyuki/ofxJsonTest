//
//  twitterAPI.h
//  
//
//  Created by Akiyuki Kamiura on 2015/09/11.
//
//

#ifndef ____twitterAPI__
#define ____twitterAPI__

#include <stdio.h>
#include <sstream>
#include <sys/time.h>
#include <map>

#include <openssl/sha.h>
#include <openssl/hmac.h>

#include "ofMain.h"

using namespace std;

class TwitterAPI {
private:
    string oauth_consumer_key = "kn1vWxtc8kv1ouAVEWTIwgPu8";
    string oauth_consumer_secret = "89xPzFcQ6bTktpT6QeMinM6m30n85EsdpB7kaktW6oBDWtBA1H";
    string oauth_token;
    string oauth_token_secret;
    
    string hmac_sha1(string key, string data);
    string percentEncode(string str);
    char *base64(const unsigned char *input, int length);
    string makeParamString(string oauth_consumer_key, string oauth_nonce, string oauth_signature, long oauth_timestamp, string oauth_token, string oauth_verifier, string status);
    
public:
    TwitterAPI(){};
    void getTimeline();
    void createSignature();
    
};

#endif /* defined(____twitterAPI__) */
