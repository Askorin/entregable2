#include "../inc/data_struct.h"
#include <ostream>

data_struct::data_struct(std::string university, unsigned long long user_id, std::string username,
            unsigned int n_tweets, unsigned int friend_count, unsigned int follower_count,
            std::string created_at) {

        this->university = university;
        this->user_id = user_id;
        this->username = username;
        this->n_tweets = n_tweets;
        this->friend_count = friend_count;
        this->follower_count = follower_count;
        this->created_at = created_at;
        this->valid = true;
}

void data_struct::setValid(bool valid) {
    this->valid = valid;
}


bool data_struct::operator == (const data_struct& data) {
    if (this->university != data.university || this->user_id != data.user_id || this->username != data.username ||
            this->n_tweets != data.n_tweets || this->friend_count != data.friend_count || this->follower_count != data.follower_count ||
            this->created_at != data.created_at || this->valid != data.valid) {
        return false;
    }
    return true;
}

std::ostream& operator << (std::ostream &os, const data_struct &elem) {
        return (os << "university: " << elem.university << "\nuser_id: " << elem.user_id 
                << "\nusername: " << elem.username << "\nn_tweets: " << elem.n_tweets
                << "\nfriend_count: " << elem.friend_count << "\nfollower_count: "
                << elem.follower_count << "\ncreated_at: " << elem.created_at);
}


