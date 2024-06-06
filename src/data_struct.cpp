#include "../inc/data_struct.h"
#include <ostream>

dataStruct::dataStruct()
    : university(), userId(), userName(), nTweets(), friendCount(),
      followerCount(), createdAt() {}

dataStruct::dataStruct(std::string university, unsigned long long userId,
                         std::string userName, unsigned int nTweets,
                         unsigned int friendCount, unsigned int followerCount,
                         std::string createdAt) {

    this->university = university;
    this->userId = userId;
    this->userName = userName;
    this->nTweets = nTweets;
    this->friendCount = friendCount;
    this->followerCount = followerCount;
    this->createdAt = createdAt;
}

bool dataStruct::operator==(const dataStruct& data) {
    if (this->university != data.university || this->userId != data.userId ||
        this->userName != data.userName || this->nTweets != data.nTweets ||
        this->friendCount != data.friendCount ||
        this->followerCount != data.followerCount ||
        this->createdAt != data.createdAt) {
        return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const dataStruct& elem) {
    return (
        os << "university: " << elem.university << "\nuser_id: " << elem.userId
           << "\nusername: " << elem.userName << "\nn_tweets: " << elem.nTweets
           << "\nfriend_count: " << elem.friendCount << "\nfollower_count: "
           << elem.followerCount << "\ncreated_at: " << elem.createdAt);
}
