#include <iostream>
#include <cassert>
#include <algorithm>

class Vector {
 private:
  struct SharedData {
    double* storage;
    int ref_count;
    mutable int read_locks;
    int write_locks;

    SharedData(size_t size) {
      storage = new double[size];
      for (size_t i = 0; i < size; ++i) storage[i] = 0.0;
      ref_count = 1;
      read_locks = 0;
      write_locks = 0;
    }

    SharedData(const double* source, size_t size) {
      storage = new double[size];
      for (size_t i = 0; i < size; ++i) storage[i] = source[i];
      ref_count = 1;
      read_locks = 0;
      write_locks = 0;
    }

    ~SharedData() {
      delete[] storage;
    }
  };

  SharedData* data_;
  size_t offset_;
  size_t size_;

  void decrement_ref() {
    if (data_) {
      data_->ref_count--;
      if (data_->ref_count == 0) {
        delete data_;
      }
    }
  }

  void detach() {
    if (data_->ref_count > 1) {
      assert(data_->read_locks == 0);
      
      SharedData* new_data = new SharedData(data_->storage + offset_, size_);
      
      decrement_ref();

      data_ = new_data;
      offset_ = 0;
    }
  }

 public:
  explicit Vector(size_t size) {
    data_ = new SharedData(size);
    offset_ = 0;
    size_ = size;
  }

  Vector(const Vector& other) {
    data_ = other.data_;
    offset_ = other.offset_;
    size_ = other.size_;
    data_->ref_count++;
  }

  Vector(const Vector& other, size_t offset, size_t size) {
    assert(offset + size <= other.size_);
    data_ = other.data_;
    offset_ = other.offset_ + offset;
    size_ = size;
    data_->ref_count++;
  }

  ~Vector() {
    decrement_ref();
  }

  Vector& operator=(const Vector& other) {
    if (this != &other) {
      decrement_ref();
      data_ = other.data_;
      offset_ = other.offset_;
      size_ = other.size_;
      data_->ref_count++;
    }
    return *this;
  }

  size_t size() const {
    return size_;
  }

  const double& operator[](size_t index) const {
    assert(index < size_);
    return data_->storage[offset_ + index];
  }

  double& operator[](size_t index) {
    assert(index < size_);
    detach();
    return data_->storage[offset_ + index];
  }

  const double* AquireConstBuffer() const {
    data_->read_locks++;
    return data_->storage + offset_;
  }

  void ReleaseConstBuffer() const {
    assert(data_->read_locks > 0);
    data_->read_locks--;
  }

  double* AquireBuffer() {
    detach();
    assert(data_->read_locks == 0);
    assert(data_->write_locks == 0);
    data_->write_locks++;
    return data_->storage + offset_;
  }

  void ReleaseBuffer() {
    assert(data_->write_locks > 0);
    data_->write_locks--;
  }

  class ConstBuffer {
   private:
    const Vector& vec_;
    const double* ptr_;
   public:
    explicit ConstBuffer(const Vector& v) : vec_(v) {
      ptr_ = v.AquireConstBuffer();
    }
    
    ~ConstBuffer() {
      vec_.ReleaseConstBuffer();
    }

    const double& operator[](size_t i) const {
      return ptr_[i];
    }
    
    const double* get() const { return ptr_; }
  };

  class Buffer {
   private:
    Vector& vec_;
    double* ptr_;
   public:
    explicit Buffer(Vector& v) : vec_(v) {
      ptr_ = v.AquireBuffer();
    }
    
    ~Buffer() {
      vec_.ReleaseBuffer();
    }

    double& operator[](size_t i) {
      return ptr_[i];
    }

    double* get() { return ptr_; }
  };
};

void TestCopyOnWrite() {
  std::cout << "test 1\n";
  Vector v1(5);
  for (size_t i = 0; i < v1.size(); ++i) v1[i] = static_cast<double>(i);

  Vector v2 = v1;
  
  std::cout << v1[0] << ' ' << v2[0] << '\n';
  
  v2[0] = 100.0;

  std::cout << v1[0] << ' ' << v2[0] << '\n';
}

void TestSubVector() {
  std::cout << "test 2\n";
  Vector big(10);
  for (size_t i = 0; i < big.size(); ++i) big[i] = static_cast<double>(i + 10);

  Vector sub(big, 2, 3);

  std::cout << sub[0] << ' ' << sub[1] << ' ' << sub[2] << '\n';
  
  big[2] = 999.0; 
  
  std::cout << sub[0] << '\n';
}

void TestRAIIAndLocks() {
  std::cout << "test 3\n";
  Vector v(3);
  v[0] = 1.0;
  v[1] = 2.0;
  v[2] = 3.0;

  {
    Vector::ConstBuffer cbuf(v);
    std::cout << cbuf[1] << '\n';
  } 

  {
    Vector::Buffer buf(v);
    buf[0] = 55.5;
    std::cout << buf[0] << '\n';
  }

  std::cout << v[0] << '\n';
}

int main() {
  TestCopyOnWrite();
  TestSubVector();
  TestRAIIAndLocks();
  return 0;
}