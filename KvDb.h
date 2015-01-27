#ifndef __KV_DB_INCLUDE__
#define __KV_DB_INCLUDE__

#pragma once

#include <map>
#include <string>
#include <stack>
#include <vector>

typedef std::map<std::string, std::string> KV_MAP;

class Cmd
{
public:
    Cmd(std::string cmd, std::string key, std::string val) 
        :m_cmd(cmd), m_key(key), m_val(val){}
    std::string m_cmd;
    std::string m_key;
    std::string m_val;
};

typedef std::vector<Cmd> CMD_LIST;
typedef std::stack<CMD_LIST> KV_TRASACTS;

class KvDb
{
public:
    KvDb() {}
    virtual ~KvDb() {}
    std::string Get(std::string key);
    void Set(std::string key, std::string val, bool mdb=false);
    bool Delete(std::string key, bool mdb=false);
    int Count(std::string val);

    void Begin();
    bool Rollback();
    void Commit();

private:
    KV_MAP m_kv_map;
    KV_TRASACTS m_kv_blocks;
};

#endif