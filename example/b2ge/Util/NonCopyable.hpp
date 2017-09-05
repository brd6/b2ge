//
// Created by brd6 on 03/02/17.
//

#ifndef _NONCOPYABLE_H_
# define _NONCOPYABLE_H_

namespace b2ge
{
  template<typename T>
  class NonCopyable
  {
   protected:
    NonCopyable() = default;

    virtual ~NonCopyable() = default;

   private:
    NonCopyable(NonCopyable const &) = delete;

    NonCopyable &operator=(NonCopyable const &) = delete;
  };
}

#endif /* !_NONCOPYABLE_H_ */