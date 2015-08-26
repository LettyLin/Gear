/*
    Singleton类， 
    设计模式中的单例模式，该类的子类在整个程序中仅会有一个实例，常将其子类用作管理器
    具体内容请google/百度  ”设计模式 单例“
    参考源码，http://m.blog.csdn.net/blog/nmhkyiuj/43760859
*/
#ifndef _H_SINGLETON_
#define _H_SINGLETON_

template <class T>
class Singleton{
public:
    static inline T* instance();    //静态内联函数，用于创建单例的唯一实例
    void release();     //释放单例的唯一实例

protected:
    Singleton(){};      //单例的实例仅能由 instance()函数创建，因此将构造和析构函数设为保护态，防止被错误调用
    ~Singleton(){};     
    static T* m_instance;   //静态成员用来保存单例的唯一实例
};

//如果实例不存在，则创建实例，否则返回实例以供使用
template <class T>
inline T* Singleton<T>::instance(){
    if(NULL == m_instance){
        m_instance = new T;
    }
    return m_instance;
}

template <class T>
void Singleton<T>::release(){
    if(NULL != m_instance){
        delete m_instance;
    }
}

//定义初始化静态成员的宏
#define DECLARE_SINGLETON_MEMBER(_Ty)	 template <> _Ty* Singleton<_Ty>::m_instance = NULL;

#endif