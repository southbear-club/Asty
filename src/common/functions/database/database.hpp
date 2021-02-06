/**
 * @file database.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-02-03
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once
#include <cstdint>
#include <iostream>
#include <vector>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

namespace asty {

namespace db {

// class IDb {
// public:
//     virtual ~IDb();

//sudo service mongodb stop 
//sudo service mongodb start
//http://mongocxx.org/mongocxx-v3/tutorial/
// // mongodb://platform:905984143w@localhost:27017/astyCloudPlatform
//     virtual int open(void);
//     virtual int close(void);
//     virtual int create(void);
//     virtual int remove(void);
//     virtual int add(void);
//     virtual int drop(void);
//     virtual int begin(void);
//     virtual int commit(void);
//     virtual int roll(void);
//     virtual int query(void);
//     virtual int exec(void);
// };

}  // namespace db

}  // namespace asty
