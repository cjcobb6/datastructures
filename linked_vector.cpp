using namespace std;
#include <time.h>
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
        ++free_index;
    }

    T& get(size_t idx) 
    {
        if(idx >= data.size()) {
            throw "out of range";
        }
        return data[idx];
    }

    void remove(size_t idx) 
    {
        if(idx >= data.size()) {
            throw "out of range";
        }
        data.erase(data.begin()+idx);
    }
};

template <class T>
class LinkedVector
{
    vector<RangeVector<T> > m_data;
    size_t m_length;
    size_t m_blockSize;
    size_t m_offset;
    public:
    LinkedVector(size_t block_size)
    {
        m_data.emplace_back(0, block_size);
        m_length = 0;
        m_offset = 0;
        m_blockSize = block_size;
    }

    void resize() 
    {
        m_data.emplace_back(m_length,m_blockSize);
    }

    bool isFull()
    {
        return lastBlock()->isFull();
    }

    RangeVector<T>* lastBlock() 
    {
        return &(m_data[m_data.size()-1]);
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
        if(idx >= m_length) {
            cout << "out of range" << endl;
            throw "out of range";
        }
        return m_data[idx / m_blockSize].get(idx % m_blockSize);
    }

    void remove(size_t idx) 
    {
    
        --m_length;
        m_data[idx / m_blockSize].remove(idx % m_blockSize);
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

    cout << "done pushing" << endl;
    for(size_t i = 0; i < link.size(); i++) 
    {
        cout << link.get(i) << endl;
        total += link.get(i);
    }

    link.remove(0);
    cout << link.get(0) << endl;
    cout << total << endl;


    cout << "big test" << endl;
    cout << "enter number of elements" << endl;
    size_t num_elts;
    cin >> num_elts;
    cout << "enter block size" << endl;
    size_t blockSize;
    cin >> blockSize;
    cout << "running...." << endl;
    {
        LinkedVector<int> bigLink(blockSize);
        time_t timer = time(0);

        for(size_t i = 0; i < num_elts; ++i) 
        {
            bigLink.push_back(i);
        }     
        time_t timer2 = time(0);
        cout << timer2 - timer << endl;
    }
    {
        vector<int> bigVec;
        time_t timer = time(0);

        for(size_t i = 0; i < num_elts; ++i) 
        {
            bigVec.push_back(i);
        }     
        time_t timer2 = time(0);
        cout << timer2 - timer << endl;
    }

    cout << "hello" << endl; 
    return 0;
}
