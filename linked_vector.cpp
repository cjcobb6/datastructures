
using namespace std;

template <class T>
struct RangeVector 
{
    size_t start_index;
    size_t end_index;
    size_t free_index;
    vector<T> data;
    size_t free_space;
    RangeVector(start, end)
    {
        data.reserve(end-start);
    }

    bool isFull() 
    {
        return free_index == end_index;
    }
}

template <class T>
class LinkedVector
{
    vector<RangeVector<T> > m_data;
    size_t m_length;
    LinkedVector(size_t block_size)
    {
        RangeVector
        m_data.emplace_back()
        m_length = 0;
    }

    bool isFull()
    {
        return lastBlock()->isFull();
    }

    RangeVector<T>* lastBlock() 
    {
        return data[data.size() - 1];
    }

    void push_back(T& elt) 
    {
        if(isFull()) 
        {
            resize();
        }
        lastBlock()->emplace_back(T);o
    }


}
