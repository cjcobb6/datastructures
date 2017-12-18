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
    RangeVector(size_t start, size_t length)
    {
        data.reserve(length);
        end_index = start + length;
        free_index = start;
        start_index = start;
    }

    bool isFull() 
    {
        return free_index == end_index;
    }

    void push_back(T elt) 
    {
        data.emplace_back(elt);
    }

    T& get(size_t idx) 
    {
        if(idx >= data.size()) throw "out of range";
        return data[idx];
    }
};

template <class T>
class LinkedVector
{
    vector<RangeVector<T> > m_data;
    size_t m_length;
    size_t m_blockSize;
    public:
    LinkedVector(size_t block_size)
    {
        m_data.emplace_back(0, block_size);
        m_length = 0;
    }

    void resize() 
    {
        std::cout << "resizing" << std::endl;
        m_data.emplace_back(m_length,m_length + m_blockSize);
    }

    bool isFull()
    {
        return lastBlock()->isFull();
    }

    RangeVector<T>* lastBlock() 
    {
        return &(m_data[m_data.size() - 1]);
    }

    void push_back(T elt) 
    {
        if(isFull()) 
        {
            resize();
        }
        lastBlock()->push_back(elt);
        m_length++;
    }

    T& get(size_t idx)
    {
        if(idx >= m_length) throw "out of range";
        RangeVector<T> block = m_data[idx / m_blockSize];
        return block.get(idx);
    }

    size_t size() { return m_length;}
};


int main(int argc, char** argv)
{


    LinkedVector<int> link(2);
    link.push_back(2);
    link.push_back(3);
    link.push_back(4);
    link.push_back(5);

    int total = 0;

    for(size_t i = 0; i < link.size(); i++) 
    {
        cout << total << endl;
        total += link.get(i);
    }
    cout << total << endl;
   cout << "hello" << endl; 
   return 0;
}
