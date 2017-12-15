
using namespace std;
#include <iostream>
#include <vector>

template <class T>
struct RangeVector 
{
    size_t start_index;
    size_t end_index;
    size_t free_index;
    vector<T> data;
    size_t free_space;
    RangeVector(size_t start, size_t end)
    {
        data.reserve(end-start);
    }

    bool isFull() 
    {
        return free_index == end_index;
    }
};

template <class T>
class LinkedVector
{
    vector<RangeVector<T> > m_data;
    size_t m_length;
    size_t m_blockSize;
    LinkedVector(size_t block_size)
    {
        m_data.emplace_back(0, block_size);
        m_data[0].reserve(block_size);
        m_length = 0;
    }

    void resize() 
    {
        m_data.emplace_back(m_length,m_length + m_blockSize);
    }

    bool isFull()
    {
        return lastBlock()->isFull();
    }

    RangeVector<T>* lastBlock() 
    {
        return m_data[m_data.size() - 1];
    }

    void push_back(T& elt) 
    {
        if(isFull()) 
        {
            resize();
        }
        lastBlock()->push_back(elt);
    }
};


int main(int argc, char** argv)
{
   cout << "hello" << endl; 
   return 0;
}
