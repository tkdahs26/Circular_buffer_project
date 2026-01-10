#include <iostream>   
#include <numeric>    
#include <algorithm>

using namespace std;

template <typename T>

class CircularBuffer {
public:
    T* buffer;
    size_t head;
    size_t tail;
    size_t _size;
    size_t _capacity;

public:
    // 생성자,초기화리스트
    CircularBuffer(size_t capacity) : _capacity(capacity), head(0), tail(0), _size(0) {
        buffer = new T[_capacity];  //capacity개수의 double배열
    }

    ~CircularBuffer() { delete[] buffer; }




    // ------------------------ 반복자(Iterator) 구현 ------------------------------------
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
    private:
        T* buffer_Iter;        // 버퍼 주소 복사
        size_t index_Iter;    
        size_t head_Iter;      // 시작 위치 복사
        size_t capacity_Iter;  // 버퍼 크기 복사

    public:
        // 생성자 
        Iterator(T* buffer, size_t index, size_t head, size_t capacity)
            : buffer_Iter(buffer), index_Iter(index), head_Iter(head), capacity_Iter(capacity) {}

        // 현재 순번의 실제 데이터를 찾아주는 std활용한 연산자함수
        T& operator*() {
         
            return buffer_Iter[(head_Iter + index_Iter) % capacity_Iter];
        }

   
        Iterator& operator++() {
            index_Iter++;
            return *this;
        }

       
        bool operator!=(const Iterator& other) const {
            return index_Iter != other.index_Iter;
        }
    };

    // ------------------------------------------------------------------------



    T& operator[](size_t index) {
      
        return buffer[(head + index) % _capacity];

    }




    void push_back(const T& value) {    //버퍼에 데이터를 쌓음
        buffer[tail] = value;             // 1. tail에 데이터 저장
        tail = (tail + 1) % _capacity;    // 2. 다음 칸으로 이동

        if (_size < _capacity) {
            _size++;                      //  빈칸이 있다면 사이즈 증가
        }
        else {
            head = (head + 1) % _capacity; //head 값 이동
        }
    }


    size_t capacity() const { //읽기전용메소드
        return _capacity;
    }


    size_t size() const {
        return _size;
    }

    // 비어있는지 확인
    bool empty() const {
        return _size == 0;
    }
    T& front() {        //가장 오래된 데이터
        return buffer[head];
    }

    T& back() {   // 가장 최신 데이터
        return buffer[(tail + _capacity - 1) % _capacity];   // tail이 0일 경우
    }


    void pop_front() {
        if (!empty()) {
            head = (head + 1) % _capacity;
            _size--;
        }
    }

    const T& operator[](size_t index) const {
        return buffer[(head + index) % _capacity];
    }

    const T& front() const {
        return buffer[head];
    }

    const T& back() const {
        return buffer[(tail + _capacity - 1) % _capacity];
    }


    // literator생성자 호출
    Iterator begin() {
        return Iterator(buffer, 0, head, _capacity);
    }//CircularBuffer필드를 Iterator 생성자 매개변수로 사용

  
    Iterator end() {
        return Iterator(buffer, _size, head, _capacity);
    }


    Iterator begin() const {
        return Iterator(buffer, 0, head, _capacity);
    }

    Iterator end() const {
        return Iterator(buffer, _size, head, _capacity);
    }



}
;

int main() {
    CircularBuffer<double> tempBuffer(5);

    tempBuffer.push_back(23.5);
    tempBuffer.push_back(24.1);
    tempBuffer.push_back(23.8);
    tempBuffer.push_back(25.2);
    tempBuffer.push_back(24.7);
    tempBuffer.push_back(26.1); 


    cout << "버퍼 내용 (인덱스 순서): [";
    for (size_t i = 0; i < tempBuffer.capacity(); ++i) {
        cout << tempBuffer.buffer[i] << (i == tempBuffer.capacity() - 1 ? "" : ", ");
    }
    cout << "]" << endl;

 
    cout << "begin()부터 순회 시: ";
    for (auto it = tempBuffer.begin(); it != tempBuffer.end(); ++it) {
        cout << *it;
        auto next_it = it;
        if (++next_it != tempBuffer.end()) cout << ", ";
    }
     
 
    double maxTemp = *std::max_element(tempBuffer.begin(), tempBuffer.end());
    double avgTemp = std::accumulate(tempBuffer.begin(), tempBuffer.end(), 0.0) / tempBuffer.size();

 
    cout << "tempBuffer.size() = " << tempBuffer.size() << endl;
    cout << "tempBuffer.capacity() = " << tempBuffer.capacity() << endl;
    cout << "tempBuffer.empty() = " << (tempBuffer.empty() ? "false" : "true") << endl;
    cout << "maxTemp = " << maxTemp << endl;
    cout << "avgTemp = " << avgTemp << endl;
    cout << "tempBuffer.front() = " << tempBuffer.front() <<   endl;
    cout << "tempBuffer.back() = " << tempBuffer.back() <<  endl;

    return 0;

}










