#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <string>

struct dataStruct {

    std::string university;
    /* 64 bits */
    unsigned long long userId;
    /* 15 chars en el peor caso, 15 bytes */
    std::string userName;
    /* 4 bytes */
    unsigned int nTweets;
    /* 4 bytes */
    unsigned int friendCount;
    /* 4 bytes */
    unsigned int followerCount;
    /* */
    std::string createdAt;

    dataStruct();

    dataStruct(std::string university, unsigned long long userId,
                std::string userName, unsigned int nTweets,
                unsigned int friendCount, unsigned int followerCount,
                std::string createdAt);

    bool operator==(const dataStruct& data);
};

std::ostream& operator<<(std::ostream& os, const dataStruct& elem);

#endif
