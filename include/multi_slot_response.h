#pragma once

#include <cstddef>
#include <iterator>
#include <vector>

#include "ranking_response.h"

namespace reinforcement_learning {
  class api_status;

  /**
   * @brief Holds (action_id, probability) that tells which action was choosen for the given slot.
   */
  struct slot_entry {
  public:
    ~slot_entry() = default;

    slot_entry(uint32_t _action_id, float _probability);

    uint32_t get_action_id() const;
    float get_probability() const;
  private:
    //! action id
    uint32_t action_id;
    //! probability associated with the action id
    float probability;
  };

  /**
   * @brief request_multi_slot_decision returns the per-slot action choice using multi_slot_response.
   */
  class multi_slot_response {
  private:
    using coll_t = std::vector<slot_entry>;

    std::string _event_id;
    std::string _model_id;
    coll_t _decision;

  public:
    using iterator_t = container_iterator<slot_entry, coll_t>;
    using const_iterator_t = const_container_iterator<slot_entry, coll_t>;

    multi_slot_response() = default;
    ~multi_slot_response() = default;

    // push_back calls must be done in slot order
    void push_back(uint32_t action_id, float prob);

    size_t size() const;

    void set_event_id(const char* event_id);
    void set_event_id(std::string&& event_id);
    const char* get_event_id() const;

    void set_model_id(const char* model_id);
    void set_model_id(std::string&& model_id);
    const char* get_model_id() const;

    void clear();
    const_iterator_t begin() const;
    iterator_t begin();
    const_iterator_t end() const;
    iterator_t end();

    multi_slot_response(multi_slot_response&&) noexcept;
    multi_slot_response& operator=(multi_slot_response&&) noexcept;
    multi_slot_response(const multi_slot_response&) = default;
    multi_slot_response& operator =(const multi_slot_response&) = default;
  };
}
