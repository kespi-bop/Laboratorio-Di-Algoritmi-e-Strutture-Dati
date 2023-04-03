
namespace lasd {

/* ************************************************************************** */

//Constructors

template <typename Data>
Vector<Data>::Vector(const ulong new_size) {
    size = new_size;
    Elements = new Data[size] {};
}

template <typename Data>
Vector<Data>::Vector(const MappableContainer<Data>& map) {
    size = map.Size();
    Elements = new Data[size] {};
    ulong index = 0;
    map.Map(
        [this, &index](const Data& dat) {
            Elements[index++] = dat;
        }
    );
}

template <typename Data>
Vector<Data>::Vector(MutableMappableContainer<Data>&& Mmap) {
    size = Mmap.Size();
    Elements = new Data[size] {};
    ulong index = 0;
    Mmap.Map(
        [this, &index](const Data& dat) {
            Elements[index++] = std::move(dat);
        }
    );
}

/* ************************************************************************** */

//Copy constructor

template <typename Data>
Vector<Data>::Vector(const Vector<Data>& other){
    size = other.size;
    Elements = new Data[size];
    for(int i = 0; i<size; i++) {
        //std::cout<<"vector["<<i<<"]="<<other[i];
        this->operator[](i)=other[i];
    }
}

//Move constructor

template <typename Data>
Vector<Data>::Vector(Vector<Data>&& other) noexcept {
    return;
}

/* ************************************************************************** */

//Copy assignement

template <typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector& other) {
    //
    // return this;
    return *this;
}

//Move assignement

template <typename Data>
Vector<Data>& Vector<Data>::operator=(Vector&& other) noexcept {
    //
    return *this;
}

/* ************************************************************************** */

//Operators

template <typename Data>
const Data& Vector<Data>::operator[](const ulong index) const {
    if(index<0 || index >= size)
        throw std::out_of_range("Error: IndexOutOfBounds");
    return Elements[index];
}

template <typename Data>
Data& Vector<Data>::operator[](const ulong index) {
    if(index<0 || index>= size)  
        throw std::out_of_range("Error: IndexOutOfBounds");
    return Elements[index];
}

template <typename Data>
bool Vector<Data>::operator==(const Vector& other) const noexcept {
    bool result=true;
    if(size!=other.size) return false;
    for(int i=0; i<size; i++) if(this[i]!=other[i]) return false;
    return true;
}

template <typename Data>
bool Vector<Data>::operator!=(const Vector& other) const noexcept {
    bool result=false;
    if(size!=other.size) return true;
    for(int i=0; i<size; i++) if(this[i]!=other[i]) return true;
    return false;
}

/* ************************************************************************** */

//Front and back

template <typename Data>
const Data& Vector<Data>::Front() const {
    return this->operator[](0); 
}

template <typename Data>
Data& Vector<Data>::Front() {
    return this->operator[](0); 
}

template <typename Data>
const Data& Vector<Data>::Back() const {
    return this->operator[](size - 1); 
}

template <typename Data>
Data& Vector<Data>::Back() {
    return this->operator[](size - 1); 
}

template <typename Data>
void Vector<Data>::Resize(const ulong new_size){
    Data* ptr = new Data[new_size];
    for(int i = 0; i<new_size; i++) 
        ptr[i]=Elements[i];
    delete[] Elements;
    size=new_size;
    Elements = ptr;
}

/* ************************************************************************** */

//Sort

template <typename Data>
void Vector<Data>::Sort() noexcept {
    SortableLinearContainer<Data>::Quicksort(0, size - 1);
}

/* ************************************************************************** */

}
