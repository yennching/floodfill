/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

template <class T>
Deque<T>::Deque():num(0),L(-1){}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T const& newItem)
{
    if (L == -1){
        L = 0;
    }

    data.push_back(newItem);
    num++;
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    T temp = data[L];
    L++;
    num--;

    vector<T> resize;

    if (num < L){
        for (int i = L; i < L + num; i++){
            resize.push_back(data[i]);
        }

        data = resize;
        L = 0;
    }
    
    return temp;
}
/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    T temp = data[L+num-1];
    data.pop_back();
    num--;

    vector<T> resize;
    
    if (num <= L){
        for (int i = L; i < L + num; i++){
            resize.push_back(data[i]);
        }

        data = resize;
        L = 0;
    }

    return temp;
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    T temp = data[L];
    return temp;
}

/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    T temp = data[num-1];
    return temp;
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    return num == 0;
}
