/* Owning intrusive double linked list for GDB, the GNU debugger.
   Copyright (C) 2024 Free Software Foundation, Inc.

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

#ifndef GDBSUPPORT_OWNING_INTRUSIVE_LIST_H
#define GDBSUPPORT_OWNING_INTRUSIVE_LIST_H

#include "gdbsupport/intrusive_list.h"

template <typename T, typename AsNode = intrusive_base_node<T>>
struct owning_intrusive_list : private intrusive_list<T, AsNode>
{
private:
  using base = intrusive_list<T, AsNode>;
public:
  using typename base::value_type;
  using typename base::pointer;
  using typename base::const_pointer;
  using typename base::reference;
  using typename base::const_reference;
  using typename base::difference_type;
  using typename base::size_type;
  using typename base::iterator;
  using typename base::reverse_iterator;
  using typename base::const_iterator;
  using typename base::const_reverse_iterator;
  using typename base::node_type;

  using base::begin;
  using base::rbegin;
  using base::cbegin;
  using base::crbegin;
  using base::end;
  using base::rend;
  using base::cend;
  using base::crend;
  using base::iterator_to;
  using base::empty;
  using base::back;
  using base::front;

  owning_intrusive_list () = default;

  owning_intrusive_list (owning_intrusive_list &&other)
    : base (std::move (other))
  {}

  ~owning_intrusive_list ()
  {
    clear ();
  }

  owning_intrusive_list &operator= (owning_intrusive_list &&other)
  {
    base::operator=(std::move (other));
    return *this;
  }

  void swap (owning_intrusive_list &other)
  {
    base::swap (other);
  }

  void splice (owning_intrusive_list &&other)
  {
    base::splice (std::move (other));
  }

  void push_front (std::unique_ptr<T> elem)
  {
    T *ptr = elem.release ();
    base::push_front (*ptr);
  }

  void push_back (std::unique_ptr<T> elem)
  {
    T *ptr = elem.release ();
    base::push_back (*ptr);
  }

  template<class... Args>
  void emplace_back (Args&&... args)
  {
    auto elem = std::make_unique(std::forward (args...));
    push_back (std::move (elem));
  }

  void pop_front ()
  {
    auto &elem = front ();
    base::pop_front ();
    delete &elem;
  }

  void pop_back ()
  {
    auto &elem = back ();
    base::pop_back ();
    delete &elem;
  }

  void insert (const_iterator pos, std::unique_ptr<T> elem)
  {
    T *ptr = elem.release ();
    base::insert (pos, *ptr);
  }

  iterator erase (const_iterator i)
  {
    auto &elem = *i;
    iterator ret = base::erase (i);
    delete &elem;
    return ret;
  }

  void clear ()
  {
    while (!this->empty ())
      pop_front ();
  }
};

#endif
