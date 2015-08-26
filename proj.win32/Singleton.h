/*
    Singleton�࣬ 
    ���ģʽ�еĵ���ģʽ����������������������н�����һ��ʵ������������������������
    ����������google/�ٶ�  �����ģʽ ������
    �ο�Դ�룬http://m.blog.csdn.net/blog/nmhkyiuj/43760859
*/
#ifndef _H_SINGLETON_
#define _H_SINGLETON_

template <class T>
class Singleton{
public:
    static inline T* instance();    //��̬�������������ڴ���������Ψһʵ��
    void release();     //�ͷŵ�����Ψһʵ��

protected:
    Singleton(){};      //������ʵ�������� instance()������������˽����������������Ϊ����̬����ֹ���������
    ~Singleton(){};     
    static T* m_instance;   //��̬��Ա�������浥����Ψһʵ��
};

//���ʵ�������ڣ��򴴽�ʵ�������򷵻�ʵ���Թ�ʹ��
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

//�����ʼ����̬��Ա�ĺ�
#define DECLARE_SINGLETON_MEMBER(_Ty)	 template <> _Ty* Singleton<_Ty>::m_instance = NULL;

#endif