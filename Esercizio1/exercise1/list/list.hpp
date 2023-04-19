
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/dictionary.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public ClearableContainer,
             virtual public DictionaryContainer<Data>,
             virtual public LinearContainer<Data>{
              // Must extend ClearableContainer,
              //             DictionaryContainer<Data>,
              //             LinearContainer<Data>

private:

  // ...

protected:

  using Container::size;

  struct Node {

    // Data
    Data element;
    Node* next = nullptr;

    /* ********************************************************************** */

    //Default constructor
    Node() {
      delete next;
    }

    // Specific constructors
    Node(const Data &elemento){
      element  = elemento;
      next = nullptr;
    }

    Node(Data &&elemento){
      std::swap(element, elemento);
      next = nullptr;
    }

    /* ********************************************************************** */

    // Copy constructor
    Node(Node& nodo){
      element = nodo.element;
      next = nodo.next;
    }

    // Move constructor
    Node(Node&& nodo){
      std::swap(element, nodo.elem);
      std::swap(next, nodo.next);
    }

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const Node& right) const{
      return ((right.element == element) && ((next == nullptr && right.next == nullptr) || (next != nullptr && right.next != nullptr)) && (*next = *right.next));
    }

    bool inline operator!=(const Node& right) const{
      return !(operator==(right));
    }

    /* ********************************************************************** */

    // Specific member functions

    // ...

  };

  Node* head = nullptr;

public:

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  List(const MappableContainer<Data>& right); // A list obtained from a MappableContainer
  List(MutableMappableContainer<Data>&& right) noexcept; // A list obtained from a MutableMappableContainer

  /* ************************************************************************ */

  // Copy constructor
  List(const List& right);

  // Move constructor
  List(List&& right) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~List() {
    while(!Empty()) RemoveFromFront();
  }

  /* ************************************************************************ */

  // Copy assignment
  List<Data>& operator=(const List& right);

  // Move assignment
  List<Data>& operator=(List&& right) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List& right) const noexcept;
  bool inline operator!=(const List& right) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  virtual void InsertAtFront(const Data& element); // Copy of the value
  virtual void InsertAtFront(Data&& element) noexcept; // Move of the value
  virtual void RemoveFromFront(); // (must throw std::length_error when empty)
  virtual Data FrontNRemove(); // (must throw std::length_error when empty)

  virtual void InsertAtBack(const Data& element); // Copy of the value
  virtual void InsertAtBack(Data&& element) noexcept; // Move of the value

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  virtual bool Insert(const Data& element) override; // Copy of the value
  virtual bool Insert(Data&& element) noexcept override; // Move of the value
  virtual bool Remove(const Data& element) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data & operator[](const ulong inedex) const override; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data & operator[](const ulong index) override; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  const Data& Front() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Front() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  const Data& Back() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data& Back() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;
  virtual void inline Fold(FoldFunctor func, void* acc) const override { PreOrderFold(func, acc); }; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderFoldableContainer)

  // type PreOrderFold(arguments) specifiers; // Override PreOrderFoldableContainer member
  virtual void PreOrderFold(FoldFunctor func, void* acc) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderFoldableContainer)

  // type PostOrderFold(arguments) specifiers; // Override PostOrderFoldableContainer member
  virtual void PostOrderFold(FoldFunctor func, void* acc) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  virtual void Map(MapFunctor func) const override { PreOrderMap(func); }; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  // type PreOrderMap(argument) specifiers; // Override PreOrderMappableContainer member
  virtual void PreOrderMap(MapFunctor func) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  // type PostOrderMap(argument) specifiers; // Override PostOrderMappableContainer member
  virtual void PostOrderMap(MapFunctor func) const override; 

  /* ************************************************************************ */

  // Specific member function (inherited from MutableMappableContainer)

  using typename MutableMappableContainer<Data>::MutableMapFunctor;

  virtual void inline Map(MutableMapFunctor func) override { PreOrderMap(func); }; // Override MutableMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MutablePreOrderMappableContainer)

  // type PreOrderMap(argument) specifiers; // Override MutablePreOrderMappableContainer member
  virtual void PreOrderMap(MutableMapFunctor func) override; 

  /* ************************************************************************ */

  // Specific member function (inherited from MutablePostOrderMappableContainer)

  // type PostOrderMap(argument) specifiers; // Override MutablePostOrderMappableContainer member
  virtual void PostOrderMap(MutableMapFunctor func) override;

protected:

  // Auxiliary member functions (for PreOrderFoldableContainer & PostOrderFoldableContainer)

  void AuxPreOrderFold(const Node* nodo, FoldFunctor func, void* acc) const; // Accessory function executing from one point of the list onwards
  void RecursivePostOrderFold(const Node* nodo, FoldFunctor func, void* acc) const; // Accessory function executing from one point of the list onwards

  /* ************************************************************************ */

  // Auxiliary member functions (for PreOrderMappableContainer & PostOrderMappableContainer)

  void AuxPreOrderMap(const Node* nodo, MapFunctor func) const; // Accessory function executing from one point of the list onwards
  void RecursivePostOrderMap(Node* nodo, MapFunctor func) const; // Accessory function executing from one point of the list onward

  /* ************************************************************************ */

  // Auxiliary member functions (for MutablePreOrderMappableContainer & MutablePostOrderMappableContainer)

  void AuxPreOrderMap(Node* nodo, MutableMapFunctor func); // Accessory function executing from one point of the list onwards
  void RecursivePostOrderMap(Node* nodo, MutableMapFunctor func); // Accessory function executing from one point of the list onward

  /* ************************************************************************ */

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
