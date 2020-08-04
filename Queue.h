template <class Item, class Handle>
class Priority_queue{

    public:
        virtual Item& find_min()=0;

        virtual Item& extract_min()=0;

        virtual Handle* insert(Item item)=0;

        virtual void decrease_key(Handle* container, Item item)=0;

        virtual void empty()=0;

        //TODO delete operation for freeing memory

        //TODO meld Operation

};
