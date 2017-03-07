#pragma once

#include <memory>

#include <ossia/detail/ptr_container.hpp>
#include <ossia/editor/state/state_element_fwd.hpp>
#include <ossia_export.h>
namespace ossia
{
/**
 * @brief The state class
 *
 * A state is a container of state_element.
 * Only non-null children will be added to the state.
 *
 * Launching the state launches all children.
 *
 * \see \ref state_element
 */
class OSSIA_EXPORT state
{
public:
  OSSIA_EXPORT friend bool operator==(const state& lhs, const state& rhs);
  OSSIA_EXPORT friend bool operator!=(const state& lhs, const state& rhs);

  auto begin()
  {
    return mChildren.begin();
  }
  auto end()
  {
    return mChildren.end();
  }
  auto begin() const
  {
    return mChildren.begin();
  }
  auto end() const
  {
    return mChildren.end();
  }
  auto cbegin() const
  {
    return mChildren.cbegin();
  }
  auto cend() const
  {
    return mChildren.cend();
  }

  auto& children() const
  {
    return mChildren;
  }

  std::size_t size() const;
  bool empty() const;

  void launch() const;

  void add(const state_element& e);
  void add(state_element&& e);

  template <class Optional_T>
  auto add(Optional_T&& opt) -> decltype(
      std::declval<typename std::remove_reference_t<Optional_T>::value_type>(),
      void())
  {
    if (opt)
      add(*std::forward<Optional_T>(opt));
  }

  void remove(const state_element& e);

  void reserve(std::size_t);
  void clear();

private:
  std::vector<state_element> mChildren;
};

inline auto begin(state& s)
{
  return s.begin();
}
inline auto begin(const state& s)
{
  return s.begin();
}
inline auto end(state& s)
{
  return s.end();
}
inline auto end(const state& s)
{
  return s.end();
}

/*! append each message of the state to the current state in order to eliminate
 address redundancy
 \param std::shared_ptr<State> the State to fill
 \param std::shared_ptr<StateElement> the StateElement to store */
OSSIA_EXPORT void flatten_and_filter(state&, const state_element& element);
OSSIA_EXPORT void flatten_and_filter(state&, state_element&& element);
}
