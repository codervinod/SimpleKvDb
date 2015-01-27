#include "KvDb.h"

std::string KvDb::Get(std::string key )
{
    KV_MAP::iterator itr = m_kv_map.find(key);
    if (itr != m_kv_map.end())
    {
        return itr->second;
    }
    return "NULL";
}

void KvDb::Set(std::string key, std::string val, bool mdb)
{
    if (!mdb)
    {
        if (!m_kv_blocks.empty())
        {
            CMD_LIST &commit_block = m_kv_blocks.top();
            commit_block.push_back(Cmd("SET", key, val));
            return;
        }
    }

    m_kv_map[key] = val;
}

bool KvDb::Delete(std::string key, bool mdb)
{
    if (!mdb)
    {
        if (!m_kv_blocks.empty())
        {
            CMD_LIST &commit_block = m_kv_blocks.top();
            commit_block.push_back(Cmd("DELETE", key, ""));
            return true;
        }
    }

    KV_MAP::iterator itr = m_kv_map.find(key);
    if (itr != m_kv_map.end())
    {
        m_kv_map.erase(itr);
        return true;
    }
    return false;
}

int KvDb::Count(std::string val)
{
    int count = 0;
    for (KV_MAP::iterator itr = m_kv_map.begin(); itr != m_kv_map.end(); ++itr)
    {
        if (itr->second == val)
            count++;
    }
    return count;
}

void KvDb::Begin()
{
    m_kv_blocks.push(CMD_LIST());
}

bool KvDb::Rollback()
{
    if (m_kv_blocks.empty())
        return false;

    m_kv_blocks.pop();
    return true;
}

void KvDb::Commit()
{
    while (!m_kv_blocks.empty())
    {
        CMD_LIST &commit_block = m_kv_blocks.top();
        for (CMD_LIST::iterator itr = commit_block.begin(); itr != commit_block.end(); ++itr)
        {
            Cmd &cmd = *itr;
            if (cmd.m_cmd == "SET")
            {
                Set(cmd.m_key, cmd.m_val,true);
            }
            /*else if (cmd.m_cmd == "GET")
            {
                Get(cmd.m_key);
            }*/
            /*else if (cmd.m_cmd == "COUNT")
            {
                Count(cmd.m_key);
            }*/
            else if (cmd.m_cmd == "DELETE", true)
            {
                Delete(cmd.m_key);
            }
        }
        m_kv_blocks.pop();
    }
}