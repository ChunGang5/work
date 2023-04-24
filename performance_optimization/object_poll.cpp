/**
 * @Author: Chen Gang (cheng_caft@yusur.tech)
 * @date: 2023-04-24 16:54:34
 */

#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <memory>

template <typename T>
class ObjectPool {
public:
    ObjectPool(size_t poolSize) {
        pool_.resize(poolSize);
        for (auto& item : pool_) {
            freeList_.push(&item);
        }
    }

    T* alloc() {
        if (freeList_.empty()) {
            return new T;
        }
        T* ptr = freeList_.front();
        freeList_.pop();
        return ptr;
    }

    void dealloc(T* ptr) {
        freeList_.push(ptr);
    }

private:
    std::vector<T> pool_;
    std::queue<T*> freeList_;
};

struct MyData {
    int a, b;
};

// 定义一个对象池，用于存储 MyData 节点
ObjectPool<MyData> myDataPool(1000);

// 定义 unordered_map
std::unordered_map<int, MyData*> myMap;

// 新增元素
void addElement(int key, int a, int b) {
    // 从对象池中获取一个节点对象
    MyData* newData = myDataPool.alloc();
    newData->a = a;
    newData->b = b;

    // 将节点对象指针存储到unordered_map中
    myMap[key] = newData;
}

// 删除元素
void removeElement(int key) {
    // 从unordered_map中获取节点对象指针，并将其从map中删除
    MyData* data = myMap[key];
    myMap.erase(key);

    // 将节点对象指针还回对象池
    myDataPool.dealloc(data);
}

// 使用元素
void useElement(int key) {
    // 从unordered_map中获取节点对象指针
    MyData* data = myMap[key];

    // 使用节点对象
    int sum = data->a + data->b;

    // 不需要释放节点对象
    // 由于对象池中的节点对象是共享的，不会在使用完后被销毁，因此无需手动释放内存
}

int main()
{
    // ObjectPool<MyStruct> pool(5);
    // std::cout << pool.size() << std::endl;
    return 0;
}


// template<typename T>
// class ObjectPool {
// public:
//     ObjectPool(size_t max_size) : max_size_(max_size) {}

//     std::shared_ptr<T> Get() {
//         std::shared_ptr<T> obj;
//         if (!pool_.empty()) {
//             obj = pool_.front();
//             pool_.pop();
//         } else {
//             obj = std::make_shared<T>();
//         }
//         return obj;
//     }

//     void Release(std::shared_ptr<T> obj) {
//         if (pool_.size() < max_size_) {
//             pool_.push(obj);
//         }
//     }

//     int size()
//     {
//         return pool_.size();
//     }

// private:
//     std::queue<std::shared_ptr<T>> pool_;
//     size_t max_size_;
// };

// struct MyStruct {
//     int a, b;
//     MyStruct() : a(0), b(0) {}
// };
