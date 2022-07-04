namespace custom {


template<typename T, typename allocator = ::std::allocator<T>()>
class forward_list
{
    struct Node {
        T value;
        Node* next;
    };

    Node* _head{ nullptr };

public:
    using value_type = T;

    forward_list() = default;
    
    ~forward_list()
    {
        while (_head) 
        {
        }
    }
};


}
