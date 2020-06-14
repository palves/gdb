/* Intrusive double linked list for GDB, the GNU debugger.
   Copyright (C) 2020 Free Software Foundation, Inc.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef GDBSUPPORT_INTRUSIVE_LIST_H
#define GDBSUPPORT_INTRUSIVE_LIST_H

/* A list node.  The elements put in an intrusive_list either inherit
   from this, or have a field of this type.  */
template<typename T>
struct intrusive_list_node
{
  T *next = nullptr;
  T *prev = nullptr;
};

/* Follows a couple types used by intrusive_list as template parameter
   to find the intrusive_list_node for a given element.  One for lists
   where the items inherits intrusive_list_node, and another for items
   that keep the node as member field.  */

/* For element types that inherit from intrusive_list_node.  */

template<typename T>
struct intrusive_base_node
{
  static intrusive_list_node<T> *as_node (T *elem)
  {
    return elem;
  }
};

/* For element types that keep the node as member field.  */

template<typename T, intrusive_list_node<T> T::*MemberNode>
struct intrusive_member_node
{
  static intrusive_list_node<T> *as_node (T *elem)
  {
    return &(elem->*MemberNode);
  }
};

/* An iterator for intrusive_list.  Use AsNode to customize how to get
   at an item's node info.  The default assumes that elements inherit
   from intrusive_list_node.  */

template<typename T, typename AsNode = intrusive_base_node<T>>
struct intrusive_list_iterator
{
  using self_type = intrusive_list_iterator;
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using pointer = T *;
  using const_pointer = const T *;
  using reference = T &;
  using const_reference = const T &;
  using difference_type = ptrdiff_t;
  using size_type = size_t;

  explicit intrusive_list_iterator (T *item)
    : m_item (item)
  {
  }

  /* Create a one-past-the-end iterator.  */
  intrusive_list_iterator ()
    : m_item (nullptr)
  {
  }

  reference operator* () const
  {
    return *m_item;
  }
  pointer operator-> () const
  {
    return m_item;
  }

  bool operator== (const self_type &other) const
  {
    return m_item == other.m_item;
  }

  bool operator!= (const self_type &other) const
  {
    return m_item != other.m_item;
  }

  self_type &operator++ ()
  {
    m_item = AsNode::as_node (m_item)->next;
    return *this;
  }
  self_type operator++ (int)
  {
    self_type temp = *this;
    m_item = AsNode::as_node (m_item)->next;
    return temp;
  }

  self_type &operator-- ()
  {
    m_item = AsNode::as_node (m_item)->prev;
    return *this;
  }
  self_type operator-- (int)
  {
    self_type temp = *this;
    m_item = AsNode::as_node (m_item)->prev;
    return temp;
  }

private:
  T *m_item;
};

/* An intrusive double-linked list.  */

template <typename T, typename AsNode = intrusive_base_node<T>>
class intrusive_list
{
public:
  using value_type = T;
  using pointer = T *;
  using const_pointer = const T *;
  using reference = T &;
  using const_reference = const T &;
  using difference_type = ptrdiff_t;
  using size_type = size_t;
  using iterator = intrusive_list_iterator<T, AsNode>;
  using const_iterator = const intrusive_list_iterator<T, AsNode>;

  intrusive_list () = default;

  ~intrusive_list ()
  {
    clear ();
  }

  intrusive_list (intrusive_list &&other)
    : m_front (other.m_front),
      m_back (other.m_back)
  {
    other.m_front = nullptr;
    other.m_back = nullptr;
  }

  intrusive_list &operator= (intrusive_list &&other)
  {
    swap (other);
    return *this;
  }

  void swap (intrusive_list &other)
  {
    std::swap (m_front, other.m_front);
    std::swap (m_back, other.m_back);
  }

  iterator iterator_to (reference value)
  {
    return iterator (&value);
  }

  const_iterator iterator_to (const_reference value)
  {
    return const_iterator (&value);
  }

  reference front ()
  {
    return *m_front;
  }
  const_reference front () const
  {
    return *m_front;
  }

  reference back ()
  {
    return *m_back;
  }
  const_reference back () const
  {
    return *m_back;
  }

  void push_front (reference elem)
  {
    intrusive_list_node<T> *elem_node = as_node (&elem);

    gdb_assert (elem_node->next == nullptr);
    gdb_assert (elem_node->prev == nullptr);

    elem_node->next = m_front;
    if (m_front != nullptr)
      as_node (m_front)->prev = elem;
    m_front = elem;

    if (m_back == nullptr)
      m_back = m_front;
  }

  void push_back (reference elem)
  {
    intrusive_list_node<T> *elem_node = as_node (&elem);

    gdb_assert (elem_node->next == nullptr);
    gdb_assert (elem_node->prev == nullptr);

    if (m_back == nullptr)
      m_front = &elem;
    else
      {
	intrusive_list_node<T> *tail_node = as_node (m_back);
	tail_node->next = &elem;
	elem_node->prev = m_back;
      }
    m_back = &elem;
  }

  /* Inserts VALUE before POS.  */
  void insert (const_iterator pos, reference value)
  {
    intrusive_list_node<T> *val_node = as_node (&value);
    intrusive_list_node<T> *pos_node = as_node (&*pos);

    if (pos_node->prev != nullptr)
      as_node (pos_node->prev)->next = &value;

    val_node->next = *pos;
    val_node->prev = pos_node->prev;
    pos_node->prev = &value;

    if (*pos == m_front)
      m_front = &value;
  }

  void pop_front ()
  {
    if (!empty ())
      erase_item (*m_front);
  }

  void pop_back ()
  {
    if (!empty ())
      erase_item (*m_back);
  }

private:
  void erase_item (T &item)
  {
    intrusive_list_node<T> *node = as_node (&item);

    T *next = node->next;
    T *prev = node->prev;

    intrusive_list_node<T> *next_node = as_node (next);
    intrusive_list_node<T> *prev_node = as_node (prev);

    if (&item == m_front)
      m_front = next;
    if (&item == m_back)
      m_back = prev;
    if (prev != nullptr)
      prev_node->next = next;
    if (next != nullptr)
      next_node->prev = prev;

    node->next = nullptr;
    node->prev = nullptr;
  }

public:
  /* Remove the element pointed by I from the list.  The element
     pointed by I is not destroyed.  */
  iterator erase (const_iterator i)
  {
    iterator ret = i;
    ++ret;

    erase_item (*i);

    return ret;
  }

  /* Erase all the elements.  The elements are not destroyed.  */
  void clear ()
  {
    while (!empty ())
      pop_front ();
  }

  /* Erase all the elements.  Disposer::operator()(pointer) is called
     for each of the removed elements.  */
  template<typename Disposer>
  void clear_and_dispose (Disposer disposer)
  {
    while (!empty ())
      {
	pointer p = &front ();
	pop_front ();
	disposer (p);
      }
  }

  bool empty () const
  {
    return m_front == nullptr;
  }

  iterator begin ()
  {
    return iterator (m_front);
  }
  const_iterator begin () const
  {
    return const_iterator (m_front);
  }

  iterator end ()
  {
    return {};
  }
  const_iterator end () const
  {
    return {};
  }

private:
  static intrusive_list_node<T> *as_node (T *elem)
  {
    return AsNode::as_node (elem);
  }

  T *m_front = nullptr;
  T *m_back = nullptr;
};

#endif /* GDBSUPPORT_INTRUSIVE_LIST_H */
