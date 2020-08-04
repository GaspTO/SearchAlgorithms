
template <class K, class V>
class Map {

    public:
        V& search(K key);
        void insert(K key, V value);
        void remove(K key);

};