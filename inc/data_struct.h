#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <string>

struct data_struct {

    /* 1 byte */
    bool valid;
    std::string university;
    /* 64 bits */
    unsigned long long user_id;
    /* 15 chars en el peor caso, 15 bytes */
    std::string username;
    /* 4 bytes */
    unsigned int n_tweets;
    /* 4 bytes */
    unsigned int friend_count;
    /* 4 bytes */
    unsigned int follower_count;
    // String por ahora...
    std::string created_at;
    
    data_struct(std::string university, unsigned long long user_id, std::string username,
            unsigned int n_tweets, unsigned int friend_count, unsigned int follower_count,
            std::string created_at);

    void setValid(bool valid);
};

std::ostream& operator << (std::ostream &os, const data_struct &elem);


#endif
